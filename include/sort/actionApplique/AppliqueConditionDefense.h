#ifndef AppliquerConditionDefense_h
#define AppliquerConditionDefense_h

#include "sort/SortAppliquerSurCase.h"
#include "sort/ManipulationAppliquerSurCase.h"

class AppliqueConditionDefense: public SortAppliquerSurCase, public ManipulationAppliquerSurCase
{
    int palier;
    bool type, ajout, retrait, inferieur, egal;
public:
    AppliqueConditionDefense(NoeudRecetteSort* n);
    AppliqueConditionDefense(int palier, bool type, bool ajout, bool retrait); //type = true = pourcentage
    virtual void appliquerSortSurCase(Case &cible, Sort* sortExecutant);
    virtual void retirerSortDeCase(Case &cible, Sort* sortExecutant);
    bool verifierCondition(Case &cible, Sort* sortExecutant);
};

#endif
