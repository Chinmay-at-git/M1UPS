#!/bin/bash
read -p 'Entrer le nom du fichier à lire  .ogg  : ' src_file
gst-launch filesrc location=$src_file ! oggdemux ! vorbisdec ! audioconvert ! alsasink
echo 'Fin de lecture du fichier'