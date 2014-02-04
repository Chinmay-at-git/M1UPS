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


/*variante 3:
    Utilisons un segment de memoire partagee pour le compteur
    Avant qu'un processus puisse utiliser un segment de memoire partagee,
    ce dernier doit être attache au processus grâce à la primitive shmat().
    La primitive shmdt() permet au processus de se detacher du segment.
    La fonction shmat retourne l'adresse du segment de memoire partagee.
    Il n'y a pas copie de zone memoire mais redirection de l'adressage 
    vers le segment partage.
*/
void incremente(int nbre, int shmid){
    int i=0;
    int* cptSon=NULL;
    printf("Salut, je suis le fils %d, j'incremente le compteur\n"
        "Je commence par m'attacher le segment de memoire\n",getpid());

    if((cptSon=(int*)shmat(shmid, NULL, 0)) < 0){
        error("Attache segment memoire partage", ERR_ATT);
    }
    for(i=0; i < nbre; i++){
       *cptSon+=1;
        printVal("incremente % d\n", *cptSon);
    }
    /* on arrete le fils pour ne pas qu'il execute le code du pere,
     car ce code est duplique a la creation du fils */
    printf("Bon, proc_fils il est temps de mourrir\n"
        "avant tout detachons le segment partagee\n");
    if(shmdt(cptSon) < 0){
        error("detachement impossible", ERR_DET);
    }
    printf("Le fils se suicide\n");
    exit(EXIT_FILS);
}

void decremente(int nbre, int shmid){
    int i=0;
    int* cptFather=NULL;
    printf("Je suis le pere, je decremente le compteur\n"
        "Je commence par m'attacher le segment de memoire\n");

    if((cptFather=(int*)shmat(shmid, NULL, 0)) < 0){
        error("Attache segment memoire partage", ERR_ATT);
    }
    for(i=0;i < nbre; i++){
        *cptFather-=1;
        printVal("decremente % d\n", *cptFather);
    }
    printf("Bon, proc_pere il est temps de mourrir\n"
        "avant tout detachons le segment partagee\n");
    if(shmdt(cptFather) < 0){
        error("detachement impossible", ERR_DET);
    }
}

int main(int argc, char *argv[]){
    int iter = 0;
    /* identifiant du segment de memoire partage */
    int shmid;
    if(argc != 2){
        printf("Error :\t ./v3 nber_iteration\n");
        exit(EXIT_FAILURE);
    }
    iter = atoi(argv[1]);
    /* creation zone memoire */
    shmid = create_shm(100,"key",1);

    /* creation des processus */
    switch(fork()){
        case -1 : error("Creation fils", ERR_CREAT_FILS);
        case 0 :
            /* on est dans le fils */
            incremente(iter, shmid);
        default : break;
    }
    decremente(iter, shmid);
    /*on attends la fin des processus */
    printf("Le pere attend la mort de son fils\n") ;
    wait(0);
    printf("Bon, faisons le menage et supprimons le segment partagee\n") ;
    /*destruction du segment de memoire */
    delete_shm(shmid);
    printf("Le pere se suicide\n") ;
    return 0;
}
