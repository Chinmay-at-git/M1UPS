#include <ncurses.h>
#include <gst/gst.h> 
#include <glib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <sys/wait.h>
#include "constant.h"

/*
    Diallo Alpha Oumar Binta
    21007631
    CC2 OIM
    Groupe 3.1
    Universite Paul Sabatier
    Toulouse III
*/ 

void clean_term(){
    erase();
    refresh();
    endwin();
}

int main (int argc, char *argv[]){
    int nberRadio, i, j, k, totalRadio;
    /*the selected radio and the old_radio_selected for border */
    int radio_selected, old_radio_selected;
    /* keypad direction */
    int dir;
    /*key pressed*/
    int ch;
    GstElement *pipeline, *source_audio;
    GstElement *mixer,*clrspace,*sink, *mad, *audio_sink, *background, *filterBackSize;
    GstCaps *filtercaps, *filtercapsBackground;
    GstBus *bus;
    GstMessage *msg;
    GError *err;
    GstPadTemplate *mixer_sink_pad_template;
    /*array of radio */
    Radio radio[MAX_RADIO];
    /*array of data*/
    CustomData data[MAX_RADIO];
    /*struct used to record a stream*/
    RecordData rec;
    char file_name[BUFFER_SIZE];
    char tmp[BUFFER_SIZE];
    
    /* Curses Initialisations */
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    /* init gstreamer*/
    gst_init (&argc, &argv);
    if (argc < 3) {
        clean_term();
        g_printerr ("Usage: %s <file_name numberOfRadio>\n", argv[0]);
        return -1;
    }
    /*settings parameters */
    strcpy(file_name,argv[1]);
    nberRadio = atoi(argv[2]);
    totalRadio = count_radio(file_name);
    err = NULL;
    radio_selected = 1;
    old_radio_selected = 1;
    dir = radio_selected;
    if(totalRadio == 0 ){
        clean_term();
        g_printerr ("No radio available found %d radio \n", totalRadio);
        exit(EXIT_FAILURE);
    }
    if(nberRadio > totalRadio || nberRadio == 0 ){
        clean_term();
        g_printerr ("Wrong value there are %d radio \n", totalRadio);
        exit(EXIT_FAILURE);
    }
    if(nberRadio > MAX_RADIO ){
        clean_term();
        g_printerr ("Wrong value  %d radios possible\n", MAX_RADIO);
        exit(EXIT_FAILURE);
    }
    /* Create elements */
    pipeline = gst_pipeline_new ("oumar-radio-player");
    filtercaps = gst_caps_new_simple ("video/x-raw-yuv",
        "width", G_TYPE_INT, PICTURE_WIDTH,
        "height", G_TYPE_INT, PICTURE_HEIGHT,
        NULL);
    if(nberRadio % 2 == 0)
        j=(nberRadio/2);
    else
        j=(nberRadio/2)+1;
    if(nberRadio == 1){
        k=1;
        j=1;
    }else{
        k=2;
    }
    filtercapsBackground = gst_caps_new_simple ("video/x-raw-yuv",
        "width", G_TYPE_INT, k*PICTURE_WIDTH+5,
        "height", G_TYPE_INT, j*PICTURE_HEIGHT+5,
        NULL);
    for(i = 0; i < nberRadio; i++){
        get_radio(i, file_name, &radio[i]);
        if (!create_element(filtercaps, &data[i], radio[i])){
            return -1;
        }
    }
    mixer = gst_element_factory_make ("videomixer", "mixer");
    clrspace = gst_element_factory_make ("ffmpegcolorspace", "clrspace");
    sink = gst_element_factory_make ("autovideosink", "sink");
    background = gst_element_factory_make ("videotestsrc", "background");
    filterBackSize = gst_element_factory_make("capsfilter", "size background");
    source_audio = gst_element_factory_make ("souphttpsrc", "file-source");
    mad = gst_element_factory_make ("mad", "mp3decoder");
    audio_sink = gst_element_factory_make ("autoaudiosink", "audio-output");
    /*verify  elements */
    if (!pipeline || !mad || !audio_sink || !sink || !mixer || !clrspace || !background  || !filterBackSize) {
        clean_term();
        g_printerr ("One element (pipeline, mad, audio_sink, sink, mixer, clrspace"
            ", background, filterBackSize) could not be created. Exiting.\n");
        return -1;
    }
    if(!record_manager(&rec)){
        return -1;
    }
    g_object_set (G_OBJECT (background), "pattern", PATTERN_WHITE, NULL); 
    g_object_set (G_OBJECT (filterBackSize), "caps", filtercapsBackground, NULL);   
    g_print ("Creation des elements termine...\n");
    /* unref du filtercaps*/
    gst_caps_unref (filtercaps);
    gst_caps_unref (filtercapsBackground);
    /* settings videobox coordinates*/
    j=0;
    k=0;
    for(i = 0; i < nberRadio; i++){
        g_object_set (G_OBJECT (data[i].videobox), "border-alpha", 0.0, NULL);
        if(i%2 == 0){
            g_object_set(data[i].videobox,"top",j*(-PICTURE_HEIGHT),"left",0,NULL);
            j++;
        }else{
            g_object_set(data[i].videobox,"top",k*(-PICTURE_HEIGHT),"left", -PICTURE_HEIGHT,NULL);
            k++;
        }
    }
    /* Listen to the bus */
    bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
    /* Build the pipeline and link elements */
    gst_bin_add_many (GST_BIN (pipeline),background,filterBackSize, mixer,clrspace, sink, NULL);
    if(gst_element_link_many(background,filterBackSize,mixer,clrspace, sink,NULL) != TRUE)
    {
        clean_term();
        g_printerr ("mixer clrspace sink could not be linked. Exiting.\n");
        return -1;
    }
    border_radio(&data[0], NULL);
    for(i = 0; i < nberRadio; i++){
        add_on_pipeline(pipeline, data[i]);
        if(!link_many(data[i], radio[i].name))
        {
            return -1;
        }
    }
    /* pipeline for radio audio output */
    gst_bin_add_many (GST_BIN (pipeline),
                        source_audio, mad, audio_sink, NULL);
    gst_element_link (source_audio, mad);
    if(gst_element_link_many (mad, audio_sink, NULL) != TRUE)
    {
        g_printerr ("mad audio_sink could not be linked. Exiting.\n");
        return -1;
    }
    /* pad mixer for settings videobox */
    mixer_sink_pad_template = gst_element_class_get_pad_template(
        GST_ELEMENT_GET_CLASS (mixer), "sink_%d");  
    if(mixer_sink_pad_template==NULL)
    {
        clean_term();
        g_printerr (" one sink mix could not be created. Exiting.\n");
        return -1;
    }
    /*order of radio in sink_template*/
    j = nberRadio;
    for(i = 0; i < nberRadio; i++){
        j--;
       data[i].mixer_sink_pad = gst_element_request_pad(mixer,
                                                        mixer_sink_pad_template,
                                                        NULL, NULL);
       data[i].sink_pad = gst_element_get_static_pad (data[j].videobox, "src");
       
       if(gst_pad_link ( data[i].sink_pad, data[i].mixer_sink_pad)
            != GST_PAD_LINK_OK){
            clean_term();
            g_printerr ("mix could not be linked.\n");
            gst_object_unref (pipeline);
            return -1;
        }
        gst_object_unref (data[i].sink_pad);
    }
    /*default radio playing */
    g_object_set (G_OBJECT (source_audio), "location", radio[0].flux, NULL);
    /* Start playing */
    gst_element_set_state (pipeline, GST_STATE_PLAYING);

    printw("Welcome to Oumar Radio Player\n"
            "\tPress ESC to Exit\n\tPress R to record\n\tPress S to stop recording\n");
    while(1){
        /* check if there is an error message with details on the bus */
        msg = gst_bus_poll (bus, GST_MESSAGE_ERROR, 0);
        if (msg) {
            gst_message_parse_error (msg, &err, NULL);
            printw ("ERROR: %s\n", err->message);
        }
        ch = getch();
        erase();
        printw("Welcome to Oumar Radio Player\n"
            "\tPress ESC to Exit\n\tPress R to record\n\tPress S to stop recording\n");
        switch(ch)
        {
            case KEY_UP:
                dir -=2;
                if(dir <= 0){
                    dir = radio_selected;
                }else{
                    old_radio_selected = radio_selected;
                    radio_selected = dir;
                    change_channel(&data[radio_selected-1],
                                   &data[old_radio_selected-1],
                                   radio[radio_selected-1], pipeline,
                                   source_audio); 
                }
                break;
            case KEY_DOWN:
                dir +=2;
                if(dir > nberRadio){
                    dir = radio_selected;
                }else{
                    old_radio_selected = radio_selected;
                    radio_selected = dir;
                    change_channel(&data[radio_selected-1],
                                   &data[old_radio_selected-1],
                                   radio[radio_selected-1], pipeline,
                                   source_audio);
                }
                break;
            case KEY_LEFT:
                dir--;
                if(dir <= 0){
                    dir = radio_selected;
                }else{
                    old_radio_selected = radio_selected;
                    radio_selected = dir;
                    change_channel(&data[radio_selected-1],
                                   &data[old_radio_selected-1],
                                   radio[radio_selected-1], pipeline,
                                   source_audio); 
                }
                break;
            case KEY_RIGHT:
                dir++;
                if(dir > nberRadio){
                    dir = radio_selected;
                }else{
                    old_radio_selected = radio_selected;
                    radio_selected = dir;
                    change_channel(&data[radio_selected-1],
                                   &data[old_radio_selected-1],
                                   radio[radio_selected-1], pipeline,
                                   source_audio);
                }
                break;
            case 'r':
            case 'R':
                strcpy(tmp, radio[radio_selected-1].name);
                strcat(tmp, ".mp3");
                record(tmp, 192, &rec);
                break;
            case 's':
            case 'S':
                stop_record(&rec);
                break;
            default:
                break;
        }
        if(ch == ESCAPE){
            /* exit the loop end of process */
            break;
        }
    }
    refresh();
    endwin();
    g_print("End of process, clean up nicely ...\n");
    if (msg){
        g_printerr("ERROR : %s\n", err->message);
        g_error_free (err);
        gst_message_unref (msg);
    }
    gst_object_unref (bus);
    /* Out of the main loop, clean up nicely */
    g_print ("Returned, stopping playback\n");
    gst_element_set_state (pipeline, GST_STATE_NULL);
    g_print ("Deleting pipeline\n");
    gst_object_unref (GST_OBJECT (pipeline));
    return 0;
}
