#ifndef SortAppliquerSurCase_h
#define SortAppliquerSurCase_h


class Case;
class Sort;

class SortAppliquerSurCase
{
    public:
    virtual void appliquerSortSurCase(Case &cible, Sort* sortExecutant) = 0;
    virtual void retirerSortDeCase(Case &cible, Sort* sortExecutant) = 0;
};

#endif
