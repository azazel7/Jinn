#include "sort/actionApplique/AppliqueConditionMana.h"

AppliqueConditionMana::AppliqueConditionMana(int palier, bool type, bool ajout, bool retrait) //type = true = pourcentage
{
    this->palier = palier;
    this->type = type;
    this->ajout = ajout;
    this->retrait = retrait;
}

void AppliqueConditionMana::appliquerSortSurCase(Case &cible, Sort* sortExecutant)
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

void AppliqueConditionMana::retirerSortDeCase(Case &cible, Sort* sortExecutant)
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

bool AppliqueConditionMana::verifierCondition(Case &cible, Sort* sortExecutant)
{
    Joueur* proprio = cible.getProprietaire();
    if(proprio == NULL)
    {
        return false;
    }
    if(type == true)
    {
        int pourcentage = floor((proprio->getManaActuel()*100)/proprio->getManaMaximum());
        if(pourcentage > this->palier)
        {
            return true;
        }
    }
    else
    {
        if(proprio->getManaActuel() < this->palier)
        {
            return true;
        }
    }
    return false;
}
