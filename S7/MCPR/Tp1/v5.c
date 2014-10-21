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

/*variante 5:
    Ce code ne fait pas ce qu'on lui demande, il peut arriver que le pere 
    affiche le contenu de la memoire avant que le fils n'ait place sa valeur 
    dedans. Il faut se servir d'un sémaphore pour gérer l'ordonnancement des 
    taches. Ne pas oublier de supprimer le segment apres avoir executer le 
    programme (commande ipcrm -m shmid) cmd ipcs==>shmid
*/

void incremente(int nbre, int shmid){
    int i=0;
    ValPartage* p1=NULL;
    printf("Salut, je suis le programme p1, j'incremente le compteur\n"
        "Je commence par m'attacher le segment de memoire\n");
    if((p1=(ValPartage*)shmat(shmid, NULL, 0)) < 0){
        error("Attache segment memoire partage", ERR_ATT);
    }
    
    for(i=0; i < nbre; i++){
        p1->cpt+=1;
        printVal("incremente % d\n", p1->cpt);
    }
    printf("valeur avant= %f\n"
        "je vais ecrire un reel 125.5 que le programme p2 va afficher\n",
         p1->valeur);
    p1->valeur = 125.5;
    printf("Bon, Detachons le segment partagee p1\n");
    if(shmdt(p1) < 0){
       error("detachement impossible", ERR_DET);
    }
}

void decremente(int nbre, int shmid){
    int i=0;
    ValPartage* p2=NULL;
    printf("Je suis le programme p2, je decremente le compteur\n"
        "Je commence par m'attacher le segment de memoire\n");
    if((p2=(ValPartage*)shmat(shmid, NULL, 0)) < 0){
        error("Attache segment memoire partage", ERR_ATT);
    }
    
    for(i=0;i < nbre; i++){
        p2->cpt-=1;
        printVal("decremente % d\n", p2->cpt);
    }
    printf("je vais afficher un reel que le programme p2 a ecrit\n"
        "valeur lut= %f\n"
        "Bon, detachons le segment partagee p2\n", p2->valeur);
    if(shmdt(p2) < 0){
        error("detachement impossible", ERR_DET);
    }
}

int main(int argc, char *argv[]){
    int iter = 0;
    int choice;
    key_t clef;
    /* identifiant du segment de memoire partage */
    int shmid = -1;
    if(argc != 3){
        printf("Error :\t ./v5 nber_iteration [0-1 (0=p1, 1=p2)]\n");
        exit(EXIT_FAILURE);
    }
    iter = atoi(argv[1]);
    /* creation zone memoire */
    clef = ftok("key",1);
    shmid = shmget( clef,
                  100,
                  0644|IPC_CREAT);
    
    /* Qui fait quoi */
    choice = atoi(argv[2]);
    switch(choice){
        case 0 :
            incremente(iter, shmid);
            break;
        case 1 : 
            decremente(iter, shmid);
            break;
    }
    return 0;
}
