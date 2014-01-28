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
	std::ostream& afficher(std::ostream& out);

};

#endif

