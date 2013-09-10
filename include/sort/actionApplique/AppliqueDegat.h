#ifndef AppliquerDegat_h
#define AppliquerDegat_h

#include "sort/SortAppliquerSurCase.h"
#include "Case.h"

class AppliqueDegat: public SortAppliquerSurCase
{
    int degat;
public:
    AppliqueDegat(int degat);
    virtual void appliquerSortSurCase(Case &cible, Sort* sortExecutant);
    virtual void retirerSortDeCase(Case &cible, Sort* sortExecutant);
};

#endif
