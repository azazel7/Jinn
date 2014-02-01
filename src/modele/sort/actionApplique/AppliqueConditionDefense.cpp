#include "sort/actionApplique/AppliqueConditionDefense.h"
#include "Case.h"

AppliqueConditionDefense::AppliqueConditionDefense(NoeudRecetteSort* n)
{
    palier = n->getValeurFilsInt("floor");
    type = n->getValeurFilsBool("type");
    ajout = n->getValeurFilsBool("onAdd");
    retrait = n->getValeurFilsBool("onWithdraw");
    inferieur = n->getValeurFilsBool("inferieur");
    egal = n->getValeurFilsBool("egal");
}

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
    int pourcentage;
    if(type == true)
    {
        pourcentage = floor((cible.getDefenseActuelle()*100)/cible.getDefenseReel());
    }
    else
    {
        pourcentage = cible.getDefenseActuelle();
    }
    if(this->inferieur == true && this->egal == false && pourcentage < this->palier)
    {
        return true;
    }
    else if(this->inferieur == true && this->egal == true && pourcentage <= this->palier)
    {
        return true;
    }
    else if(this->inferieur == false && this->egal == false && pourcentage > this->palier)
    {
        return true;
    }
    else if(this->inferieur == false && this->egal == true && pourcentage >= this->palier)
    {
        return true;
    }
    return false;
}
