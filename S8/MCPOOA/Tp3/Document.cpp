/* 
 * File:   Document.cpp
 * Author: oumar
 * 
 * Created on 31 janvier 2014, 10:19
 */

#include "Document.h"
#include <string>
using namespace std;

Document::Document(string& v_titre, string* v_resume, string v_auteur) :
        titre(v_titre), auteur(v_auteur){
    resume = new string(*v_resume);
}
Document::Document() : resume(0), titre(*new string("")){}
Document::Document(const Document& copie) : titre(copie.titre),
        auteur(copie.auteur), resume(0){
	resume = new string(*(copie.resume));
}
ostream& Document::afficher(ostream& out) const{
    if(resume != 0){
        out << "Auteur -> " << auteur << "\tTitre -> " << titre << endl;
        out << "Resume : " << *(resume) << endl;
    }
    return out;
}
ostream& operator<<(ostream& out, const Document& doc){
    return doc.afficher(out);
}
Document& Document::operator=(const Document& doc){
    if(this != &doc){
        titre = doc.titre;
        auteur = doc.auteur;
        delete resume;
        resume = new string(*(doc.resume));
    }
    return *this;
}
Document::~Document(){if(resume != 0) delete resume;}
Document* Document::clone() const{
	return new Document(*this);
}





