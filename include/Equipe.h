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

	virtual Joueur* choisirJoueur();

    virtual bool joueurExiste(string & nom);

    virtual string getNom();

    virtual void ajouterJoueur(Joueur* nouveauJoueur);

    virtual int nombreDeJoueur();

 private:
    string nom;
    int joueurChoisi;
private:

    /**
     * @element-type Joueur
     */
    std::vector< Joueur* > joueur;

};

#endif // Equipe_h
