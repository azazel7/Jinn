#include "sort/actionApplique/AppliqueBaseProtection.h"

void AppliqueBaseProtection::appliquerSortSurCase(Case &cible, Sort* sortExecutant)
{
    cible.modifierDefenseReel(+1);
}
void AppliqueBaseProtection::retirerSortDeCase(Case &cible, Sort* sortExecutant)
{
    cible.modifierDefenseReel(-1);
}
