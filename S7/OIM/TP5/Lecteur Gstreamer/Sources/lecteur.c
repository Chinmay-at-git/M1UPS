#include <gst/gst.h> 
#include <glib.h>
#include "flux.h"
#include "avi.h"
/*gcc lecteur.c flux.c avi.c ogg.c mpg.c mp3.c wav.c -o hello `pkg-config --cflags --libs gstreamer-0.10`*/


int main (int   argc, char *argv[])
{
  char* test;
test = flux(argc,argv);//on recupere le type de flux
printf("plop %s\n",test);//on l'affiche

//selection du pipeline en fonction du type de flux
if (strcmp(test,"video/x-msvideo")==0){
	avi(argc,argv);
}

else if (strcmp(test,"application/ogg")==0){
	ogg(argc,argv);
}
else if (strcmp(test,"video/mpeg, systemstream=(boolean)true, mpegversion=(int)1")==0){
	mpg(argc,argv);
}
else if (strcmp(test,"audio/x-wav")==0){
	wav(argc,argv);
}
else if (strcmp(test,"application/x-id3")==0){
	mp3(argc,argv);
}
else
{printf("erreur de flux\n");}


  return 0;
} 
