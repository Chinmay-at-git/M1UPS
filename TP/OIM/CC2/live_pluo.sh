 gst-launch -e videomixer name=mix ! ffmpegcolorspace ! ximagesink \
   videotestsrc pattern=0 ! video/x-raw-yuv, framerate=1/1, width=350, height=250 ! \
     textoverlay font-desc="Sans 24" text="CAM1" valign=top halign=left shaded-background=true ! \
     videobox border-alpha=0 top=-200 left=-50 ! mix. \
   videotestsrc pattern="snow" ! video/x-raw-yuv, framerate=1/1, width=350, height=250 ! \
     textoverlay font-desc="Sans 24" text="CAM2" valign=top halign=left shaded-background=true ! \
     videobox border-alpha=0 top=-200 left=-450 ! mix. \
   videotestsrc pattern=13 ! video/x-raw-yuv, framerate=1/1, width=350, height=250 ! \
     textoverlay font-desc="Sans 24" text="CAM3" valign=top halign=left shaded-background=true ! \
     videobox border-alpha=0 top=-200 left=-850 ! mix. \
   multifilesrc location="pluto.jpg" caps="image/jpeg,framerate=1/1" ! jpegdec ! \
     textoverlay font-desc="Sans 26" text="Live from Pluto" halign=left shaded-background=true auto-resize=false ! \
     ffmpegcolorspace ! video/x-raw-yuv,format=\(fourcc\)AYUV ! mix.