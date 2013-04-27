#include "UsineSort.h"

Sort* UsineSort::fabriqueSort(string const& nom)
{
    if(nom == "Sceau de Controle")
    {
        return new SceauControle();
    }
    if(nom == "Boule de Feu")
    {
        return new BouleDeFeu();
    }
    if(nom == "Rune de Protection")
    {
        return new RuneDeProtection();
    }
    if(nom == "Sort Test Duree")
    {
        return new SortTestDuree();
    }
    return NULL;
}

std::vector<string> UsineSort::liste()
{
    vector<string> retour;
    retour.push_back("Sceau de Controle");
    retour.push_back("Boule de Feu");
    retour.push_back("Rune de Protection");
    return retour;
}
