#ifndef Joueur_h
#define Joueur_h

#include <vector>

#include "Action.h"
#include "Equipe.h"
#include "Sort.h"
#include "Partie.h"
#include "UsineSort.h"
#include <iostream>
#include <cstdlib>

using namespace std;

class Action;
class Equipe;
class Partie;

class Joueur
{

public:

	Joueur();

	Joueur(int gainInit, int manaMax, int abiliteInit, string nom);

    virtual Action effectuerAction(Partie & partie);

	virtual void diminuerMana(int quantite = 1);

	virtual bool estMort();

	virtual void genererStatistique();

	virtual string saisieNom();

	virtual string saisieEquipe(std::vector< Equipe* > & equipe);

	virtual string saisieSort(vector<Sort* > const& sort);

    virtual string getNom();

    virtual void setNom(string nom);

    virtual void ajouterSort(string nomSort);

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
    std::vector<Sort*> listeSort;

};

#endif // Joueur_h
