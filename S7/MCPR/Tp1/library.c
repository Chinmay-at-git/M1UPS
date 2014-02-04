#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "constante.h"

/*
    Diallo Alpha Oumar Binta
    21007631
    Tp MCPR
    Universite Paul Sabatier
    Toulouse III
*/ 


/**
    Affiche le message d'erreur msg sur la sortie standard et 
    sort du programme avec le code de retour status
*/
void error(char *msg, int status){
    perror(msg);
    exit(status);
}
/**
    Affiche le message msg et l'entier val sur la sortie standard
*/
void printVal(char *msg, int val){
    fprintf(stdout, msg, val);
}

int create_shm(int size, char *name, int cle){
 /* l'identificateur de la memoire partagee */
  int shmid;
  /*la clef associee au segment*/
  key_t clef;
  /* L'instruction ftok(name,(key_t) cle) permet de construire 
     une cle identifiant le segment */
  if((clef = ftok(name,(key_t) cle)) < 0){
    error("La creation de la clef a echouee", ERR_KEY);
  }
  /* L'instruction IPC_CREAT|IPC_EXCL|SHM_R|SHM_W permet d'indiquer 
     les droits d'acces de ce segment de memoire */
  if((shmid = shmget( clef,
                  size,
                  IPC_CREAT|IPC_EXCL|SHM_R|SHM_W )) < 0){
    error("La creation du segment de memoire partage a echouee", ERR_SEG);
  }
  printf("l'identificateur du segment est %d \n",shmid);
  printf("ce segment est associe a la clef %d \n",clef);

  return shmid ;
}

void info_shm(int shmid){

  struct shmid_ds buf;

  if (shmctl(shmid,IPC_STAT,&buf) == -1){
    error("Erreur lors de l'utilsation de infoSegment", 1);
  }

  printf("Affichage des champs de controles\n") ;
  printf("Identificateur du proprietaire : %d\n",buf.shm_perm.uid);
  printf("Identificateur du groupe du proprietaire : %d\n",buf.shm_perm.gid);
  printf("Identificateur du createur : %d\n",buf.shm_perm.cuid);
  printf("Identificateur du groupe du createur : %d\n",buf.shm_perm.cgid);
  printf("Mode d'acces : %d\n",buf.shm_perm.mode);
  printf("Taille du segment : %d\n",buf.shm_segsz);
}

void delete_shm(int shmid){
  if (shmctl(shmid,IPC_RMID,NULL) == -1){
    error("Erreur lors de la destruction", 1);
  }
}

