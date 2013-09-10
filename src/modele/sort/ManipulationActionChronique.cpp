#include "sort/ManipulationActionChronique.h"


void ManipulationActionChronique::effectuerActionChronique(Case &cible, Sort* sort)
{
    for(int i = 0; i < this->listeEffetChronique.size(); i++)
    {
        this->listeEffetChronique[i]->effectuerActionChronique(cible, sort);
    }
}

void ManipulationActionChronique::ajouterActionChronique(SortActionChronique* newEffect)
{
    this->listeEffetChronique.push_back(newEffect);
}
