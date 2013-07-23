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
    map<string, Joueur*> getListeJoueur();

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

    void ajouterMessage(string auteur, string message);
    list<pair<string, string> > getListeMessage();

    void setJoueurClient(string joueur);
    string getJoueurClient();

    void setNombrePlace(int value);
    int getNombrePlace();

    void setNombreJoueur(int value);
    int getNombreJoueur();

    void setNombreSortParJoueur(int value);
    int getNombreSortParJoueur();

    void setEquipeGagnante(string nom);
    string getEquipeGagnante();

    map<int, Case*> getListeCase();

    void ajouterNotification(string notification);
    list<string> getListeNotification();
private:
    map<string, Joueur*> listeJoueur;
    map<int, Case*> listeCase;
    Joueur* joueurCourant;
    string joueurClient;
    vector<Sort*> listeSortDispo;
    vector<string> listeEquipe;
    list<pair<string, string> > listeMessage;
    list<string> listeNotification;
    string equipeGagnante;

    int nombrePlace;
    int nombreJoueur;
    int nombreSortParJouer;

};
#endif
