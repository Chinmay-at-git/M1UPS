#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int cpt=0,nb1,nb2;

void increment(){
	
	int i;
	
	for(i=0;i<nb1;i++){
		
		 cpt++;
		printf("increment ==%d\n", cpt);
	}
	exit(2);
}

void decrement(){
	
	
	int i;
	for(i=0;i<nb2;i++){
		 cpt--;
		 printf("decrement ==%d\n" ,cpt);
	}
	exit(3);
}

int main(int argc,char** argv){
	
	int vr;
	if(argc!=3){
		perror("nombre d'argument different de 2\n");
		exit(1);
	}
	nb1=atoi(argv[1]);
	nb2=atoi(argv[2]);
	
	switch(fork()){
		case -1:{
			 perror("erreur de creation du fork");
			 exit(4);
		}
		case 0:{
			increment();
			
		}
		default: break;
				
	}	
	
	decrement();
	wait(&vr);

}
