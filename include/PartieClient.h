#ifndef PartieClient_h
#define PartieClient_h

#include <map>
#include <vector>
#include "Joueur.h"


class PartieClient
{
public:
    PartieClient();
    void ajouterJoueur(Joueur *joueur);
    void retirerJoueur(string const& nom);
    void ajouterSortJoueur(string const& nomJoueur, string const& nomSort);
    void retirerSortJoueur(string const& nomJoueur, string const& nomSort);
    Joueur* getJoueur(string const& nom);

    void ajouterCase(Case * newCase);
    void retirerCase(Position * position);
    void ajouterSortCase(Position * position, Sort* sort, int duree);
    void retirerSortCase(Position * position, int id);
    Case* getCase(Position * position);
    Sort* getSort(Position* position, int id_sort);

    void setJoueurCourant(Joueur* joueur);
    Joueur* getJoueurCourant();

    vector<Sort*> getListeSortDispo();
    void setListeSortDispo(vector<Sort*> nouvelleListe);

    vector<string> getListeEquipe();
    void setListeEquipe(vector<string> nouvelleListe);

private:
    map<string, Joueur*> listeJoueur;
    map<int, Case*> listeCase;
    Joueur* joueurCourant;
    vector<Sort*> listeSortDispo;
    vector<string> listeEquipe;
};
#endif
