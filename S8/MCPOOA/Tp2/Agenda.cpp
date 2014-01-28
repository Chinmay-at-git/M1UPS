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
ostream& operator<<(ostream& out, const Agenda& A) {
	return out << A.tableau;
}
Agenda& Agenda::operator=(const Agenda& A){
	//voir si on affecte pas l'objet à lui meme
	if(this != &A){
		tableau = A.tableau;
	}
	return *this;
}
Agenda Agenda::operator+(const Agenda& A){
	Agenda res(*this);
	res.concat(A);
	return res;
}
Agenda& Agenda::operator+=(const Agenda& A){
	concat(A);
	return *this;
}
Agenda& Agenda::operator-=(string nom){
	tableau -= nom;
	return *this;
}
Entree Agenda::operator[](string nom) const{
	return tableau[nom];
}
Entree Agenda::operator[](int i) const{
	return tableau[i];
}
bool Agenda::operator==(const Agenda& A) const{
	return tableau == A.tableau;
}
bool Agenda::operator/(string nom) const{
	Entree tmp = tableau[nom];
	return !tmp.getNom().empty();
}
void Agenda::operator()(string lettre){
    int size = lettre.size();
	for(int i(0); i < tableau.getNbElem(); i++){
        if(tableau[i].getNom().substr(0, size) == lettre)
            cout << tableau[i].getNom() << endl;
    }
}