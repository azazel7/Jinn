#include "sort/Sort.h"


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
    this->id = nextId;
    nextId +=1;

}
Sort::Sort()
{
    this->id = nextId;
    nextId +=1;
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

Joueur* Sort::getProprietaire() const
{
	return proprietaire;
}

int Sort::getCoupManaParCase()
{
	return coupManaParCase;
}

string Sort::getNom() const
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

int Sort::getPorteeMax() const
{
    return this->porteeMax;
}

int Sort::getnombreCibleMax() const
{
        return this->nombreCibleMax;
}

unsigned int Sort::getId() const
{
        return this->id;
}

void Sort::setId(unsigned int id)
{
        this->id = id;
}

void Sort::appliquerSortSurCase(Case &cible)
{
        for(int i = 0; i < this->listeApplicationSurCase.size(); i++)
        {
                this->listeApplicationSurCase[i]->appliquerSortSurCase(cible, this);
        }
}


void Sort::retirerDeCase(Case &cible)
{
        for(int i = 0; i < this->listeApplicationSurCase.size(); i++)
        {
                this->listeApplicationSurCase[i]->retirerSortDeCase(cible, this);
        }
}

void Sort::effectuerActionChronique(Case &cible)
{
        for(int i = 0; i < this->listeEffetChronique.size(); i++)
        {
                this->listeEffetChronique[i]->effectuerActionChronique(cible, this);
        }
}

void Sort::ajouterApplication(SortAppliquerSurCase* newEffect)
{
        this->listeApplicationSurCase.push_back(newEffect);
}
Sort::~Sort()
{
        for(int i = 0; i < this->listeApplicationSurCase.size(); i++)
        {
                delete this->listeApplicationSurCase[i];
        }
        for(int i = 0; i < this->listeEffetChronique.size(); i++)
        {
                delete this->listeEffetChronique[i];
        }
        this->listeApplicationSurCase.clear();
        this->listeEffetChronique.clear();
}

string Sort::getDescription()
{
        return this->description;
}

void Sort::setDescription(string const& newDescription)
{
        this->description = newDescription;
}

Sort& Sort::operator=(Sort const& sortModele)
{
    Sort* sort = UsineSort::fabriqueSort(sortModele.getNom());
    sort->setProprietaire(sortModele.getProprietaire());
    sort->origine = sortModele.origine;
    return *sort;
}
