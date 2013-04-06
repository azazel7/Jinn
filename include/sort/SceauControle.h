#ifndef SceauControle_h
#define SceauControle_h

#include "Sort.h"
#include "Case.h"


class SceauControle : public Sort
{
    public:
    SceauControle();
    virtual void appliquerSortSurCase(Case &cible);
    virtual void modifierSuivantOrigine(Case const& origine);
    virtual void modifierSuivantProprietaire();
    virtual void retirerDeCase(Case &cible);
    virtual string description();
};


#endif // SceauControle_h
