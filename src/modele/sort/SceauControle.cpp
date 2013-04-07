#include "sort/SceauControle.h"

SceauControle::SceauControle(): Sort("Sceau de Controle", 1, false, 5, 100, 1, 0, 0, 0, 0, 0)
{

}

void SceauControle::appliquerSortSurCase(Case &cible)
{
    cout << "propri " << this->proprietaire << endl;
    cout << "cible : " << cible << endl;
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
