#include "ui/VueCreerJoueur.h"

VueCreerJoueur::VueCreerJoueur(PartieClient* partie)
{
    this->partie = partie;
    this->curseur = IndexCreerJoueur::curseur_liste_equipe;
    this->nomEquipe = "";
    this->nomJoueur = "";
    this->positionEquipe = 0;
    this->positionSort = 0;
}
void VueCreerJoueur::dessinerFenetre()
{

}
void VueCreerJoueur::modifierPosition(int valeur)
{
    if(this->curseur == IndexCreerJoueur::curseur_liste_equipe)
    {
        this->positionEquipe += valeur;
        if(this->positionEquipe < 0)
        {
            this->positionEquipe = 0;
        }
        else if(this->positionEquipe >= this->partie->getListeEquipe().size())
        {
            this->positionEquipe = this->partie->getListeEquipe().size();
        }
    }
    else if(this->curseur == IndexCreerJoueur::curseur_liste_sort)
    {
        this->positionSort += valeur;
        if(this->positionSort < 0)
        {
            this->positionSort = 0;
        }
        else if(this->positionSort >= this->partie->getListeSortDispo().size())
        {
            this->positionSort = this->partie->getListeSortDispo().size();
        }
    }
    this->dessinerFenetre();
}
void VueCreerJoueur::modifierCurseur(int valeur)
{
    this->curseur += valeur;
    if(this->curseur > IndexCreerJoueur::curseur_nom_equipe)
    {
        this->curseur = IndexCreerJoueur::curseur_nom_equipe;
    }
    else if(this->curseur < 0)
    {
        this->curseur = 0;
    }
    this->dessinerFenetre();
}
void VueCreerJoueur::ajouterLettre(char lettre)
{
    if(this->curseur == IndexCreerJoueur::curseur_nom_joueur)
    {
        this->nomJoueur += lettre;
    }
    else if(this->curseur == IndexCreerJoueur::curseur_nom_equipe)
    {
        this->nomEquipe += lettre;
    }
    this->dessinerFenetre();
}
void VueCreerJoueur::retirerLettre()
{
    if(this->curseur == IndexCreerJoueur::curseur_nom_joueur)
    {
        this->nomJoueur = this->nomJoueur.substr(0, this->nomJoueur.size());
    }
    else if(this->curseur == IndexCreerJoueur::curseur_nom_equipe)
    {
        this->nomEquipe = this->nomEquipe.substr(0, this->nomEquipe.size());
    }
    this->dessinerFenetre();
}
