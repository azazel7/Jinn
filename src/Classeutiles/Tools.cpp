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

// trim from start
std::string & Tools::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string & Tools::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
std::string & Tools::trim(std::string &s) {
    return ltrim(rtrim(s));
}
