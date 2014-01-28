#include "Entree.h"
#include <string>
using namespace std;

Entree::Entree(){}
Entree::Entree(string leNom, string numero) : nom(leNom),numTel(numero){}

ostream& Entree::afficher(ostream& out){
	out << "Name -> "  << nom << 
		"\tNumber -> "  << numTel << endl;
	return out;
}