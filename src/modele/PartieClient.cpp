#include "PartieClient.h"

PartieClient::PartieClient()
{
    this->joueurCourant = NULL;
}
void PartieClient::ajouterJoueur(Joueur *joueur)
{
    if(this->listeJoueur[joueur->getNom()] == NULL)
    {
        this->listeJoueur[joueur->getNom()] = joueur;
    }
}
void PartieClient::retirerJoueur(string const& nom)
{
    this->listeJoueur.erase(nom);
}
void PartieClient::ajouterSortJoueur(string const& nomJoueur, string const& nomSort)
{
    this->listeJoueur[nomJoueur]->ajouterSort(nomSort);
}

void PartieClient::retirerSortJoueur(string const& nomJoueur, string const& nomSort)
{
    this->listeJoueur[nomJoueur]->retirerSort(nomSort);
}

Joueur* PartieClient::getJoueur(string const& nom)
{
    return this->listeJoueur[nom];
}

void PartieClient::ajouterCase(Case * newCase)
{
    int code = Position::codePosition(newCase->getPosition()->getX(), newCase->getPosition()->getY());
    if(this->listeCase[code] == NULL)
    {
        this->listeCase[code] = newCase;
    }
}
void PartieClient::retirerCase(Position * position)
{
    int code = Position::codePosition(position->getX(), position->getY());
    this->listeCase.erase(code);
}
void PartieClient::ajouterSortCase(Position * position, Sort* sort, int duree)
{
    int code = Position::codePosition(position->getX(), position->getY());
    this->listeCase[code]->ajouterSort(sort, duree);
}

void PartieClient::retirerSortCase(Position * position, int id)
{
    int code = Position::codePosition(position->getX(), position->getY());
    this->listeCase[code]->retirerSortId(id, false);
}
Case* PartieClient::getCase(Position * position)
{
    int code = Position::codePosition(position->getX(), position->getY());
    return this->listeCase[code];
}
Sort* PartieClient::getSort(Position* position, int id_sort)
{
    Case* caseCible = this->getCase(position);
    if(caseCible == NULL)
    {
        return NULL;
    }
    return caseCible->getSortId(id_sort);
}

void PartieClient::setJoueurCourant(Joueur* joueur)
{
    this->joueurCourant = joueur;
}
Joueur* PartieClient::getJoueurCourant()
{
    return this->joueurCourant;
}
