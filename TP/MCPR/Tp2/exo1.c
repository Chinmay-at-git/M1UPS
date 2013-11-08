#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define EXIT_FILS 1
#define ERR_CREAT_FILS -1
#define ERR_SEG -2
#define ERR_ATT -3
#define ERR_DET -4
#define ERR_ALLOC -5
#define ERR_KEY -6
#define ERR_SEM -7
#define ERR_SUPPR -8
#define ID_PROJET 'R'

/*
    Diallo Alpha Oumar Binta
    21007631
    Tp MCPR
    Universite Paul Sabatier
    Toulouse III
*/ 

/*
 * Exercice 1
*/

/* Structure utilise pour la variable partage entre les processus*/
typedef struct{
    int cpt; /*compteur*/
    double valeur; /*valeur reelle partage*/
}ValPartage;

int main(int argc, char *argv[]){
    int nb_iter, pid; /*nbre  d'iterattion */
    /*identifiant segment de memoire partagee et du semaphore*/
    int shmid, semid;
    /*la clef associee au segment*/
    key_t clef;
    /*opertaion P et V */
    struct sembuf p;
    struct sembuf v;
    /* variable */
    ValPartage *varOr = NULL;
    ValPartage *varFils = NULL;
    ValPartage *varPere = NULL;
    int i,j;

    /*test des parametres en entree*/
    if(argc != 2){
        printf("Error :\t%s nb_iteration\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    nb_iter = atoi(argv[1]);
    /* L'instruction ftok(name,(key_t) cle) permet de construire 
        une cle identifiant le segment */
    if((clef = ftok("shm_key", ID_PROJET)) < 0){
        perror("La creation de la clef a echouee");
        exit(ERR_KEY);
    }
    /* creation zone memoire et du semaphore */
    if((shmid = shmget( clef,
                  100,
                  IPC_CREAT|IPC_EXCL|SHM_R|SHM_W )) < 0){
        perror("La creation du segment de memoire partage a echouee");
        exit(ERR_SEG);
    }
    /*
     * Nous voulons creer un semaphore, IPC_EXCL ==> si un semaphore existe avec
     *  cet identifiant, la creation echoue
     */
    if((semid = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0666)) < 0){
        perror("La creation du semaphore a echoue");
        exit(ERR_SEM);
    }
    if((varOr = shmat(shmid, NULL, 0)) < 0){
        perror("Attache segment memoire partage varOr");
        exit(ERR_ATT);
    }
    
    printf("############### INITIALISATION #############\n");
    printf("Identificateur du segment %d \n", shmid);
    printf("Identificateur du semaphore %d \n", semid);
    printf("Segment associe a la clef %d \n", clef);
    printf("Compteur initial varOr\n");
    printf("** varOr->cpt = %d\n", varOr->cpt);
    printf("** varOr->valeur = %f\n", varOr->valeur);
    /*initialisation du semaphore,
     0 ==> Numéro de notre sémaphore: le premier et le seul
     1 ==> mutex un seul programme a acces a la section critique
     */
    semctl(semid, 0, SETVAL, 1);
    /*initialisation des operations P (blocage) et V (reveil)*/
    p.sem_num = 0; p.sem_op = -1; p.sem_flg = 0;
    v.sem_num = 0; v.sem_op = 1;  v.sem_flg = 0;


    /* creation des processus */
    if((pid = fork()) == 0){
        /* on est dans le fils */
        printf("########### FILS ###########\n");
        if((varFils = shmat(shmid, NULL, 0)) < 0){
            perror("Attache segment memoire partage varFils");
            exit(ERR_ATT);
        }
        for(i = 0; i < nb_iter; i++){
            semop(semid, &p, 1);
            varFils->cpt += 1;
            semop(semid, &v, 1);
        }
        printf("** varFils->cpt = %d\n", varFils->cpt);
        printf("\tLe fils affiche %f\n", varFils->valeur);
        if(shmdt(varFils) < 0){
            perror("Fils detachement impossible");
            exit(ERR_DET);
        }
        exit(0);
    }else{
        /*on est dans le pere */
        printf("########### PERE ###########\n");
        if((varPere = shmat(shmid, NULL, 0)) < 0){
            perror("Attache segment memoire partage varPere");
            exit(ERR_ATT);
        }
        for(j = 0; j < nb_iter; j++){
            semop(semid, &p, 1);
            varPere->cpt -= 1;
            varPere->valeur += 2.5;
            semop(semid, &v, 1);
        }
        printf("** varPere->cpt = %d\n", varPere->cpt);
        printf("\tLe pere ecrit %f\n", varPere->valeur);
        if(shmdt(varPere) < 0){
            perror("Pere detachement impossible");
            exit(ERR_DET);
        }
    }
    /*on attends la fin des processus */
    printf("Le pere attend la mort de son fils\n") ;
    wait(0);
    printf("########### FINAL ###########\n");
    printf("** varOr->cpt = %d\n", varOr->cpt);
    printf("** varOr->valeur = %f\n", varOr->valeur);
    if(shmdt(varOr) < 0){
        perror("varOr initial detachement impossible");
        exit(ERR_DET);
    }
    printf("Bon, faisons le menage et supprimons le segment partagee\n") ;
    /*destruction du segment de memoire */
    if(shmctl(shmid,IPC_RMID,NULL) < 0){
        perror("Erreur destruction segment");
        exit(ERR_SUPPR);
    }
    if(semctl(semid, 0, IPC_RMID, 0) < 0){
        perror("Erreur destruction semaphore");
        exit(ERR_SUPPR);
    }
    return 0;
}

