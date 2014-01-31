#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <iostream>

class Document
{
	std::string titre;
	std::string* resume;
	std::string auteur;
public:
	Document();
	Document(std::string v_titre, std::string v_resume, std::string v_auteur);
	Document(const Document& copie);
	Document* clone() const;
	std::string* getResume(){return resume;}
	friend std::ostream& operator<<(std::ostream& out, const Document& doc);
	~Document();
	
};

#endif