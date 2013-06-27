#include "UsineSort.h"
#include "sort/AppliqueDegat.h"
#include "sort/AppliqueControle.h"

Sort* UsineSort::fabriqueSort(string const& nom)
{
    Sort* retour = NULL;
    if(nom == "Sceau de Controle")
    {
        retour = new Sort("Sceau de Controle", 1, false, 5, 100, 1, 0, 0, 0, 0, 0);
        retour->ajouterApplication(new AppliqueControle());
        retour->setDescription("Sort permettant de prendre le controle d'une case");
    }
    if(nom == "Boule de Feu")
    {
        retour = new Sort("Boule de Feu", 1, false, 5, 100, 1, 5, 0, 0, 0, 0);
        retour->ajouterApplication(new AppliqueDegat());
        retour->setDescription("Lance une boule de feu infligeant 5 dégats");
    }
    if(nom == "Rune de Protection")
    {
//        return new RuneDeProtection();
    }
    if(nom == "Sort Test Duree")
    {
//        return new SortTestDuree();
    }
    return retour;
}

std::vector<string> UsineSort::liste()
{
    vector<string> retour;
    retour.push_back("Sceau de Controle");
    retour.push_back("Boule de Feu");
    retour.push_back("Rune de Protection");
    return retour;
}
