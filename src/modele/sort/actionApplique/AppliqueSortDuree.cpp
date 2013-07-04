#include "sort/actionApplique/AppliqueSortDuree.h"

void AppliquerSortDuree::appliquerSortSurCase(Case &cible, Sort* sortExecutant)
{
    Sort* sort = NULL;
    sort = UsineSort::fabriqueSort(sortExecutant);
    cible.ajouterSort(sort, sort->getDuree());
}
void AppliquerSortDuree::retirerSortDeCase(Case &cible, Sort* sortExecutant)
{
}
