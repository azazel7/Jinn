#include "sort/Sort.h"
#include "sort/actionChronique/chroniqueDegat.h"

ChroniqueDegat::ChroniqueDegat(NoeudRecetteSort* n)
{
    degat = n->getValeurFilsInt("degat");
}

ChroniqueDegat::ChroniqueDegat(int degat)
{
    this->degat = degat;
}

void ChroniqueDegat::effectuerActionChronique(Case &cible, Sort *sortExecutant)
{
    cible.modifierDefense(-this->degat);
}
