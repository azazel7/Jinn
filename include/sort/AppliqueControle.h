#ifndef AppliquerControle_h
#define AppliquerControle_h

#include "sort/SortAppliquerSurCase.h"
#include "Case.h"

class AppliqueControle: public SortAppliquerSurCase
{
    public:
    virtual void appliquerSortSurCase(Case &cible, Sort* sortExecutant);
    virtual void retirerSortDeCase(Case &cible, Sort* sortExecutant);
};

#endif
