#ifndef AppliquerVolDefense_h
#define AppliquerVolDefense_h

#include "sort/SortAppliquerSurCase.h"
#include "Case.h"

class AppliqueVolDefense: public SortAppliquerSurCase
{
    int degat;
    bool defenseMax, pourcentage, ajout, retrait;
public:
    AppliqueVolDefense(int degat, bool pourcentage, bool ajout, bool retrait, bool defenseMax); //type = true => pourcentage
    virtual void appliquerSortSurCase(Case &cible, Sort* sortExecutant);
    virtual void retirerSortDeCase(Case &cible, Sort* sortExecutant);
    void infliger(Case &cible, Sort* sortExecutant);
};

#endif
