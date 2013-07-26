#ifndef Sort_h
#define Sort_h

#include <vector>
#include <iostream>
#include <cstdlib>
#include "sort/SortAppliquerSurCase.h"
#include "sort/SortActionChronique.h"
#include "Case.h"

using namespace std;
class Joueur;
class Case;

enum TypeSort { FEU, EAU, TERRE, AIR, TENEBRE, LUMIERE };

//que faire une fois la boucle des ID bouclée ? Il faut 1 an à raison de 100 sorts lancé par seconde pour la boucler. Et aucun sort ne dure 2^32 tours
static unsigned int nextId = 1;

class Sort
{

public:

    /**
     * @brief appliquerSortSurCase Applique le sort sur une case
     * @param cible
     */
    void appliquerSortSurCase(Case &cible);

    /**
     * @brief retirerDeCase Pour les sorts à durée, faire en sorte qu'il se retire correctement
     * @param cible
     */
    void retirerDeCase(Case &cible);

    /**
     * @brief effectuerActionChronique Permet de spécifier quelle action faire à chaque tour
     * @param cible la case qui est affectée
     */
    void effectuerActionChronique(Case &cible);

    /**
     * @brief description Produit une description du sort
     * @return
     */
    string getDescription() const;

    ~Sort();

    static int calculeNouveauTauxReussite(int dissip, int ancienTaux);

    static bool testerReussite(int taux);

    Sort(string nom, int coupMana, bool elite, int porteeMax, int reussite,
         int nbCible, int attaque, int duree, int znEffet, int dissip,
         int nbMaxSortDissip);

    Sort();

    int getPourcentageReussite();

    int getCoupManaParCase();

    Joueur* getProprietaire() const;

    void setProprietaire(Joueur* proprietaire);

    string getNom() const;

    bool getElite();

    int getPorteeMax() const;

    int getnombreCibleMax() const;

    unsigned int getId() const;

    void setId(unsigned int id);

    int getDuree() const;

    void ajouterApplication(SortAppliquerSurCase* newEffect);

    void setDescription(string const& newDescription);

    Case* getOrigine();

    void setOrigine(Case* origine);

protected:
    string nom;
    string description;
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
    TypeSort typeSort;
    unsigned int id;

    vector<SortAppliquerSurCase*> listeApplicationSurCase;
    vector<SortActionChronique*> listeEffetChronique;
    Case* origine;
    Joueur *proprietaire;
};

#endif // Sort_h
