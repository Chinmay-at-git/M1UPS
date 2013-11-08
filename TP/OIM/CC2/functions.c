#include <stdio.h>
#include <stdlib.h>
#include <gst/gst.h> 
#include <glib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <ncurses.h>
#include "constant.h"

/*
    Diallo Alpha Oumar Binta
    21007631
    CC2 OIM
    Groupe 3.1
    Universite Paul Sabatier
    Toulouse III
*/ 

static void
on_pad_added (GstElement *element,
              GstPad *pad,
              gpointer data)
{
  GstPad *sinkpad;
  GstElement *decoder = (GstElement *) data;
  /* We can now link the pad */
  printw("\nimage decoder\n");
  sinkpad = gst_element_get_static_pad (decoder, "sink");
  gst_pad_link (pad, sinkpad);
  gst_object_unref (sinkpad);
}
/**
 * Set in Radio the information given in the file file_name
 * 
 */
void get_radio(int number, char* file_name, Radio *radio)
{
    FILE* _file = NULL;
    char str[BUFFER_SIZE] = "";
    int i;
    char last_temp[BUFFER_SIZE];
    /*open the file read mode */
    _file = fopen(file_name, "r");
    if (_file != NULL)
    {
        i=0;
        while (fgets(str, BUFFER_SIZE, _file) != NULL && i<number)
            i++;
        strcpy(radio->name, strtok(str, "\t"));
        strcpy(radio->flux, strtok(NULL, "\t"));
        strcpy(last_temp, strtok(NULL, "\t"));
        if (strstr(last_temp, "\n") != NULL)
          strncpy(radio->logo, last_temp, strlen(last_temp)-1);
        else
          strncpy(radio->logo, last_temp, strlen(last_temp));
    }else{
        g_printerr ("Could not open %s \n", file_name);
        exit(EXIT_FAILURE);
    }
    fclose(_file);
}
/**
 * Return an int the total line number of the file file_name
 * 
 */
int count_radio(char* file_name)
{
    FILE* _file = NULL;
    int i;
    char str[BUFFER_SIZE] = "";
    _file = fopen(file_name, "r");
    if (_file != NULL)
    {
        i=0;
        while (fgets(str, BUFFER_SIZE, _file) != NULL)
            i++;
    }else{
        g_printerr ("Could not open %s \n", file_name);
        exit(EXIT_FAILURE);
    }
    fclose(_file);
    return i;
}
/**
 * link the CustomData data elements to the source
 */
int link_many(CustomData data, char *name){
    /* if selected we add border to the videobox*/
    if(gst_element_link_many (data.conv, data.freeze, data.filter,data.textoverlay,
            data.contour,data.videobox, NULL) != TRUE)
    {
        g_printerr ("source radio %s could not be linked. Exiting.\n", name);
        return 0;
    }
    g_signal_connect (data.source, "pad-added", G_CALLBACK (on_pad_added), data.conv);
    return 1;
}
/**
 * Add CustomData data to the pipeline
 */
void add_on_pipeline(GstElement *pipeline, CustomData data){
    gst_bin_add_many (GST_BIN (pipeline), data.source, data.videobox, data.contour, data.filter,
                      data.textoverlay, data.freeze, data.conv, NULL);
}
/**
 * Create elements of CustomData data
 */
int create_element(GstCaps *filtercaps, CustomData *data, Radio radio){
    char tmp[255];
    
    sprintf(tmp,"source %s", radio.name);
    data->source = gst_element_factory_make ("uridecodebin", tmp);
    sprintf(tmp,"filter %s", radio.name);
    data->filter = gst_element_factory_make("capsfilter", tmp);
    sprintf(tmp,"videobox %s", radio.name);
    data->videobox = gst_element_factory_make("videobox", tmp);
    data->textoverlay = gst_element_factory_make("textoverlay", radio.name);
    sprintf(tmp,"contour videobox %s", radio.name);
    data->contour = gst_element_factory_make ("videobox", tmp);
    sprintf(tmp,"convert %s", radio.name);
    data->conv = gst_element_factory_make ("autovideoconvert", tmp);
    sprintf(tmp,"imagefreeze %s", radio.name);
    data->freeze = gst_element_factory_make ("imagefreeze", tmp);
    /* set value of the data */
    g_object_set (G_OBJECT (data->source), "uri", radio.logo, NULL);
    g_object_set (G_OBJECT (data->textoverlay), "text", radio.name, NULL);
    g_object_set (G_OBJECT (data->textoverlay), "font-desc", "Sans, 35", NULL);
    /* set the size of the box */
    g_object_set (G_OBJECT (data->filter), "caps", filtercaps, NULL);

    if(!data->source || !data->filter || !data->videobox
        || !data->textoverlay || !data->freeze || !data->contour || !data->conv) {
        g_printerr ("One element could of radio %s not be created. Exiting.\n",
                    radio.name);
        return 0;
    }
    return 1;
}
/**
 * Make a videobox border to CustomData data and destroy
 * the border of videobox to CustomData old_data
 */
void border_radio(CustomData *data, CustomData *old_data){
    if(old_data != NULL){
        g_object_set (G_OBJECT (old_data->contour), "border-alpha", 0.0, NULL);
        g_object_set (G_OBJECT (old_data->contour), "top", 0, NULL);
        g_object_set (G_OBJECT (old_data->contour), "bottom", 0, NULL);
        g_object_set (G_OBJECT (old_data->contour), "left", 0, NULL);
        g_object_set (G_OBJECT (old_data->contour), "right", 0, NULL);
    }
    g_object_set (G_OBJECT (data->contour), "border-alpha", 1.0, NULL);
    g_object_set (G_OBJECT (data->contour), "fill", OUMAR_RED, NULL);
    g_object_set (G_OBJECT (data->contour), "top", -1, NULL);
    g_object_set (G_OBJECT (data->contour), "bottom", -1, NULL);
    g_object_set (G_OBJECT (data->contour), "left", -1, NULL);
    g_object_set (G_OBJECT (data->contour), "right", -1, NULL);
}
/**
 * play the stream of Radio radio via the pipeline and source_audio
 */
void play_radio(Radio radio, GstElement *pipeline, GstElement *source_audio){
    gst_element_set_state (pipeline, GST_STATE_READY);
    g_object_set (G_OBJECT (source_audio), "location", radio.flux, NULL);
    printw("Now playing... %s\n", radio.name);
    gst_element_set_state (pipeline, GST_STATE_PLAYING);
}
/**
 * Change radio channel
 */
void change_channel(CustomData *data, CustomData *old_data, Radio radio, GstElement *pipeline, GstElement *source_audio){
    border_radio(data, old_data);
    play_radio(radio, pipeline, source_audio);
}
/**
*record the audio stream in the file filname with the bitrate
*/
void record(char *filename, int bitrate, RecordData *rec) {
    printw("RECORDING %s\n", filename);
    gst_element_set_state(GST_ELEMENT(rec->pipeline), GST_STATE_NULL);
    g_object_set(G_OBJECT(rec->fileSink), "location", filename, NULL);
    g_object_set(G_OBJECT(rec->lameEncoder), "bitrate", bitrate, NULL);
    gst_element_set_state(GST_ELEMENT(rec->pipeline), GST_STATE_PLAYING);
}
/**
*init a record manager
*/
int record_manager(RecordData *rec) {
    /* Record pipeline
     autoaudiosrc ! audioconvert ! lame bitrate=192 ! filesink location=rmc.mp3*/
    rec->pipeline = gst_pipeline_new("record-pipeline"); 
    rec->audioSrc = gst_element_factory_make("autoaudiosrc", "audio_in");
    rec->audioConvert = gst_element_factory_make("audioconvert", "audio_converter");
    rec->lameEncoder = gst_element_factory_make("lame", "lame_encoder");
    rec->fileSink = gst_element_factory_make("filesink", "file_sink");
    if (!rec->pipeline || !rec->audioSrc || !rec->audioConvert
         || !rec->lameEncoder || !rec->fileSink) {
        g_printerr ("One element of record pipeline could not be created. Exiting.\n");
        return 0;
    }
    gst_bin_add_many(GST_BIN(rec->pipeline), rec->audioSrc, rec->audioConvert, rec->lameEncoder, rec->fileSink, NULL);
    if(gst_element_link_many(rec->audioSrc, rec->audioConvert, rec->lameEncoder, rec->fileSink, NULL) != TRUE)
    {
        g_printerr ("mixer clrspace sink could not be linked. Exiting.\n");
        return 0;
    }
    return 1;
}
/**
*Stop the record rec
*/
void stop_record(RecordData *rec) {
    printw("END OF THE RECORD\n");
    gst_element_set_state(GST_ELEMENT(rec->pipeline), GST_STATE_READY);
}
