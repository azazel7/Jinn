#include "sort/actionApplique/AppliqueSoin.h"

AppliqueSoin::AppliqueSoin(int valeur, bool ajout, bool retrait)
{
    this->valeurSoin = valeur;
    this->ajout = ajout;
    this->retrait = retrait;
}
void AppliqueSoin::appliquerSortSurCase(Case &cible, Sort* sortExecutant)
{
    if(this->ajout == true)
    {
        cible.modifierDefense(this->valeurSoin);
    }
}

void AppliqueSoin::retirerSortDeCase(Case &cible, Sort* sortExecutant)
{
    if(this->retrait == true)
    {
        cible.modifierDefense(this->valeurSoin);
    }
}
