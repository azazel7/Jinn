#ifndef Partie_h
#define Partie_h

#include <vector>

#include "Equipe.h"
#include "Plateau.h"
#include "Joueur.h"
#include "UsineSort.h"
#include "GestionnaireNotificationPartie.h"

using namespace std;

class Plateau;
class Joueur;
class Equipe;
class UsineSort;

class Partie : public GestionnaireNotificationPartie
{
    enum { ATTENTE_JOUEUR };
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
    virtual void initialiser();

    /**
     * Liste tous les sorts disponible pour la partie
     */
    virtual std::vector<Sort*> listeSort();

    /**
      * Verifie la fin de la partie
      */
    virtual bool finPartie();

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

    virtual void effectuerAction(Action* action, Joueur *joueur);

protected:

    /**
     *  Correspond au nom de la partie (nottament s'il y a plusieurs partie sur une application serveur)
     */
    string nom;
    int nombreDePlace;
    bool enCours;
    int nombreSortParJoueur;
    Joueur* joueurCourant;
    Plateau *plateau;
    /**
     * @element-type Equipe
     */
    std::vector< Equipe* > equipe;

};

#endif // Partie_h
