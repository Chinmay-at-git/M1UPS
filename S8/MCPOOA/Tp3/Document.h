/* 
 * File:   Document.h
 * Author: oumar
 *
 * Created on 31 janvier 2014, 10:19
 */

#ifndef DOCUMENT_H
#define	DOCUMENT_H

#include <iostream>

class Document
{
    std::string& titre;
    std::string* resume;
    std::string auteur;
public:
    Document();
    Document(std::string& v_titre, std::string* v_resume, std::string v_auteur);
    Document(const Document& copie);
    
    
    friend std::ostream& operator<<(std::ostream& out, const Document& doc);
    /*
     *un destructeur doit toujours être virtuel si on utilise le polymorphisme.
     */
    virtual ~Document();
    /*
     *virtual pour assurer le polymorphisme
     * (HERITAGE +(POINTEUR OU REFERENCE) + FONCTIONS VIRTUELLES)
     */
    virtual std::ostream& afficher(std::ostream& out) const;
    virtual Document* clone() const;
    //l'operateur d'affectation doit etre redefinie. S'il ne l'est pas
    //l'affectation ne s'appliquera que sur le type de base, donc les certains
    //membres de la classe derivee ne seront pas copie
    virtual Document& operator=(const Document& doc);
	
};


#endif	/* DOCUMENT_H */

