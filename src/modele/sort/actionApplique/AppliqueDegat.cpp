#include "sort/actionApplique/AppliqueDegat.h"
#include "NoeudRecetteSort.h"

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

AppliqueDegat::AppliqueDegat(NoeudRecetteSort* n)
{
    this->degat = n->getValeurFilsInt("degat");
}
