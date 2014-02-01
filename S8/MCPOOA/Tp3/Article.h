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
    Article(const Article& orig);
    virtual ~Article();
private:

};

#endif	/* ARTICLE_H */

