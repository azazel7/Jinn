#ifndef AppliquerConditionPresenceSort_h
#define AppliquerConditionPresenceSort_h

#include "sort/SortAppliquerSurCase.h"
#include "sort/ManipulationAppliquerSurCase.h"

class AppliqueConditionPresenceSort: public SortAppliquerSurCase, public ManipulationAppliquerSurCase
{
    string nom;
    bool proprioEgal, ajout, retrait;
public:
    AppliqueConditionPresenceSort(string nom, bool proprioEgal, bool ajout, bool retrait); //type = true = pourcentage
    virtual void appliquerSortSurCase(Case &cible, Sort* sortExecutant);
    virtual void retirerSortDeCase(Case &cible, Sort* sortExecutant);
    bool verifierCondition(Case &cible, Sort* sortExecutant);
};

namespace
{
    class PredicatChercherSort
    {
        string nom;
    public:
        PredicatChercherSort(string nom);
        bool operator()(pair<int, Sort*> const& square) const;
    };
}
#endif
