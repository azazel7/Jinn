#include "sort/actionApplique/AppliqueDegat.h"

AppliqueDegat::AppliqueDegat(int degat)
{
    this->degat = degat;
}

void AppliqueDegat::appliquerSortSurCase(Case &cible, Sort* sortExecutant)
{
    cible.modifierDefense(-this->degat);
}
void AppliqueDegat::retirerSortDeCase(Case &cible, Sort* sortExecutant)
{

}
