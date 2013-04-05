#ifndef Joueur_h
#define Joueur_h

#include <vector>

#include "Action.h"
#include <iostream>

using namespace std;

class Sort;
class Action;

class Joueur
{

public:

	Joueur();

	Joueur(int gainInit, int manaMax, int abiliteInit, string nom);

	virtual Action effectuerAction();

	virtual void diminuerMana(int quantite = 1);

	virtual bool estMort();

private:
	string nom;
	int gainInitialMana;
	int manaMaximum;
	int manaActuel;
	int abilite;

public:

	/**
	 * @element-type Sort
	 */
	std::vector<Sort*> maitriser;

};

#endif // Joueur_h
