#ifndef Plateau_h
#define Plateau_h

#include <vector>

#include "Action.h"
#include "Case.h"
#include "sort/Sort.h"
#include "Position.h"

class Action;
class Position;
class Sort;
class Case;

class Plateau {

 public:

    Plateau();

    Plateau(int largeur, int hauteur);

    virtual Case* getCase(int x, int y);

    virtual Case* getCase(Position const& position);

    virtual void appliquerAction(Action action);

    virtual int nombreCase();

    virtual int nombreCaseControlable();

    virtual void initialiserPlateau();

    virtual int getHauteur();

    virtual int getLargeur();

    virtual vector<Case*> getListeCase();

    virtual void retirerSortDeDureeEcoulee();

    virtual void regenererDefenseCase();

    virtual void regenererManaPourJoueur();

    virtual void effectuerActionChronique();

    virtual void retirerJoueur(Joueur* joueur);

    virtual ~Plateau();

 private:
    int largeur;
    int hauteur;
    /**
     * @element-type Case
     */
    std::vector< Case* > listeCase;
};

#endif // Plateau_h
