#ifndef CONSTANT_H
#define CONSTANT_H


#define EXIT_FILS 1
#define ERR_CREAT_FILS -1
#define ERR_SEG -2
#define ERR_ATT -3
#define ERR_DET -4
#define ERR_ALLOC -5
#define ERR_KEY -6

/*
    Diallo Alpha Oumar Binta
    21007631
    Tp MCPR
    Universite Paul Sabatier
    Toulouse III
*/ 

/* Structure utilise pour la variable partagee entre les processus*/
typedef struct{
    int cpt; /*compteur*/
    double valeur; /*valeur reelle partagee*/
}ValPartage;

/**
	Affiche le message d'erreur msg sur la sortie standard et sort
	 du programme avec le code de retour status
*/
void error(char *msg, int status);
/**
	Affiche le message msg et l'entier val sur la sortie standard
*/
void printVal(char *msg, int val);
/**
	Cette fonction  cree un segment de memoire partage, affiche
	l'identificateur du segment et la cle associee.
	Pour finir cette fonction retourne l'identificateur du segment. 
*/
int create_shm(int size, char *name, int cle);
/**
	Cette fonction permet d'afficher toutes les informations
	du segement shmid
*/
void info_shm(int shmid);
/**
	Cette fonction permet de supprimer le segement shmid
*/
void delete_shm(int shmid);

#endif
