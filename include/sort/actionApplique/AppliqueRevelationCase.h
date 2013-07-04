#ifndef AppliqueRevelationCase_h
#define AppliqueRevelationCase_h

#include "sort/SortAppliquerSurCase.h"
#include "Case.h"

class AppliqueRevelationCase: public SortAppliquerSurCase
{
public:
    virtual void appliquerSortSurCase(Case &cible, Sort* sortExecutant);
    virtual void retirerSortDeCase(Case &cible, Sort* sortExecutant);
};

#endif
