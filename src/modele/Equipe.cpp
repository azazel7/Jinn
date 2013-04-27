#include "Equipe.h"

Joueur* Equipe::choisirJoueur()
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

Equipe::Equipe(string nom)
{
	this->nom = nom;
	this->joueurChoisi = 0;
}

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

vector<Joueur* > Equipe::getJoueur()
{
    return this->joueur;
}

void Equipe::retirerJoueur(Joueur* joueurASuppr)
{
        vector<Joueur* >::iterator it;
        for(it = joueur.begin(); it != joueur.end(); it++)
        {
                if(*it == joueurASuppr)
                {
                        joueur.erase(it);
                        return;
                }
        }
}
