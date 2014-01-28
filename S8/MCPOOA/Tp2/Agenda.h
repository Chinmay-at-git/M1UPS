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
	
	friend std::ostream& operator<<(std::ostream& out, const Agenda& A);

	Agenda& operator=(const Agenda& A);
	Agenda operator+(const Agenda& A);
	Agenda& operator+=(const Agenda& A);
	Agenda& operator-=(std::string nom);
	Entree operator[](std::string) const;
	Entree operator[](int i) const;
	bool operator==(const Agenda& A) const;
	bool operator/(std::string nom) const;
	void operator()(std::string nom);
};

#endif

