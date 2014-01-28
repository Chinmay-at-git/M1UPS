#include "Entree.h"
#include <string>
using namespace std;

Entree::Entree(){}
Entree::Entree(string leNom, string numero) : nom(leNom),numTel(numero){}

ostream& operator<<(ostream& out, const Entree& entree){
	out << "Name -> "  << entree.nom << 
		"\tNumber -> "  << entree.numTel << endl;
	return out;
}
bool Entree::operator!=(const Entree& E) const{
	return !((*this) == E);
}
bool Entree::operator==(const Entree& E) const{
	return nom == E.nom && numTel == E.numTel;
}