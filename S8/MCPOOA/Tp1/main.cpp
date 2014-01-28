#include <iostream>
#include "Agenda.h"
using namespace std;

int main(int args, char** argv)
{
    Entree uneEntree = Entree("alpha", "06-68-62-25-58");
    uneEntree.afficher(cout);
    Tableau tab;
    tab.afficher(cout);
    tab.ajouter("sow", "07-55-55-555");
    tab.ajouter("barry", "07-55-55-555");
	tab.ajouter("sow", "08-55-55-555");
    tab.afficher(cout);
    cout << "suppression oumar" << endl;
    tab.supprimer("sow");
    tab.afficher(cout);
    
    cout << endl << "Constructeur par copie de Tab2 par tab" << endl;
    Tableau tab2(tab);
    tab2.afficher(cout);
    
    cout << endl << "Agenda" << endl;
    Agenda monAgenda;
    monAgenda.ajouter("sow", "07-55-55-555");
    monAgenda.ajouter("alpha", "07-55-55-555");
    monAgenda.ajouter("barry", "07-55-55-555");
    monAgenda.afficher(cout);
    
    cout << endl << "Creation agenda1 a partir de monAgenda" << endl;
    Agenda agenda1(monAgenda);
    agenda1.afficher(cout);
    cout << endl << "Suppression sow, alpha, barry agenda1" << endl;
    agenda1.supprimer("sow", "07-55-55-555");
    agenda1.supprimer("alpha");
    agenda1.supprimer("barry");
    agenda1.afficher(cout);
    cout << endl << "Ajout sur agenda1" << endl;
    agenda1.ajouter("katie", "14-55-55-555");
    agenda1.ajouter("Ousmane", "98-55-55-555");
    agenda1.ajouter("thierry", "66-55-55-555");
    agenda1.afficher(cout);
    cout << endl << "Concatenation agenda1 et monAgenda" << endl;
    agenda1.concat(monAgenda);
    agenda1.afficher(cout);
    
    return 0;
}

/*
 Appel constructeur par copie
 Tableau tab2(tab);
 Tableau tab2=tab
 afficher(tab2);
 retour d'un objet comme resultat de fonctions
 
 Appel operator=
 tab2=tab
 
 Si Agenda contient maintenant un pointeur vers Tableau, il faudrait implementer
  un destructeur pour la memoire qui sera allouee au niveau du constructeur,
 implementer un constructeur par copie (tout cela pour ne pas que deux objets
 pointent sur la meme case memoire, si deux objets pointent sur la meme case
 memoire, si le premier est detruit, arrivee a la destruction du second le 
 programme plante (core dump)
*/