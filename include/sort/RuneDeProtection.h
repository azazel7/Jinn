#ifndef RuneDeProtection_h
#define RuneDeProtection_h

#include "Sort.h"
#include "Case.h"


class RuneDeProtection : public Sort
{
    public:
    RuneDeProtection();
    virtual void appliquerSortSurCase(Case &cible);
    virtual void modifierSuivantOrigine(Case const& origine);
    virtual void modifierSuivantProprietaire();
    virtual void retirerDeCase(Case &cible);
    virtual void effectuerActionChronique(Case &cible);
    virtual string description();

private:
    int modificationDefense;

};


#endif // RuneDeProtection_h
