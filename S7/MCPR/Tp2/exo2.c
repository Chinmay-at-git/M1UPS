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
 * Exercice 2 : Affichage de message alternee
*/



int main(int argc, char *argv[]){
    int nb_process; /*nbre  de processus */
    int** pidFils = NULL;
    /*identifiant du semaphore*/
    int semid;
    /*opertaion P et V */
    struct sembuf p;
    struct sembuf v;
    int i, j;

    if(argc != 2){
        printf("Error :\t%s nb_process\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    nb_process = atoi(argv[1]);
    pidFils = malloc(nb_process*sizeof(int));
    for(i=0; i < nb_process; i++){
        pidFils[i] = malloc(sizeof(int));
    }
    /*
     * Nous voulons creer un semaphore, IPC_EXCL ==> si un semaphore existe avec
     *  cet identifiant, la creation echoue
     */
    if((semid = semget(IPC_PRIVATE, nb_process, IPC_CREAT | IPC_EXCL | 0666))
        < 0){
        perror("La creation du semaphore a echoue");
        exit(ERR_SEM);
    }

    printf("############### INITIALISATION #############\n");
    /*initialisation du semaphore,
     0 ==> Numéro de notre sémaphore: le premier
     1 ==> mutex un seul programme a acces a la section critique
     */
    semctl(semid, 0, SETVAL, 1);
    for(i = 1; i < nb_process; i++){
        semctl(semid, i, SETVAL, 1);
    }
    /*initialisation des operations P (blocage) et V (reveil)*/
    p.sem_op = -1; p.sem_flg = 0;
    v.sem_op = 1;  v.sem_flg = 0;
    printf("############### CREATION PROCESSUS #############\n");
    for(i = 1; i < nb_process; i++){
        if(semctl(semid, i, SETVAL, 0) < 0){
            printf("erreur init s %d\n", i);
            exit(7);
        }
    }
    for(i = 0; i < nb_process; i++){
        /* creation des processus */
        if((*pidFils[i] = fork()) == 0){
            j = 0;
            while(j < nb_process*2){
                p.sem_num = i; 
                semop(semid, &p, 1);
                printf("Message Fils num %d pid %d sem %d\n", i, getpid(), 
p.sem_num);
                j++;
                v.sem_num = (i+1)%nb_process;
                semop(semid, &v, 1);
            }
            exit(i);
        }
    }


    /*on attends la fin des processus */
    printf("Le pere attend la mort de ses fils\n") ;
    for(i = 0; i < nb_process; i++){
        wait(0);
    }
    printf("########### FINAL ###########\n");
    if(semctl(semid, i, IPC_RMID, 0) < 0){
        perror("Erreur destruction semaphore");
        exit(ERR_SUPPR);
    }
    printf("Semaphore detruit\n");
    free(pidFils);
    return 0;
}

