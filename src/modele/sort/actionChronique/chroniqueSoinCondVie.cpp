#include "sort/actionChronique/chroniqueSoinCondVie.h"

ChroniqueSoinCondVie::ChroniqueSoinCondVie(int soin, int palier, bool type)
{
    this->palier = palier;
    this->soin = soin;
    this->type = type;
}

void ChroniqueSoinCondVie::effectuerActionChronique(Case &cible, Sort *sortExecutant)
{
    if(type == true)
    {
        int pourcentage = floor((cible.getDefenseActuelle()*100)/cible.getDefenseReel());
        if(pourcentage < this->palier)
        {
            cible.modifierDefense(this->soin);
        }
    }
    else
    {
        if(cible.getDefenseActuelle() < this->palier)
        {
            cible.modifierDefense(this->soin);
        }
    }
}
