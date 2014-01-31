#include "Livre.h"

Livre::Livre(string v_editeur, int parution, string v_titre,
	 string v_resume, string v_auteur) : Docuemnt(v_titre, v_resume, v_auteur),
	 									 editeur(v_editeur), annee(parution){}