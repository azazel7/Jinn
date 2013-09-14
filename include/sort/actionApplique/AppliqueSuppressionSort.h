#ifndef AppliqueSuppressionSort_h
#define AppliqueSuppressionSort_h

#include "sort/SortAppliquerSurCase.h"
#include "Case.h"

class AppliqueSuppressionSort: public SortAppliquerSurCase
{
    int nombreSort, probabilite;
    bool ajout, retrait, sortEnnemi;
public:
    AppliqueSuppressionSort(int nombreSort, bool ajout, bool retrait, bool sortEnnemi = true, int probabilite = 100);
    virtual void appliquerSortSurCase(Case &cible, Sort* sortExecutant);
    virtual void retirerSortDeCase(Case &cible, Sort* sortExecutant);
    void infliger(Case &cible, Sort* sortExecutant);
};
namespace
{
    class PredicatCompterSort
    {
        bool sortEnnemi;
        Sort* sortExecutant;
    public:
        PredicatCompterSort(bool sortEnnemi, Sort* sortExecutant);
        bool operator()(pair<int, Sort*> const& paire) const;
        static bool estEligible(bool sortEnnemi, Sort* sortSurCase, Sort* sortExecutant);
    };
}
#endif
