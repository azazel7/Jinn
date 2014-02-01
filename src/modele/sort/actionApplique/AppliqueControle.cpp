#include "sort/actionApplique/AppliqueControle.h"
#include "Case.h"
#include "NoeudRecetteSort.h"


AppliqueControle::AppliqueControle(NoeudRecetteSort* n)
{

}

void AppliqueControle::appliquerSortSurCase(Case &cible, Sort* sortExecutant)
{
        cible.setProprietaire(sortExecutant->getProprietaire());
}

void AppliqueControle::retirerSortDeCase(Case &cible, Sort* sortExecutant)
{

}
