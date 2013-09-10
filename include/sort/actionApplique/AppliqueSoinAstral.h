#ifndef AppliqueSoinAstral_h
#define AppliqueSoinAstral_h

#include "sort/SortAppliquerSurCase.h"
#include "Case.h"

class AppliqueSoinAstral: public SortAppliquerSurCase
{
    int valeurSoin;
    bool ajout, retrait;
public:
    AppliqueSoinAstral(int valeur, bool ajout, bool retrait);
    virtual void appliquerSortSurCase(Case &cible, Sort* sortExecutant);
    virtual void retirerSortDeCase(Case &cible, Sort* sortExecutant);
};

#endif
