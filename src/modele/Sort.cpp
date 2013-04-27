#include "Sort.h"

Sort::Sort()
{

}

Sort::~Sort()
{
}

Sort::Sort(string nom, int coupMana, bool elite, int porteeMax, int reussite, int nbCible, int attaque, int duree, int znEffet, int dissip, int nbMaxSortDissip)
{
    this->nom = nom;
    this->coupManaParCase = coupMana;
    this->elite = elite;
    this->porteeMax = porteeMax;
    this->pourcentageReussite = reussite;
    this->nombreCibleMax = nbCible;
    this->attaque = attaque;
    this->duree = duree;
    this->zoneEffet = znEffet;
    this->effetDissipation = dissip;
    this->nombreMaxSortDissipable = nbMaxSortDissip;

}

int Sort::calculeNouveauTauxReussite(int dissip, int ancienTaux)
{
    return ancienTaux;
}

int Sort::getPourcentageReussite()
{
	return pourcentageReussite;
}

bool Sort::testerReussite(int taux)
{
    int nb = rand()%100;
    if(nb <= taux)
    {
        return true;
    }
    return false;
}

Joueur* Sort::getProprietaire()
{
	return proprietaire;
}

int Sort::getCoupManaParCase()
{
	return coupManaParCase;
}

string Sort::getNom()
{
    return nom;
}

void Sort::setProprietaire(Joueur* proprietaire)
{
    this->proprietaire = proprietaire;
}

bool Sort::getElite()
{
    return this->elite;
}

int Sort::getPorteeMax()
{
    return this->porteeMax;
}
