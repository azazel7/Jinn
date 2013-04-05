#ifndef Joueur_h
#define Joueur_h

#include <vector>

#include "Action.h"
#include "Equipe.h"
#include <iostream>
#include <cstdlib>

using namespace std;

class Sort;
class Action;
class Equipe;

class Joueur
{

public:

	Joueur();

	Joueur(int gainInit, int manaMax, int abiliteInit, string nom);

	virtual Action effectuerAction();

	virtual void diminuerMana(int quantite = 1);

	virtual bool estMort();

	virtual void genererStatistique();

	virtual string saisieNom();

	virtual string saisieEquipe(std::vector< Equipe* > & equipe);

	virtual string saisieSort(vector<Sort* > const& sort);


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
