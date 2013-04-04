#ifndef Equipe_h
#define Equipe_h

#include <vector>
#include <iostream>

using namespace std;

class Joueur;

class Equipe {

 public:

    virtual Joueur* choisirJoueur();

    Equipe(string nom);


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
