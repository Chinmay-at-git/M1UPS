/* 
 * File:   Bibliotheque.h
 * Author: oumar
 *
 * Created on 7 février 2014, 11:03
 */

#ifndef BIBLIOTHEQUE_H
#define	BIBLIOTHEQUE_H
#include <list>
#include <iostream>
#include "Document.h"

class Bibliotheque {
    std::list<Document*> tab;
public:
    Bibliotheque();
    Bibliotheque(const Bibliotheque& orig);
    virtual ~Bibliotheque();
    
    void ajouter(Document *D);
    Document* rechercher(std::string T);
    void afficher();
private:

};

#endif	/* BIBLIOTHEQUE_H */

