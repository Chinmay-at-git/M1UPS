PRG=radio
clean:
	rm -f *.o

realclean: clean
	rm -f $(PRG) *~ out.*

radio: main.c
	gcc -Wall main.c -o radio `pkg-config --cflags --libs gstreamer-0.10`