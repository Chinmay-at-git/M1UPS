#include <gst/gst.h> 
#include <glib.h>
#include <stdbool.h>
#include <string.h>
#include "tag.h"

static char *getExt (char *fspec) {//retourne l'adresse du caractère recherché, ici =
    char *e = strchr (fspec, '=');
    if (e == NULL)
        e = "";
    return e;
}

//lecture des message sur le pipeline
static gboolean bus_call (GstBus     *bus,
                          GstMessage *msg,
                          gpointer    data)
{
  GMainLoop *loop = (GMainLoop *) data;

  switch (GST_MESSAGE_TYPE (msg)) {

   case GST_MESSAGE_EOS://fin de lecture
      g_print ("End of stream\n");
      g_main_loop_quit (loop);
      break;
    case GST_MESSAGE_ERROR: {//message d'erreur on ferme la fenêtre
      gchar  *debug;
      GError *error;
 
      gst_message_parse_error (msg, &error, &debug);
      g_free (debug);

      g_printerr ("Error: %s\n", error->message);
      g_error_free (error);

      g_main_loop_quit (loop);
      break;
    }
    default:
      break;
  }
  return TRUE;
}

static void
on_pad_added (GstElement *element,
              GstPad     *pad,
              gpointer    data)
{
  GstPad *sinkpad;
  GstElement *decoder = (GstElement *) data;

  /* We can now link this pad with the decoder sink pad */
  g_print ("Dynamic pad created, linking demuxer/decoder\n");

  sinkpad = gst_element_get_static_pad (decoder, "sink");
 
  gst_pad_link (pad, sinkpad);
  gst_object_unref (sinkpad);
}

int mp3 (int   argc,
          char *argv[])
{
  GMainLoop *loop;

  GstElement *pipeline, *source, *decoder, *conv, *volume, *sink;
  GstBus *bus;

  /* Initialisation */
  gst_init (&argc, &argv);
double vol=1;

int  i;
//gestion des éléments arg[i] initialisation des options
for(i=1;i<argc;i++){
	if(strstr (argv[i], "volume")!=NULL){
vol=(double)atof(getExt(argv[i])+1);
         }
else if(strstr (argv[i], "info")!=NULL){
tag(argc,argv);
         }
else if(strstr (argv[i], "options")!=NULL){
printf("volume=[0.0-10.0]\n");
         }

}

 loop = g_main_loop_new (NULL, FALSE);

  /* Verification des arguments d'entree */
  if (argc < 2) {
    g_printerr ("Usage: %s <Ogg/Vorbis filename>\n", argv[0]);
    return -1;
  }

  /* Creation des elements gstreamer */
  pipeline = gst_pipeline_new ("audio-player");
  source   = gst_element_factory_make ("filesrc",       "file-source");
  decoder  = gst_element_factory_make ("mad",     "mp3-decoder");
  conv     = gst_element_factory_make ("audioconvert",  "converter");
  sink     = gst_element_factory_make ("autoaudiosink", "audio-output");
  volume     = gst_element_factory_make ("volume", "option1");

  if (!pipeline || !volume || !source || !decoder || !conv || !sink) {
    g_printerr ("One element could not be created. Exiting.\n");
    return -1;
  }

  /* Mise en place du pipeline */
  /* on configurer le nom du fichier a l'element source */
//configuration des valeurs des éléments options
  g_object_set (G_OBJECT (source), "location", argv[1], NULL);
  g_object_set(G_OBJECT(volume), "volume",vol, NULL);

  /* on rajoute une gestion de messages */
  bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
  gst_bus_add_watch (bus, bus_call, loop);
  gst_object_unref (bus);

  /* on rajoute tous les elements dans le pipeline */
  gst_bin_add_many (GST_BIN (pipeline),
                    source, decoder, conv, volume , sink, NULL);

  /* On relie les elements entre eux */
  //gst_element_link (source, demuxer);
  gst_element_link_many (source, decoder, conv, volume , sink, NULL);
  //g_signal_connect (decoder, "pad-added", G_CALLBACK (on_pad_added), decoder);



  /* passage a l'etat "playing" du pipeline */
  g_print ("Lecture de : %s\n", argv[1]);
  gst_element_set_state (pipeline, GST_STATE_PLAYING);

  /* Iteration */
  g_print ("En cours...\n");
  g_main_loop_run (loop);

  /* En dehors de la boucle principale, on nettoie proprement */
  g_print ("Arret de la lecture\n");
  gst_element_set_state (pipeline, GST_STATE_NULL);
  g_print ("Suppression du pipeline\n");
  gst_object_unref (GST_OBJECT (pipeline));
  return 0;
} 
