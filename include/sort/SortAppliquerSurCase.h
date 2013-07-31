#ifndef SortAppliquerSurCase_h
#define SortAppliquerSurCase_h


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
};

#endif
