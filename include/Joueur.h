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
#include "Tools.h"
#include "Position.h"
#include "Case.h"
#include "sort/Sort.h"
#include "reseau/constanteReseau.h"

using namespace std;

class Action;
class Equipe;
class Partie;

class Joueur
{

public:

    /**
     * @brief Joueur Constructeur
     */
    Joueur();

    /**
     * @brief Joueur Constructeur
     * @param gainInit
     * @param manaMax
     * @param niveauAbilite
     * @param nom
     * @param abilite
     */
    Joueur(int gainInit, int manaMax, int niveauAbilite, string nom, TypeSort abilite);

    /**
     * @brief diminuerMana Diminue le mana
     * @param quantite
     */
    virtual void diminuerMana(int quantite = 1);

    /**
     * @brief augmenterMana Augmente le mana
     * @param quantite
     */
    virtual void augmenterMana(int quantite = 1);

    /**
     * @brief estMort Verifie l'état du joueur
     * @return true si le joueur est mort
     */
    virtual bool estMort() const;

    /**
     * @brief genererStatistique Génére les statistique du joueur
     */
    virtual void genererStatistique();

    string getNom() const;

    virtual void setNom(string nom);

    int getManaActuel() const;

    int getManaMaximum() const;

    int getGainInitialMana() const;

    TypeSort getAbilite() const;

    void setAbilite(TypeSort value);

    int getNiveauAbilite() const;

    void setNiveauAbilite(int value);

    int getSocket() const;

    void setSocket(int socket);

    void setManaActuel(int valeur);

    void setManaMaximum(int valeur);

    void setGainMana(int valeur);

    void setEquipe(Equipe* newEquipe);

    Equipe* getEquipe();

    string getNomEquipe() const;

    /**
     * @brief ajouterSort Ajoute un sort à la liste des sort disponible du joueur
     * @param sort Un pointeur vers le sort
     */
    void ajouterSort(Sort *sort);

    /**
     * @brief ajouterSort Ajoute un sort à la liste des sort disponible du joueur
     * @param nom Le nom du sort
     */
    void ajouterSort(string const& nom);

    /**
     * @brief retirerSort Retire un sort à la liste des sort du joueur
     * @param nom Le nom du sort à retirer
     */
    void retirerSort(string const& nom);

    /**
     * @brief possedeSort Verifie s'il posséde le sort
     * @param sort Un pointeur vers le sort
     * @return true si le joueur posséde le sort
     */
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

    void notifierCase(Case const& caseANotif, bool compteProprietaire = true) const;

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
    TypeSort abilite;
    int niveauAbilite;
    int socket;
    std::vector<Sort*> listeSort;
    Equipe *equipe;

};

ostream& operator<<( ostream &flux, Joueur const& pos);

#endif // Joueur_h
