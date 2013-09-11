#include "sort/actionApplique/AppliqueConditionPresenceSort.h"

AppliqueConditionPresenceSort::AppliqueConditionPresenceSort(string nom, bool proprioEgal, bool ajout, bool retrait)
{
    this->nom = nom;
    this->proprioEgal = proprioEgal;
    this->ajout = ajout;
    this->retrait = retrait;
}

void AppliqueConditionPresenceSort::appliquerSortSurCase(Case &cible, Sort* sortExecutant)
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

void AppliqueConditionPresenceSort::retirerSortDeCase(Case &cible, Sort* sortExecutant)
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

bool AppliqueConditionPresenceSort::verifierCondition(Case &cible, Sort* sortExecutant)
{
    if(cible.getListSort().size() == 0)
    {
        return false;
    }
    //FIXME boucle infini dans le find_if
    auto trouve = find_if(cible.getListSort().begin(), cible.getListSort().end(), PredicatChercherSort(this->nom));
    if( trouve != cible.getListSort().end())
    {
        return true;
    }
    return false;
}

PredicatChercherSort::PredicatChercherSort(string nom)
{
    this->nom = nom;
}

bool PredicatChercherSort::operator()(pair<int, Sort*> const& pair) const
{
    Sort* sort = pair.second;
    if(sort != NULL && sort->getNom() == this->nom)
    {
        return true;
    }
    return false;
}
