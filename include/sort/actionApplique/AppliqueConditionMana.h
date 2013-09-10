#ifndef AppliquerConditionMana_h
#define AppliquerConditionMana_h

#include "sort/SortAppliquerSurCase.h"
#include "sort/ManipulationAppliquerSurCase.h"

class AppliqueConditionMana: public SortAppliquerSurCase, public ManipulationAppliquerSurCase
{
    int degat;
    int palier;
    bool type, ajout, retrait;
public:
    AppliqueConditionMana(int palier, bool type, bool ajout, bool retrait); //type = true = pourcentage
    virtual void appliquerSortSurCase(Case &cible, Sort* sortExecutant);
    virtual void retirerSortDeCase(Case &cible, Sort* sortExecutant);
    bool verifierCondition(Case &cible, Sort* sortExecutant);
};

#endif
