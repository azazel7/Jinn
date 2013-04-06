#include "sort/SceauControle.h"

SceauControle::SceauControle(): Sort()
{
    this->nom = "Sceau de Controle";
}

void SceauControle::appliquerSortSurCase(Case &cible)
{
    cible.setProprietaire(this->proprietaire); //On modifie le proprietaire
}

void SceauControle::modifierSuivantOrigine(Case const& origine)
{
    cout << "Rien à modifier selon origine" << endl;
}

void SceauControle::modifierSuivantProprietaire()
{
    cout << "Modification selon : " << proprietaire->getNom() << endl;
}

void SceauControle::retirerDeCase(Case &cible)
{

}

string SceauControle::description()
{
    return "Sort permettant de prendre le controle d'une case";
}
