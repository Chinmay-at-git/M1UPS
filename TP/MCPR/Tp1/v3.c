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

void error(char *msg, int status){
    perror(msg);
    exit(status);
}
void printVal(char *msg, int *val){
    fprintf(stdout, msg, *val);
}

/*variante 3:
Utilisons un segment de memoire paratge
*/
int *cpt;
void incrementeV1(int nbre){
    int i=0;
    for(i=0; i < nbre; i++){
       *cpt+=1;
        printVal("incrementeV1 % d\n", cpt);
    }
    /* on arrete le fils pour ne pas qu'il execute le code du pere,
     car ce code est duplique a la creation du fils */
    exit(EXIT_FILS);
}

void decrementeV1(int nbre){
    int i=0;
    for(i=0;i < nbre; i++){
        *cpt-=1;
        printVal("decrementeV1 % d\n", cpt);
    }
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
    key_t cle = ftok("/dev/null", 0);
    if((id_seg = shmget(cle, sizeof(int), IPC_CREAT | 0666)) < 0){
        error("Creation segment memoire partage", ERR_SEG);
    }
    /* on attache le segement de memoire partage */
    if((cpt=(int*)shmat(id_seg, NULL, 0)) < 0){
        error("Attache segment memoire partage", ERR_ATT);
    }
    *cpt =0;

    /* creation des processus */
    switch(fork()){
        case -1 : error("Creation fils", ERR_CREAT_FILS);
        case 0 :
            /* on est dans le fils */
            incrementeV1(iter);
        default : break;
    }
    decrementeV1(iter);
    /*on attends la fin des processus */
    wait(NULL);
    /* detacher le segment de memoire */
    shmdt(cpt);
    /*destruction du segment de memoire */
    shmctl(id_seg, IPC_RMID, NULL);
    return 0;
}
