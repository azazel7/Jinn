#include "reseau/client/ReceptionClient.h"
#include "PartieClient.h"
#include "ui/VueCreerJoueur.h"
#include <curses.h>

int main(int argc, char** argv)
{
   initscr();
   keypad(stdscr, TRUE);
   start_color();
   init_pair(1, COLOR_BLUE, COLOR_CYAN);
//    ReceptionClient* recepteur = new ReceptionClient(
   PartieClient* partie = new PartieClient();
   VueCreerJoueur creaJoueur(partie);
   vector<string> lequipe;
   vector<Sort*> lsort;
   lequipe.push_back("Equipe1");
   lequipe.push_back("Equipe4");
   lequipe.push_back("Equipe3");
   lequipe.push_back("Equipe2");
   lsort.push_back(UsineSort::fabriqueSort("Boule de Feu"));
   lsort.push_back(UsineSort::fabriqueSort("Sceau de Controle"));
   lsort.push_back(UsineSort::fabriqueSort("Rune de Protection"));
   partie->setListeEquipe(lequipe);
    partie->setListeSortDispo(lsort);

    creaJoueur.dessinerFenetre();
    creaJoueur.saisieInformation();
   endwin();
}
