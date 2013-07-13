#ifndef VueCreerJoueur_h
#define VueCreerJoueur_h

#include "reseau/client/ReceptionClient.h"
#include "PartieClient.h"
#include <curses.h>
#include <algorithm>

namespace IndexCreerJoueur
{
    static const int curseur_liste_equipe = 0;
    static const int curseur_liste_sort = 1;
    static const int curseur_nom_joueur = 2;
    static const int curseur_nom_equipe = 3;
}

class VueCreerJoueur
{
    public:
        VueCreerJoueur(PartieClient* partie, ReceptionClient* reception);
        void dessinerFenetre();
        //Modifie la position dans les listes
        void modifierPosition(int valeur);
        //Avance ou recule le curseur
        void modifierCurseur(int valeur);
        //Ajoute en fonction de la position du curseur au nom de joueur ou de l'équipe
        void ajouterLettre(char lettre);
        //Retire la dernière lettre
        void retirerLettre();

        void saisieInformation();
        void enterSort();
        void enterEquipe();
    private:
        PartieClient* partie;
        ReceptionClient* receptionClient;
        int curseur;
        string nomJoueur;
        string nomEquipe;
        int positionEquipe, positionSort;
        list<string> sortChoisie;
};
#endif
