#ifndef Logger_h
#define Logger_h

#include <iostream>
#include "logger/GestionnaireLogger.h"

using namespace std;
class GestionnaireLogger;

class Logger
{
public:
    virtual void ecrirMessage(TypeMessage type, string message) = 0;
    virtual ~Logger();
    bool estADelete();

protected:
    bool aDelete;
};
#endif
