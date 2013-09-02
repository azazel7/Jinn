#ifndef ChroniqueDegatCumulatif_h
#define ChroniqueDegatCumulatif_h

#include "sort/Sort.h"
#include "sort/SortActionChronique.h"

class ChroniqueDegatCumulatif : public SortActionChronique
{
    int degat;
    int modificateur;
    public:
    ChroniqueDegatCumulatif(int degat, int modificateur);
    void effectuerActionChronique(Case &cible, Sort *sortExecutant);
};

#endif
