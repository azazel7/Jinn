#ifndef Case_h
#define Case_h

#include "Joueur.h"
#include "Position.h"

#include <iostream>
using namespace std;

class Joueur;

class Case
{

public:

	virtual void setProprietaire(Joueur *nouveauProprietaire);

	Case(int defIni, int bonOff, int dissip, int attenu, int mana, int regenDef,
			int camoufla, Position position);

private:
	bool controlable;
	int defenseInitiale;
	int defenseReel;
	int defenseActuelle;
	int bonusOffensifInitial;
	int bonusOffensifActuel;
	int effetDissipation;
	int effetAttenuation;
	int apportMana;
	int regenerationDefense;
	int camouflageInitial;
	int camouflageReel;

public:
	Joueur *proprietaire;
	Position *position;
};

#endif // Case_h
