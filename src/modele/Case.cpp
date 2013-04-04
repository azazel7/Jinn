#include "Case.h"

void Case::setProprietaire(Joueur *nouveauProprietaire)
// don't delete the following line as it's needed to preserve source code of this autogenerated element
// section -64--88-1-13--510ac093:13dbbee67dc:-8000:0000000000000EED begin
{
	//TODO Notifier ancien propriétaire
	this->proprietaire = nouveauProprietaire;
}
// section -64--88-1-13--510ac093:13dbbee67dc:-8000:0000000000000EED end
// don't delete the previous line as it's needed to preserve source code of this autogenerated element

Case::Case(int defIni, int bonOff, int dissip, int attenu, int mana, int regenDef, int camoufla, Position* position)
// don't delete the following line as it's needed to preserve source code of this autogenerated element
// section -64--88-1-13--239a61df:13dc1d51575:-8000:0000000000000F1D begin
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
// section -64--88-1-13--239a61df:13dc1d51575:-8000:0000000000000F1D end
// don't delete the previous line as it's needed to preserve source code of this autogenerated element


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

