/**
 * \file pmp.c
 * \brief callback Poulo Media Player functions
 * \author Diallo Alpha Oumar Binta
 * \version 0.1
 * \date 23 octobre 2014
 *.
 *
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <gst/gst.h> 
#include <glib.h>
#include <gtk/gtk.h>
#include "pmp.h"

 /**
 * \fn  void cb_play_stream (GtkButton *button, StreamData *data)
 * \brief function called when the PLAY button is clicked.
 *
 * \param button GtkButton.
 * \param data StreamData.
 */
 void cb_play_stream (GtkButton *button, StreamData *data)
{
  gst_element_set_state (data->pipeline, GST_STATE_PLAYING);

  (void)button;
}
/**
 * \fn  void cb_pause_stream (GtkButton *button, StreamData *data)
 * \brief function called when the PAUSE button is clicked.
 *
 * \param button GtkButton.
 * \param data StreamData.
 */
 void cb_pause_stream (GtkButton *button, StreamData *data)
{
  gst_element_set_state (data->pipeline, GST_STATE_PAUSED);

  (void)button;
}
/**
 * \fn  void cb_stop_stream (GtkButton *button, StreamData *data)
 * \brief function called when the STOP button is clicked.
 *
 * \param button GtkButton.
 * \param data StreamData.
 */
 void cb_stop_stream (GtkButton *button, StreamData *data)
{
  gst_element_set_state (data->pipeline, GST_STATE_READY);

  (void)button;
}
/**
 * \fn  void cb_en_dis_subtitles (GtkButton *button, StreamData *data)
 * \brief function called when the (enable subtitles or disable subtitles) button is clicked.
 *
 * \param button GtkButton.
 * \param data StreamData.
 */
 void cb_en_dis_subtitles (GtkButton *button, StreamData *data)
{
  data->toggleSubtitle = (data->toggleSubtitle) ? FALSE : TRUE;
  char* label = (data->toggleSubtitle) ? "disable subtitles" : "enable subtitles";
  g_object_set (G_OBJECT (data->subOverlay), "silent", !data->toggleSubtitle, NULL);
  gtk_button_set_label(button, label);
}
/**
 * \fn  void cb_delete_event (GtkWidget *widget, GdkEvent *event, StreamData *data)
 * \brief function called when the main window is closed.
 *
 * \param widget GtkWidget.
 * \param event GdkEvent.
 * \param data StreamData.
 */
 void cb_delete_event (GtkWidget *widget, GdkEvent *event, StreamData *data)
{
  (void)widget;
  (void)event;

  gst_element_set_state (data->pipeline, GST_STATE_READY);
  gtk_main_quit ();
}
/**
 * \fn  void cb_quit (GtkWidget *p_widget, StreamData *user_data)
 * \brief function called when the main window is closed.
 *
 * \param widget GtkWidget.
 * \param data StreamData.
 */
void cb_quit (GtkWidget *p_widget, StreamData *data)
{
  gst_element_set_state (data->pipeline, GST_STATE_READY);
  gtk_main_quit();
  (void)p_widget;
}
void cb_about(GtkWidget* widget, gpointer data)
{
  GtkWidget *pAbout;
    (void)widget;

    pAbout = gtk_message_dialog_new(GTK_WINDOW(data),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_INFO,
        GTK_BUTTONS_OK,
        "POULO MEDIA PALYER\n"
        "DM2");
 
    gtk_dialog_run(GTK_DIALOG(pAbout));
    gtk_widget_destroy(pAbout);
}
/**
 * \fn  void cb_slider_position (GtkRange *range, StreamData *data)
 * \brief function called when the slider changes its position.
 *
 * \param range GtkRange.
 * \param data StreamData.
 */
 void cb_slider_position (GtkRange *range, StreamData *data)
{
  gst_element_seek_simple (data->pipeline, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH 
    | GST_SEEK_FLAG_KEY_UNIT,
     (gint64)(gtk_range_get_value (GTK_RANGE (data->slider)) * GST_SECOND));

  (void)range;
}
/**
 * \fn  void cb_bus_error_msg (GstBus *bus, GstMessage *msg, StreamData *data)
 * \brief function called when an error message is posted on the bus.
 *
 * \param bus GstBus.
 * \param msg GstMessage.
 * \param user_data gpointer.
 */
 void cb_bus_error_msg (GstBus *bus, GstMessage *msg, StreamData *data)
{
    GError *err;
    gchar *debug_info;

    gst_message_parse_error (msg, &err, &debug_info);
    g_printerr ("P.M.P >> Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
    g_printerr ("P.M.P >> Debugging information: %s\n", debug_info ? debug_info : "none");
    g_clear_error (&err);
    g_free (debug_info);

    gst_element_set_state (data->pipeline, GST_STATE_READY);

    (void)bus;
}
/**
 * \fn  void cb_bus_eos_msg (GstBus *bus, GstMessage *msg, StreamData *data)
 * \brief function called when an End-Of-Stream message is posted on the bus.
 *
 * \param bus GstBus.
 * \param msg GstMessage.
 * \param user_data gpointer.
 */
 void cb_bus_eos_msg (GstBus *bus, GstMessage *msg, StreamData *data)
{
  g_print ("P.M.P >> end-of-stream reached.\n");
  /* setting the pipeline to READY to stops playback */
  gst_element_set_state (data->pipeline, GST_STATE_READY);

  (void)bus;
  (void)msg;
}
/**
 * \fn  void cb_pad_added (GstElement *element, GstPad *pad, gpointer data)
 * \brief link this pad with the decoder sink pad, create a dynamic pad.
 *
 * \param element GstElement.
 * \param pad GstPad.
 * \param data gpointer.
 */
 void cb_pad_added (GstElement *element, GstPad *pad, gpointer data)
{
    GstPad *sinkpad;
    GstElement *decoder = (GstElement *) data;
    sinkpad = gst_element_get_static_pad (decoder, "sink");
    gst_pad_link (pad, sinkpad);
    gst_object_unref (sinkpad);

    (void)element;
}
