#include "sort/actionApplique/AppliqueVolDeMana.h"

AppliqueVolDeMana::AppliqueVolDeMana(int degat, bool type, bool ajout, bool retrait, bool manaMax, bool peutTuer)
{
    this->degat = degat;
    this->ajout = ajout;
    this->retrait = retrait;
    this->type = type;
    this->manaMax = manaMax;
    this->peutTuer = peutTuer;
}

void AppliqueVolDeMana::appliquerSortSurCase(Case &cible, Sort* sortExecutant)
{
    if(this->ajout == false)
    {
        return;
    }
    this->infliger(cible, sortExecutant);
}
void AppliqueVolDeMana::retirerSortDeCase(Case &cible, Sort* sortExecutant)
{
    if(this->retrait == false)
    {
        return;
    }
    this->infliger(cible, sortExecutant);
}

void AppliqueVolDeMana::infliger(Case &cible, Sort* sortExecutant)
{
    Joueur* prorio = cible.getProprietaire();
    int deg = 0;
    if(prorio == NULL || sortExecutant->getProprietaire() == NULL)
    {
        return;
    }
    if(this->type == true)
    {
        if(this->manaMax == true)
        {
            deg = floor((prorio->getManaMaximum()*this->degat)/100);
        }
        else
        {
            deg = floor((prorio->getManaActuel()*this->degat)/100);
        }
    }
    else
    {
        deg = this->degat;
    }
    if(this->peutTuer == false)
    {
        if(deg >= prorio->getManaActuel())
        {
            deg = prorio->getManaActuel() - 1;
        }
    }
    prorio->diminuerMana(deg);
    sortExecutant->getProprietaire()->augmenterMana(deg);
}
