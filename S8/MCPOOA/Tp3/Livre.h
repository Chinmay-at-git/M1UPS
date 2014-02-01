/* 
 * File:   Livre.h
 * Author: oumar
 *
 * Created on 31 janvier 2014, 10:25
 */

#ifndef LIVRE_H
#define	LIVRE_H
#include "Document.h"

class Livre : public Document{
    std::string editeur;
    int annee;
public:
    Livre();
    Livre(std::string, int, Document doc);
    Livre(const Livre& orig);
    ~Livre();
    virtual std::ostream& afficher(std::ostream& out) const;
    virtual Livre* clone() const;

};

#endif	/* LIVRE_H */

