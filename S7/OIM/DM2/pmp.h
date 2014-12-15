#ifndef PMP_H
#define PMP_H

/**
 * \file pmp.h
 * \brief Constant file.
 * \author Diallo Alpha Oumar Binta
 * \version 0.1
 * \date 23 octobre 2014
 *
 * Student : 21007631, 3.1 IHM.
 *
 */

 /**
  * \struct StreamData
  * \brief Object StreamData for playing streams.
  *
  * StreamData is an object containing all the elements necessary for viewing
  * the stream.
  */
  typedef struct{
    GstElement *pipeline, *videoSrc, *subSource, *subParse, *subOverlay, 
        *demuxer, *audioQueue, *videoQueue, *audioConv, *videoConv, 
        *videoSink, *audioSink; /*!< GstElement for playing the stream. */

    gboolean toggleSubtitle; /*!< subtitle checker, TRUE subtitles are set. */

    gint64 duration; /*!< duration of the clip in nanoseconds. */

    gulong sliderSignalId; /*!< Signal ID for the slider update signal. */

    GtkWidget *slider; /*!< Slider widget to keep track of current position. */
  }StreamData;

 /**
 * \fn  void cb_play_stream (GtkButton *button, StreamData *data)
 * \brief function called when the PLAY button is clicked.
 *
 * \param button GtkButton.
 * \param data StreamData.
 */
 void cb_play_stream (GtkButton *button, StreamData *data);
/**
 * \fn  void cb_pause_stream (GtkButton *button, StreamData *data)
 * \brief function called when the PAUSE button is clicked.
 *
 * \param button GtkButton.
 * \param data StreamData.
 */
 void cb_pause_stream (GtkButton *button, StreamData *data);
/**
 * \fn  void cb_stop_stream (GtkButton *button, StreamData *data)
 * \brief function called when the STOP button is clicked.
 *
 * \param button GtkButton.
 * \param data StreamData.
 */
 void cb_stop_stream (GtkButton *button, StreamData *data);
/**
 * \fn  void cb_en_dis_subtitles (GtkButton *button, StreamData *data)
 * \brief function called when the (enable subtitles or disable subtitles) button is clicked.
 *
 * \param button GtkButton.
 * \param data StreamData.
 */
 void cb_en_dis_subtitles (GtkButton *button, StreamData *data);
/**
 * \fn  void cb_delete_event (GtkWidget *widget, GdkEvent *event, StreamData *data)
 * \brief function called when the main window is closed.
 *
 * \param widget GtkWidget.
 * \param event GdkEvent.
 * \param data StreamData.
 */
 void cb_delete_event (GtkWidget *widget, GdkEvent *event, StreamData *data);
/**
 * \fn  void cb_slider_position (GtkRange *range, StreamData *data)
 * \brief function called when the slider changes its position.
 *
 * \param range GtkRange.
 * \param data StreamData.
 */
 void cb_slider_position (GtkRange *range, StreamData *data);
 /**
 * \fn  void cb_quit (GtkWidget *p_widget, StreamData *user_data)
 * \brief function called when the main window is closed.
 *
 * \param widget GtkWidget.
 * \param data StreamData.
 */
 void cb_quit (GtkWidget *p_widget, StreamData *data);
 void cb_about(GtkWidget* widget, gpointer data);
/**
 * \fn  void cb_bus_error_msg (GstBus *bus, GstMessage *msg, StreamData *data)
 * \brief function called when an error message is posted on the bus.
 *
 * \param bus GstBus.
 * \param msg GstMessage.
 * \param user_data gpointer.
 */
 void cb_bus_error_msg (GstBus *bus, GstMessage *msg, StreamData *data);
/**
 * \fn  void cb_bus_eos_msg (GstBus *bus, GstMessage *msg, StreamData *data)
 * \brief function called when an End-Of-Stream message is posted on the bus.
 *
 * \param bus GstBus.
 * \param msg GstMessage.
 * \param user_data gpointer.
 */
 void cb_bus_eos_msg (GstBus *bus, GstMessage *msg, StreamData *data);
/**
 * \fn  void cb_pad_added (GstElement *element, GstPad *pad, gpointer data)
 * \brief link this pad with the decoder sink pad, create a dynamic pad.
 *
 * \param element GstElement.
 * \param pad GstPad.
 * \param data gpointer.
 */
 void cb_pad_added (GstElement *element, GstPad *pad, gpointer data);

/******************************* PMP UI *******************************/
/**
 * \fn  void pmp_create_gtk_ui (StreamData *data)
 * \brief function called to create GTK+ user interface, its creates all the 
 * GTK+ widgets that compose our application, and registers the callbacks.
 *
 * \param data StreamData.
 */
 void pmp_create_gtk_ui (StreamData *data);
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
 void cb_video_widget_realize (GtkWidget * widget, gpointer data);
/**
 * \fn  gboolean pmp_refresh_gtk_ui (StreamData *data)
 * \brief function called to refresh the GUI.
 *
 * \param data StreamData.
 * \return TRUE if the ui is refreshed else FALSE.
 */
 gboolean pmp_refresh_gtk_ui (StreamData *data);
/**
 * \fn  GstBusSyncReply bus_sync_handler (GstBus * bus, GstMessage * message, gpointer user_data)
 * \brief set the window handler to contain the video stream.
 *
 * \param bus GstBus.
 * \param message GstMessage.
 * \param user_data gpointer.
 */
GstBusSyncReply bus_sync_handler (GstBus * bus, GstMessage * message, gpointer user_data);
#endif
