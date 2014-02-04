#include <gst/gst.h>
static GMainLoop *loop;//permet de lire les messages
char* tp;//valeur de retour du type de flux en entrée

//Lecture des messages
static gboolean my_bus_callback (GstBus *bus, GstMessage *message, gpointer data)
{
//g_print ("Got %s message\n", GST_MESSAGE_TYPE_NAME (message));
switch (GST_MESSAGE_TYPE (message)) {

case GST_MESSAGE_ERROR: {
GError *err;
gchar *debug;
gst_message_parse_error (message, &err, &debug);
g_print ("Error: %s\n", err->message);
g_error_free (err);
g_free (debug);
g_main_loop_quit (loop);//si erreur on quitte
break;
}
case GST_MESSAGE_EOS:
/* end-of-stream */
g_main_loop_quit (loop);//si fin on quitte
break;
default:

break;
}

return TRUE;
}

static gboolean idle_exit_loop (gpointer data)
{
g_main_loop_quit ((GMainLoop *) data);
/* once */
return FALSE;
}

//recherche du type de flux
static void cb_typefound (GstElement *typefind, guint probability, GstCaps *caps, gpointer data)
{
GMainLoop *loop = data;
char *type;
tp = gst_caps_to_string (caps);
//printf ("Media type %s found, probability %d%%\n", tp, probability);
//g_free (type);
/* since we connect to a signal in the pipeline thread context, we need
* to set an idle handler to exit the main loop in the mainloop context.
* Normally, your app should not need to worry about such things. */
g_idle_add (idle_exit_loop, loop);
}

char* flux (int argc, char *argv[]){
GMainLoop *loop;
GstElement *pipeline, *filesrc, *typefind, *fakesink;
GstBus *bus;
/* init GStreamer */
gst_init (&argc, &argv);
loop = g_main_loop_new (NULL, FALSE);
/* check args */
if (argc < 2) {
printf ("Usage: %s <filename>\n", argv[0]);
return tp;
}
/* creation du pipeline */
pipeline = gst_pipeline_new ("pipe");
bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));

  /* on rajoute une gestion de messages */
gst_bus_add_watch (bus, my_bus_callback, NULL);
gst_object_unref (bus);

/* Creation des elements gstreamer et configuration*/
filesrc = gst_element_factory_make ("filesrc", "source");
g_object_set (G_OBJECT (filesrc), "location", argv[1], NULL);
typefind = gst_element_factory_make ("typefind", "typefinder");//l'élément essentiel permettant l'identification du type de flux
g_signal_connect (typefind, "have-type", G_CALLBACK (cb_typefound), loop);
fakesink = gst_element_factory_make ("fakesink", "sink");
/* on rajoute tous les elements dans le pipeline */
gst_bin_add_many (GST_BIN (pipeline), filesrc, typefind, fakesink, NULL);
gst_element_link_many (filesrc, typefind, fakesink, NULL);
gst_element_set_state (GST_ELEMENT (pipeline), GST_STATE_PLAYING);
g_main_loop_run (loop);

gst_element_set_state (GST_ELEMENT (pipeline), GST_STATE_NULL);
gst_object_unref (GST_OBJECT (pipeline));
//printf ("Media type %s found\n", tp);
return tp; //on retourne le type de flux (char*)
}

