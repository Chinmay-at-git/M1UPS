/* 
 * File:   Livre.cpp
 * Author: oumar
 * 
 * Created on 31 janvier 2014, 10:25
 */
#include "Livre.h"
using namespace std;

Livre::Livre(){}
Livre::Livre(std::string edit, int parution, Document doc) :
        Document(doc), editeur(edit), annee(parution){}
Livre::Livre(const Livre& orig) :
        editeur(orig.editeur), annee(orig.annee), Document(orig){}

ostream& Livre::afficher(ostream& out) const{
    out << "Editeur -> " << editeur << "\tAnnee -> " << annee << endl;
    Document::afficher(out);
    return out;
}


Livre* Livre::clone() const{
	return new Livre(*this);
}
Document& Livre::operator=(const Document& doc){
    if(this != &doc){
        //appel de l'operateur de la classe de base
        Document::operator =(doc);
        //on ne peut effectuer cette affectation que si Document est polymorphe
        const Livre& livre = dynamic_cast<const Livre&> (doc);
        this->annee = livre.annee;
        this->editeur = livre.editeur;
    }
    return *this;
}


Livre::~Livre(){}