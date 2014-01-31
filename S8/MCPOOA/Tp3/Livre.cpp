#include "Livre.h"
Livre::Livre(){}
Livre::Livre(string v_editeur, int parution, string v_titre,
	 string v_resume, string v_auteur) : Document(v_titre, v_resume, v_auteur){


	
	editeur= v_editeur;
	annee = parution;

	 									 }

Livre::~Livre(){}

Livre::Livre(const Livre& copie) : Document(copie){
	editeur = copie.editeur;
	annee = copie.annee;
}