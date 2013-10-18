#!/bin/bash
#chiane de traitement permettant de convertir un fichier encode en
#mp3 vers un fichier son encode en OGG
#procedure : ouvrir ! extraire/décoder ! convertir/encoder ! multiplexer ! enregistrer

#on demande le nom du fichier mp3 en entree puis le nom du fichier converti(format .ogg)

read -p 'Entrer le nom du fichier src  .mp3  : ' src_file
read -p 'Entrer le nom du fichier dest  .ogg  : ' dest_file
gst-launch filesrc location=$src_file ! mad ! audioconvert ! vorbisenc ! oggmux ! filesink location=$dest_file
echo 'Fichier converti'
