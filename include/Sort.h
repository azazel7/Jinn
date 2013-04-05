#ifndef Sort_h
#define Sort_h

#include <vector>

#include "Case.h"
#include <iostream>

using namespace std;

class Effet;
class Joueur;
class Case;

class Sort
{

public:

	virtual void appliquerSortSurCase(Case &cible);

	virtual void modifierSuivantOrigine(Case const& origine);

	virtual void modifierSuivantProprietaire();

	virtual string description();

	virtual ~Sort();

	static int calculeNouveauTauxReussite(int dissip, int ancienTaux);

	static bool testerReussite(int taux);

	Sort(string nom, int coupMana, bool elite, int porteeMax, int reussite,
			int nbCible, int att, int duree, int znEffet, int dissip,
			int nbMaxSortDissip);

	virtual int getPourcentageReussite();

	virtual int getCoupManaParCase();

	virtual Joueur* getProprietaire();

private:
	string nom;
	int coupManaParCase;
	bool elite;
	int porteeMax;
	int pourcentageReussite;
	int nombreCibleMax;
	int attaque;
	int duree;
	int zoneEffet;
	int effetDissipation;
	int nombreMaxSortDissipable;

public:

	/**
	 * @element-type Effet
	 */
	std::vector<Effet*> effet;

	Joueur *proprietaire;
};

#endif // Sort_h
