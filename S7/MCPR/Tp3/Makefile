PRG1=exo1
PRG2=exo2
clean:
	rm -f *.o

realclean: clean
	rm -f $(PRG1) $(PRG2) *~ out.*

exo1: exo1.c
	gcc -Wall exo1.c -o exo1
exo2: exo2.c
	gcc -Wall exo2.c -o exo2