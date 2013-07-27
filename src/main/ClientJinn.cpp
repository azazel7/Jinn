#include "reseau/client/ReceptionClient.h"
#include "PartieClient.h"
#include "ui/VueCreerJoueur.h"
#include "ui/DessinateurPartie.h"
#include "logger/LoggerFileDescriptor.h"
#include <curses.h>
#include <chrono>
#include <thread>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <boost/regex.hpp>

namespace ClientJinn
{
ReceptionClient* recepteur = NULL;
void miseEnEcoute()
{
    cout << "Demarrage thread" << endl;
    ClientJinn::recepteur->miseEnEcoute();
}
}

int main(int argc, char** argv)
{
    int opth = 1;
    int port = -1;
    string ip = "127.0.0.1";
    bool argumentBon = true;
    while( (opth = getopt(argc, argv, "hp:a:j:s:L:H:")) != -1)
    {
        switch(opth)
        {
        case 'h':
            cout << "Usage : " << argv[0] << " [OPTION]" << endl;
            cout << "-h\tAffiche cet aide" << endl;
            cout << "-p [PORT]\tIndique le port de connexion. (Défaut : 14790)" << endl;
            cout << "-a [IP]\tIndique une adresse ip de connexion. (Défaut : 127.0.0.1)" << endl;
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

    Logger *logger = new LoggerFileDescriptor(open("log", O_WRONLY), false);
    GestionnaireLogger::ajouterRegistre(logger);
    PartieClient* partie = new PartieClient();
    ClientJinn::recepteur = new ReceptionClient(partie, ip, port);
    if(ClientJinn::recepteur->initialiserClient() != true)
    {
        cout << "Erreur de connexion" << endl;
        return -1;
    }
    std::thread threadEcoute(ClientJinn::miseEnEcoute);
    threadEcoute.detach();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    ClientJinn::recepteur->envoyerCommandeEquipe();
    ClientJinn::recepteur->envoyerCommandeSort();
    ClientJinn::recepteur->envoyerCommandeInformationPartie();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    cout <<"Equipe : " << partie->getListeEquipe().size() << endl;
    cout <<"Sort : " << partie->getListeSortDispo().size() << endl;
    cout << "Place : " << partie->getNombreJoueur() << "/" << partie->getNombrePlace() << endl;
    cout << "Sort par joueur : " << partie->getNombreSortParJoueur() << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    VueCreerJoueur creaJoueur(partie, ClientJinn::recepteur);
    DessinateurPartie dessinateur(partie, ClientJinn::recepteur);
    partie->ajouterMessage("Tarte", "Bonjour à tous");
    partie->ajouterMessage("L", "Salut");
    partie->ajouterMessage("Pinki Pie", "Yop");
    ClientJinn::recepteur->setDessinateur(&dessinateur);
    initscr();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_CYAN);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_GREEN);
    creaJoueur.dessinerFenetre();
    creaJoueur.saisieInformation();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    dessinateur.dessinerPartie();
    dessinateur.saisie();
    endwin();

    cout << "L'équipe " << partie->getEquipeGagnante() << " a gagnée la partie." << endl;
}
