#include "sort/RuneDeProtection.h"

RuneDeProtection::RuneDeProtection(): Sort("Rune de Protection", 1, false, 5, 100, 1, 0, 3, 0, 0, 0)
{
    this->modificationDefense = 1;
}

void RuneDeProtection::appliquerSortSurCase(Case &cible)
{
    cible.modifierDefenseReel(1);
    cible.ajouterSort(this, this->duree);
}

void RuneDeProtection::modifierSuivantOrigine(Case const& origine)
{

}

void RuneDeProtection::modifierSuivantProprietaire()
{
}

void RuneDeProtection::retirerDeCase(Case &cible)
{
    cible.modifierDefenseReel(-1);
}

void RuneDeProtection::effectuerActionChronique(Case &cible)
{
    cout << "je suis toujour là, sur la case " << cible  << endl;
}

string RuneDeProtection::description()
{
    string retour = "Augmente la defense maximal d'une case de ";
    retour +=  this->modificationDefense;
    retour += " pendant ";
    retour += this->duree  + " tour(s)";
    return retour;
}
