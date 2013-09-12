#ifndef ChroniqueVisionJoueur_h
#define ChroniqueVisionJoueur_h

#include "sort/Sort.h"
#include "Case.h"
#include "sort/SortActionChronique.h"

class ChroniqueVisionJoueur : public SortActionChronique
{
    public:
    void effectuerActionChronique(Case &cible, Sort *sortExecutant);
};

#endif
