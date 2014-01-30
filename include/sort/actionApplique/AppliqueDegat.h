#ifndef AppliquerDegat_h
#define AppliquerDegat_h

#include "sort/SortAppliquerSurCase.h"
#include "Case.h"
class NoeudRecetteSort;

class AppliqueDegat: public SortAppliquerSurCase
{
    int degat;
public:
    AppliqueDegat(int degat);
    AppliqueDegat(NoeudRecetteSort* n);
    virtual void appliquerSortSurCase(Case &cible, Sort* sortExecutant);
    virtual void retirerSortDeCase(Case &cible, Sort* sortExecutant);
};

#endif
