#include "sort/actionApplique/AppliqueConditionDefense.h"

AppliqueConditionDefense::AppliqueConditionDefense(int palier, bool type, bool ajout, bool retrait) //type = true = pourcentage
{
    this->palier = palier;
    this->type = type;
    this->ajout = ajout;
    this->retrait = retrait;
}

void AppliqueConditionDefense::appliquerSortSurCase(Case &cible, Sort* sortExecutant)
{
    if(this->ajout == false)
    {
        return;
    }
    if(this->verifierCondition(cible, sortExecutant) == true)
    {
        this->appliquerListeEffet(cible, sortExecutant);
        this->conditionAppliction = true;
    }
}

void AppliqueConditionDefense::retirerSortDeCase(Case &cible, Sort* sortExecutant)
{
    if(this->retrait == false)
    {
        return;
    }
    if(this->conditionAppliction == true || this->verifierCondition(cible, sortExecutant) == true)
    {
        this->retirerListeEffet(cible, sortExecutant);
    }
}

bool AppliqueConditionDefense::verifierCondition(Case &cible, Sort* sortExecutant)
{
    if(type == true)
    {
        int pourcentage = floor((cible.getDefenseActuelle()*100)/cible.getDefenseReel());
        if(pourcentage > this->palier)
        {
            return true;
        }
    }
    else
    {
        if(cible.getDefenseActuelle() < this->palier)
        {
            return true;
        }
    }
    return false;
}
