gst-launch -e videomixer name=mix ! ffmpegcolorspace ! ximagesink \
   videotestsrc pattern=1 ! video/x-raw-yuv, framerate=5/1, width=320, height=180 ! videobox border-alpha=0 top=0 left=0 ! mix. \
   videotestsrc pattern=15 ! video/x-raw-yuv, framerate=5/1, width=320, height=180 ! videobox border-alpha=0 top=0 left=-320 ! mix. \
   videotestsrc pattern=13 ! video/x-raw-yuv, framerate=5/1, width=320, height=180 ! videobox border-alpha=0 top=-180 left=0 ! mix. \
   videotestsrc pattern=0 ! video/x-raw-yuv, framerate=5/1, width=320, height=180 ! videobox border-alpha=0 top=-180 left=-320 ! mix. \
   videotestsrc pattern=3 ! video/x-raw-yuv, framerate=5/1, width=640, height=360 ! mix.
  
#marche
gst-launch-1.0 uridecodebin uri=http://www.logotheque.fr/6396-2/logo+RMC+INFO.jpg ! imagefreeze ! textoverlay font-desc="Sans 20" text="CAM1" ! autovideoconvert ! ximagesink
  
                    
#marche                 
gst-launch-1.0 -e videomixer name=mix ! ffmpegcolorspace ! ximagesink \
  videotestsrc pattern=1  ! video/x-raw-yuv,width=100,height=100 ! \
videobox border-alpha=0 top=0 left=0 ! mix. \
  videotestsrc pattern=0  ! video/x-raw-yuv,width=100,height=100 ! \
videobox border-alpha=0 top=0 left=-100 ! mix.


gst-launch-1.0 -e videomixer name=mix ! autovideoconvert ! ximagesink  \
  uridecodebin uri=http://www.logotheque.fr/6396-2/logo+RMC+INFO.jpg ! imagefreeze ! autovideoconvert ! video/x-raw, framerate=5/1, width=100, height=100 ! textoverlay font-desc="Sans 50" text="CAM1" ! mix. \
  uridecodebin uri=http://media.nrj.fr/webradio_logo/100x100/2013/03/rire-default-120-120-tr_player72034.png ! imagefreeze ! autovideoconvert ! video/x-raw, framerate=5/1, width=100, height=100 ! videobox border-alpha=1.0 alpha=1.0 top=-180 left=0 ! mix. \

