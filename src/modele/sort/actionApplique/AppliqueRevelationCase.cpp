#include "sort/actionApplique/AppliqueRevelationCase.h"

void AppliqueRevelationCase::appliquerSortSurCase(Case &cible, Sort* sortExecutant)
{
    sortExecutant->getProprietaire()->notifierCase(cible, false);
}

void AppliqueRevelationCase::retirerSortDeCase(Case &cible, Sort* sortExecutant)
{

}
