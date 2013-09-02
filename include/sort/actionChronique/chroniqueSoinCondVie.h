#ifndef ChroniqueSoinCondVie_h
#define ChroniqueSoinCondVie_h

#include "sort/Sort.h"
#include "sort/SortActionChronique.h"

class ChroniqueSoinCondVie : public SortActionChronique
{
    int soin;
    int palier;
    bool type; //True = pourcentage / False = Point de defense
    public:
    ChroniqueSoinCondVie(int soin, int palier, bool type);
    void effectuerActionChronique(Case &cible, Sort *sortExecutant);
};

#endif
