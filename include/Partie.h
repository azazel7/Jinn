#ifndef Partie_h
#define Partie_h

#include <vector>

#include "Equipe.h"

using namespace std;

class Plateau;

class Partie {

 public:

    Partie(string nom, int nombrePlace);


    /** 
     *  Demarre la partie.
     */
    virtual void demarrerPartie();


    /** 
     *  Verifie la victoire d'une équipe
     */
    virtual bool verifierVictoire(Equipe equipe);


    /** 
     *  Initialise la partie, les different joueurs, les differentes equipes et le terrain
     */
    virtual void initialiser();

 public:
    
    /** 
     *  Correspond au nom de la partie (nottament s'il y a plusieurs partie sur une application serveur)
     */
    string nom;
    int nombreDePlace;

 public:

    Plateau *posseder;

    /**
     * @element-type Equipe
     */
    std::vector< Equipe* > equipe;

};

#endif // Partie_h
