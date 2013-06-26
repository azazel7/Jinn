#ifndef SortActionChronique_h
#define SortActionChronique_h

#include "sort/Sort.h"
#include "Case.h"

class SortActionChronique
{
    public:
    virtual void effectuerActionChronique(Case &cible, Sort *sortExecutant) = 0;
};

#endif
