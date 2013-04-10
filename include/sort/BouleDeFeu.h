#ifndef BouleDeFeu_h
#define BouleDeFeu_h

#include "Sort.h"
#include "Case.h"


class BouleDeFeu : public Sort
{
    public:
    BouleDeFeu();
    virtual void appliquerSortSurCase(Case &cible);
    virtual void modifierSuivantOrigine(Case const& origine);
    virtual void modifierSuivantProprietaire();
    virtual void retirerDeCase(Case &cible);
    virtual void effectuerActionChronique(Case &cible);
    virtual string description();
};


#endif // BouleDeFeu_h
