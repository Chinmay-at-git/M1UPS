#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include<sys/shm.h>



int *cpt,nb1,nb2;

void increment(){
	
	int i;
	
	for(i=0;i<nb1;i++){
		
		 *cpt+=1;
		
		printf("increment ==%d\n", *cpt);
	}
	exit(2);
}

void decrement(){
	
	
	int i;
	for(i=0;i<nb2;i++){
		
		 *cpt-=1;

		 printf("decrement ==%d\n" ,*cpt);
	}
	
}

int main(int argc,char** argv){
	
	int id; // identificateur du seg de memoire partagé 
	


	if(argc!=3){
		perror("nombre d'argument different de 2\n");
		exit(1);
	}
	nb1=atoi(argv[1]);
	nb2=atoi(argv[2]);

	//on obtient un id du zone de memoire partagé
	if((id=shmget(IPC_PRIVATE,sizeof(int),IPC_CREAT|0666))<0){
		perror("erreur de creation du segment de memoire\n");
		exit(3);
	}	

	//attache lesegment de memoire partagé

	if((cpt=(int*)shmat(id, NULL, 0))<0){
		perror("erreur d'atachement");
		exit(4);
	}
	*cpt=0;
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
	wait(NULL);
	//detache le segment de memoire partagé
	shmdt(cpt);
	//detruit le segment de memoire partagé
	shmctl(id, IPC_RMID, NULL);
	// fin du père
	exit(5);



}
