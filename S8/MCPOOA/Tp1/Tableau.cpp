#include "Tableau.h"
#include "Entree.h"
#include <string>
using namespace std;

Tableau::Tableau(int v_taille, int v_elem) : taille(v_taille), nbelem(v_elem), entree(0){
	entree = new Entree[taille];
	testAllocation();
}

Tableau::~Tableau(void){
	if(entree != NULL)
		delete[] entree;
}

Tableau::Tableau(const Tableau& copie){
	taille = copie.taille;
	nbelem = copie.nbelem;
	entree = new Entree[taille];
	testAllocation();
	recopier(copie);
}

ostream& Tableau::afficher(ostream& out){
	out << "\nLenght -> " << taille << "\tNbElem -> " << nbelem << endl;
	if(taille == 0 || nbelem == 0)
		out << "Empty" << endl;
	else
		for (int j=0; j < nbelem; j++) 
			entree[j].afficher(out);
	return out;
}

void Tableau::ajouter(string nom, string numero){
	if (nbelem < taille){
		entree[nbelem] = Entree(nom, numero);
		nbelem++;
	}else{
		Tableau temp(*(this));
		delete[] entree;
		taille+=1;
		entree = new Entree[taille];
		testAllocation();
		recopier(temp);
		entree[nbelem] = Entree(nom, numero);
		nbelem++;
	}
}
/*
On va utiliser un indice j qui sera l'indice dans le tableau où doit être mis le prochain élément
différent de l'entree à supprimer. Cet élément est initialisé à vide (Entree()).
On parcourt une seule fois le tableau et on place les valeurs différentes de l'entree dans la case
numéro j du tableau en incrémentant à chaque fois j de 1.
*/
//suppression et tassement
void Tableau::supprimer(std::string nom, std::string numero)
{
	int i, j(0), tmp(nbelem);
	if(entree == 0 || nbelem == 0){
        cout << "Empty !" << endl;
        return;
    }
	for(i=0 ; i<nbelem ; i++)
		if (entree[i].nom == nom && entree[i].numTel == numero) {
			tmp--;
		}else{
			entree[j] = entree[i];
			j++;
		}
	for(i=j ; i < nbelem ; i++)
		entree[i] = Entree();
	nbelem=tmp;
}
//suppression et tassement
void Tableau::supprimer(std::string nom)
{
    int i, j(0), tmp;
	if(entree == 0 || nbelem == 0){
        cout << "Empty !" << endl;
        return;
    }
	for(i=0 ; i<nbelem ; i++)
		if (entree[i].nom != nom) {
			entree[j] = entree[i];
			j++;
		}
	tmp=j;
	for(i=j ; i < nbelem ; i++)
		entree[i] = Entree();
	nbelem=tmp;
}
void Tableau::testAllocation(){
	if(entree == NULL){
		cerr << "Allocation Failed" << endl;
		exit(0);
	}
}
void Tableau::recopier(const Tableau& copie){
	for(int i=0; i <nbelem; i++){
		entree[i] = copie.entree[i];
	}	
}
void Tableau::fusion(const Tableau& T){
	int i,j,k(0);
	int size = taille + T.taille;
	int totalEl= nbelem + T.nbelem;
	Tableau temp(*(this));
	delete[] entree;
	
	entree = new Entree[taille];
	testAllocation();
	for(i=0; i < nbelem; i++){
		entree[i] = temp.entree[i];
	}
	for(j=i; k < T.nbelem; j++){
		entree[j] = T.entree[k++];
	}
	taille = size;
	nbelem = totalEl;
}