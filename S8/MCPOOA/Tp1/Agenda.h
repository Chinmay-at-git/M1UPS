#ifndef AGENDA_H
#define AGENDA_H
#include "Tableau.h"

class Agenda
{
	Tableau tableau;
public:
	Agenda(void);
	Agenda(const Agenda& copie);
	Agenda(Tableau tab);
	Agenda(int size);
	void concat(const Agenda& agenda2);
	void ajouter(std::string nom, std::string numero);
	void supprimer(std::string nom, std::string numero);
	void supprimer(std::string nom);
	std::ostream& afficher(std::ostream& out);
};

#endif

