#include "Case.h"

void Case::setProprietaire(Joueur *nouveauProprietaire)
{
	//TODO Notifier ancien propriétaire
	this->proprietaire = nouveauProprietaire;
}

Case::Case(int defIni, int bonOff, int dissip, int attenu, int mana, int regenDef, int camoufla, Position* position)
{
	this->defenseInitiale = defIni;
	this->defenseActuelle = defIni;
	this->defenseReel = defIni;

	this->bonusOffensifInitial = bonOff;
	this->bonusOffensifActuel = bonOff;

	this->effetDissipation = dissip;
	this->effetAttenuation = attenu;
	this->apportMana = mana;
	this->regenerationDefense = regenDef;
	this->camouflageInitial = camoufla;
	this->camouflageReel = camoufla;
	this->controlable = true;
	this->position = position;
	this->proprietaire = NULL;
}

void Case::retirerSortEcoule()
{
    list<pair<int, Sort*> >::iterator iterator;
    for(iterator = sort.begin(); iterator != sort.end(); iterator++)
    {
        iterator->first--;
        if(iterator->first < 0)
        {
            iterator->second->retirerDeCase(*this);
            sort.erase(iterator);
        }
    }
}

void Case::effectuerActionChroniqueDesSorts()
{
    list<pair<int, Sort*> >::iterator iterator;
    //On parcour tous les sorts de la case
    for(iterator = sort.begin(); iterator != sort.end(); iterator++)
    {
        //On effectue l'action à chaque tour
        iterator->second->effectuerActionChronique(*this);
    }
}

void Case::ajouterSort(Sort* nouveauSort, int duree)
{
    //On créer un nouvelle paire
    pair<int, Sort*> nouvellePaire = make_pair(duree, nouveauSort);
    //On ajoute la nouvelle paire
    sort.push_front(nouvellePaire);
}

int Case::dureeRestanteSort(Sort* sortCherche)
{
    list<pair<int, Sort*> >::iterator iterator;
    //On parcour tous les sorts de la case
    for(iterator = sort.begin(); iterator != sort.end(); iterator++)
    {
        if(iterator->second == sortCherche)
        {
            return iterator->first;
        }
    }
}

void Case::modifierDefense(int nombre)
{
    this->defenseActuelle += nombre;
    if(this->defenseActuelle > this->defenseReel)
    {
        this->defenseActuelle = this->defenseReel;
    }
    else if(this->defenseActuelle < 0)
    {
        this->defenseActuelle = 0;
    }
}

Position* Case::getPosition() const
{
	return position;
}
int Case::getApportMana() const
{
	return apportMana;
}

void Case::setApportMana(int apportMana)
{
	this->apportMana = apportMana;
}

int Case::getBonusOffensifActuel() const
{
	return bonusOffensifActuel;
}

void Case::setBonusOffensifActuel(int bonusOffensifActuel)
{
	this->bonusOffensifActuel = bonusOffensifActuel;
}

int Case::getBonusOffensifInitial() const
{
	return bonusOffensifInitial;
}

void Case::setBonusOffensifInitial(int bonusOffensifInitial)
{
	this->bonusOffensifInitial = bonusOffensifInitial;
}

int Case::getCamouflageInitial() const
{
	return camouflageInitial;
}

void Case::setCamouflageInitial(int camouflageInitial)
{
	this->camouflageInitial = camouflageInitial;
}

int Case::getCamouflageReel() const
{
	return camouflageReel;
}

void Case::setCamouflageReel(int camouflageReel)
{
	this->camouflageReel = camouflageReel;
}

bool Case::isControlable() const
{
	return controlable;
}

void Case::setControlable(bool controlable)
{
	this->controlable = controlable;
}

int Case::getDefenseActuelle() const
{
	return defenseActuelle;
}

void Case::setDefenseActuelle(int defenseActuelle)
{
	this->defenseActuelle = defenseActuelle;
}

int Case::getDefenseInitiale() const
{
	return defenseInitiale;
}

void Case::setDefenseInitiale(int defenseInitiale)
{
	this->defenseInitiale = defenseInitiale;
}

int Case::getDefenseReel() const
{
	return defenseReel;
}

void Case::setDefenseReel(int defenseReel)
{
	this->defenseReel = defenseReel;
}

int Case::getEffetAttenuation() const
{
	return effetAttenuation;
}

void Case::setEffetAttenuation(int effetAttenuation)
{
	this->effetAttenuation = effetAttenuation;
}

int Case::getEffetDissipation() const
{
	return effetDissipation;
}

void Case::setEffetDissipation(int effetDissipation)
{
	this->effetDissipation = effetDissipation;
}

void Case::setPosition(Position* position)
{
	this->position = position;
}

Joueur* Case::getProprietaire() const
{
	return proprietaire;
}

int Case::getRegenerationDefense() const
{
	return regenerationDefense;
}

void Case::setRegenerationDefense(int regenerationDefense)
{
	this->regenerationDefense = regenerationDefense;
}

ostream& operator<<( ostream &flux, Case const& pos)
{
    string nom = "Sans proprietaire";
    Joueur *propri;
    propri = pos.getProprietaire();
    if(propri != NULL)
    {
        nom = propri->getNom();
    }
    flux << "(" << *(pos.getPosition()) << " [" << pos.getDefenseActuelle() << "/" << pos.getDefenseReel() << "] " << " " << nom << ")";
    return flux;
}
