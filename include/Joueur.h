#ifndef Joueur_h
#define Joueur_h

#include <vector>
#include <cstdlib>
#include <iostream>
#include <cstdlib>
#include <sys/socket.h>

#include "Action.h"
#include "Equipe.h"
#include "Sort.h"
#include "Partie.h"
#include "UsineSort.h"
#include "reseau/ReceptionServeur.h"
#include "Tools.h"

using namespace std;

class Action;
class Equipe;
class Partie;

class Joueur
{

public:

    Joueur();

    Joueur(int gainInit, int manaMax, int abiliteInit, string nom);

    virtual Action effectuerAction(Partie & partie);

    virtual void diminuerMana(int quantite = 1);

    virtual void augmenterMana(int quantite = 1);

    virtual bool estMort() const;

    virtual void genererStatistique();

    virtual string saisieNom();

    virtual string saisieEquipe(std::vector< Equipe* > & equipe);

    virtual string saisieSort(vector<Sort* > const& sort);

    string getNom() const;

    virtual void setNom(string nom);

    virtual void ajouterSort(Sort *sort);

    int getManaActuel() const;

    int getManaMaximum() const;

    int getGainInitialMana() const;

    int getSocket() const;

    void setSocket(int socket);

    bool possedeSort(Sort* sort);

    bool possedeSort(string nomsort);

    void notifierCreation() const;

    void notifierPartie(Partie &partie) const;

    void notifierDebutPartie() const;

    void notifierDebutTour(string nomJoueur) const;

    void notifierFinTourPartie() const;

    void notifierMort(string nomJoueur) const;

    void notifierActionSort(string information) const;

private:
    string nom;
    int gainInitialMana;
    int manaMaximum;
    int manaActuel;
    int abilite;
    int socket;
    std::vector<Sort*> listeSort;

};

ostream& operator<<( ostream &flux, Joueur const& pos);

#endif // Joueur_h
