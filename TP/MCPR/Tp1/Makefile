PRG1=v1
PRG2=v2
PRG3=v3
PRG4=v4
PRG5=v5
clean:
	rm -f *.o

realclean: clean
	rm -f $(PRG1) $(PRG2) $(PRG3) $(PRG4) $(PRG5) *~ out.*

v1: v1.c
	gcc -Wall v1.c  -o v1
v3: v3.c
	gcc -Wall v3.c  -o v3
v2: v2.c
	gcc -Wall v2.c  -o v2
v4: v4.c
	gcc -Wall v4.c  -o v4
v5: v5.c
	gcc -o v5 v5.c library.c