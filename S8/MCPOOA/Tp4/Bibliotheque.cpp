/* 
 * File:   Bibliotheque.cpp
 * Author: oumar
 * 
 * Created on 7 février 2014, 11:03
 */

#include "Bibliotheque.h"
using namespace std;

Bibliotheque::Bibliotheque() {}

Bibliotheque::Bibliotheque(const Bibliotheque& orig) {}

Bibliotheque::~Bibliotheque() {}

void Bibliotheque::ajouter(Document *D){
    tab.push_back(D);
}

Document* Bibliotheque::rechercher(std::string T){
    for(list<Document*>::iterator it = tab.begin(); it != tab.end(); it++){
        if((*it)->titre == T){
            return (*it);
        }
    }
    return NULL;
}

void Bibliotheque::afficher(){
    cout << "Contenu de la Bibiliotheque" << endl;
    for(list<Document*>::iterator it = tab.begin(); it != tab.end(); it++){
        (*it)->afficher(cout);
        cout << endl;
    }
}

