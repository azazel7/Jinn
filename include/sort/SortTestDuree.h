#ifndef SortTestDuree_h
#define SortTestDuree_h

#include <iostream>
#include "Sort.h"
#include "Case.h"


class SortTestDuree : public Sort
{
    public:
    SortTestDuree();
    virtual void appliquerSortSurCase(Case &cible);
    virtual void modifierSuivantOrigine(Case const& origine);
    virtual void modifierSuivantProprietaire();
    virtual void retirerDeCase(Case &cible);
    virtual void effectuerActionChronique(Case &cible);
    virtual string description();
};


#endif // SortTestDuree_h
