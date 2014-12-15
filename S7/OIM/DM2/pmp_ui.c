/**
 * \file pmp_ui.c
 * \brief UI Poulo Media Player functions
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
#include <gst/interfaces/xoverlay.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include "pmp.h"

static gulong video_window_xid = 0; /*!< video vindow id for X interface to set the stream container. */
/**
 * \fn  void pmp_create_gtk_ui (StreamData *data)
 * \brief function called to create GTK+ user interface, its creates all the 
 * GTK+ widgets that compose our application, and registers the callbacks.
 *
 * \param data StreamData.
 */
 void pmp_create_gtk_ui (StreamData *data)
{
  GtkWidget *pmp_main_window;
  GtkWidget *pmp_video_window;
  GtkWidget *main_vbox;
  GtkWidget *main_hbox;
  GtkWidget *controls_box;
  GtkWidget *play_button, *pause_button, *stop_button, *en_dis_subtitle_button;

  GtkWidget *p_MenuBar = NULL;
  GtkWidget *p_Menu = NULL;
  GtkWidget *p_MenuItem = NULL;
   
  pmp_main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_signal_connect (G_OBJECT (pmp_main_window), "delete-event", G_CALLBACK (cb_delete_event), data);
   
  pmp_video_window = gtk_drawing_area_new ();
  g_signal_connect (pmp_video_window, "realize", G_CALLBACK (cb_video_widget_realize), NULL);
  gtk_widget_set_double_buffered (pmp_video_window, FALSE);
  
  p_MenuBar = gtk_menu_bar_new();
  p_Menu = gtk_menu_new();

  p_MenuItem = gtk_image_menu_item_new_from_stock(GTK_STOCK_MEDIA_PLAY, NULL);
  g_signal_connect (G_OBJECT (p_MenuItem), "activate", G_CALLBACK (cb_play_stream), (StreamData*) data);
  gtk_menu_shell_append(GTK_MENU_SHELL(p_Menu), p_MenuItem);

  p_MenuItem = gtk_image_menu_item_new_from_stock(GTK_STOCK_MEDIA_PAUSE, NULL);
  g_signal_connect (G_OBJECT (p_MenuItem), "activate", G_CALLBACK (cb_pause_stream), (StreamData*) data);
  gtk_menu_shell_append(GTK_MENU_SHELL(p_Menu), p_MenuItem);

  p_MenuItem = gtk_image_menu_item_new_from_stock(GTK_STOCK_MEDIA_STOP, NULL);
  g_signal_connect (G_OBJECT (p_MenuItem), "activate", G_CALLBACK (cb_stop_stream), (StreamData*) data);
  gtk_menu_shell_append(GTK_MENU_SHELL(p_Menu), p_MenuItem);

  p_MenuItem = gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT, NULL);
  g_signal_connect (G_OBJECT (p_MenuItem), "activate", G_CALLBACK (cb_quit), (StreamData*) data);
  gtk_menu_shell_append(GTK_MENU_SHELL(p_Menu), p_MenuItem);

  p_MenuItem = gtk_menu_item_new_with_label("Fichier");
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(p_MenuItem), p_Menu);
  gtk_menu_shell_append(GTK_MENU_SHELL(p_MenuBar), p_MenuItem);

  p_Menu = gtk_menu_new();

  p_MenuItem = gtk_menu_item_new_with_label("A propos");
  g_signal_connect(G_OBJECT(p_MenuItem), "activate", G_CALLBACK(cb_about), (GtkWidget*) pmp_main_window);
  gtk_menu_shell_append(GTK_MENU_SHELL(p_Menu), p_MenuItem);

  p_MenuItem = gtk_menu_item_new_with_label("?");
  gtk_menu_item_set_submenu(GTK_MENU_ITEM(p_MenuItem), p_Menu);
  gtk_menu_shell_append(GTK_MENU_SHELL(p_MenuBar), p_MenuItem);

  play_button = gtk_button_new_from_stock(GTK_STOCK_MEDIA_PLAY);
  g_signal_connect (G_OBJECT (play_button), "clicked", G_CALLBACK (cb_play_stream), data);
   
  pause_button = gtk_button_new_from_stock(GTK_STOCK_MEDIA_PAUSE);
  g_signal_connect (G_OBJECT (pause_button), "clicked", G_CALLBACK (cb_pause_stream), data);
   
  stop_button = gtk_button_new_from_stock(GTK_STOCK_MEDIA_STOP);
  g_signal_connect (G_OBJECT (stop_button), "clicked", G_CALLBACK (cb_stop_stream), data);

  if (data->toggleSubtitle)
  {
    en_dis_subtitle_button = gtk_button_new_with_label ("disable subtitles");
    g_signal_connect (G_OBJECT (en_dis_subtitle_button), "clicked", G_CALLBACK (cb_en_dis_subtitles), data);
  }
   
  data->slider = gtk_hscale_new_with_range (0, 100, 1);
  gtk_scale_set_draw_value (GTK_SCALE (data->slider), 0);
  data->sliderSignalId = g_signal_connect (G_OBJECT (data->slider), "value-changed", G_CALLBACK (cb_slider_position), data);

  controls_box = gtk_hbox_new (FALSE, 0);
  gtk_box_pack_start (GTK_BOX (controls_box), play_button, FALSE, FALSE, 2);
  gtk_box_pack_start (GTK_BOX (controls_box), pause_button, FALSE, FALSE, 2);
  gtk_box_pack_start (GTK_BOX (controls_box), stop_button, FALSE, FALSE, 2);
  
  if (data->toggleSubtitle)
  {
    gtk_box_pack_start (GTK_BOX (controls_box), en_dis_subtitle_button, FALSE, FALSE, 2);
  }
  
  gtk_box_pack_start (GTK_BOX (controls_box), data->slider, TRUE, TRUE, 2);
   
  main_hbox = gtk_hbox_new (FALSE, 0);
  gtk_box_pack_start (GTK_BOX (main_hbox), pmp_video_window, TRUE, TRUE, 0);
   
  main_vbox = gtk_vbox_new (FALSE, 0);

  gtk_box_pack_start (GTK_BOX (main_vbox), p_MenuBar, FALSE, FALSE, 2);
  gtk_box_pack_start (GTK_BOX (main_vbox), main_hbox, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (main_vbox), controls_box, FALSE, FALSE, 0);
  gtk_container_add (GTK_CONTAINER (pmp_main_window), main_vbox);
  gtk_window_set_default_size (GTK_WINDOW (pmp_main_window), 640, 480);
  gtk_window_set_title (GTK_WINDOW (pmp_main_window), "Poulo Media Player");
   
  gtk_widget_show_all (pmp_main_window);
  /* realize window now so that the video window gets created and we can
     obtain its XID before the pipeline is started up and the videoSink
    asks for the XID of the window to render onto*/
    gtk_widget_realize (pmp_video_window);

   /* we should have the XID now */
  g_assert (video_window_xid != 0);
}
/**
 * \fn  void cb_video_widget_realize (GtkWidget * widget, gpointer data)
 * \brief function called when the GUI toolkit creates the physical window 
 * that will hold the video. At this point we can retrieve its handler (which 
 * has a different meaning depending on the windowing system) and pass it to 
 * GStreamer through the XOverlay interface.
 *
 * \param widget GtkWidget.
 * \param user_data gpointer.
 */
 void cb_video_widget_realize (GtkWidget * widget, gpointer data)
{
    GdkWindow *window = gtk_widget_get_window (widget);
    if (!gdk_window_ensure_native (window))
        g_error ("P.M.P >> Couldn't create native window needed for GstXOverlay!");
    video_window_xid = GDK_WINDOW_XID (window);

    (void)data;
}
/**
 * \fn  gboolean pmp_refresh_gtk_ui (StreamData *data)
 * \brief function called to refresh the GUI.
 *
 * \param data StreamData.
 * \return TRUE if the ui is refreshed else FALSE.
 */
 gboolean pmp_refresh_gtk_ui (StreamData *data)
{
    GstFormat fmt = GST_FORMAT_TIME;
    gint64 current = -1;

    if (!GST_CLOCK_TIME_IS_VALID (data->duration)) {
        if (!gst_element_query_duration (data->pipeline, &fmt, &data->duration)) {
            g_printerr ("P.M.P >> Could not query current duration.\n");
        } else {
            gtk_range_set_range (GTK_RANGE (data->slider), 0, (gdouble)data->duration / GST_SECOND);
        }
    }

    if (gst_element_query_position (data->pipeline, &fmt, &current)) {
        g_signal_handler_block (data->slider, data->sliderSignalId);
        gtk_range_set_value (GTK_RANGE (data->slider), (gdouble)current / GST_SECOND);
        g_signal_handler_unblock (data->slider, data->sliderSignalId);
    }

    return TRUE;
}
/**
 * \fn  GstBusSyncReply bus_sync_handler (GstBus * bus, GstMessage * message, gpointer user_data)
 * \brief set the window handler to contain the video stream.
 *
 * \param bus GstBus.
 * \param message GstMessage.
 * \param user_data gpointer.
 */
 GstBusSyncReply bus_sync_handler (GstBus * bus, GstMessage * message, gpointer user_data)
{
    if (GST_MESSAGE_TYPE (message) != GST_MESSAGE_ELEMENT)
        return GST_BUS_PASS;
    if (!gst_structure_has_name (message->structure, "prepare-xwindow-id"))
        return GST_BUS_PASS;
    if (video_window_xid != 0) {
        GstXOverlay *xoverlay;
        /* GST_MESSAGE_SRC (message) is the video sink element */
        xoverlay = GST_X_OVERLAY (GST_MESSAGE_SRC (message));
        gst_x_overlay_set_window_handle (xoverlay, video_window_xid);
    } else {
        g_warning ("P.M.P >> Should have obtained video_window_xid by now!");
    }
    gst_message_unref (message);

    (void)bus;
    (void)user_data;
    return GST_BUS_DROP;
}