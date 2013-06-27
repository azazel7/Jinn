#ifndef AppliquerDegat_h
#define AppliquerDegat_h

#include "sort/SortAppliquerSurCase.h"

class AppliqueDegat: public SortAppliquerSurCase
{
    public:
    virtual void appliquerSortSurCase(Case &cible, Sort* sortExecutant);
    virtual void retirerSortDeCase(Case &cible, Sort* sortExecutant);
};

#endif
