#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constant.h"

/*
    Auteur : Diallo Alpha Oumar Binta
    Numéro étudiant : 21007631
    Groupe 3.2
    Annee scolaire : 2013-2014
    Controle continu numero OIM
*/
/**
    initIterator
    Entree : iter un iterateur
    Intialise les champs de l'iterateur
*/
void initIterator(Iterator* iter){
    iter->i = 0;
    iter->j = 0;
    iter->state = 1;
}
/**
  iteratorHasNext
  Entree : un iterateur
  Sortie :
    1 s'il esciste une élément suivant
    0 sinon
*/
int iteratorHasNext(Iterator iter){
    return (iter.i <= (BLOCKSIZE-1) && iter.j <= (BLOCKSIZE-1));
}
/**
  blocIteratorNext
  Entree : un iterateur iter
  Retourne dans iter la prochaine iteration suivant le parcours
  defini sur le schema zigzag
*/
void blocIteratorNext(Iterator* iter){
    iter->j += iter->state;
	iter->i -= iter->state;
	if(iter->j > (BLOCKSIZE-1)) {
		iter->j = (BLOCKSIZE-1);
		iter->i += 2;
	}else if(iter->i > (BLOCKSIZE-1)) {
		iter->i = (BLOCKSIZE-1);
		iter->j += 2;
	}else if(iter->j < 0){
        //ne pas sortir du bloc
        iter->j = 0;
	}else if(iter->i < 0){
        //ne pas sortir du bloc
        iter->i = 0;
	}else{
	    //pas de changement d'etat
	    return;
	}
    //changement d'etat
    iter->state *= -1;
}
/**
    bloc2Vector
    Entree : _bloc un bloc de pixel de taille BLOCKSIZE*BLOCKSIZE
             _vector un vecteur de taille BLOCKSIZE*BLOCKSIZE
    Retourne dans vector les valeurs du bloc de pixel dans le sens
    de parcours zigzag
*/
void bloc2Vector(Bloc _bloc, Vector _vector){
    Iterator iter;
     int i=0;
    initIterator(&iter);
    do{
        _vector[i] = _bloc[iter.i][iter.j];
        blocIteratorNext(&iter);
        i++;
    }while(iteratorHasNext(iter));
}
/**
 *  putInVect
    Entree : _vector un vecteur de taille BLOCKSIZE*BLOCKSIZE
             lbPicture le vecteur lineaire de l'image
             offset  indice de depart
    Recopie dans lbPicture les valeurs du vecteur à partir de offset
 */
void putInVect(Vector _vector, LinearBlocPicture lbPicture, int offset){
    int z=0;
    do{
        lbPicture[offset+z] = _vector[z];
        z++;
    }while(z != (BLOCKSIZE*BLOCKSIZE));
    
}
/**
    picture2BlocVector
    Entree : picture une image de type Picture
             lbPicture une image de type LinearBlocPicture
    Retourne dans lbPicture l'image de type LinearBlocPicture de picture
*/
void picture2BlocVector(Picture picture, LinearBlocPicture lbPicture){
    int i,j, nbBlock=0, offset=0, k, l;
    Bloc _bloc;
    Vector _vector;
    //parcours de l'image
    for(i=0; i<PICTURESIZE; i+=BLOCKSIZE){
        for(j=0; j< PICTURESIZE; j+=BLOCKSIZE){
            //creation d'un bloc
            for(k=0; k < BLOCKSIZE; k++)
                for(l=0; l< BLOCKSIZE; l++){
                    _bloc[k][l] = picture[i+k][j+l];
                }
        }
        nbBlock++;
        //transfromation du bloc en vecteur
        bloc2Vector(_bloc, _vector);
        //copie du vecteur dans l'image de type lineaire
        putInVect(_vector, lbPicture,offset);
        offset+=(BLOCKSIZE*BLOCKSIZE);
    }
    printf("Test picture2BlocVector, Il y a %d blocs parcouru\n", nbBlock);
}

void testParcoursZigZag(){
    Bloc bloc;
    Vector _vector;
    int z=0;
    bloc[0][0]=16;
    bloc[0][1]=11;
    bloc[0][2]=10;
    bloc[0][3]=16;
    bloc[0][4]=24;
    bloc[0][5]=40;
    bloc[0][6]=51;
    bloc[0][7]=61;

    bloc[1][0]=12;
    bloc[1][1]=12;
    bloc[1][2]=14;
    bloc[1][3]=19;
    bloc[1][4]=26;
    bloc[1][5]=58;
    bloc[1][6]=60;
    bloc[1][7]=55;

    bloc[2][0]=14;
    bloc[2][1]=13;
    bloc[2][2]=16;
    bloc[2][3]=24;
    bloc[2][4]=40;
    bloc[2][5]=57;
    bloc[2][6]=69;
    bloc[2][7]=56;

    bloc[3][0]=14;
    bloc[3][1]=17;
    bloc[3][2]=22;
    bloc[3][3]=29;
    bloc[3][4]=51;
    bloc[3][5]=87;
    bloc[3][6]=80;
    bloc[3][7]=62;

    bloc[4][0]=18;
    bloc[4][1]=22;
    bloc[4][2]=37;
    bloc[4][3]=56;
    bloc[4][4]=68;
    bloc[4][5]=109;
    bloc[4][6]=103;
    bloc[4][7]=77;

    bloc[5][0]=24;
    bloc[5][1]=35;
    bloc[5][2]=55;
    bloc[5][3]=64;
    bloc[5][4]=81;
    bloc[5][5]=104;
    bloc[5][6]=113;
    bloc[5][7]=92;

    bloc[6][0]=49;
    bloc[6][1]=64;
    bloc[6][2]=78;
    bloc[6][3]=87;
    bloc[6][4]=103;
    bloc[6][5]=121;
    bloc[6][6]=120;
    bloc[6][7]=101;

    bloc[7][0]=72;
    bloc[7][1]=92;
    bloc[7][2]=95;
    bloc[7][3]=98;
    bloc[7][4]=112;
    bloc[7][5]=100;
    bloc[7][6]=103;
    bloc[7][7]=99;
    printf("Test parcours zigzag");
    printBloc(bloc);
    bloc2Vector(bloc, _vector);
    printf("Valeur du vecteur apres parcours zigzag\n");
    do{
        printf("%d, ", _vector[z]);
        z++;
    }while(z != (BLOCKSIZE*BLOCKSIZE));
    printf("\n");
}
/**
 * Affiche le contenu du Bloc bloc
 */
void printBloc (Bloc bloc) {
    int i, j ;
    printf ("\nContenu du bloc\n\n   ") ;
    for (i=0; i<BLOCKSIZE; i++) {
        for (j=0; j<BLOCKSIZE; j++) {
            printf ("\t%d", bloc[i][j]) ;
        }
        printf ("\n") ;
    }
    printf ("\n") ;
}


int main(int argc, char *argv[]) {
    Picture picture;
    LinearBlocPicture lbPicture;
    testParcoursZigZag();
    picture2BlocVector( picture,  lbPicture);    
  return 0;
}
