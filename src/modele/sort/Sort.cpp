#include "sort/Sort.h"

Sort::Sort(string nom, int coupMana, bool elite, int porteeMax, int reussite, int nbCible, int attaque, int duree, int znEffet, int dissip, int nbMaxSortDissip, TypeSort type)
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
    this->typeSort = type;
    this->id = nextId;
    this->proprietaire = NULL;
    this->origine = NULL;
    nextId +=1;

}
Sort::Sort()
{
    this->id = nextId;
    nextId +=1;
}

int Sort::calculeNouveauTauxReussite(int dissip, int ancienTaux)
{
    return ceil(ancienTaux - dissip);
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

unsigned long int Sort::getId() const
{
    return this->id;
}

void Sort::setId(unsigned long int id)
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

void Sort::ajouterActionChronique(SortActionChronique* newEffect)
{
    this->listeEffetChronique.push_back(newEffect);
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

string Sort::getDescription() const
{
    return this->description;
}

void Sort::setDescription(string const& newDescription)
{
    this->description = newDescription;
}

int Sort::getDuree() const
{
    return this->duree;
}

Case* Sort::getOrigine()
{
    return this->origine;
}

void Sort::setOrigine(Case* origine)
{
    this->origine = origine;
}

int Sort::getAttaque()
{
    return this->attaque;
}
TypeSort Sort::getTypeSort()
{
    return this->typeSort;
}

void Sort::setTypeSort(TypeSort type)
{
    this->typeSort = type;
}

bool Sort::comparaisonType(TypeSort typeSort, TypeSort typeLanceur)
{
    if(typeLanceur == typeSort)
    {
        return true;
    }
    return false;
}

int Sort::nouvelleEffet(int niveauAbilite, int effet)
{
    double modificationEffet = (effet * niveauAbilite) / 100;
    return effet + ceil(modificationEffet);
}

string to_string(TypeSort const& pos)
{
    string chaine;
    switch(pos)
    {
    case FEU:
        chaine = "Feu";
        break;
    case EAU:
        chaine = "Eau";
        break;
    case TERRE:
        chaine = "Terre";
        break;
    case AIR:
        chaine = "Air";
        break;
    case LUMIERE:
        chaine = "Lumiere";
        break;
    case TENEBRE:
        chaine = "Tenebre";
        break;
    case NEUTRE:
        chaine = "Neutre";
        break;
    default:
        chaine = "Inconnu";
        break;
    }
    return chaine;
}

void Sort::setCoutManaParCase(int value)
{
    this->coupManaParCase = value;
}

ostream& operator<<( ostream &flux, TypeSort const& pos)
{
    string chaine = to_string(pos);
    flux << chaine;
    return flux;
}
