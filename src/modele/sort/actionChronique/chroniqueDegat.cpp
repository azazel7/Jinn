#include "sort/actionChronique/chroniqueDegat.h"

ChroniqueDegat::ChroniqueDegat(int degat)
{
    this->degat = degat;
}

void ChroniqueDegat::effectuerActionChronique(Case &cible, Sort *sortExecutant)
{
    cible.modifierDefense(-this->degat);
}
