#include "sort/BouleDeFeu.h"

BouleDeFeu::BouleDeFeu(): Sort("Boule de Feu", 1, false, 5, 100, 1, 1, 0, 0, 0, 0)
{

}

void BouleDeFeu::appliquerSortSurCase(Case &cible)
{
    cible.setDefenseActuelle(cible.getDefenseActuelle() - this->attaque);
}

void BouleDeFeu::modifierSuivantOrigine(Case const& origine)
{
}

void BouleDeFeu::modifierSuivantProprietaire()
{
}

void BouleDeFeu::retirerDeCase(Case &cible)
{
}

void BouleDeFeu::effectuerActionChronique(Case &cible)
{

}

string BouleDeFeu::description()
{
    string retour = "Lance une boule de feu infligeant ";
    retour += this->attaque;
    retour += " dégats";
    return retour;
}
