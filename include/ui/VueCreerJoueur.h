#ifndef VueCreerJoueur_h
#define VueCreerJoueur_h

#include "PartieClient.h"
namespace IndexCreerJoueur
{
    static const int curseur_liste_sort = 0;
    static const int curseur_liste_equipe = 1;
    static const int curseur_nom_joueur = 2;
    static const int curseur_nom_equipe = 3;
}

class VueCreerJoueur
{
    public:
        VueCreerJoueur(PartieClient* partie);
        void dessinerFenetre();
        //Modifie la position dans les listes
        void modifierPosition(int valeur);
        //Avance ou recule le curseur
        void modifierCurseur(int valeur);
        //Ajoute en fonction de la position du curseur au nom de joueur ou de l'équipe
        void ajouterLettre(char lettre);
        //Retire la dernière lettre
        void retirerLettre();
    private:
        PartieClient* partie;
        int curseur;
        string nomJoueur;
        string nomEquipe;
        int positionEquipe, positionSort;
};
#endif
