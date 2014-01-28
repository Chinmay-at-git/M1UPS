#ifndef ENTREE_H
#define ENTREE_H
#include <iostream>

class Entree
{
	std::string nom;
	std::string numTel;
	
	friend class Tableau;
public:
	Entree();
	Entree(std::string leNom, std::string numero);
	std::string getNom(){return nom;}
	std::string getNumTel(){return numTel;}

	//surcharge de l'operateur d'affichage (fonction globale)
	//car 1er operande=base (friend pour acceder aux attributs prives)
	friend std::ostream& operator<<(std::ostream& out, const Entree& entree);
	bool Entree::operator==(const Entree& E) const;
	bool Entree::operator!=(const Entree& E) const;

};

#endif

