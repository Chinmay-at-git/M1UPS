#!/bin/bash
read -p 'Entrer le nom du fichier à lire  .ogg  : ' src_file
gst-launch filesrc location=$src_file ! oggdemux ! vorbisdec ! audioconvert ! alsasink
echo 'Fin de lecture du fichier'

#!/bin/bash
read -p 'Entrer le nom du fichier à lire  .mp3  : ' src_file
gst-launch filesrc location=$src_file ! mad ! autoaudiosink
echo 'Fin de lecture du fichier'


#!/bin/bash
#read -p 'Entrer le nom du fichier à lire  .ogg  : ' 
src_file='trailer_400p.ogg'

gst-launch filesrc location='trailer_400p.ogg' ! oggdemux name=demux ! avimux name=mux ! filesink location="test.avi" ! demux. ! queue  ! queue ! audioconvert ! queue ! mux.

#!/bin/bash
#chiane de traitement permettant de convertir un fichier encode en
#mp3 vers un fichier son encode en OGG
#procedure : ouvrir ! extraire/décoder ! convertir/encoder ! multiplexer ! enregistrer

#on demande le nom du fichier mp3 en entree puis le nom du fichier converti(format .ogg)

read -p 'Entrer le nom du fichier src  .mp3  : ' src_file
read -p 'Entrer le nom du fichier dest  .ogg  : ' dest_file
gst-launch filesrc location=$src_file ! mad ! audioconvert ! vorbisenc ! oggmux ! filesink location=$dest_file
echo 'Fichier converti'

commande pour lancer une video gst-launch filesrc location=trailer_400p.ogg ! oggdemux ! theoradec ! xvimagesink
lancer une video(image + audio : gst-launch filesrc location=trailer_400p.ogg ! oggdemux name=demux demux. ! queue ! vorbisdec ! audioconvert ! audioresample ! autoaudiosink demux. ! queue ! theoradec  ! autovideosink

commande pour lancer un fichier mp3, mad est la meilleure option : 

