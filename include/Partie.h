#ifndef Partie_h
#define Partie_h

#include <vector>

#include "Action.h"
#include "Equipe.h"
#include "Plateau.h"
#include "Joueur.h"
#include "UsineSort.h"
#include "logger/GestionnaireLogger.h"

using namespace std;

class Plateau;
class Joueur;
class Equipe;
class UsineSort;
class Action;

class Partie
{
public:

    Partie(string nom, int nombrePlace, int nombreSortParJoueur);


    /**
     *  Demarre la partie.
     */
    virtual void demarrerPartie();

    /**
     *  Verifie la victoire d'une équipe
     */
    virtual bool verifierVictoire(Equipe & equipe);

    /**
     *  Initialise la partie, les different joueurs, les differentes equipes et le terrain
     */
    virtual void initialiser(int largeur = 3, int hauteur = 3);

    /**
     * Liste tous les sorts disponible pour la partie
     */
    virtual std::vector<Sort*> listeSort();

    /**
      * Verifie la fin de la partie
      */
    virtual bool finPartie(string &nomEquipeGagnante);
        virtual void finirPartie(string nomEquipeGagnante);
    /**
     * @brief actionValide verifie si une action est valide
     * @param action l'action à vérifier
     * @return
     */
    virtual bool actionValide(Action & action);

    virtual bool isEnCours();

    virtual void setEnCours(bool valeur);

    virtual Plateau* getPlateau();

    virtual bool prete();

    virtual int nombreDeJoueur();

    virtual bool joueurExiste(string nom);

    virtual void regenererManaJoueur();

    virtual bool estJoueurCourrant(Joueur* joueur);

    virtual vector<string> listeEquipe();

    virtual int getNombreSortParJoueur();

    virtual Equipe* equipeExiste(string const& nom);

    virtual Joueur* ajouterJoueur(string const& nom, string const& nomEquipe, vector<string> const& listeSort);

    virtual int getNombreDePlace();

    virtual vector<Equipe* > getEquipe();

    virtual vector<Joueur*> getJoueur();

    virtual void effectuerAction(Action* action, Joueur *joueur);

    virtual void retirerJoueur(Joueur* joueur);

    virtual void changerJoueur();

    virtual void finTourPartie();

    virtual Joueur* choisirJoueur();

    virtual bool isFinis();

    virtual ~Partie();

protected:

    /**
     *  Correspond au nom de la partie (nottament s'il y a plusieurs partie sur une application serveur)
     */
    string nom;
    int nombreDePlace;
    bool enCours;
    bool estFini;
    int nombreSortParJoueur;
    int nombreDeJoueurAyantJoue;
    Joueur* joueurCourant;
    Plateau *plateau;
    std::vector< Equipe* > equipe;
    std::vector< Joueur* > joueur;
    int indexEquipeCourante;

};

#endif // Partie_h
