#ifndef Action_h
#define Action_h

#include <vector>

#include "Case.h"
#include "Sort.h"

#include <iostream>

using namespace std;

class Sort;
class Case;

class Action
{

public:

    Action();

	Action(Case *origine, Sort *sort, std::vector<Case*> cible);
	/**
	 *  Permet de recupérer le sort lié à une action
	 */
	virtual Sort* getSort();

	/**
	 *  Récupére l'origine du sort
	 */
	virtual Case* getOrigine();

	/**
	 *  Récupére la liste des cibles du sort
	 */
	virtual std::vector<Case*> getCible();

protected:

	Case *origine;

	/**
	 * @element-type Case
	 */
	std::vector<Case*> cible;

	Sort *sort;
};

#endif // Action_h
