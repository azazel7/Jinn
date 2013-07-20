#include <iostream>
#include "Position.h"
#include "Case.h"
#include "Position.h"
#include "UsineSort.h"
#include "Partie.h"
#include "Joueur.h"
#include "reseau/serveur/ReceptionServeur.h"
#include "sort/Sort.h"
#include <signal.h>

using namespace std;

ReceptionServeur *serveur = NULL;
void traitement_sigint(int sig)
{
    cout << "Reception du signal " << sig << endl;
    if(sig == SIGINT)
    {
        if(serveur != NULL)
        {
            serveur->finirServeur();
            serveur->fermerServeur();
            delete serveur;
            serveur = NULL;
            GestionnaireLogger::viderRegistre();
            Position::libererPositions();
            exit(0);
        }
    }
}
int main()
{
    signal(SIGINT, &traitement_sigint);
    Logger *logger = new LoggerFileDescriptor(1, false);
    GestionnaireLogger::ajouterRegistre(logger);
    Partie *p = new Partie("p1", 2, 3);
    p->initialiser();
    serveur = new ReceptionServeur(p);
    serveur->initialiserServeur();
    serveur->miseEnEcoute();
    serveur->fermerServeur();
    delete serveur;
    serveur = NULL;
    GestionnaireLogger::viderRegistre();
    Position::libererPositions();
    return 0;
}

