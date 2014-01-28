#include "sort/actionApplique/AppliqueConditionComparaisonMana.h"
#include "Case.h"
#include "Joueur.h"

AppliqueConditionComparaisonMana::AppliqueConditionComparaisonMana(int difference, bool superieur, bool ajout, bool retrait) //type = true = pourcentage
{
    this->difference = difference;
    this->ajout = ajout;
    this->superieur = superieur;
    this->retrait = retrait;
}

void AppliqueConditionComparaisonMana::appliquerSortSurCase(Case &cible, Sort* sortExecutant)
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

void AppliqueConditionComparaisonMana::retirerSortDeCase(Case &cible, Sort* sortExecutant)
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

bool AppliqueConditionComparaisonMana::verifierCondition(Case &cible, Sort* sortExecutant)
{
    Joueur* proprio = cible.getProprietaire();
    if(proprio == NULL)
    {
        return false;
    }
    if(this->superieur == true)
    {
        if(proprio->getManaActuel() > sortExecutant->getProprietaire()->getManaActuel() + this->difference)
        {
            return true;
        }
    }
    else
    {
        if(proprio->getManaActuel() + this->difference < sortExecutant->getProprietaire()->getManaActuel())
        {
            return true;
        }
    }
    return false;
}
