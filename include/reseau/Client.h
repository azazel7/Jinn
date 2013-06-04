#ifndef Client_h
#define Client_h

#include "Joueur.h"
#include "Partie.h"

class Client
{
        Client();
        void setPartie(Partie* partie);
        Partie* getPartie();

        void setJoueur(Joueur *joueur);
        Joueur* getJoueur();

    private:
        Partie *partie;
        Joueur *joueur;
};


#endif
