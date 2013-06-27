#include "sort/AppliqueBaseProtection.h"

void AppliqueBaseProtection::appliquerSortSurCase(Case &cible, Sort* sortExecutant)
{
        Sort& sort = *sortExecutant;
        cible.modifierDefenseReel(+1);
        cible.ajouterSort(&sort, sort.getDuree());

}
void AppliqueBaseProtection::retirerSortDeCase(Case &cible, Sort* sortExecutant)
{
        cible.modifierDefenseReel(-1);
}
