#ifndef TABLEAU_H
#define TABLEAU_H

#include <iostream>
#include "Entree.h"
class Tableau
{
	int taille;
	Entree* entree;
	int nbelem;
public:
	Tableau(int v_taille=10, int v_elem=0);
	~Tableau(void);
	Tableau(const Tableau& copie);
	void ajouter(std::string nom, std::string numero);
	void supprimer(std::string nom, std::string numero);
	void supprimer(std::string nom);
	void fusion(const Tableau& T);
	int getTaille(){return taille;}
	int getNbElem(){return nbelem;}

	friend std::ostream& operator<<(std::ostream& out, const Tableau& T);
	Tableau& operator=(const Tableau& A);
	Tableau& operator-=(std::string nom);
	Entree operator[](std::string nom) const;
	Entree operator[](int i) const;
	bool operator==(const Tableau& T) const;
	bool operator!=(const Tableau& T) const;


private:
	void testAllocation();
	void recopier(const Tableau& copie);
};

#endif

