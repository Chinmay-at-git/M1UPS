#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>


#define EXIT_FILS 1
#define ERR_CREAT_FILS -1
#define ERR_SEG -2
#define ERR_ATT -3
#define ERR_DET -4

typedef struct{
    int cpt; //compteur
    double valeur; //valeur reelle partage
}ValPartage;

void error(char *msg, int status){
    perror(msg);
    exit(status);
}
void printVal(char *msg, int *val){
    fprintf(stdout, msg, *val);
}

/*variante 4:
Les processus partagent deux informations
*/
ValPartage *valeurP;
void initValeurPartage(ValPartage* val){
    val->cpt = 0;
    val->valeur = 0;
}
void incrementeV(int nbre){
    int i=0;
    for(i=0; i < nbre; i++){
       valeurP->cpt+=1;
       printVal("incrementeV % d\n", &(valeurP->cpt));
    }
    printf("Valeur double partage modifie par le fils +5.5 % f\n", valeurP->valeur);
    valeurP->valeur += 5.5;
    /* on arrete le fils pour ne pas qu'il execute le code du pere,
     car ce code est duplique a la creation du fils */
    exit(EXIT_FILS);
}

void decrementeV(int nbre){
    int i=0;
    for(i=0;i < nbre; i++){
        valeurP->cpt-=1;
        printVal("decrementeV % d\n", &(valeurP->cpt));
    }
    printf("Valeur double partage affiche par le pere % f\n", valeurP->valeur);
}

int main(int argc, char *argv[]){
    int iter=0;
    /* identifiant du segment de memoire partage */
    int id_seg;
    if(argc != 2){
        error("Le nombre d'iteration n'est pas renseigne", EXIT_FAILURE);
    }
    iter = atoi(argv[1]);
    /* creation zone memoire 
    (id_seg = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)
    */
    /*creation d'une cle */
    key_t cle = ftok("key", 0);
    if((id_seg = shmget(cle, sizeof(ValPartage), IPC_CREAT | 0666)) < 0){
        error("Creation segment memoire partage", ERR_SEG);
    }
    /* on attache le segement de memoire partage */
    if((valeurP=(ValPartage*)shmat(id_seg, NULL, 0)) < 0){
        error("Attache segment memoire partage", ERR_ATT);
    }
    initValeurPartage(valeurP);

    /* creation des processus */
    switch(fork()){
        case -1 : error("Creation fils", ERR_CREAT_FILS);
        case 0 :
            /* on est dans le fils */
            incrementeV(iter);
        default : break;
    }
    decrementeV(iter);
    /*on attends la fin des processus */
    wait(NULL);
    /* detacher le segment de memoire */
    shmdt(valeurP);
    /*destruction du segment de memoire */
    shmctl(id_seg, IPC_RMID, NULL);
    return 0;
}
