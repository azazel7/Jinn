#include "sort/SortTestDuree.h"

SortTestDuree::SortTestDuree(): Sort("Test Duree", 1, false, 5, 100, 1, 0, 3, 0, 0, 0)
{

}

void SortTestDuree::appliquerSortSurCase(Case &cible)
{
        SortTestDuree* sort = new SortTestDuree();
        *sort = *this;
    cible.ajouterSort(sort, this->duree);
}

void SortTestDuree::modifierSuivantOrigine(Case const& origine)
{
}

void SortTestDuree::modifierSuivantProprietaire()
{
}

void SortTestDuree::retirerDeCase(Case &cible)
{
}

void SortTestDuree::effectuerActionChronique(Case &cible)
{

}

string SortTestDuree::description()
{
    string retour = "Test duree";
    return retour;
}
