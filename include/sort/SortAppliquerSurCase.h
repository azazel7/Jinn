#ifndef SortAppliquerSurCase_h
#define SortAppliquerSurCase_h

#include <iostream>
#include <map>
#include "NoeudRecetteSort.h"
#include "RecetteSort.h"
#include "sort/ManipulationAppliquerSurCase.h"

using namespace std;
class Case;
class Sort;

class SortAppliquerSurCase
{
    public:
    /**
     * @brief appliquerSortSurCase Applique l'effet sur la case cible en fonction du sort
     * @param cible La case cible
     * @param sortExecutant Le sort effectuant l'effet
     */
    virtual void appliquerSortSurCase(Case &cible, Sort* sortExecutant) = 0;

    /**
     * @brief retirerSortDeCase S'il est inversable, revoque les effets produit par la fonction appliquerSortSurCase
     * @param cible La case cible
     * @param sortExecutant Le sort effectuant l'effet
     */
    virtual void retirerSortDeCase(Case &cible, Sort* sortExecutant) = 0;

    virtual ~SortAppliquerSurCase();
};

class SortAppliquerSurCaseFactory
{
public:
    SortAppliquerSurCaseFactory(string name);

    virtual SortAppliquerSurCase* getNewInstance(NoeudRecetteSort* n) = 0;
    static std::map<string, SortAppliquerSurCaseFactory*> getListe();
private:
    static std::map<string, SortAppliquerSurCaseFactory*>  liste;

};

template<class T>
class SortAppliquerSurCaseRegister : public SortAppliquerSurCaseFactory
{
public:
    SortAppliquerSurCaseRegister(string name) : SortAppliquerSurCaseFactory(name)
    {
    }
    virtual SortAppliquerSurCase* getNewInstance(NoeudRecetteSort* n)
    {
        SortAppliquerSurCase* tmp = new T(n);
        ManipulationAppliquerSurCase* manip = NULL;
        if((manip = dynamic_cast<ManipulationAppliquerSurCase*>(tmp)) != 0)
        {
            vector<NoeudRecetteSort*> const& fils = n->getListFils();
            for(NoeudRecetteSort* enfant : fils)
            {
                if(enfant->getAttribut() == APPLICATION_CHAINE)
                {
                    if(SortAppliquerSurCaseFactory::getListe().count(enfant->getValeur()) == 1)
                    {
                        SortAppliquerSurCase* s = SortAppliquerSurCaseFactory::getListe()[enfant->getValeur()]->getNewInstance(enfant);
                        manip->ajouterApplication(s);
                    }
                }
            }
        }
        return tmp;
    }
};

#endif
