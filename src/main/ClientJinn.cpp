#include "reseau/client/ReceptionClient.h"
#include "PartieClient.h"
#include "ui/VueCreerJoueur.h"
#include "ui/DessinateurPartie.h"
#include <curses.h>
#include <chrono>
#include <thread>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

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
    Logger *logger = new LoggerFileDescriptor(open("log", O_WRONLY), false);
    GestionnaireLogger::ajouterRegistre(logger);
   PartieClient* partie = new PartieClient();
   ClientJinn::recepteur = new ReceptionClient(partie, "127.0.0.1", 14790);
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
   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
   VueCreerJoueur creaJoueur(partie, ClientJinn::recepteur);
   DessinateurPartie dessinateur(partie, ClientJinn::recepteur);
//   vector<string> lequipe;
//   vector<Sort*> lsort;
//   lequipe.push_back("Equipe1");
//   lequipe.push_back("Equipe4");
//   lequipe.push_back("Equipe3");
//   lequipe.push_back("Equipe2");
//   lsort.push_back(UsineSort::fabriqueSort("Boule de Feu"));
//   lsort.push_back(UsineSort::fabriqueSort("Sceau de Controle"));
//   lsort.push_back(UsineSort::fabriqueSort("Rune de Protection"));
//   partie->setListeEquipe(lequipe);
//    partie->setListeSortDispo(lsort);
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
}
