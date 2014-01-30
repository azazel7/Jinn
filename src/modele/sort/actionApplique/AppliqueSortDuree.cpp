#include "sort/actionApplique/AppliqueSortDuree.h"

AppliquerSortDuree::AppliquerSortDuree(NoeudRecetteSort* n)
{
   duree = n->getValeurFilsInt("duree");
   cerr << "Duree : " << duree << endl;
}

void AppliquerSortDuree::appliquerSortSurCase(Case &cible, Sort* sortExecutant)
{
    cerr << "Application duree : " << duree << endl;
    Sort* sort = NULL;
    sort = UsineSort::fabriqueSort(sortExecutant);
    cible.ajouterSort(sort, duree);
}
void AppliquerSortDuree::retirerSortDeCase(Case &cible, Sort* sortExecutant)
{
}
