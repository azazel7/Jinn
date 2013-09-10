#ifndef Sort_h
#define Sort_h

enum TypeSort { FEU = 1, EAU = 2, TERRE = 3, AIR = 4, TENEBRE = 5, LUMIERE = 6, NEUTRE = 7};

#include <vector>
#include <iostream>
#include <cstdlib>
#include "sort/SortAppliquerSurCase.h"
#include "sort/SortActionChronique.h"
#include "Case.h"

using namespace std;
class Joueur;
class Case;


//que faire une fois la boucle des ID bouclée ? Il faut plusieurs millier de siécles à raison de 10000 sorts lancé par seconde pour la boucler. Et aucun sort ne dure 2^64 tours
static unsigned long int nextId = 1;

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
     * @return La description du sort
     */
    string getDescription() const;

    /**
      * @brief Destructeur
      */
    ~Sort();

    /**
     * @brief calculeNouveauTauxReussite Calcule un taux de réussite en fonction de la dissipation d'une case
     * @param dissip La dissipation de la case
     * @param ancienTaux Le taux de réussite du sort
     * @return Le nouveau taux de réussite
     */
    static int calculeNouveauTauxReussite(int dissip, int ancienTaux);

    /**
     * @brief testerReussite Test la réussite d'un sort en fonction de son taux
     * @param taux Le taux de réussite du sort
     * @return true si le sort à réussi
     */
    static bool testerReussite(int taux);

    /**
     * @brief Sort Constructeur
     * @param nom
     * @param coupMana
     * @param elite
     * @param porteeMax
     * @param reussite
     * @param nbCible
     * @param attaque
     * @param duree
     * @param znEffet
     * @param dissip
     * @param nbMaxSortDissip
     */
    Sort(string nom, int coupMana, bool elite, int porteeMax, int reussite,
         int nbCible, int attaque, int duree, int znEffet, int dissip,
         int nbMaxSortDissip, TypeSort type);

    /**
     * @brief Sort Constructeur
     */
    Sort();


    int getPourcentageReussite();

    int getCoupManaParCase();

    void setCoutManaParCase(int value);

    Joueur* getProprietaire() const;

    void setProprietaire(Joueur* proprietaire);

    string getNom() const;

    bool getElite();

    int getPorteeMax() const;

    int getnombreCibleMax() const;

    unsigned long int getId() const;

    void setId(unsigned long int id);

    int getDuree() const;

    /**
     * @brief ajouterApplication Ajout un nouvel effet qui s'appliquera instantanément lors de l'execution du sort
     * @param newEffect L'effet
     */
    void ajouterApplication(SortAppliquerSurCase* newEffect);

    /**
     * @brief ajouterActionChronique Ajoute un effet chronique au sort
     * @param newEffect Le nouvel effet
     */
    void ajouterActionChronique(SortActionChronique* newEffect);

    void setDescription(string const& newDescription);

    Case* getOrigine();

    void setOrigine(Case* origine);

    int getAttaque();

    TypeSort getTypeSort();

    void setTypeSort(TypeSort type);

    static bool comparaisonType(TypeSort typeSort, TypeSort typeLanceur);

    static int nouvelleEffet(int niveauAbilite, int effet);

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
    unsigned long int id;

    vector<SortAppliquerSurCase*> listeApplicationSurCase;
    vector<SortActionChronique*> listeEffetChronique;
    Case* origine;
    Joueur *proprietaire;
};

ostream& operator<<( ostream &flux, TypeSort const& pos);
#endif // Sort_h
