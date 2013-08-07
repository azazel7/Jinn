#include "Tools.h"

vector<string> Tools::splitByNSize(string const& chaine, int tailleBloc)
{
    int tailleTab = ceil((double)chaine.size()/(double)tailleBloc);
    int n = 0;
    if(tailleTab == 0)
    {
        tailleTab = 1;
    }
    vector<string> retour(tailleTab);
    for(int i = 0; i < chaine.size(); i+= tailleBloc)
    {
        retour[n] = chaine.substr(i, tailleBloc);
        n++;
    }
    return retour;
}
