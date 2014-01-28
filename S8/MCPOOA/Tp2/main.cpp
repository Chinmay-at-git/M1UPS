#include "Agenda.h"
using namespace std;

int main(int args, char** argv)
{   
    Agenda monAgenda;
    monAgenda.ajouter("aaow", "07-55-55-555");
    monAgenda.ajouter("alpha", "07-55-55-555");
    monAgenda.ajouter("barry", "08-55-55-555");
    
    Agenda agenda1;
    agenda1 = monAgenda;
    agenda1.ajouter("aapetit", "---------");
    
    monAgenda += agenda1;
    Agenda agenda3 = monAgenda + agenda1;
    cout << agenda3;
    
    Entree search = agenda3["barry"];
    cout << "resultat de la recherche" << endl;
    cout << search;
    agenda3 -= "barry";
    cout << agenda3;
    
    cout << "agenda3 == monAgenda -> " << (agenda3 == monAgenda) << endl;
    cout << "agenda3/alpha : " << (agenda3/"alpha") << endl;
    cout << "agenda3(\"aa\") : " << endl;
    agenda3("aa");
    
    return 0;
}
