#include "sort/actionApplique/AppliqueVolDefense.h"

AppliqueVolDefense::AppliqueVolDefense(int degat, bool pourcentage, bool ajout, bool retrait, bool defenseMax)
{
    this->degat = degat;
    this->ajout = ajout;
    this->retrait = retrait;
    this->pourcentage = pourcentage;
    this->defenseMax = defenseMax;
}

void AppliqueVolDefense::appliquerSortSurCase(Case &cible, Sort* sortExecutant)
{
    if(this->ajout == false)
    {
        return;
    }
    this->infliger(cible, sortExecutant);
}
void AppliqueVolDefense::retirerSortDeCase(Case &cible, Sort* sortExecutant)
{
    if(this->retrait == false)
    {
        return;
    }
    this->infliger(cible, sortExecutant);
}

void AppliqueVolDefense::infliger(Case &cible, Sort* sortExecutant)
{
    Case* origine = sortExecutant->getOrigine();
    int deg = 0;
    if(origine == NULL)
    {
        return;
    }
    if(this->pourcentage == true)
    {
        if(this->defenseMax == true)
        {
            deg = floor((cible.getDefenseReel()*this->degat)/100);
        }
        else
        {
            deg = floor((cible.getDefenseActuelle()*this->degat)/100);
        }
    }
    else
    {
        deg = this->degat;
    }
    if(deg > cible.getDefenseActuelle())
    {
        deg = cible.getDefenseActuelle();
    }
    cible.modifierDefense(-deg);
    origine->modifierDefense(+deg);
}
