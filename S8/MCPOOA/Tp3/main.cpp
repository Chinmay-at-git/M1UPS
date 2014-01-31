#include "Document.h"
using namespace std;

int main(int argc, char const *argv[])
{
	/* code */
	cout << "Clonage " << endl;
	Document doc3;
	int i= 0;
	if(!i){
		Document doc2("Titre", "Resume", "Auteur");
		doc3 = *(doc2.clone());
		cout << "doc2 ->" << &doc2 << endl;
	}
	
	cout << doc3;

	
	cout << "doc3 ->" << &doc3<< endl;

	return 0;
}