#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include<sys/shm.h>
#include<sys/sem.h>


int *cpt,nb1,nb2;

void increment(){
	
	int i;
	
	for(i=0;i<nb1;i++){
		
		 *cpt+=1;
		
		printf("increment ==%d\n", *cpt);
	}

}

void decrement(){
	
	
	int i;
	for(i=0;i<nb2;i++){
		
		 *cpt-=1;

		 printf("decrement ==%d\n" ,*cpt);
	}
	
}

int main(int argc,char** argv){
	
	int id,sem_id; // identificateur du seg de memoire partagé 
	
	//Initialisation des operations P et V
	struct sembuf op;
	op.sem_num = 0; //Numéro de notre sémaphore: le premier et le seul
	op.sem_flg = 0; //On ne s'en occupe pas
	op.sem_op = 1; //Pour un P() on décrémente

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


	
	if((sem_id=semget(IPC_PRIVATE,1,IPC_CREAT|0666))<0){
		perror("Erreur de creationn semaphore");
		exit(6);
	}

	//initialisation du semaphore
	semctl(sem_id, 0, SETVAL, 1);
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
			op.sem_op = -1;
			semop(sem_id, &op, 1);
			increment();
			op.sem_op = 1; //Pour un V() on incrémente
			semop(sem_id, &op, 1);
			exit(2);

			
		}
		default: break;
				
	}	
	

	decrement();
	op.sem_op = 1; //Pour un V() on incrémente
	semop(sem_id, &op, 1);
	wait(NULL);
	//detache le segment de memoire partagé
	shmdt(cpt);
	//detruit le segment de memoire partagé
	shmctl(id, IPC_RMID, NULL);
	// fin du père
	semctl(sem_id, 0, IPC_RMID, 0);
	exit(0);



}
