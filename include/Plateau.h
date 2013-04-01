#ifndef Plateau_h
#define Plateau_h

#include <vector>

#include "Action.h"
#include "Case.h"
#include "Sort.h"


class Plateau {

 public:

    Plateau();

    Plateau(int largeur, int hauteur);

    virtual Case getCase(int x, int y);

    virtual void lancerSort(Case origine, Case cible, Sort sort);

    virtual void appliquerAction(Action action);

    virtual bool effectuerAction();

    virtual int nombreCase();

    virtual int nombreCaseControlable();

    virtual ~Plateau();


 private:
    int largeur;
    int hauteur;

 public:


    /**
     * @element-type Case
     */
    std::vector< Case* > constituer;
};

#endif // Plateau_h
