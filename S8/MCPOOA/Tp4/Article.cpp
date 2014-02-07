/* 
 * File:   Article.cpp
 * Author: oumar
 * 
 * Created on 1 février 2014, 17:54
 */

#include "Article.h"
using namespace std;
Article::Article() {}

Article::Article(std::string titreR, std::string edit, int publie, 
        string& v_titre, string* v_resume, string v_auteur)
        : Document(v_titre, v_resume, v_auteur), titreRevue(titreR),
        editeur(edit),annee(publie){}

Article::Article(const Article& orig) : Document(orig),
        titreRevue(orig.titreRevue), editeur(orig.editeur), annee(orig.annee){
}
Article* Article::clone() const{
    return new Article(*this);
}
ostream& Article::afficher(ostream& out) const{
    out << "Titre revue -> " << titreRevue << endl;
    out << "Editeur\t-> " << editeur << "\tAnnee -> " << annee << endl;
    Document::afficher(out);
    return out;
}
Document& Article::operator=(const Document& doc){
    if(this != &doc){
        //appel de l'operateur de la classe de base
        Document::operator =(doc);
        //on ne peut effectuer cette affectation que si Document est polymorphe
        const Article& article = dynamic_cast<const Article&> (doc);
        this->annee = article.annee;
        this->editeur = article.editeur;
        this->titreRevue = article.titreRevue;
    }
    return *this;
}
int Article::coutDuDocument(){
    return 200;
}
Article::~Article() {}

