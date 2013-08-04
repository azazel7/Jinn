#ifndef VueCreerJoueur_h
#define VueCreerJoueur_h

#include "reseau/client/ReceptionClient.h"
#include "PartieClient.h"
#include <curses.h>
#include <algorithm>

#define HAUTEUR_INFO_PARTIE 3
#define HAUTEUR_INFO_JOUEUR 4
#define HAUTEUR_INFO_SORT 6
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
        void saisieInformation();

    private:
        void dessinerInfoPartie(int hauteur, int largeur);
        void dessinerSort(int hauteur, int largeur);
        void dessinerInfoSort(int hauteur, int largeur);
        void dessinerInfoJoueur(int hauteur, int largeur);
        void dessinerAide(int hauteur, int largeur);
        void dessinerEquipe(int hauteur, int largeur);
        void activerCouleurCurseur(WINDOW *win, int index, bool activer, int position = -1);
        void enterSort();
        void enterEquipe();
        //Modifie la position dans les listes
        void modifierPosition(int valeur);
        //Avance ou recule le curseur
        void modifierCurseur(int valeur);
        //Ajoute en fonction de la position du curseur au nom de joueur ou de l'équipe
        void ajouterLettre(char lettre);
        //Retire la dernière lettre
        void retirerLettre();

        PartieClient* partie;
        ReceptionClient* receptionClient;
        int curseur;
        string nomJoueur;
        string nomEquipe;
        int positionEquipe, positionSort;
        list<string> sortChoisie;
};
#endif
