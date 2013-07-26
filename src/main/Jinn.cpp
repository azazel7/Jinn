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
#include <boost/regex.hpp>

using namespace std;

ReceptionServeur *serveur = NULL;
void traitement_sigint(int sig)
{
    if(sig == SIGINT)
    {
        GestionnaireLogger::ecrirMessage(INFO, "Reception du signal SIGINT");
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
int main(int argc, char** argv)
{
    int opth = 1;
    int port = -1;
    int nombreSort = -1;
    int nombreJoueur = -1;
    int largeur = -1, hauteur = -1;
    string ip = "0.0.0.0";
    bool argumentBon = true;
    while( (opth = getopt(argc, argv, "hp:a:j:s:L:H:")) != -1)
    {
        switch(opth)
        {
        case 'h':
            cout << "Usage : " << argv[0] << " [OPTION]" << endl;
            cout << "-h\tAffiche cet aide" << endl;
            cout << "-p [PORT]\tIndique un nouveau port d'écoute. (Défaut : 14790)" << endl;
            cout << "-a [IP]\tIndique une adresse ip d'écoute. (Défaut : 0.0.0.0)" << endl;
            cout << "-j [NOMBRE]\tIndique le nombre de joueur pour la partie. (Défaut : 2)" << endl;
            cout << "-s [NOMBRE]\tIndique le nombre de sort par joueur. (Défaut : 3)(Max : " << UsineSort::liste().size() << ")" << endl;
            cout << "-L [NOMBRE]\tIndique la largeur du terrain. (Défaut : 3)" << endl;
            cout << "-H [NOMBRE]\tIndique la hauteur du terrain. (Défaut : 3)" << endl;
            return -1;
            break;
        case 'p':
            port = atoi(optarg);
            if(port <= 0)
            {
                cout << "Numéro de port invalide." << endl;
                argumentBon = false;
            }
            break;
        case 'j':
            nombreJoueur = atoi(optarg);
            if(nombreJoueur <= 0)
            {
                cout << "Nombre de joueur invalide." << endl;
                argumentBon = false;
            }
            break;
        case 'L':
            largeur = atoi(optarg);
            if(largeur <= 0)
            {
                cout << "Largeur invalide." << endl;
                argumentBon = false;
            }
            break;
        case 'H':
            hauteur = atoi(optarg);
            if(hauteur <= 0)
            {
                cout << "Hauteur invalide." << endl;
                argumentBon = false;
            }
            break;
        case 's':
            nombreSort = atoi(optarg);
            if(nombreSort <= 0 || nombreSort > UsineSort::liste().size())
            {
                cout << "Nombre de sort par joueur invalide." << endl;
                argumentBon = false;
            }
            break;
        case 'a':
            ip = optarg;
            boost::regex expression ("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
            if(regex_match(ip, expression) == false)
            {
                cout << "addresse ip invalide." << endl;
                argumentBon = false;
            }
            break;
        }
    }
    if(argumentBon == false)
    {
        return -1;
    }
    if(port <= 0)
    {
        port = 14790;
    }
    if(nombreJoueur <= 0)
    {
        nombreJoueur = 2;
    }
    if(nombreSort <= 0)
    {
        nombreSort = 3;
    }
    if(largeur <= 0)
    {
        largeur = 3;
    }
    if(hauteur <= 0)
    {
        hauteur = 3;
    }
    signal(SIGINT, &traitement_sigint);
    Logger *logger = new LoggerFileDescriptor(1, false);
    GestionnaireLogger::ajouterRegistre(logger);
    Partie *p = new Partie("p1", nombreJoueur, nombreSort);
    p->initialiser();
    serveur = new ReceptionServeur(p, ip, port);
    serveur->initialiserServeur();
    serveur->miseEnEcoute();
    serveur->fermerServeur();
    delete serveur;
    serveur = NULL;
    GestionnaireLogger::viderRegistre();
    Position::libererPositions();
    return 0;
}

