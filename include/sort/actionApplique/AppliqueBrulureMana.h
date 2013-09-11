#ifndef AppliquerBrulureMana_h
#define AppliquerBrulureMana_h

#include "sort/SortAppliquerSurCase.h"
#include "Case.h"

class AppliqueBrulureMana: public SortAppliquerSurCase
{
    int degat;
    bool peutTuer, manaMax, type, ajout, retrait;
public:
    AppliqueBrulureMana(int degat, bool type, bool ajout, bool retrait, bool manaMax, bool peutTuer); //type = true => pourcentage
    virtual void appliquerSortSurCase(Case &cible, Sort* sortExecutant);
    virtual void retirerSortDeCase(Case &cible, Sort* sortExecutant);
    void infliger(Case &cible, Sort* sortExecutant);
};

#endif
