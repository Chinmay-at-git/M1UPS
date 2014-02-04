#ifndef CONSTANT_H
#define CONSTANT_H


#define PICTURESIZE 1024
#define BLOCKSIZE 8
typedef unsigned char Picture[PICTURESIZE][PICTURESIZE];
typedef unsigned char LinearBlocPicture[PICTURESIZE*PICTURESIZE];
typedef unsigned char Bloc[BLOCKSIZE][BLOCKSIZE];
typedef unsigned char Vector[BLOCKSIZE*BLOCKSIZE];

typedef struct{
    int i; //indice de ligne
    int j; //indice de colonne
    int state; //etat, position
}Iterator;


/*
    Auteur : Diallo Alpha Oumar Binta
    Numéro étudiant : 21007631
    Groupe 3.2
    Annee scolaire : 2013-2014
    Controle continu numero OIM
*/
/**
  affiche le message d'erreur et quitte le programme avec le code de retour
  indiqué
*/
void error(char *msg, int status);
/**
  iteratorHasNext
  Entree : un iterateur
  Sortie :
    1 s'il esciste une élément suivant
    0 sinon
*/
int iteratorHasNext(Iterator iter);
/**
    initIterator
    Entree : iter un iterateur
    Intialise les champs de l'iterateur
*/
void initIterator(Iterator* iter);
/**
  blocIteratorNext
  Entree : un iterateur iter
  Retourne dans iter la prochaine iteration suivant le parcours
  defini sur le schema zigzag
*/
void blocIteratorNext(Iterator* iter);
/**
    bloc2Vector
    Entree : bloc un bloc de pixel de taille BLOCKSIZE*BLOCKSIZE
             vecteur un vecteur de taille BLOCKSIZE*BLOCKSIZE
    Retourne dans vector les valeurs du bloc de pixel dans le sens
    de parcours zigzag
*/
void bloc2Vector(Bloc _bloc, Vector _vector);
/**
    picture2BlocVector
    Entree : picture une image de type Picture
             lbPicture une image de type LinearBlocPicture
    Retourne dans lbPicture l'image de type LinearBlocPicture de picture
*/
void picture2BlocVector(Picture picture, LinearBlocPicture lbPicture);
/**
 *  putInVect
    Entree : _vector un vecteur de taille BLOCKSIZE*BLOCKSIZE
             lbPicture le vecteur lineaire de l'image
             offset  indice de depart
    Recopie dans lbPicture les valeurs du vecteur à partir de offset
 */
void putInVect(Vector _vector, LinearBlocPicture lbPicture, int offset);
/**
 * Affiche le contenu du Bloc bloc
 */
void printBloc (Bloc bloc);
#endif
