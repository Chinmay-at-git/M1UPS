PRG=lecteuraudiovideo
default_target: $(PRG)
clean:
	rm -f *.o

realclean: clean
	rm -f $(PRG) *~ out.*

lecteuraudiovideo: main.c
	gcc -Wall -ansi main.c pmp_cb.c pmp_ui.c -o $(PRG) `pkg-config --cflags --libs gtk+-2.0 gstreamer-0.10 gstreamer-interfaces-0.10`