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

/*variante 4:
    Les processus partagent maintenant deux informations : le compteur entier 
    (sur lequel les memes operations sont faites) et une valeur reelle qui sera 
    modifiee par un processus et affichee par l’autre (pour verifier que le
    partage se fait bien).
    Conclusion:
        Ce code ne fait pas ce qu'on lui demande, il peut arriver que le pere
        affiche le contenu de la memoire avant que le fils n'ait place sa valeur.
        Il faut se servir d'un sémaphore pour gérer l'ordonnancement des tâches.
*/

void incremente(int nbre, int shmid){
    int i=0;
    ValPartage* valSon=NULL;
    printf("Salut, je suis le fils %d, j'incremente le compteur\n"
        "Je commence par m'attacher le segment de memoire\n",getpid());

    if((valSon=(ValPartage*)shmat(shmid, NULL, 0)) < 0){
        error("Attache segment memoire partage", ERR_ATT);
    }
    for(i=0; i < nbre; i++){
        valSon->cpt+=1;
        printVal("incremente % d\n", valSon->cpt);
    }
    printf("je vais ecrire un reel 125.5 que mon pere va afficher\n") ;
    valSon->valeur = 125.5;
    /* on arrete le fils pour ne pas qu'il execute le code du pere,
     car ce code est duplique a la creation du fils */
    printf("Bon, proc_fils il est temps de mourrir\n"
        "avant tout detachons le segment partagee\n");
    if(shmdt(valSon) < 0){
        error("detachement impossible", ERR_DET);
    }
    printf("Le fils se suicide\n");
    exit(EXIT_FILS);
}

void decremente(int nbre, int shmid){
    int i=0;
    ValPartage* valFather=NULL;
    printf("Je suis le pere, je decremente le compteur\n"
        "Je commence par m'attacher le segment de memoire\n");

    if((valFather=(ValPartage*)shmat(shmid, NULL, 0)) < 0){
        error("Attache segment memoire partage", ERR_ATT);
    }
    for(i=0;i < nbre; i++){
        valFather->cpt-=1;
        printVal("decremente % d\n", valFather->cpt);
    }

    printf("je vais afficher un reel que mon fils a ecrit\n"
        "valeur lut par le pere = %f\n"
        "Bon, proc_pere il est temps de mourrir\n"
        "avant tout detachons le segment partagee\n", valFather->valeur);

    if(shmdt(valFather) < 0){
        error("detachement impossible", ERR_DET);
    }
}

int main(int argc, char *argv[]){
    int iter = 0;
    /* identifiant du segment de memoire partage */
    int shmid;
    if(argc != 2){
        printf("Error :\t ./v4 nber_iteration\n");
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

/*

*/