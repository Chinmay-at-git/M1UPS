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
    ce dernier doit etre attache au segment grace a la primitive shmat().
    La fonction shmat retourne l'adresse du segment de memoire partagee.
    La primitive shmdt() permet au processus de se detacher du segment.
    Il n'y a pas copie de zone memoire mais redirection de l'adressage 
    vers le segment partage.
    Le compteur est partage entre le pere et le fils, mais il n'existe aucun 
    ordonnancement (le pere peut ecrire dans la variable compteur avant le fils 
    et vice versa)
*/
void incremente(int nbre, int shmid){
    int i = 0;
    int* cptSon = NULL;
    printf("Salut, je suis le fils %d, j'incremente le compteur\n"
        "Je commence par m'attacher le segment de memoire\n", getpid());

    if((cptSon = (int*)shmat(shmid, NULL, 0)) < 0){
        error("Attache segment memoire partage", ERR_ATT);
    }
    for(i = 0; i < nbre; i++){
       *cptSon += 1;
        printVal("incremente % d\n", *cptSon);
    }
    /* on arrete le fils pour ne pas qu'il execute le code du pere,
     car ce code est duplique a la creation du fils */
    printf("Bon, process_fils il est temps de mourrir\n"
        "avant tout detachons le segment partage\n");
    if(shmdt(cptSon) < 0){
        error("detachement impossible", ERR_DET);
    }
    printf("Le fils se suicide\n");
    exit(EXIT_FILS);
}

void decremente(int nbre, int shmid){
    int i = 0;
    int* cptFather = NULL;
    printf("Je suis le pere, je decremente le compteur\n"
        "Je commence par m'attacher le segment de memoire\n");

    if((cptFather = (int*)shmat(shmid, NULL, 0)) < 0){
        error("Attache segment memoire partage", ERR_ATT);
    }
    for(i = 0;i < nbre; i++){
        *cptFather-=1;
        printVal("decremente % d\n", *cptFather);
    }
    printf("Bon, process_pere il est temps de mourrir\n"
        "avant tout detachons le segment partage\n");
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
    printf("Faisons le menage et supprimons le segment partage\n") ;
    /*destruction du segment de memoire */
    delete_shm(shmid);
    printf("Le pere se suicide\n") ;
    return 0;
}
/*
oumar@diallopc:~/Bureau/MCPR/Tp1$ ./v3 4
l'identificateur du segment est 5898259 
ce segment est associe a la clef 16843535 
Je suis le pere, je decremente le compteur
Je commence par m'attacher le segment de memoire
Salut, je suis le fils 6959, j'incremente le compteur
Je commence par m'attacher le segment de memoire
incremente  0
decremente -1
decremente -1
decremente -2
incremente -1
incremente -1
decremente -2
incremente  0
Bon, process_pere il est temps de mourrir
Bon, process_fils il est temps de mourrir
avant tout detachons le segment partage
Le pere attend la mort de son fils
avant tout detachons le segment partage
Le fils se suicide
Faisons le menage et supprimons le segment partage
Le pere se suicide

oumar@diallopc:~/Bureau/MCPR/Tp1$ ./v3 4
l'identificateur du segment est 6029331 
ce segment est associe a la clef 16843535 
Je suis le pere, je decremente le compteur
Je commence par m'attacher le segment de memoire
Salut, je suis le fils 6967, j'incremente le compteur
Je commence par m'attacher le segment de memoire
decremente  0
decremente -1
decremente -2
decremente -3
Bon, process_pere il est temps de mourrir
avant tout detachons le segment partage
Le pere attend la mort de son fils
incremente  1
incremente -2
incremente -1
incremente  0
Bon, process_fils il est temps de mourrir
avant tout detachons le segment partage
Le fils se suicide
Faisons le menage et supprimons le segment partage
Le pere se suicide
*/
