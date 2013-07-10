#ifndef Case_h
#define Case_h

#include "Joueur.h"
#include "Position.h"
#include "list"
#include "sort/Sort.h"


#include <iostream>
using namespace std;

class Joueur;
class Sort;
class Case
{

public:
    virtual void setProprietaire(Joueur *nouveauProprietaire);

    Case(int defIni, int bonOff, int dissip, int attenu, int mana, int regenDef,
         int camoufla, Position* position);

    void retirerSortEcoule();
    void ajouterSort(Sort* nouveauSort, int duree);
    void effectuerActionChroniqueDesSorts();
    int dureeRestanteSort(Sort* sortCherche);
    void modifierDefense(int nombre);
    void modifierDefenseReel(int nombre);
    void retirerJoueur(Joueur* joueur);
    void retirerSort(int index, bool compteEffet);
    void retirerSortId(int id, bool compteEffet);
    list<pair<int, Sort*> > getListSort();
    Sort* getSort(int index);
    Sort* getSortId(int id);
    int getApportMana() const;
    void setApportMana(int apportMana);
    int getBonusOffensifActuel() const;
    void setBonusOffensifActuel(int bonusOffensifActuel);
    int getBonusOffensifInitial() const;
    void setBonusOffensifInitial(int bonusOffensifInitial);
    int getCamouflageInitial() const;
    void setCamouflageInitial(int camouflageInitial);
    int getCamouflageReel() const;
    void setCamouflageReel(int camouflageReel);
    bool isControlable() const;
    void setControlable(bool controlable);
    int getDefenseActuelle() const;
    void setDefenseActuelle(int defenseActuelle);
    int getDefenseInitiale() const;
    void setDefenseInitiale(int defenseInitiale);
    int getDefenseReel() const;
    void setDefenseReel(int defenseReel);
    int getEffetAttenuation() const;
    void setEffetAttenuation(int effetAttenuation);
    int getEffetDissipation() const;
    void setEffetDissipation(int effetDissipation);
    void setPosition(Position* position);
    Position* getPosition() const;
    Joueur* getProprietaire() const;
    int getRegenerationDefense() const;
    void setRegenerationDefense(int regenerationDefense);
    int nombreDeSortEnCour();
    string getNomProprietaire() const;

    ~Case();

private:
    bool controlable;
    int defenseInitiale;
    int defenseReel;
    int defenseReelEffective;
    int defenseActuelle;
    int bonusOffensifInitial;
    int bonusOffensifActuel;
    int effetDissipation;
    int effetAttenuation;
    int apportMana;
    int regenerationDefense;
    int camouflageInitial;
    int camouflageReel;

private:
    Joueur *proprietaire;
    Position *position;
    list<pair<int, Sort*> > sort;
};

ostream& operator<<( ostream &flux, Case const& pos);

#endif // Case_h
