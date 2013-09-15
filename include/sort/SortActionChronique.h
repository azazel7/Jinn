#ifndef SortActionChronique_h
#define SortActionChronique_h

#include "sort/Sort.h"
#include "Case.h"

class SortActionChronique
{
    public:
    /**
     * @brief effectuerActionChronique Effectue un effet sur la case cible en fonction du sort
     * @param cible La case cible
     * @param sortExecutant Le sort produisant cet effet
     */
    virtual void effectuerActionChronique(Case &cible, Sort *sortExecutant) = 0;

    virtual ~SortActionChronique();
};

#endif
