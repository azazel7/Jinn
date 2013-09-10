#ifndef AppliqueConsommerMana_h
#define AppliqueConsommerMana_h

#include "sort/SortAppliquerSurCase.h"
#include "Case.h"

class AppliqueConsommerMana: public SortAppliquerSurCase
{
    int valeurSoin;
    bool type, ajout, retrait;
public:
    AppliqueConsommerMana(int valeur, bool type, bool ajout, bool retrait);
    virtual void appliquerSortSurCase(Case &cible, Sort* sortExecutant);
    virtual void retirerSortDeCase(Case &cible, Sort* sortExecutant);
};

#endif
