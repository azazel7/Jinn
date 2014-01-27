#ifndef ChroniqueDegat_h
#define ChroniqueDegat_h

#include "sort/SortActionChronique.h"
class Sort;
class NoeudRecetteSort;

class ChroniqueDegat : public SortActionChronique
{
    int degat;
    public:
    ChroniqueDegat(int degat);
    ChroniqueDegat(NoeudRecetteSort* n);
    void effectuerActionChronique(Case &cible, Sort *sortExecutant);
};

#endif
