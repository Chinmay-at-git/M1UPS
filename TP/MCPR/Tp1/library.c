#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "constante.h"

/* valeur partage */
ValPartage *valeurP;
key_t cle;

void init_var(){
    valeurP = malloc(sizeof(ValPartage));
}
void init_seg_partage(){
    /* identifiant du segment de memoire partage */
    int id_seg;
    /* creation zone memoire */
    /*creation d'une cle, la cle doit etre la meme pour les deux programmes. Les deux programmes utilisent le meme fichier ici key. Le segment de memoire paratage est cree s'il n'existe pas
     */
    cle = ftok("key", 0);
    if((id_seg = shmget(cle, sizeof(ValPartage), IPC_CREAT | 0666)) >= 0){
        init_var();
    }else{
        printf("Creation segment memoire partage");
        exit(ERR_SEG);
    }
    /* on attache le segement de memoire partage */
    if((valeurP=(ValPartage*)shmat(id_seg, NULL, 0)) < 0){
        printf("Attache segment memoire partage");
        exit(ERR_ATT);
    }
}


