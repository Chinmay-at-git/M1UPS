##ifndef LIVRE_H
#define LIVRE_H



class Livre : public Document
{
	std::string editeur;
	int annee;

public:
	Livre(std::string editeur, int parution, std::string v_titre, std::string v_resume, std::string v_auteur);
	Livre(const Livre& copie);
	~Livre();
	
};
#endif