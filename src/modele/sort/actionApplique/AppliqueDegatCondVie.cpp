#include "sort/actionApplique/AppliqueDegatCondVie.h"

AppliqueDegatCondVie::AppliqueDegatCondVie(int degat, int palier, bool type, bool ajout, bool retrait) //type = true = pourcentage
{
    this->degat = degat;
    this->palier = palier;
    this->type = type;
    this->ajout = ajout;
    this->retrait = retrait;
}

void AppliqueDegatCondVie::appliquerSortSurCase(Case &cible, Sort* sortExecutant)
{
    if(this->ajout == false)
    {
        return;
    }
    this->infligerDegat(cible);
}

void AppliqueDegatCondVie::retirerSortDeCase(Case &cible, Sort* sortExecutant)
{
    if(this->retrait == false)
    {
        return;
    }
    this->infligerDegat(cible);
}

void AppliqueDegatCondVie::infligerDegat(Case &cible)
{
    if(type == true)
    {
        int pourcentage = floor((cible.getDefenseActuelle()*100)/cible.getDefenseReel());
        if(pourcentage > this->palier)
        {
            cible.modifierDefense(-this->degat);
        }
    }
    else
    {
        if(cible.getDefenseActuelle() < this->palier)
        {
            cible.modifierDefense(-this->degat);
        }
    }

}
