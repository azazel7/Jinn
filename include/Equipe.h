#ifndef Equipe_h
#define Equipe_h

#include <vector>
#include <iostream>

using namespace std;

class Joueur;

class Equipe {

 public:

    virtual void choisirJoueur();

    Equipe(string nom);


 private:
    string nom;

 public:

    /**
     * @element-type Joueur
     */
    std::vector< Joueur* > joueur;

};

#endif // Equipe_h
