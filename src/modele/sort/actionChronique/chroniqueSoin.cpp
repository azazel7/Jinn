#include "sort/actionChronique/chroniqueSoin.h"


ChroniqueSoin::ChroniqueSoin(int soin)
{
    this->soin = soin;
}

void ChroniqueSoin::effectuerActionChronique(Case &cible, Sort *sortExecutant)
{
    cible.modifierDefense(+this->soin);
}
