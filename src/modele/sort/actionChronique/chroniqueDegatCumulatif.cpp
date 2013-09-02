#include "sort/actionChronique/chroniqueDegatCumulatif.h"

ChroniqueDegatCumulatif::ChroniqueDegatCumulatif(int degat, int modificateur)
{
    this->degat = degat;
    this->modificateur = modificateur;
}

void ChroniqueDegatCumulatif::effectuerActionChronique(Case &cible, Sort *sortExecutant)
{
    cible.modifierDefense(-this->degat);
    this->degat += this->modificateur;
}
