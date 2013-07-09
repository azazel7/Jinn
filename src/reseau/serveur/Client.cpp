#include "reseau/serveur/Client.h"

Client::Client()
{
        this->partie = NULL;
        this->joueur = NULL;
}
void Client::setPartie(Partie* partie)
{
        this->partie = partie;
}
Partie* Client::getPartie() const
{
        return this->partie;
}

void Client::setJoueur(Joueur* joueur)
{
        this->joueur = joueur;
}
Joueur* Client::getJoueur()
{
        return this->joueur;
}
