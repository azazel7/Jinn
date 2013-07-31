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
    /**
     * @brief Plateau
     *  Constructeur par defaut
     */
    Plateau();

    /**
     * @brief Plateau
     *  Constructeur avec dimension
     * @param largeur largeur du plateau
     * @param hauteur hauteur du plateau
     */
    Plateau(int largeur, int hauteur);

    /**
     * @brief getCase Permet d'obtenir une case
     * @param x l'abscice
     * @param y l'ordonnée
     * @return Un pointeur sur la case
     */
    Case* getCase(int x, int y);

    /**
     * @brief getCase Permet d'obtenir une case en fonction de ses coordonée
     * @param position La position de la case
     * @return Un pointeur sur la case
     */
    Case* getCase(Position const& position);

    /**
     * @brief appliquerAction applique une action sur le plateau
     * @param action L'action à appliquer
     */
    void appliquerAction(Action action);

    /**
     * @brief nombreCase Calcule le nombre de case du plateau
     * @return le nombre de case du plateau
     */
    int nombreCase();

    /**
     * @brief nombreCaseControlable Calcule le nombre de case controllable du plateau
     * @return le nombre de case contrallable sur le plateau
     */
    int nombreCaseControlable();

    /**
     * @brief initialiserPlateau Initialise le plateau avec ses cases
     */
    void initialiserPlateau();

    /**
     * @brief getHauteur Getter de la hauteur
     * @return la hauteur du plateau
     */
    int getHauteur();

    /**
     * @brief getLargeur
     * @return la largeur du plateau
     */
    int getLargeur();

    /**
     * @brief getListeCase Permet d'obtenir la liste des cases
     * @return la liste des cases
     */
    vector<Case*> getListeCase();

    /**
     * @brief retirerSortDeDureeEcoulee Execute la vérification des sorts et de leurs durée pour chaque case
     */
    void retirerSortDeDureeEcoulee();

    /**
     * @brief regenererDefenseCase Régénère la defense des cases
     */
    void regenererDefenseCase();

    /**
     * @brief regenererManaPourJoueur Régénère les propriétaire des cases
     */
    void regenererManaPourJoueur();

    /**
     * @brief effectuerActionChronique Effectue les actions chroniques des sorts sur leurs case
     */
    void effectuerActionChronique();

    /**
     * @brief retirerJoueur retire un joueur du plateau (Retire ses sort et le supprime de ses cases)
     * @param joueur
     */
    void retirerJoueur(Joueur* joueur);

    /**
      * @brief Destructeur
      */
    ~Plateau();

 private:
    int largeur;
    int hauteur;
    /**
     * @element-type Case
     */
    std::vector< Case* > listeCase;
};

#endif // Plateau_h
