#include "Action.h"

Action::Action()
{
    this->origine = NULL;
    this->sort = NULL;
}

Action::Action(Case *origine, Sort *sort, std::vector<Case*> cible)
{
	this->origine = origine;
	this->sort = sort;
	this->cible = cible;
}


/** 
     *  Permet de recupérer le sort lié à une action
     */
Sort* Action::getSort()
{
		return sort;
}


/** 
     *  Récupére l'origine du sort
     */
Case* Action::getOrigine()
{
	return origine;
}


/** 
     *  Récupére la liste des cibles du sort
     */
std::vector<Case*> Action::getCible()
{
	return cible;
}

void Action::setOrigine(Case* origine)
{
    this->origine = origine;
}

void Action::setSort(Sort* sort)
{
    this->sort = sort;
}

void Action::ajouterCible(Case* nouvelleCase)
{
    cible.push_back(nouvelleCase);
}
