#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <math.h>
#include <sort/Sort.h>

using namespace std;
class Tools
{
    public:
    static vector<string> splitByNSize(const string &chaine, int tailleBloc);
    static std::string& trim(std::string &s);
    static std::string& rtrim(std::string &s);
    static std::string& ltrim(std::string &s);
};

template<typename T>
std::string to_string( const T & Value )
{
    // utiliser un flux de sortie pour créer la chaîne
    std::ostringstream oss;
    // écrire la valeur dans le flux
    oss << Value;
    // renvoyer une string
    return oss.str();
}
#endif // TOOLS_H
