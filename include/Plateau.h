#ifndef Plateau_h
#define Plateau_h

#include <vector>

#include "Action.h"
#include "Case.h"
#include "Sort.h"
#include "Position.h"

class Action;
class Position;
class Sort;

class Plateau {

 public:

    Plateau();

    Plateau(int largeur, int hauteur);

    virtual Case* getCase(int x, int y);

    virtual Case* getCase(Position const& position);

    virtual void appliquerAction(Action action);

    virtual int nombreCase();

    virtual int nombreCaseControlable();

    virtual ~Plateau();

    virtual void initialiserPlateau();

    virtual int getHauteur();

    virtual int getLargeur();

    virtual void retirerSortDeDureeEcoulee();

 private:
    int largeur;
    int hauteur;
    /**
     * @element-type Case
     */
    std::vector< Case* > listeCase;
};

#endif // Plateau_h
