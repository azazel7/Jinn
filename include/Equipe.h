#ifndef Equipe_h
#define Equipe_h

#include <vector>
#include <iostream>
#include "Joueur.h"

using namespace std;

class Joueur;

class Equipe {

public:

    /**
     * @brief Equipe Constructeur
     * @param nom le nom de l'équipe
     */
    Equipe(string nom);

    /**
     * @brief getNom Getter du nom de l'équipe
     * @return Le nom de l'équipe
     */
    string getNom();

    /**
     * @brief setNom Setter du nom de l'équipe
     * @param nom le nouveau nom
     */
    void setNom(string nom);

    /**
     * @brief getNombreJoueur Getter du nombre de joueur
     * @return le nombre de joueur
     */
    int getNombreJoueur();

    /**
     * @brief setNombreJoueur setter du nombre de joueur
     * @param nombre le nouveau nombre de joueur
     */
    void setNombreJoueur(int nombre);

    /**
     * @brief getIndexCourrant Getter de l'index courant
     * @return l'index du joueur courant
     */
    int getIndexCourrant();

    /**
     * @brief setIndexCourrant Setter de l'index courant
     * @param newIndex le nouvel index
     */
    void setIndexCourrant(int newIndex);

    /**
     * @brief tournerIndex fait avancer l'index d'un cran
     */
    void tournerIndex();

private:
    /**
     * @brief nom Nom de l'équipe
     */
    string nom;
    /**
     * @brief nombreJoueur Le nombre de joueur dans l'équipe
     */
    int nombreJoueur;
    /**
     * @brief indexJoueurCourrant Index du joueur qui est en train de joueur
     */
    int indexJoueurCourrant;
};

#endif // Equipe_h
