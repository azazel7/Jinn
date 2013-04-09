#include "Equipe.h"

Joueur* Equipe::choisirJoueur()
// don't delete the following line as it's needed to preserve source code of this autogenerated element
// section -64--88-1-11-15711965:13d9366bd46:-8000:0000000000000B29 begin
{
	if(joueur.size() > 0)
	{
        for(int i = 0; i < joueur.size(); i++)
        {
            int tmp = joueurChoisi;
            joueurChoisi = (joueurChoisi+1)%joueur.size();
            if(joueur[tmp]->estMort() == false)
            {
                return joueur[tmp];
            }
        }
	}
	return NULL;
}
// section -64--88-1-11-15711965:13d9366bd46:-8000:0000000000000B29 end
// don't delete the previous line as it's needed to preserve source code of this autogenerated element

Equipe::Equipe(string nom)
// don't delete the following line as it's needed to preserve source code of this autogenerated element
// section -64--88-1-13--239a61df:13dc1d51575:-8000:0000000000000F1F begin
{
	this->nom = nom;
	this->joueurChoisi = 0;
}
// section -64--88-1-13--239a61df:13dc1d51575:-8000:0000000000000F1F end
// don't delete the previous line as it's needed to preserve source code of this autogenerated element

bool Equipe::joueurExiste(string & nom)
{
    for(int i = 0; i < joueur.size(); i++)
    {
        if(joueur[i]->getNom() == nom)
        {
            return true;
        }
    }
    return false;
}

string Equipe::getNom()
{
	return this->nom;
}

void Equipe::ajouterJoueur(Joueur* nouveauJoueur)
{
	if(nouveauJoueur != NULL)
	{
		this->joueur.push_back(nouveauJoueur);
	}
}

int Equipe::nombreDeJoueur()
{
    return this->joueur.size();
}

void Equipe::regenererManaJoueur()
{
    for(int i = 0; i < joueur.size(); i++)
    {
        if(joueur[i]->estMort() == false)
        {
            joueur[i]->augmenterMana(joueur[i]->getGainInitialMana());
        }

    }
}
