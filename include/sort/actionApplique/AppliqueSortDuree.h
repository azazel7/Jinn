#ifndef AppliquerSortDuree_h
#define AppliquerSortDuree_h

#include "sort/SortAppliquerSurCase.h"
#include "Case.h"

class AppliquerSortDuree: public SortAppliquerSurCase
{
public:
    virtual void appliquerSortSurCase(Case &cible, Sort* sortExecutant);
    virtual void retirerSortDeCase(Case &cible, Sort* sortExecutant);
};

#endif
