#include "sort/actionApplique/AppliqueSoinAstral.h"

AppliqueSoinAstral::AppliqueSoinAstral(int valeur, bool ajout, bool retrait)
{
    this->valeurSoin = valeur;
    this->ajout = ajout;
    this->retrait = retrait;
}
void AppliqueSoinAstral::appliquerSortSurCase(Case &cible, Sort* sortExecutant)
{
    if(this->ajout == true)
    {
        cible.modifierDefense(this->valeurSoin*sortExecutant->getCoupManaParCase());
    }
}

void AppliqueSoinAstral::retirerSortDeCase(Case &cible, Sort* sortExecutant)
{
    if(this->retrait == true)
    {
        cible.modifierDefense(this->valeurSoin*sortExecutant->getCoupManaParCase());
    }
}
