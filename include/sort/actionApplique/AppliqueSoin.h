#ifndef AppliqueSoin_h
#define AppliqueSoin_h

#include "sort/SortAppliquerSurCase.h"
#include "Case.h"

class AppliqueSoin: public SortAppliquerSurCase
{
    int valeurSoin;
    bool ajout, retrait;
public:
    AppliqueSoin(int valeur, bool ajout, bool retrait);
    virtual void appliquerSortSurCase(Case &cible, Sort* sortExecutant);
    virtual void retirerSortDeCase(Case &cible, Sort* sortExecutant);
};

#endif
