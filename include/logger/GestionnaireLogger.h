#ifndef GestionnaireLogger_h
#define GestionnaireLogger_h

enum  TypeMessage { FATAL, ERROR, WARN, INFO, SUCCESS};
#include <iostream>
#include <cstdlib>
#include <list>
#include "logger/Logger.h"

using namespace std;
class Logger;


class GestionnaireLogger
{
public:
    /**
     * @brief ecrirMessage Ecrire un message à tous les registres
     * @param type Le niveau d'importance du message
     * @param message Le message à écrire
     */
    void static ecrirMessage(TypeMessage type, string message);
    /**
     * @brief ajouterRegistre Ajoute un registre à la liste
     * @param newRegistreur
     */
    void static ajouterRegistre(Logger *newRegistreur);
    /**
     * @brief retirerRegistre Retire un registre de la liste
     * @param registreur
     */
    void static retirerRegistre(Logger *registreur);
    /**
     * @brief viderRegistre Vide la liste des registres
     */
    void static viderRegistre();

private:
    static list<Logger*> listeRegistre;
};

#endif
