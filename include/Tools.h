#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <sstream>

class Tools
{
public:
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
