/**
 * \file main.c
 * \brief Poulo Media Player application.
 * \author Diallo Alpha Oumar Binta
 * \version 0.1
 * \date 23 octobre 2014
 *
 * Main programm to launch the Poulo Media player.
 *
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gst/gst.h> 
#include <glib.h>
#include <gtk/gtk.h>
#include <gst/interfaces/xoverlay.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include "pmp.h"

/**
 * \fn  int create_stream_data_elements(StreamData * data, int argc, char **argv)
 * \brief function called to create all elements needs to play the stream.
 *
 * \param data StreamData.
 * \param argc int.
 * \param argv char.

 * \return EXIT_SUCCESS if SUCCESS else -1.
 */
 int create_stream_data_elements(StreamData * data, int argc, char **argv)
 {
     data->duration = GST_CLOCK_TIME_NONE;
     data->pipeline     = gst_pipeline_new ("P.M.P :: Poulo Media Player");
     data->videoSrc     = gst_element_factory_make ("filesrc", "file-source");
     data->subSource    = gst_element_factory_make ("filesrc", "subtitle-source");
     data->demuxer      = gst_element_factory_make ("decodebin", "bin-decoder");
     data->audioQueue   = gst_element_factory_make ("queue", "audio-queue");
     data->videoQueue   = gst_element_factory_make ("queue", "video-queue");
     data->audioConv    = gst_element_factory_make ("audioconvert", "audio-converter");
     data->videoConv    = gst_element_factory_make ("ffmpegcolorspace", "video-converter");
     data->videoSink    = gst_element_factory_make ("autovideosink", "video-output");
     data->audioSink    = gst_element_factory_make ("autoaudiosink", "audio-output");
     data->subOverlay   = gst_element_factory_make ("subtitleoverlay", "subtitle");
     data->subParse     = gst_element_factory_make ("subparse", "parse");

     if (!data->pipeline || !data->videoSrc || !data->demuxer || !data->audioConv
      || !data->videoConv || !data->audioQueue || !data->videoQueue 
      || !data->audioSink || !data->videoSink || !data->subParse 
      || !data->subOverlay) {
       g_printerr ("P.M.P >> One element could not be created. Exiting.\n");
       return -1;
     }

     gst_bin_add_many (GST_BIN (data->pipeline), data->videoSrc, data->demuxer, 
         data->audioQueue, data->videoQueue, data->videoConv, data->audioConv, 
         data->videoSink, data->audioSink, NULL);

     gst_element_link (data->videoSrc, data->demuxer);
     gst_element_link_many (data->audioQueue, data->audioConv, data->audioSink, NULL);

     if (argc > 2){
         /* subtiles are set in params */
         data->toggleSubtitle = TRUE;
         gst_bin_add_many (GST_BIN (data->pipeline), data->subParse, data->subSource, data->subOverlay, NULL);
         /* subtiles file source */
         g_object_set (G_OBJECT (data->subSource), "location", argv[2], NULL);
         gst_element_link (data->subSource, data->subParse);
         if(!gst_element_link_pads(data->subParse, NULL, data->subOverlay, NULL)) {
             g_printerr("P.M.P >> Pads couldn't be linked, subparse subOverlay\n");
             return -1;
         }
         gst_element_link_many (data->videoQueue, data->videoConv, data->subOverlay, data->videoSink, NULL);
     }else{
         /* no need to add subOverlay to the sink */
         gst_element_link_many (data->videoQueue, data->videoConv, data->videoSink, NULL);
     }
     g_signal_connect (data->demuxer, "pad-added", G_CALLBACK (cb_pad_added), data->videoQueue);
     g_signal_connect (data->demuxer, "pad-added", G_CALLBACK (cb_pad_added), data->audioQueue);
     /* stream source file */
     g_object_set (G_OBJECT (data->videoSrc), "location", argv[1], NULL);

     return EXIT_SUCCESS;
 }

int main (int argc, char **argv)
{
    StreamData data;
    GstStateChangeReturn ret;
    GstBus *bus;

    gtk_init (&argc, &argv);
    gst_init (&argc, &argv);

    if (argc < 2 || argc > 3) {
      g_printerr ("Usage: %s <Ogg/Vorbis filename> [srt filename]\n", argv[0]);
      return -1;
    }

    /* Intialzing struct data */
    memset (&data, 0, sizeof (data));
    /* Initialize our data structure and ui*/
    if (create_stream_data_elements(&data, argc, argv))
    {
        g_printerr ("P.M.P >> Unable to set stream data\n");
        return -1;
    }
    pmp_create_gtk_ui(&data);

    /* bus signal watcher */
    bus = gst_pipeline_get_bus (GST_PIPELINE (data.pipeline));
    gst_bus_set_sync_handler (bus, (GstBusSyncHandler) bus_sync_handler, NULL);
    gst_bus_add_signal_watch (bus);
    g_signal_connect (G_OBJECT (bus), "message::error", (GCallback)cb_bus_error_msg, &data);
    g_signal_connect (G_OBJECT (bus), "message::eos", (GCallback)cb_bus_eos_msg, &data);
    gst_object_unref (bus);

    ret = gst_element_set_state (data.pipeline, GST_STATE_PLAYING);
    if (ret == GST_STATE_CHANGE_FAILURE) {
      g_printerr ("P.M.P >> Unable to set the pipeline to the playing state.\n");
      gst_object_unref (data.pipeline);
      return -1;
    }else if (argc > 2)
    {
        g_print ("P.M.P >> Playing video\t%s\n\t\t\t%s\n", argv[1], argv[2]);
    }else{
        g_print ("P.M.P >> Playing video\t%s\n", argv[1]);
    }

    g_timeout_add_seconds (1, (GSourceFunc)pmp_refresh_gtk_ui, &data);
    g_print ("P.M.P >> Running...\n");
    gtk_main ();
    g_print ("P.M.P >> Cleaning...\n");
    gst_element_set_state (data.pipeline, GST_STATE_NULL);
    gst_object_unref (data.pipeline);
    g_print ("P.M.P >> terminated\n");

    return EXIT_SUCCESS;
}
