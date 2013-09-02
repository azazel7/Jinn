#ifndef ChroniqueDegat_h
#define ChroniqueDegat_h

#include "sort/Sort.h"
#include "sort/SortActionChronique.h"

class ChroniqueDegat : public SortActionChronique
{
    int degat;
    public:
    ChroniqueDegat(int degat);
    void effectuerActionChronique(Case &cible, Sort *sortExecutant);
};

#endif
