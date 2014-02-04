/* 
 * File:   main.cpp
 * Author: oumar
 *
 * Created on 31 janvier 2014, 10:17
 */

#include <cstdlib>
#include "Livre.h"
#include "Article.h"
#include <string>
using namespace std;

/*
 * 
 */

void presenter(const Document doc){
    doc.afficher(cout);
}
int main(int argc, char** argv) {
    string title="titre du doc";
    string resume="resume";
    Document doc(title, &resume, "auteur");

    Document* d= &doc;
    cout << "Affichage Doc" << endl;
    d->afficher(cout);
    
    Livre l1("Hachette", 2010, doc);
    d = &l1;
    cout << "Affichage Doc (polymorphisme livre 1)" << endl;
    d->afficher(cout);
    
    
    Article a1("titreRevue", "editeur", 2014, doc);
    d = &a1;
    cout << "Affichage Doc (polymorphisme Article 1)" << endl;
    d->afficher(cout);
    
    cout << "Test operateur affectation" << endl;
    Livre l2;
    l2 = l1;
    l2.afficher(cout);
    
    
    return 0;
}

