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
    virtual Sort* getSort();

	/**
	 *  Récupére l'origine du sort
	 */
	virtual Case* getOrigine();

	/**
	 *  Récupére la liste des cibles du sort
	 */
	virtual std::vector<Case*> getCible();

    virtual void setOrigine(Case* origine);

    virtual void setSort(Sort* sort);

    virtual void ajouterCible(Case* nouvelleCase);

    virtual bool possedeCible(Case* nouvelleCase);

protected:

	Case *origine;

	/**
	 * @element-type Case
	 */
	std::vector<Case*> cible;

	Sort *sort;
};

#endif // Action_h
