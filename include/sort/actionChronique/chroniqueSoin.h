#ifndef ChroniqueSoin_h
#define ChroniqueSoin_h

#include "sort/Sort.h"
#include "sort/SortActionChronique.h"

class ChroniqueSoin : public SortActionChronique
{
    int soin;
    public:
    ChroniqueSoin(int soin);
    void effectuerActionChronique(Case &cible, Sort *sortExecutant);
};

#endif
