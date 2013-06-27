#include "sort/AppliqueControle.h"

void AppliqueControle::appliquerSortSurCase(Case &cible, Sort* sortExecutant)
{
        if(cible.getDefenseActuelle() <= 0)
        {
                cible.setProprietaire(sortExecutant->getProprietaire());
        }
}

void AppliqueControle::retirerSortDeCase(Case &cible, Sort* sortExecutant)
{

}
