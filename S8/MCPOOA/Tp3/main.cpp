#include "Document.h"
#include "Livre.h"
using namespace std;

int main(int argc, char const *argv[])
{
	/* code */
	Document doc1("Titre", "Resume", "Auteur");
	cout << doc1;

	Livre livre;

	return 0;
}