#ifndef AppliquerConditionComparaisonMana_h
#define AppliquerConditionComparaisonMana_h

#include "sort/SortAppliquerSurCase.h"
#include "sort/ManipulationAppliquerSurCase.h"

class AppliqueConditionComparaisonMana: public SortAppliquerSurCase, public ManipulationAppliquerSurCase
{
    int difference;
    bool superieur, ajout, retrait;
public:
    AppliqueConditionComparaisonMana(int difference, bool superieur, bool ajout, bool retrait); //type = true = pourcentage
    virtual void appliquerSortSurCase(Case &cible, Sort* sortExecutant);
    virtual void retirerSortDeCase(Case &cible, Sort* sortExecutant);
    bool verifierCondition(Case &cible, Sort* sortExecutant);
};

#endif
