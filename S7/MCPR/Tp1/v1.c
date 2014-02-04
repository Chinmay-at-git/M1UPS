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

/*variante 1:
    chaque processus declare le compteur localement dans la fonction 
    representant son traitement. On constate que le compteur est 
    incremente par le fils et decrementer par le pere, les valeurs
    sont differentes car il ne s'agit pas du meme compteur.
*/

void incremente(int nbre){
    int cpt=0, i=0;
    printf("Salut, je suis le fils %d, j'incremente le compteur\n",getpid());
    for(i=0; i < nbre; i++){
        cpt++;
        printVal("cpt = %d\n", cpt);
    }
    /* on arrete le fils pour ne pas qu'il execute le code du pere,
     car ce code est duplique a la creation du fils */
    printf("Le fils se suicide\n");
    exit(EXIT_FILS);
}

void decremente(int nbre){
    int cpt=0, i=0;
    printf("Je suis le pere, je decremente le compteur\n") ;
    for(i=0;i < nbre; i++){
        cpt--;
        printVal("cpt = %d\n", cpt);
    }
}

int main(int argc, char *argv[]){
    int iter=0;
    if(argc != 2){
        printf("Error :\t ./v1 nber_iteration\n");
        exit(EXIT_FAILURE);
    }
    iter = atoi(argv[1]);
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
    return 0;
}
/*
oumar@diallopc:~/Bureau/MCPR/Tp1$ ./v1 4
Je suis le pere, je decremente le compteur
cpt = -1
cpt = -2
cpt = -3
cpt = -4
Le pere se suicide
Salut, je suis le fils 3702, j'incremente le compteur
cpt = 1
cpt = 2
cpt = 3
cpt = 4
Le fils se suicide
oumar@diallopc:~/Bureau/MCPR/Tp1$ ./v1 4
Je suis le pere, je decremente le compteur
cpt = -1
Salut, je suis le fils 3704, j'incremente le compteur
cpt = -2
cpt = -3
cpt = -4
Le pere se suicide
cpt = 1
cpt = 2
cpt = 3
cpt = 4
Le fils se suicide
*/
