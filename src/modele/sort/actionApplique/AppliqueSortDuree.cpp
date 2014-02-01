#include "sort/actionApplique/AppliqueSortDuree.h"

AppliquerSortDuree::AppliquerSortDuree(NoeudRecetteSort* n)
{
   duree = n->getValeurFilsInt("duree");
}

void AppliquerSortDuree::appliquerSortSurCase(Case &cible, Sort* sortExecutant)
{
    Sort* sort = NULL;
    sort = UsineSort::fabriqueSort(sortExecutant);
    cible.ajouterSort(sort, duree);
}
void AppliquerSortDuree::retirerSortDeCase(Case &cible, Sort* sortExecutant)
{
}
