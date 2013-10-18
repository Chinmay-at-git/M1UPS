#!/bin/bash
#read -p 'Entrer le nom du fichier à lire  .ogg  : ' 
src_file='trailer_400p.ogg'

gst-launch filesrc location='trailer_400p.ogg' ! oggdemux name=demux ! avimux name=mux ! filesink location="test.avi" ! demux. ! queue  ! queue ! audioconvert ! queue ! mux.