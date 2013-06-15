#include "logger/GestionnaireLogger.h"

list<Logger*> GestionnaireLogger::listeRegistre;

void GestionnaireLogger::ecrirMessage(TypeMessage type, string message)
{
    for(list<Logger*>::iterator iterator = GestionnaireLogger::listeRegistre.begin(); iterator != GestionnaireLogger::listeRegistre.end(); iterator++)
    {
                (*iterator)->ecrirMessage(type, message);
    }

}
void GestionnaireLogger::ajouterRegistre(Logger *newRegistreur)
{
        GestionnaireLogger::listeRegistre.push_front(newRegistreur);
}
void GestionnaireLogger::retirerRegistre(Logger *registreur)
{
    for(list<Logger*>::iterator iterator = GestionnaireLogger::listeRegistre.begin(); iterator != GestionnaireLogger::listeRegistre.end(); iterator++)
    {
        if((*iterator) == registreur)
        {
                GestionnaireLogger::listeRegistre.erase(iterator);
                break;
        }
    }

}
