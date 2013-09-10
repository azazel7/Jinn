#include "sort/ManipulationAppliquerSurCase.h"

ManipulationAppliquerSurCase::ManipulationAppliquerSurCase()
{
    this->conditionAppliction = false;
}

void ManipulationAppliquerSurCase::appliquerListeEffet(Case &cible, Sort* sort)
{
    for(int i = 0; i < this->listeApplicationSurCase.size(); i++)
    {
        this->listeApplicationSurCase[i]->appliquerSortSurCase(cible, sort);
    }
}

void ManipulationAppliquerSurCase::retirerListeEffet(Case &cible, Sort *sort)
{
    for(int i = 0; i < this->listeApplicationSurCase.size(); i++)
    {
        this->listeApplicationSurCase[i]->retirerSortDeCase(cible, sort);
    }
}

void ManipulationAppliquerSurCase::ajouterApplication(SortAppliquerSurCase* newEffect)
{
    this->listeApplicationSurCase.push_back(newEffect);
}
