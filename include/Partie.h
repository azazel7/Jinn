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
    void demarrerPartie();

    /**
     *  Verifie la victoire d'une équipe
     */
    bool verifierVictoire(Equipe & equipe);

    /**
     *  Initialise la partie, les different joueurs, les differentes equipes et le terrain
     */
    void initialiser(int largeur = 3, int hauteur = 3);

    /**
     * Liste tous les sorts disponible pour la partie
     */
    std::vector<Sort*> listeSort();

    /**
      * Verifie la fin de la partie
      */
    bool finPartie(string &nomEquipeGagnante);

    /**
     * @brief finirPartie Finis la partie
     * @param nomEquipeGagnante Le nom de l'équipe gagnante
     */
    void finirPartie(string nomEquipeGagnante);

    /**
     * @brief isEnCours Verifie si la partie est en cour
     * @return true si la partie est en cour
     */
    bool isEnCours();

    /**
     * @brief setEnCours change l'état de la partie
     * @param valeur l'état de la partie
     */
    void setEnCours(bool valeur);

    /**
     * @brief getPlateau getter du plateau
     * @return Un pointeur sur le plateau
     */
    Plateau* getPlateau();

    /**
     * @brief prete verifie si la partie est prête à débuter
     * @return true si la partie est prête à démarrer
     */
    bool prete();

    /**
     * @brief nombreDeJoueur
     * @return
     */
    int nombreDeJoueur();

    /**
     * @brief joueurExiste Verifie l'existance d'un joueur
     * @param nom Le nom du joueur
     * @return true si le joueur existe
     */
    bool joueurExiste(string nom);

    /**
     * @brief regenererManaJoueur Régénère le mana des joueurs
     */
    void regenererManaJoueur();

    /**
     * @brief estJoueurCourrant Verifie si le joueur en argument est le joueur qui joue actuellement
     * @param joueur Le joueur à vérifier
     * @return true si c'est le joueur courant
     */
    bool estJoueurCourrant(Joueur* joueur);

    /**
     * @brief listeEquipe Permet d'obtenir la liste des equipes
     * @return tableau avec le nom des équipes
     */
    vector<string> listeEquipe();

    /**
     * @brief getNombreSortParJoueur Getter du nombre de sort par joueur
     * @return le nombre de sort par joueur
     */
    int getNombreSortParJoueur();

    /**
     * @brief equipeExiste Verifie l'existance d'une équipe
     * @param nom Le nom de l'équipe
     * @return Un pointeur vers l'équipe ou NULL
     */
    Equipe* equipeExiste(string const& nom);

    /**
     * @brief ajouterJoueur Ajoute un joueur à la partie
     * @param nom Le nom du joueur
     * @param nomEquipe Le nom de son équipe
     * @param listeSort La liste de ses sort
     * @return  Un pointeur vers le nouveau joueur ou NULL si la création à échoué.
     */
    Joueur* ajouterJoueur(string const& nom, string const& nomEquipe, vector<string> const& listeSort);

    /**
     * @brief getNombreDePlace getter du nombre de place
     * @return le nombre de place
     */
    int getNombreDePlace();

    /**
     * @brief getEquipe Getter d'équipes
     * @return le tableau des équipe
     */
    vector<Equipe* > getEquipe();

    /**
     * @brief getJoueur Getter des joueur
     * @return Le tableau des joueurs
     */
    vector<Joueur*> getJoueur();

    /**
     * @brief effectuerAction effectue l'action d'un joueur sur la partie
     * @param action L'action à effectuer
     * @param joueur Le joueur qui agis
     */
    void effectuerAction(Action* action, Joueur *joueur);

    /**
     * @brief retirerJoueur Retire un joueur de la partie (retiré du plateau et de la liste des joueurs)
     * @param joueur Le joueur à retirer
     */
    void retirerJoueur(Joueur* joueur);

    /**
     * @brief changerJoueur Change le joueur courant pour le suivant
     */
    void changerJoueur();

    /**
     * @brief finTourPartie Effectue les actions lorsque tous les joueurs on joué (regen case, regen mana ...)
     */
    void finTourPartie();

    /**
     * @brief choisirJoueur Choisie un nouveau joueur en fonction de l'équipe
     * @return UN pointeur vers le joueur choisi ou NULL en cas d'erreur
     */
    Joueur* choisirJoueur();

    /**
     * @brief isFinis Getter de estFini, ne fait pas de calcule pour vérifier la véracité du booléen
     * @return
     */
    bool isFinis();

    /**
     * @brief ~Partie Destructeur de la partie
     */
    ~Partie();

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
