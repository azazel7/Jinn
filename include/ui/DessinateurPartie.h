#ifndef DessinateurPartie_h
#define DessinateurPartie_h

#include "PartieClient.h"
#include "reseau/client/ReceptionClient.h"
#include <curses.h>

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
        void dessinerJoueurs(int hauteur, int largeur);
        void dessinerMessage(int hauteur, int largeur);
        void dessinerPlateau(int hauteur, int largeur);
        void dessinerCaseCourante(int hauteur, int largeur);
        void saisie();
        void effectuerAction(int n);

    private:
        void tournerIndexPanneaux();
        void traitementTouchePlateau(int touche);
        void traitementToucheMessage(int touche);
        void traitementToucheParPanneaux(int touche);

        PartieClient* partie;
        ReceptionClient* recepteur;
        Position* positionCourante;
        string message;

        int indexPanneau;



};
#endif
