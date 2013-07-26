#ifndef Joueur_h
#define Joueur_h

#include <vector>
#include <iostream>
#include <cstdlib>
#include <sys/socket.h>

#include "Action.h"
#include "Equipe.h"
#include "sort/Sort.h"
#include "Partie.h"
#include "UsineSort.h"
#include "reseau/serveur/ReceptionServeur.h"
#include "Tools.h"
#include "Position.h"

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

    int getManaActuel() const;

    int getManaMaximum() const;

    int getGainInitialMana() const;

    int getAbilite() const;

    int setAbilite(int value);

    int getSocket() const;

    void setSocket(int socket);

    void setManaActuel(int valeur);

    void setManaMaximum(int valeur);

    void setGainMana(int valeur);

    void setEquipe(Equipe* newEquipe);

    Equipe* getEquipe();

    string getNomEquipe() const;

    void ajouterSort(Sort *sort);

    void ajouterSort(string const& nom);

    void retirerSort(string const& nom);

    bool possedeSort(Sort* sort);

    bool possedeSort(string nomsort);

    vector<Sort* > getListeSort();

    void notifierCreation() const;

    void notifierPartie(Partie &partie) const;

    void notifierDebutPartie() const;

    void notifierDebutTour(string nomJoueur) const;

    void notifierFinTourPartie() const;

    void notifierMort(string nomJoueur) const;

    void notifierActionSort(string information) const;

    void notifierPropriaitaireCase(string nomJoueur, bool type, int x, int y);

    void notifierFinPartie(string nomEquipeGagnante) const;

    void notifierSuppressionJoueur(string nomJoueur) const;

    void notifierSort(const Sort &sort, int duree, Position *position) const;

    void notifierResultatSort(string const& nom, Position const& cible, bool reussite);

    void notifierCase(Case const& caseANotif, bool compteProprietaire) const;

    void notifierJoueur(Joueur const& joueur, bool compteEquipe = true) const;

    string creerChaineNotificationSort(Sort const& sort, int duree, Position *position) const;

    string creerChaineNotificationJoueur(Joueur const& joueur, bool compteEquipe = true) const;

    string creerChaineNotificationCase(Case const& caseANotif, bool compteProprietaire = true) const;

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
