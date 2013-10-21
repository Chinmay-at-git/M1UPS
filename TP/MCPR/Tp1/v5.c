#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "constante.h"

extern ValPartage *valeurP;
extern key_t cle;

void error(char *msg, int status){
    perror(msg);
    exit(status);
}
void printVal(char *msg, int *val){
    fprintf(stdout, msg, *val);
}

/*variante 5:
Les processus n'ont aucun lien de parente et partagent deux informations contenu dans valeurP
*/
void incrementeV(int nbre){
    int i=0;
    init_seg_partage();
    for(i=0; i < nbre; i++){
       valeurP->cpt+=1;
       printVal("incrementeV % d\n", &(valeurP->cpt));
    }
    printf("Valeur double partage fils avant % f\n", valeurP->valeur);
    valeurP->valeur += 5.5;
    printf("Valeur double partage modifie fils apres +5.5 % f\n", valeurP->valeur);
}

void decrementeV(int nbre){
    int i=0;
    init_seg_partage();
    for(i=0;i < nbre; i++){
        valeurP->cpt-=1;
        printVal("decrementeV % d\n", &(valeurP->cpt));
    }
    printf("Valeur double partage affiche par le pere % f\n", valeurP->valeur);
}

int main(int argc, char *argv[]){
    int iter=0;
    int choice;
    if(argc != 3){
        error("V4 nbre_iter [0-1 (0=fils, 1=pere)]", EXIT_FAILURE);
    }
    iter = atoi(argv[1]);
    /* Qui fait quoi */
    choice = atoi(argv[2]);
    switch(choice){
        case 0 :
            incrementeV(iter);
            break;
        case 1 : 
            decrementeV(iter);
            break;
    }
    return 0;
}
