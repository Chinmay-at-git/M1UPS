#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ERR_CREAT_FILS -1
#define EXIT_FILS 1

void error(char *msg, int status){
    perror(msg);
    exit(status);
}
void printVal(char *msg, int *val){
    fprintf(stdout, msg, val);
}

/*variante 2:
Le compteur est declare en tant que variable globale
on constate que les deux processus travaillent separemement, la varibale compteur n'est pas partage
*/
int *cpt;
void incrementeV1(int nbre){
    int i=0;
    for(i=0; i < nbre; i++){
        cpt++;
        printVal("incrementeV1 % d\n", cpt);
    }
    /* on arrete le fils pour ne pas qu'il execute le code du pere,
     car ce code est duplique a la creation du fils */
    exit(EXIT_FILS);
}

void decrementeV1(int nbre){
    int i=0;
    for(i=0;i < nbre; i++){
        cpt--;
        printVal("decrementeV1 % d\n", cpt);
    }
}

int main(int argc, char *argv[]){
    int iter=0;
    if(argc != 2){
        error("Le nombre d'iteration n'est pas renseigne", EXIT_FAILURE);
    }
    iter = atoi(argv[1]);
    /* creation des processus */
    switch(fork()){
        case -1 : error("Creation fils", ERR_CREAT_FILS);
        case 0 :
            /* on est dans le fils */
            incrementeV1(iter);
        default : break;
    }
    decrementeV1(iter);
    return 0;
}
