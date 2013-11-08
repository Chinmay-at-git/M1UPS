#ifndef CONSTANT_H
#define CONSTANT_H

#define PICTURE_HEIGHT 120
#define PICTURE_WIDTH 120
#define MAX_RADIO 100
#define BUFFER_SIZE 1024

#define OUMAR_RED 3
#define PATTERN_WHITE 3


#define ENTER 10
#define ESCAPE 27

/*
    Diallo Alpha Oumar Binta
    21007631
    CC2 OIM
    Groupe 3.1
    Universite Paul Sabatier
    Toulouse III
*/ 

typedef struct _Radio{
    char logo[255];
    char name[255]; 
    char flux[255];
    int number;
}Radio;

typedef struct _CustomData {
    GstElement *source;
    GstElement *filter;
    GstElement *videobox;
    GstElement *textoverlay;
    GstElement *contour;
    GstElement *freeze;
    GstElement *conv;
    GstPad *mixer_sink_pad, *sink_pad;
}CustomData;

typedef struct _RecordData {
    GstElement *pipeline;
    GstElement *audioSrc;
    GstElement *audioConvert;
    GstElement *lameEncoder;
    GstElement *fileSink;
}RecordData;

/**
 * Set in Radio the information given in the file file_name
 * 
 */
void get_radio(int number, char* file_name, Radio *radio);
/**
 * Return an int the total line number of the file file_name
 * 
 */
int count_radio(char* file_name);
/**
 * link the CustomData data elements to the source
 */
int link_many(CustomData data, char *name);
/**
 * Add CustomData data to the pipeline
 */
void add_on_pipeline(GstElement *pipeline, CustomData data);
/**
 * select radio defined by CustomData data
 */
void select_radio(CustomData *data, Radio radio);
/**
 * Return 1 if the CustomData data is created
 */
int create_element(GstCaps *filtercaps, CustomData *data, Radio radio);
/**
 * Make a videobox border to CustomData data and destroy
 * the border of videobox to CustomData old_data
 */
void border_radio(CustomData *data, CustomData *old_data);
/**
 * play the stream of Radio radio via the pipeline and source_audio
 */
void play_radio(Radio radio, GstElement *pipeline, GstElement *source_audio);
/**
 * Change radio channel
 */
void change_channel(CustomData *data, CustomData *old_data, Radio radio,
                    GstElement *pipeline, GstElement *source_audio);
/**
*record the audio stream in the file filname with the bitrate
*/
void record(char *filename, int bitrate, RecordData *rec);
/**
*init a record manager
*/
int record_manager(RecordData *rec);
/**
*record the audio stream in the file filname with the bitrate
*/
void record(char *filename, int bitrate, RecordData *rec);
/**
*Stop the record rec
*/
void stop_record(RecordData *rec);
#endif
