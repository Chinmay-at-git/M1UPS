#include "Agenda.h"
#include <string>
using namespace std;

Agenda::Agenda(void){}

Agenda::Agenda(Tableau tab) : tableau(tab){}

Agenda::Agenda(int size) : tableau(size){}

Agenda::Agenda(const Agenda& copie) : tableau(copie.tableau){}

void Agenda::ajouter(std::string nom, std::string numero){
	tableau.ajouter(nom, numero);
}
void Agenda::supprimer(std::string nom, std::string numero){
	tableau.supprimer(nom, numero);
}
void Agenda::supprimer(std::string nom){
	tableau.supprimer(nom);
}
void Agenda::concat(const Agenda& agenda2){
	tableau.fusion(agenda2.tableau);
}
ostream& Agenda::afficher(std::ostream& out){
	return tableau.afficher(out);
}