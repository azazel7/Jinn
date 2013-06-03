#ifndef Equipe_h
#define Equipe_h

#include <vector>
#include <iostream>
#include "Joueur.h"

using namespace std;

class Joueur;

class Equipe {

public:

    Equipe(string nom);

    string getNom();

    void setNom(string nom);

    int getNombreJoueur();

    void setNombreJoueur(int nombre);

    int getIndexCourrant();

    void setIndexCourrant(int newIndex);

    void tournerIndex();

private:
    string nom;
    int nombreJoueur;
    int indexJoueurCourrant;
};

#endif // Equipe_h
