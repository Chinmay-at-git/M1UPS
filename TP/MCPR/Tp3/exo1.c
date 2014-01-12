#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/sem.h>

#define N 15;
#define T 10;

struct sembuf * p;
struct sembuf * v;

typedef struct _Message
{
        int type;
        char * value;
} Message;

void initSemOperation(int nb);
void freeSemOperation();
void createMessages(Message * msg, int value, int n);
void deleteMessages(Message * msg, int n);


int main(int argc, char const *argv[])
{
        if( argc < 3) 
        {
                printf("Usage : %s [Nb_Producteurs] [Nb_Consomateur]\n", argv[0]);
                exit(1);
        }
        int nbProd = atoi(argv[1]);
        int nbCons = atoi(argv[2]);
        int nbType = T;
        int n = N;
        int i;


//creation des variables partagees

// tableau message
        int semidMessage = shmget( ftok("varPartage/message",1), (sizeof(Message) * n), IPC_CREAT | 0666 );
        int semidValue = shmget( ftok("varPartage/value",1), (sizeof(char) * n * 32), IPC_CREAT | 0666 );
        Message * msgs = shmat(semidMessage, NULL,0);
        createMessages(msgs, semidValue, n);
        shmdt(msgs);
// nombre message écris
        int semidNb = shmget( ftok("varPartage/nb",1), sizeof(int), IPC_CREAT | 0666 );
        int * nbMessage = shmat(semidNb, NULL, 0);
        *nbMessage = 0;
        shmdt(nbMessage);
// l'indice d'écriture
        int semidIE = shmget( ftok("varPartage/ie",1), sizeof(int), IPC_CREAT | 0666 );
        int * indice = shmat(semidIE, NULL, 0);
        *indice = 0;
        shmdt(indice);
// l'indice de lecture
        int semidIL = shmget( ftok("varPartage/il",1), sizeof(int), IPC_CREAT | 0666 );
        indice = shmat(semidIL, NULL, 0);
        *indice = 0;
        shmdt(indice);

//creation des semaphores

        initSemOperation(n);
// sémaphore pour l'ecriture
        int semidWrite = semget(ftok("sem/keyMess",1), n, IPC_CREAT | 0666);
        for (i = 0; i < n; ++i)
                semctl(semidWrite, i, SETVAL, 1);
// semaphore pour le type message
        int semidType = semget(ftok("sem/type",1), nbType, IPC_CREAT | 0666);
        for (i = 0; i < nbType; ++i)
                semctl(semidType, i, SETVAL, 0);
// sémaphore sur les variables
        int semidCount = semget(ftok("sem/keyMem",1), 1, IPC_CREAT | 0666);
        semctl(semidCount, 0, SETVAL, 1);
        int semidSIE = semget(ftok("sem/ie",1), 1, IPC_CREAT | 0666);
        semctl(semidSIE, 0, SETVAL, 1);
        int semidSIL = semget(ftok("sem/il",1), 1, IPC_CREAT | 0666);
        semctl(semidSIL, 0, SETVAL, 1);
// sémaphore sur les producteurs
        int semidProd = semget(ftok("sem/keyProd",1), 1, IPC_CREAT | 0666);
        semctl(semidProd, 0, SETVAL, n);
// sémaphore sur les consommateurs
        int semidCons = semget(ftok("sem/keyCons",1), 1, IPC_CREAT | 0666);
        semctl(semidCons, 0, SETVAL, 0);
//producteurs

        for (i = 0; i < nbProd; ++i)
        {
                if( fork() == 0)
                {
                        Message * m = shmat(semidMessage, NULL,0);

                        int * nb = shmat(semidNb, NULL, 0);
                        int * ie = shmat(semidIE, NULL, 0);
                        int mt = i%nbType;
                        int j;
                        for (j = 0; j < n; ++j)
                        {
                                semop(semidProd, &p[0], 1);                
                                semop(semidSIE, &p[0], 1);
                                {
                                        int ind = *ie;
                                        semop(semidWrite, &p[ind], 1);
                                        {
                                                sprintf(m[ind].value,"%d - Message - %d - %d", i, ind, mt);
                                                printf("PROD %d - %s\n", i, m[ind].value );
                                                m[ind].type = mt;
                                                *ie = (ind + 1) % n;
                                        }
                                        semop(semidWrite, &v[ind], 1);
                                }
                                semop(semidSIE, &v[0], 1);
                                semop(semidCount, &p[0], 1);
                                {
                                        if( *nb == 0 )
                                                semop(semidType, &v[mt], 1);
                                        *nb = *nb + 1;
                                }
                                semop(semidCount, &v[0], 1);
                                semop(semidCons, &v[0], 1);
                        }
                        shmdt(m);
                        shmdt(nb);
                        shmdt(ie);
                        exit(0);
                }
        }
//les consommateurs
        for (i = 0; i < nbCons; ++i)
        {
                if( fork() == 0)
                {
                        Message * m = shmat(semidMessage, NULL,0);
                        int * nb = shmat(semidNb, NULL, 0);
                        int * il = shmat(semidIL, NULL, 0);
                        int mt = i%nbType;
                        int j;

                        for (j = 0; j < n; ++j)
                        {
                                semop(semidCons, &p[0], 1);
                                semop(semidType, &p[mt], 1);
                                semop(semidSIL, &p[0], 1);
                                {
                                        int indice = *il;
                                        printf("\tCONS %d - %s\n", i, m[indice].value );
                                        *il = (indice +1) % n;
                                        semop(semidType, &v[(*il+1)%nbType], 1);

                                }
                                semop(semidSIL, &v[0], 1);

                                semop(semidCount, &p[0], 1);
                                {
                                        *nb = *nb - 1;
                                }
                                semop(semidCount, &v[0], 1);
                                semop(semidProd, &v[0], 1);
                        }
                        shmdt(m);
                        shmdt(nb);
                        shmdt(il);
                        exit(0);
                }
        }



        for(i=0; i < nbCons+nbProd; ++i)
                wait(0);

        semctl(semidWrite, 0, IPC_RMID, 0);
        semctl(semidCount, 0, IPC_RMID, 0);
        semctl(semidProd, 0, IPC_RMID, 0);
        semctl(semidCons, 0, IPC_RMID, 0);
        freeSemOperation();

        shmctl(semidMessage, IPC_RMID, NULL);
        shmctl(semidValue, IPC_RMID, NULL);
        shmctl(semidNb, IPC_RMID, NULL);
        shmctl(semidIE, IPC_RMID, NULL);
        shmctl(semidIL, IPC_RMID, NULL);

        return 0;
}


void initSemOperation(int nb)
{
        p = malloc(sizeof(struct sembuf)*nb);
        v = malloc(sizeof(struct sembuf)*nb);
        int i;
        for (i = 0; i < nb; ++i)
        {
                p[i].sem_num = i; p[i].sem_op = -1; p[i].sem_flg = 0;
                v[i].sem_num = i; v[i].sem_op = 1; v[i].sem_flg = 0;
        }
}

void freeSemOperation()
{
        free(p);
        free(v);
}

void createMessages(Message * msg, int value, int n)
{
        char * values = shmat(value, NULL,0);
        int i;
        for (i = 0; i < n; ++i)
        {
                msg[i].value = values + (32*i);
                sprintf(msg[i].value, "message %d", i);
                msg[i].type = 0;
        }
}

void deleteMessages(Message * msg, int n)
{
        int i;
        for (i = 0; i < n; ++i)
                free(msg[i].value);
        free(msg);
}