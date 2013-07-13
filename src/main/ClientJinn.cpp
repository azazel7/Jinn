#include "reseau/client/ReceptionClient.h"
#include "PartieClient.h"
#include "ui/VueCreerJoueur.h"
#include <curses.h>
#include <chrono>
#include <thread>

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
    Logger *logger = new LoggerFileDescriptor(1, false);
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
   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
   cout << "envoie commande" << endl;
   ClientJinn::recepteur->envoyerCommandeEquipe();
//   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
//   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
   cout << "envoie commande" << endl;
   ClientJinn::recepteur->envoyerCommandeSort();
   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
   cout <<"Equipe : " << partie->getListeEquipe().size() << endl;
   cout <<"Sort : " << partie->getListeSortDispo().size() << endl;
   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
   std::this_thread::sleep_for(std::chrono::milliseconds(1000));
   VueCreerJoueur creaJoueur(partie, ClientJinn::recepteur);
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

   initscr();
   keypad(stdscr, TRUE);
   start_color();
   init_pair(1, COLOR_BLUE, COLOR_CYAN);
    creaJoueur.dessinerFenetre();
    creaJoueur.saisieInformation();


   endwin();
}
