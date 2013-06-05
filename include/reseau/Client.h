#ifndef Client_h
#define Client_h

#include "Joueur.h"
#include "Partie.h"

class Partie;
class Joueur;

class Client
{
    public:
        Client();
        void setPartie(Partie* partie);
        Partie* getPartie() const;

        void setJoueur(Joueur *joueur);
        Joueur* getJoueur();

    private:
        Partie *partie;
        Joueur *joueur;
};


#endif
