#ifndef AppliquerControle_h
#define AppliquerControle_h

#include "sort/SortAppliquerSurCase.h"

class Case;

class AppliqueControle: public SortAppliquerSurCase
{
public:
    AppliqueControle(NoeudRecetteSort* n);
    virtual void appliquerSortSurCase(Case &cible, Sort* sortExecutant);
    virtual void retirerSortDeCase(Case &cible, Sort* sortExecutant);
};

#endif
