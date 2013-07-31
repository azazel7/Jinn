#include "sort/actionApplique/AppliqueDegat.h"
#include "Case.h"

void AppliqueDegat::appliquerSortSurCase(Case &cible, Sort* sortExecutant)
{
    cible.modifierDefense(sortExecutant->getAttaque());
}
void AppliqueDegat::retirerSortDeCase(Case &cible, Sort* sortExecutant)
{

}
