#ifndef ManipulationActionChronique_h
#define ManipulationActionChronique_h

#include <vector>

class SortActionChronique;
class Sort;
class Case;
using namespace std;

class ManipulationActionChronique
{
protected:
    vector<SortActionChronique*> listeEffetChronique;

public:
    /**
     * @brief effectuerActionChronique Permet de spécifier quelle action faire à chaque tour
     * @param cible la case qui est affectée
     */
    void effectuerActionChronique(Case &cible, Sort* sort);

    /**
     * @brief ajouterActionChronique Ajoute un effet chronique au sort
     * @param newEffect Le nouvel effet
     */
    void ajouterActionChronique(SortActionChronique* newEffect);

    virtual ~ManipulationActionChronique();
    //TODO Destructeur dans manipulation
};

#endif
