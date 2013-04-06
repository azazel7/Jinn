#include "Partie.h"




Partie::Partie(string nom, int nombrePlace)
// don't delete the following line as it's needed to preserve source code of this autogenerated element
// section -64--88-1-10-3b98f0fe:13dba1c87fc:-8000:0000000000000EB4 begin
{
	this->nom = nom;
	this->nombreDePlace = nombrePlace;
    this->enCours = false;
}
// section -64--88-1-10-3b98f0fe:13dba1c87fc:-8000:0000000000000EB4 end
// don't delete the previous line as it's needed to preserve source code of this autogenerated element


/** 
     *  Demarre la partie.
     */
void Partie::demarrerPartie()
// don't delete the following line as it's needed to preserve source code of this autogenerated element
// section -64--88-1-11-15711965:13d9366bd46:-8000:0000000000000B21 begin
{
    int equipeCourante = 0;
    Joueur* courant = NULL;
    Action action;
    enCours = true;
    while(enCours == true)
    {
        courant = equipe[equipeCourante]->choisirJoueur();
        action = courant->effectuerAction();
        //TODO verifier si l'action est valide
        plateau->appliquerAction(action);
        if(finPartie() == true)
        {
            enCours = false;
        }
    }



}
// section -64--88-1-11-15711965:13d9366bd46:-8000:0000000000000B21 end
// don't delete the previous line as it's needed to preserve source code of this autogenerated element


/** 
     *  Verifie la victoire d'une équipe
     */
bool Partie::verifierVictoire(Equipe & equipe)
// don't delete the following line as it's needed to preserve source code of this autogenerated element
// section -64--88-1-11-15711965:13d9366bd46:-8000:0000000000000B23 begin
{
    int nombreCaseControllee = 0;
    Case* courante;
    string nom;
    for(int x = 0; x < plateau->getLargeur(); x++)
    {
        for(int y = 0; y < plateau->getHauteur(); y++)
        {
            courante = plateau->getCase(x, y);
            if(courante != NULL)
            {
                nom = courante->getProprietaire()->getNom();
                if(equipe.joueurExiste(nom) == true)
                {
                    nombreCaseControllee++;
                }
            }
        }
    }
    if(nombreCaseControllee == plateau->nombreCaseControlable())
    {
        return true;
    }
    return false;
}
// section -64--88-1-11-15711965:13d9366bd46:-8000:0000000000000B23 end
// don't delete the previous line as it's needed to preserve source code of this autogenerated element


/** 
     *  Initialise la partie, les different joueurs, les differentes equipes et le terrain
     */
void Partie::initialiser()
// don't delete the following line as it's needed to preserve source code of this autogenerated element
// section -64--88-1-10-3b98f0fe:13dba1c87fc:-8000:0000000000000EB7 begin
{
	plateau = new Plateau();
}
// section -64--88-1-10-3b98f0fe:13dba1c87fc:-8000:0000000000000EB7 end
// don't delete the previous line as it's needed to preserve source code of this autogenerated element

std::vector<Sort*> Partie::listeSort()
{

}

void Partie::nouveauJoueur(Joueur & joueur)
{
	bool valid = false;
	string nom, equipe;
    //On récupére le nom
	while(valid == false)
	{
		valid = true;
		nom = joueur.saisieNom();
		for (int i = 0; i < this->equipe.size(); i++)
		{
			if (this->equipe[i]->joueurExiste(nom))
			{
				valid = false;
				break;
			}
		}
	}

    //On récupére l'equipe
	equipe = joueur.saisieEquipe(this->equipe);
	valid = false;
	//On cherche l'equipe correspondant au nom
	for(int i = 0; i < this->equipe.size(); i++)
	{
		if(this->equipe[i]->getNom() == equipe)
		{
			valid = true;
			this->equipe[i]->ajouterJoueur(&joueur);
		}
	}
	//sinon, on la créer
	if(valid == false)
	{
		Equipe* nouvelleEquipe = new Equipe(equipe);
		nouvelleEquipe->ajouterJoueur(&joueur);//on ajoute le joueur
		this->equipe.push_back(nouvelleEquipe);
	}


	//selection des sorts
	//TODO faire en sorte que le nombre de sort soi variable
	//TODO Peut-être faire en sorte que la liste des sorts soi stocké
	vector<Sort*> listeSort = this->listeSort();
	for(int i = 0; i < 7; i++)
	{
		joueur.saisieSort(listeSort);
		//TODO Un joueur peut maitriser plusieurs fois le même sort
		//TODO génrer le cas des élites
	}

	joueur.genererStatistique();
	//TODO notifier le joueur de ses stats
}

bool Partie::finPartie()
{
    for(int i = 0; i < equipe.size(); i++)
    {
        if(verifierVictoire(*(equipe[i])) == true)
        {
            return true;
            //TODO notifier les équipes
        }
    }
    return false;
}

bool Partie::isEnCours()
{
    return enCours;
}

void Partie::setEnCours(bool valeur)
{
    this->enCours = valeur;
}
