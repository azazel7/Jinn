#ifndef Logger_h
#define Logger_h

#include <iostream>
#include "logger/GestionnaireLogger.h"

using namespace std;
class GestionnaireLogger;

class Logger
{
public:
    /**
     * @brief ecrirMessage Ecrire un message
     * @param type L'importance du message
     * @param message Le message
     */
    virtual void ecrirMessage(TypeMessage type, string message) = 0;
    /**
     * @brief ~Logger Destructeur
     */
    virtual ~Logger();
    /**
     * @brief estADelete Getter de aDelete
     * @return true si le logger est à supprimer par le gestionnaire
     */
    bool estADelete();

protected:
    bool aDelete;
};
#endif
