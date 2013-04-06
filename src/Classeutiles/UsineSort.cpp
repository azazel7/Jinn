#include "UsineSort.h"

Sort* UsineSort::fabriqueSort(string const& nom)
{
    if(nom == "Sceau de Controle")
    {
        return new SceauControle();
    }
    return NULL;
}

std::vector<string> liste()
{
    vector<string> retour;
    retour.push_back("Sceau de Controle");
    return retour;
}
