#include "sort/actionApplique/AppliqueBaseProtection.h"

AppliqueBaseProtection::AppliqueBaseProtection(int valeur)
{
    this->valeur = valeur;
}

void AppliqueBaseProtection::appliquerSortSurCase(Case &cible, Sort* sortExecutant)
{
    cible.modifierDefenseReel(this->valeur);
}
void AppliqueBaseProtection::retirerSortDeCase(Case &cible, Sort* sortExecutant)
{
    cible.modifierDefenseReel(-this->valeur);
}
