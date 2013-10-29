#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "constante.h"

/*
    Diallo Alpha Oumar Binta
    21007631
    Tp MCPR
    Universite Paul Sabatier
    Toulouse III
*/  

/*variante 2:
    Le compteur est declare en tant que variable globale
    on constate que les deux processus travaillent separemement,
    la variabale compteur n'est pas partagee (ex: en affectant au compteur une 
    valeur, on ne trouve pas la meme incremente ou decremente dans le 
    processus suivant)
*/

int *cpt;

void incremente(int nbre){
    int i=0;
    printf("Salut, je suis le fils %d, j'incremente le compteur\n",getpid());
    *cpt = 12;
    for(i=0; i < nbre; i++){
        *cpt+=1;
        printVal("cpt = %d\n", *cpt);
    }
    /* on arrete le fils pour ne pas qu'il execute le code du pere,
     car ce code est duplique a la creation du fils */
    printf("Le fils se suicide\n");
    exit(EXIT_FILS);
}

void decremente(int nbre){
    int i=0;
    printf("Je suis le pere, je decremente le compteur\n") ;
    for(i=0;i < nbre; i++){
        *cpt-=1;
        printVal("cpt = %d\n", *cpt);
    }
}

int main(int argc, char *argv[]){
    int iter=0;
    if(argc != 2){
        printf("Error :\t ./v2 nber_iteration\n");
        exit(EXIT_FAILURE);
    }
    iter = atoi(argv[1]);
    /*initialisation de la variable */
    if((cpt = malloc(sizeof(int*))) == NULL){
        error("Allocation memoire cpt", ERR_ALLOC);
    }
    
    /* creation des processus */
    switch(fork()){
        case -1 : error("Creation fils", ERR_CREAT_FILS);
        case 0 :
            /* on est dans le fils */
            incremente(iter);
        default : break;
    }
    decremente(iter);
    printf("Le pere se suicide\n");
    /* on libere la memoire, tout malloc son free */
    free(cpt);
    return 0;
}

/*
oumar@diallopc:~/Bureau/MCPR/Tp1$ ./v2 4
Je suis le pere, je decremente le compteur
cpt = -1
cpt = -2
cpt = -3
cpt = -4
Salut, je suis le fils 4942, j'incremente le compteur
Le pere se suicide
cpt = 1
cpt = 2
cpt = 3
cpt = 4
Le fils se suicide
oumar@diallopc:~/Bureau/MCPR/Tp1$ make v2
gcc -Wall v2.c  library.c -o v2
oumar@diallopc:~/Bureau/MCPR/Tp1$ ./v2 4
Je suis le pere, je decremente le compteur
cpt = -1
cpt = -2
cpt = -3
cpt = -4
Le pere se suicide
Salut, je suis le fils 4964, j'incremente le compteur
cpt = 13
cpt = 14
cpt = 15
cpt = 16
Le fils se suicide
*/