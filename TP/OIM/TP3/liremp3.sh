#!/bin/bash
read -p 'Entrer le nom du fichier à lire  .mp3  : ' src_file
gst-launch filesrc location=$src_file ! mad ! autoaudiosink
echo 'Fin de lecture du fichier'
