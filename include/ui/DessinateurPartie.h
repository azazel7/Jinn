#ifndef DessinateurPartie_h
#define DessinateurPartie_h

#include "PartieClient.h"
#include "reseau/client/ReceptionClient.h"
#include <curses.h>

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
        PartieClient* partie;
        ReceptionClient* recepteur;
        Position* positionCourante;
        string message;


};
#endif
