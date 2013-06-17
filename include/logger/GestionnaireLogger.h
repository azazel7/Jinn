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
                void static ecrirMessage(TypeMessage type, string message);
                void static ajouterRegistre(Logger *newRegistreur);
                void static retirerRegistre(Logger *registreur);
                void static viderRegistre();

        private:
                static list<Logger*> listeRegistre;
};

#endif
