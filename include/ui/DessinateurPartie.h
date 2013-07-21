#ifndef DessinateurPartie_h
#define DessinateurPartie_h

#include "PartieClient.h"
#include "reseau/client/ReceptionClient.h"
#include <curses.h>
#include <mutex>

class ReceptionClient;

namespace IndexDessinateurPartie
{
    static const int index_plateau = 0;
    static const int index_message = 1;
}

class DessinateurPartie
{
    public:
        DessinateurPartie(PartieClient* partie, ReceptionClient* recepteur);
        void dessinerPartie();
        void saisie();

    private:
        void dessinerJoueurs(int hauteur, int largeur);
        void dessinerMessage(int hauteur, int largeur);
        void dessinerPlateau(int hauteur, int largeur);
        void dessinerCaseCourante(int hauteur, int largeur);
        void dessinerListeSortJoueur(int hauteur, int largeur);
        void effectuerAction(int n);
        void tournerIndexPanneaux();
        void traitementTouchePlateau(int touche);
        void traitementToucheMessage(int touche);
        void traitementToucheParPanneaux(int touche);
        void ajouterCible(Position *position);
        void modifierCouleurPlateau(Position *position, bool activer, WINDOW* win);
        PartieClient* partie;
        ReceptionClient* recepteur;
        Position* positionCourante;
        Position* origineSort;
        list<Position*> listeCible;
        string message;

        int indexPanneau;
        std::mutex mut;


};
#endif
