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

    /**
     * @brief appliquerSortSurCase Applique le sort sur une case
     * @param cible
     */
    virtual void appliquerSortSurCase(Case &cible) = 0;

    /**
     * @brief modifierSuivantOrigine modifie le sort suivant l'origine de la case
     * @param origine
     */
    virtual void modifierSuivantOrigine(Case const& origine) = 0;

    /**
     * @brief modifierSuivantProprietaire modifie le sort suivant les statistiques de sont proprietaire
     */
    virtual void modifierSuivantProprietaire() = 0;

    /**
     * @brief retirerDeCase Pour les sorts à durée, faire en sorte qu'il se retire correctement
     * @param cible
     */
    virtual void retirerDeCase(Case &cible) = 0;

    /**
     * @brief description Produit une description du sort
     * @return
     */
    virtual string description() = 0;

	virtual ~Sort();

	static int calculeNouveauTauxReussite(int dissip, int ancienTaux);

	static bool testerReussite(int taux);

	Sort(string nom, int coupMana, bool elite, int porteeMax, int reussite,
			int nbCible, int att, int duree, int znEffet, int dissip,
			int nbMaxSortDissip);

    Sort();

	virtual int getPourcentageReussite();

	virtual int getCoupManaParCase();

	virtual Joueur* getProprietaire();

    virtual string getNom();

protected:
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
