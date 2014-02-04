#include <gst/gst.h> 
#include <glib.h>
#include <stdbool.h>
#include <string.h>
#include "tag.h"

static int cpt=0;//compteur d'avancement, sert à utiliser seek_simple une seule fois lors du message "TRYPE_ENTER"
static int search=0;//variable valeur de l'endroi de démarrage de la vidéo (initialement au début donc à 0)
static GMainLoop *loop;//permet la lecture des messages


static char *getExt (char *fspec) { //retourne l'adresse du caractère recherché, ici =
    char *e = strchr (fspec, '=');
    if (e == NULL)
        e = "";
    return e;
}



static gboolean bus_call(GstBus *bus, GstMessage *message, gpointer data) //lecture des message sur le pipeline
{
    GstElement *play = GST_ELEMENT(data);;

switch (GST_MESSAGE_TYPE (message)) {



case GST_MESSAGE_ERROR: //message d'erreur on ferme la fenêtre
g_print("fenetre fermé\n");
     g_main_loop_quit (loop);
      break;

case GST_MESSAGE_EOS://fin de lecture


            if (!gst_element_seek(play, //permet de revenir en debut de lecture
                        1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH,
                        GST_SEEK_TYPE_SET, 0,//point de lecture 0
                        GST_SEEK_TYPE_NONE, GST_CLOCK_TIME_NONE)) {
                //g_print("Seek failed!\n");
            }else{/*g_print("Seek succeed!\n");*/}
            break;
    case GST_MESSAGE_STREAM_STATUS://changement de status
    {
      GstStreamStatusType type;
      GstElement *owner;
      const GValue *val;
      gchar *path;
      GstTask *task = NULL;

     // g_message ("received STREAM_STATUS");
      gst_message_parse_stream_status (message, &type, &owner);
//g_message ("type:   %d", type);

      

      switch (type) {
        case GST_STREAM_STATUS_TYPE_ENTER://entrée en lecture
//printf("fer%d\n",cpt);
if(cpt==0){
//printf("fer%d\n",cpt);
          if (!gst_element_seek_simple(play, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH,search*1e9)) {//aller au point de lecture "search*1e9", 1e9 pour convertir en seconde
                //g_print("Seek failed!\n");
            }else {cpt++;}
}
          break;
       
        default:
//g_print("Seek fad!\n");
          break;
      }
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


int avi (int   argc,
          char *argv[])
{

  GstElement *pipeline, *source, *demuxer, *decodera, *decoderv , *conv, *sinka , *sinkv , *queuea, *queuev, *volume, *gamma , *videobalance;
  GstBus *bus;

  /* Initialisation */
  gst_init (&argc, &argv);
double vol=1;
double gam=1.0;
double sat=1;
double cont=1;
double br=0;
bool ascii=false;

//gestion des éléments arg[i] initialisation des options
int  i;
for(i=1;i<argc;i++){
	if(strstr (argv[i], "volume")!=NULL){
//printf ("%s\n",getExt(argv[i])+1);
vol=(double)atof(getExt(argv[i])+1);
//printf ("%f\n",vol);
         }
else if(strstr (argv[i], "gamma")!=NULL){
gam=(double)atof(getExt(argv[i])+1);
         }
else if(strstr (argv[i], "saturation")!=NULL){
sat=(double)atof(getExt(argv[i])+1);
         }
else if(strstr (argv[i], "contrast")!=NULL){
cont=(double)atof(getExt(argv[i])+1);
         }
else if(strstr (argv[i], "brightness")!=NULL){
br=(double)atof(getExt(argv[i])+1);
         }
else if(strstr (argv[i], "ascii")!=NULL){
ascii=true;
         }
else if(strstr (argv[i], "start")!=NULL){
search=(atoi(getExt(argv[i])+1));
//printf ("%d %d\n",search,atoi(getExt(argv[i])+1));
         }
else if(strstr (argv[i], "info")!=NULL){
tag(argc,argv);
         }
else if(strstr (argv[i], "options")!=NULL){
printf("volume=[0.0-10.0]\ngamma=[0.0-10.0]\nsaturation=[0.0-2.0]\ncontrast=[0.0-2.0]\nbrightness=[-1.0-1.0]\n");
         }
}


 loop = g_main_loop_new (NULL, FALSE);

  /* Verification des arguments d'entree */
  if (argc < 2) {
    g_printerr ("Usage: %s <avi filename>\n", argv[3]);
    return -1;
  }

  /* Creation des elements gstreamer */
  pipeline = gst_pipeline_new ("video-player");
  source   = gst_element_factory_make ("filesrc",       "file-source");
  demuxer  = gst_element_factory_make ("avidemux",      "ogg-demuxer");
  queuea  = gst_element_factory_make ("queue",      "queue-audio");
  queuev  = gst_element_factory_make ("queue",      "queue-video");
  decodera  = gst_element_factory_make ("mad",     "vorbis-decoder");
  decoderv  = gst_element_factory_make ("xviddec",     "theora-decoder");
  conv     = gst_element_factory_make ("audioconvert",  "converter");
  sinka     = gst_element_factory_make ("autoaudiosink", "audio-output");
  if(!ascii) sinkv     = gst_element_factory_make ("xvimagesink", "video-output");
else sinkv     = gst_element_factory_make ("aasink", "video-output");
  volume     = gst_element_factory_make ("volume", "option1");
  gamma     = gst_element_factory_make ("gamma", "option2");
  videobalance     = gst_element_factory_make ("videobalance", "option3");

  

  if (!pipeline || !source || !demuxer || !queuea || !queuev || !videobalance || !gamma || !volume || !decodera || !decoderv || !conv || !sinka || !sinkv) {
    g_printerr ("One element could not be created. Exiting.\n");
    return -1;
  }


  /* Mise en place du pipeline */
  /* on configurer le nom du fichier a l'element source */
//configuration des valeurs des éléments options
  g_object_set (G_OBJECT (source), "location", argv[1], NULL);
  g_object_set(G_OBJECT(volume), "volume",vol, NULL);
  g_object_set(G_OBJECT(gamma), "gamma",gam, NULL);
  g_object_set(G_OBJECT(videobalance), "saturation",sat, NULL);
  g_object_set(G_OBJECT(videobalance), "contrast",cont, NULL);
  g_object_set(G_OBJECT(videobalance), "brightness",br, NULL);

//printf("source: %s",argv[1]);
;

  /* on rajoute une gestion de messages */
  bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
  gst_bus_add_watch (bus, bus_call, pipeline);//on passe ici en paramètre le pipeline et non loop car on veut pouvoir interagir avec dans bus_call
  gst_object_unref (bus);




  /* on rajoute tous les elements dans le pipeline */
  gst_bin_add_many (GST_BIN (pipeline),
                    source, demuxer , queuea , decodera, conv, volume, sinka, queuev , decoderv, gamma, videobalance, sinkv , NULL);

  /* On relie les elements entre eux */
  gst_element_link (source, demuxer);
  gst_element_link_many (queuev, decoderv, gamma , videobalance , /*conv,*/ sinkv, NULL);
  gst_element_link_many (queuea, decodera , conv, volume, sinka, NULL);
  g_signal_connect (demuxer, "pad-added", G_CALLBACK (on_pad_added), queuea);
  g_signal_connect (demuxer, "pad-added", G_CALLBACK (on_pad_added), queuev);
 


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
