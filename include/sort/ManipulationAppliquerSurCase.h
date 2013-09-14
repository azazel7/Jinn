#ifndef ManipulationAppliquerSurCase_h
#define ManipulationAppliquerSurCase_h

#include "sort/Sort.h"
#include "sort/SortAppliquerSurCase.h"
#include "Case.h"
#include <vector>

using namespace std;

class ManipulationAppliquerSurCase
{
protected:
    vector<SortAppliquerSurCase*> listeApplicationSurCase;
    bool conditionAppliction;
public:
    ManipulationAppliquerSurCase();
    /**
     * @brief appliquerSortSurCase Applique le sort sur une case
     * @param cible
     */
    void appliquerListeEffet(Case &cible, Sort *sort);

    /**
     * @brief retirerDeCase Pour les sorts à durée, faire en sorte qu'il se retire correctement
     * @param cible
     */
    void retirerListeEffet(Case &cible, Sort* sort);

    /**
     * @brief ajouterApplication Ajout un nouvel effet qui s'appliquera instantanément lors de l'execution du sort
     * @param newEffect L'effet
     */
    void ajouterApplication(SortAppliquerSurCase* newEffect);
    //TODO Destructeur dans manipulation
    virtual ~ManipulationAppliquerSurCase();
};

#endif
