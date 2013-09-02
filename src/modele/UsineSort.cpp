#include "UsineSort.h"
#include "sort/actionApplique/AppliqueDegat.h"
#include "sort/actionApplique/AppliqueControle.h"
#include "sort/actionApplique/AppliqueBaseProtection.h"
#include "sort/actionApplique/AppliqueRevelationCase.h"
#include "sort/actionApplique/AppliqueSortDuree.h"
#include "sort/actionApplique/AppliqueSoin.h"

#include "sort/actionChronique/chroniqueDegat.h"
#include "sort/actionChronique/chroniqueDegatCumulatif.h"
#include "sort/actionChronique/chroniqueSoin.h"
#include "sort/actionChronique/chroniqueSoinCondVie.h"

Sort* UsineSort::fabriqueSort(string const& nom)
{
    Sort* retour = NULL;
    if(nom == "Sceau de Controle")
    {
        retour = new Sort("Sceau de Controle", 1, false, 5, 100, 1, 0, 0, 0, 0, 0, NEUTRE);
        retour->ajouterApplication(new AppliqueControle());
        retour->setDescription("Sort permettant de prendre le controle d'une case");
    }
    else if(nom == "Boule de Feu")
    {
        retour = new Sort("Boule de Feu", 5, false, 5, 100, 1, 50, 0, 0, 0, 0, FEU);
        retour->ajouterApplication(new AppliqueDegat());
        retour->setDescription("Lance une boule de feu infligeant 50 degats");
    }
    else if(nom == "Rune de Protection")
    {
        retour = new Sort("Rune de Protection", 5, false, 5, 100, 1, 0, 3, 0, 0, 0, NEUTRE);
        retour->ajouterApplication(new AppliquerSortDuree());
        retour->ajouterApplication(new AppliqueBaseProtection(40));
        retour->setDescription("Augmente la defense maximal d'une case de 1 pendant 3 tours");
    }
    else if(nom == "Sceau de Vision")
    {
        retour = new Sort("Sceau de Vision", 1, false, 5, 100, 1, 0, 0, 0, 0, 0, NEUTRE);
        retour->ajouterApplication(new AppliqueRevelationCase());
        retour->setDescription("Sort permettant de visualiser une case");
    }
    else if(nom == "Spirale de Feu")
    {
        retour = new Sort("Spirale de Feu", 7, false, 5, 90, 1, 0, 5, 0, 0, 0, FEU);
        retour->ajouterActionChronique(new ChroniqueDegat(8));
        retour->ajouterApplication(new AppliquerSortDuree());
        retour->setDescription("Piege la case dans une spirale de feu infligeant 8 points de degats par tour");
    }
    else if(nom == "Esprit Patient")
    {
        retour = new Sort("Esprit Patient", 10, false, 5, 90, 1, 0, 2, 0, 0, 0, LUMIERE);
        retour->ajouterApplication(new AppliquerSortDuree());
        retour->ajouterApplication(new AppliqueSoin(120, false, true));
        retour->setDescription("A la fin de la duree du sort, Esprit Patient redonne 120 point de defense a la case");
    }
    return retour;
}

std::vector<string> UsineSort::liste()
{
    vector<string> retour;
    retour.push_back("Sceau de Controle");
    retour.push_back("Boule de Feu");
    retour.push_back("Rune de Protection");
    retour.push_back("Sceau de Vision");
    retour.push_back("Spirale de Feu");
    retour.push_back("Esprit Patient");
    return retour;
}

Sort* UsineSort::fabriqueSort(Sort* sortModele)
{
    Sort* sort = UsineSort::fabriqueSort(sortModele->getNom());
    sort->setProprietaire(sortModele->getProprietaire());
    sort->setOrigine(sortModele->getOrigine());
    sort->setId(sortModele->getId());
    return sort;
}
