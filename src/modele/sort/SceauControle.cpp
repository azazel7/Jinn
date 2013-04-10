#include "sort/SceauControle.h"

SceauControle::SceauControle(): Sort("Sceau de Controle", 1, false, 5, 100, 1, 0, 0, 0, 0, 0)
{

}

void SceauControle::appliquerSortSurCase(Case &cible)
{
    if(cible.getDefenseActuelle() <= 0)
    {
        cible.setProprietaire(this->proprietaire); //On modifie le proprietaire
    }
}

void SceauControle::modifierSuivantOrigine(Case const& origine)
{
}

void SceauControle::modifierSuivantProprietaire()
{
}

void SceauControle::retirerDeCase(Case &cible)
{
}

void SceauControle::effectuerActionChronique(Case &cible)
{

}

string SceauControle::description()
{
    return "Sort permettant de prendre le controle d'une case";
}
