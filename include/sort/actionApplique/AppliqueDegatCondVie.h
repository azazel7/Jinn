#ifndef AppliquerDegatCondVie_h
#define AppliquerDegatCondVie_h

#include "sort/SortAppliquerSurCase.h"

class AppliqueDegatCondVie: public SortAppliquerSurCase
{
    int degat;
    int palier;
    bool type, ajout, retrait;
public:
    AppliqueDegatCondVie(int degat, int palier, bool type, bool ajout, bool retrait); //type = true = pourcentage
    virtual void appliquerSortSurCase(Case &cible, Sort* sortExecutant);
    virtual void retirerSortDeCase(Case &cible, Sort* sortExecutant);
    void infligerDegat(Case &cible);
};

#endif
