PRG1=v1
PRG2=v2
PRG3=v3
clean:
	rm -f *.o

realclean: clean
	rm -f $(PRG1) $(PRG2) $(PRG3) *~ out.*

v1: v1.c
	gcc -Wall v1.c  -o v1
v3: v3.c
	gcc -Wall v3.c  -o v3
v2: v2.c
	gcc -Wall v2.c  -o v2