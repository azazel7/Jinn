#ifndef Action_h
#define Action_h

#include <vector>
#include "sort/Sort.h"
#include <iostream>

using namespace std;

class Case;
class Sort;

class Action
{

public:

    /**
     * @brief Action Constructeur de base
     */
    Action();

    /**
     * @brief Action Constructeur permettant de setter tous les éléments de l'action
     * @param origine L'origine de l'action
     * @param sort Le sort de l'action
     * @param cible La liste des cibles
     */
	Action(Case *origine, Sort *sort, std::vector<Case*> cible);

    /**
     * @brief getSort Getter du sort de l'action
     * @return Le sort de l'action
     */
    Sort* getSort();

    /**
     * @brief getOrigine Getter de l'origine
     * @return La case d'origine de l'action
     */
    Case* getOrigine();

    /**
     * @brief getCible Getter de la liste des cibles
     * @return
     */
    std::vector<Case*> getCible();

    /**
     * @brief setOrigine
     * @param origine
     */
    void setOrigine(Case* origine);

    /**
     * @brief setSort setter de Sort
     * @param sort Un pointeur vers le nouveau sort
     */
    void setSort(Sort* sort);

    /**
     * @brief ajouterCible Ajoute une cible à la liste
     * @param nouvelleCase La case à ajouter aux cibles
     */
    void ajouterCible(Case* nouvelleCase);

    /**
     * @brief possedeCible verifie si une case fait déjà partie des cibles
     * @param nouvelleCase La case à vérifier
     * @return true si la cible est déjà dans la liste
     */
    bool possedeCible(Case* nouvelleCase);

protected:

	Case *origine;

	/**
	 * @element-type Case
	 */
	std::vector<Case*> cible;

	Sort *sort;
};

#endif
