#include "UsineSort.h"
#include "sort/actionApplique/AppliqueDegat.h"
#include "sort/actionApplique/AppliqueControle.h"
#include "sort/actionApplique/AppliqueBaseProtection.h"
#include "sort/actionApplique/AppliqueRevelationCase.h"
#include "sort/actionApplique/AppliqueSortDuree.h"
#include "sort/actionApplique/AppliqueSoin.h"
#include "sort/actionApplique/AppliqueDegatCondVie.h"
#include "sort/actionApplique/AppliqueConditionDefense.h"

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
        retour = new Sort("Boule de Feu", 5, false, 5, 100, 1, 0, 0, 0, 0, 0, FEU);
        retour->ajouterApplication(new AppliqueDegat(50));
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
    else if(nom == "Chaleur de Savane")
    {
        retour = new Sort("Chaleur de Savane", 20, true, 5, 90, 1, 0, 5, 0, 0, 0, FEU);
        retour->ajouterApplication(new AppliquerSortDuree());
        retour->ajouterActionChronique(new ChroniqueDegatCumulatif(8, 8));
        retour->setDescription("Sort durant 5 tours et infligeant a la case 8 point de degat par tour d'activation");
    }
    else if(nom == "Esprit Gardien")
    {
        retour = new Sort("Esprit Gardien", 7, false, 5, 90, 1, 0, 10, 0, 0, 0, TERRE);
        retour->ajouterApplication(new AppliquerSortDuree());
        retour->ajouterActionChronique(new ChroniqueSoinCondVie(30, 50, true));
        retour->setDescription("Pendant 10 tours, si la case cible a moins de 50% de sa defense, le sort lui redonne 30 point de vie");
    }
    else if(nom == "Frappe Sournoise")
    {
        retour = new Sort("Frappe Sournoise", 6, false, 5, 90, 1, 0, 0, 0, 0, 0, TENEBRE);
        AppliqueConditionDefense* cond = new AppliqueConditionDefense(90, true, true, false);
        cond->ajouterApplication(new AppliqueDegat(70));
        retour->ajouterApplication(new AppliqueDegat(30));
        retour->ajouterApplication(cond);
        retour->setDescription("Inflige 30 points de degat. Si la cible a plus de 90% de sa vie, inflige 70 points de degat supplementaire");
    }
    else if(nom == "Choc Spirituel")
    {

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
    retour.push_back("Chaleur de Savane");
    retour.push_back("Esprit Gardien");
    retour.push_back("Frappe Sournoise");
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
