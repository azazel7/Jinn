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

    void setEquipe(Equipe* newEquipe);

    Equipe* getEquipe();

    string getNomEquipe();

    bool possedeSort(Sort* sort);

    bool possedeSort(string nomsort);

    void notifierCreation() const;

    void notifierPartie(Partie &partie) const;

    void notifierDebutPartie() const;

    void notifierDebutTour(string nomJoueur) const;

    void notifierFinTourPartie() const;

    void notifierMort(string nomJoueur) const;

    void notifierActionSort(string information) const;

    void notifierPropriaitaireCase(string nomJoueur, bool type, int x, int y);

    void notifierFinPartie(string nomEquipeGagnante) const;


    ~Joueur();

private:
    string nom;
    int gainInitialMana;
    int manaMaximum;
    int manaActuel;
    int abilite;
    int socket;
    std::vector<Sort*> listeSort;
    Equipe *equipe;

};

ostream& operator<<( ostream &flux, Joueur const& pos);

#endif // Joueur_h
