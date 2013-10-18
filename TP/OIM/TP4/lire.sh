#!/bin/bash
#gst-inspect audioecho correspond a un man de la commande audioecho

#exo1 $1= nom du fichier wav
function augmentationVol
{
  echo 'Augmentation volume du fichier son'
  gst-launch filesrc location=$1 ! wavparse ! volume volume=3 ! autoaudiosink
}
#exo2 $1 nom du fichier wav
function rajoutEcho
{
  echo 'Ajout d''un echo sur le fichier son'
  gst-launch filesrc location=$1 ! wavparse ! audioconvert ! audioecho delay=500000000 intensity=0.6 feedback=0.4 ! audioconvert ! autoaudiosink
}
#exo3 $1 nom du fichier wav
function passeBas
{
  echo 'Ajout d''un passe bas sur le fichier son'
  gst-launch filesrc location=$1 ! wavparse ! audioconvert ! audiocheblimit mode=low-pass cutoff=6000 ! audioconvert ! autoaudiosink
}
#exo4 $1 nom du fichier wav
function passeHaut
{
  echo 'Ajout d''un passe haut sur le fichier son'
  gst-launch filesrc location=$1 ! wavparse ! audioconvert ! audiocheblimit mode=high-pass cutoff=6000 ! audioconvert ! autoaudiosink
}
#exo5 $1 nom du fichier wav
function suppressionVoix
{
  echo 'Supression de la voix sur le fichier son'
  gst-launch filesrc location=$1 ! wavparse ! audioconvert ! audiochebband mode=band-reject lower-frequency=100 upper-frequency=8000 ! audioconvert ! autoaudiosink
}

#exo2-1 flux video a partir d'une image
function fluxVideo
{
  echo 'Flux video à partir de l''image'
  #gst-launch filesrc location=$1 ! decodebin2 ! imagefreeze ! autovideosink
  gst-launch filesrc location=$1 ! decodebin2 ! imagefreeze ! videobalance saturation=0.0  ! autovideosink
}

#exo2-2 flux video 
function fluxVideotestsrc
{
  echo 'Flux video videotestsrc'
  gst-launch videotestsrc ! autovideosink
}
#exo2-3 flux video recadre
function videoCrop
{
  gst-launch videotestsrc ! videocrop top=180 left=240 ! autovideosink
}
#exo2-4 detection contour
function detectContour
{
  gst-launch filesrc location=$1 !oggdemux ! theoradec ! ffmpegcolorspace ! edgetv ! ffmpegcolorspace ! autovideosink
}
#exo2-5 gamma
#valeur haute =>brighter
#valeur basse =>darker
function videoGamma
{
  gst-launch filesrc location=$1 !oggdemux ! theoradec ! ffmpegcolorspace ! gamma gamma=5.0 ! ffmpegcolorspace ! autovideosink
}
#exo2-6
function videoContrast
{
  gst-launch filesrc location=$1 !oggdemux ! theoradec ! ffmpegcolorspace ! videobalance saturation=0.7 brightness=0.5 contrast=1 ! ffmpegcolorspace ! autovideosink
}
#exo2-7
function videoFlip
{
  gst-launch filesrc location=$1 !oggdemux ! theoradec ! ffmpegcolorspace ! videoflip method=clockwise ! videoflip method=clockwise ! ffmpegcolorspace ! autovideosink
}

#exo1
#augmentationVol 'extrait.wav'
#exo2
#rajoutEcho 'extrait.wav'
#exo3
#passeBas 'parolebruitee.wav'
#exo4
#passeHaut 'extrait.wav'
#exo5
#suppressionVoix 'extrait.wav'
#exo2-1
#fluxVideo '2CV.jpg'
#exo2-2
#fluxVideotestsrc
#exo2-3
#videoCrop
#exo2-4
#detectContour 'trailer_400p.ogg'
#exo2-5
#videoGamma 'trailer_400p.ogg'
#exo2-6
#videoContrast 'trailer_400p.ogg'
#exo2-7
videoFlip 'trailer_400p.ogg'