/* 
 * File:   Article.h
 * Author: oumar
 *
 * Created on 1 février 2014, 17:54
 */

#ifndef ARTICLE_H
#define	ARTICLE_H
#include "Document.h"

class Article : public Document{
public:
    Article();
    Article(std::string titreR, std::string edit, int publie,std::string&,
            std::string*, std::string);
    Article(const Article& orig);
    virtual ~Article();
    virtual std::ostream& afficher(std::ostream& out) const;
    virtual Article* clone() const;
    Document& operator=(const Document& doc);
    virtual int coutDuDocument();
private:
    std::string titreRevue;
    std::string editeur;
    int annee;
};

#endif	/* ARTICLE_H */

