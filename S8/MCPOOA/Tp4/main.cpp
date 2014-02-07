/* 
 * File:   main.cpp
 * Author: oumar
 *
 * Created on 31 janvier 2014, 10:17
 */

#include <cstdlib>
#include "Bibliotheque.h"
#include "Article.h"
#include "Livre.h"
#include <string>
using namespace std;

/*
 * 
 */

int main(int argc, char** argv) {
    string resume="resume du document";
    
    Livre l1("Hachette", 2010,* new string("Livre1"), &resume, "Oumar");
    Livre l2("Hachette2", 2013,* new string("Livre2"), &resume,
            "Diallo");
    Article a1("titreRevue", "editeur", 2014,* new string("Article1"), &resume,
            "Alpha");
    
    Bibliotheque bi;
    bi.ajouter(&l1);
    bi.ajouter(&a1);
    bi.ajouter(&l2);
    bi.afficher();
    cout << "Recherche titre = Livre2" << endl;
    Document* res = bi.rechercher("Livre2");
    if(res != 0) res->afficher(cout);
    
    cout << "Cout Livre1 -> " << l1.coutDuDocument() << endl;
    cout << "Cout Article1 -> " << a1.coutDuDocument() << endl;
    
    return 0;
}

