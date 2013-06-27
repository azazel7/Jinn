#ifndef AppliquerBaseProtection_h
#define AppliquerBaseProtection_h

#include "sort/SortAppliquerSurCase.h"
#include "Case.h"

class AppliqueBaseProtection: public SortAppliquerSurCase
{
    public:
    virtual void appliquerSortSurCase(Case &cible, Sort* sortExecutant);
    virtual void retirerSortDeCase(Case &cible, Sort* sortExecutant);
};

#endif
