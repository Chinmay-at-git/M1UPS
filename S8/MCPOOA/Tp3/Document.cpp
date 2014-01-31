#include "Document.h"
#include <string>
using namespace std;

Document::Document():resume(0){}
Document::Document(string v_titre, string v_resume, string v_auteur) : titre(v_titre), auteur(v_auteur){
	resume = new string(v_resume);
}
Document::Document(const Document& copie) : titre(copie.titre), auteur(copie.auteur), resume(0){
	resume = new string(*(copie.resume));
}
ostream& operator<<(ostream& out, const Document& doc){
	if(doc.resume != 0){
		out << "Auteur -> " << doc.auteur << "\tTitre -> " << doc.titre << endl;
		out << "Resume : " << *(doc.resume) << endl;
	}
	
	return out;
}

Document::~Document(){if(resume != 0) delete resume;}

Document* Document::clone() const{
	return new Document(*this);
}

