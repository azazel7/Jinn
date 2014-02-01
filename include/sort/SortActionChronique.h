#ifndef SortActionChronique_h
#define SortActionChronique_h

#include <iostream>
#include <map>
#include "sort/Sort.h"
#include "Case.h"
#include "ManipulationActionChronique.h"
#include "RecetteSort.h"


class SortActionChronique
{
    public:
    /**
     * @brief effectuerActionChronique Effectue un effet sur la case cible en fonction du sort
     * @param cible La case cible
     * @param sortExecutant Le sort produisant cet effet
     */
    virtual void effectuerActionChronique(Case &cible, Sort *sortExecutant) = 0;

    virtual ~SortActionChronique();
};

class SortActionChroniqueFactory
{
public:
    SortActionChroniqueFactory(string name);

    virtual SortActionChronique* getNewInstance(NoeudRecetteSort* n) = 0;
    static std::map<string, SortActionChroniqueFactory*> getListe();
private:
    static std::map<string, SortActionChroniqueFactory*>  liste;

};

template<class T>
class SortActionChroniqueRegister : public SortActionChroniqueFactory
{
public:
    SortActionChroniqueRegister(string name) : SortActionChroniqueFactory(name)
    {}
    virtual SortActionChronique* getNewInstance(NoeudRecetteSort* n)
    {
        SortActionChronique* tmp = new T(n);
        ManipulationActionChronique* manip = NULL;
        if((manip = dynamic_cast<ManipulationActionChronique*>(tmp)) != 0)
        {
            vector<NoeudRecetteSort*> const& fils = n->getListFils();
            for(NoeudRecetteSort* enfant : fils)
            {
                if(enfant->getAttribut() == CHRONIQUE_CHAINE)
                {
                    if(SortActionChroniqueFactory::getListe().count(enfant->getValeur()) == 1)
                    {
                        SortActionChronique* s = SortActionChroniqueFactory::getListe()[enfant->getValeur()]->getNewInstance(enfant);
                        manip->ajouterActionChronique(s);
                    }
                }
            }
        }
        return tmp;
    }
};
#endif
