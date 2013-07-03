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

    Action();

	Action(Case *origine, Sort *sort, std::vector<Case*> cible);
	/**
	 *  Permet de recupérer le sort lié à une action
	 */
    Sort* getSort();

	/**
	 *  Récupére l'origine du sort
	 */
    Case* getOrigine();

	/**
	 *  Récupére la liste des cibles du sort
	 */
    std::vector<Case*> getCible();

    void setOrigine(Case* origine);

    void setSort(Sort* sort);

    void ajouterCible(Case* nouvelleCase);

    bool possedeCible(Case* nouvelleCase);

protected:

	Case *origine;

	/**
	 * @element-type Case
	 */
	std::vector<Case*> cible;

	Sort *sort;
};

#endif // Action_h
