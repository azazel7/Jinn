#include "sort/actionApplique/AppliqueConsommerMana.h"

AppliqueConsommerMana::AppliqueConsommerMana(int valeur, bool type,bool ajout, bool retrait) //type = true => pourcentage
{
    this->valeurSoin = valeur;
    this->type = type;
    this->ajout = ajout;
    this->retrait = retrait;
}
void AppliqueConsommerMana::appliquerSortSurCase(Case &cible, Sort* sortExecutant)
{
    if(this->ajout == true)
    {
        Joueur* proprio = sortExecutant->getProprietaire();
        if(proprio == NULL)
        {
            return;
        }
        if(this->type == true)
        {
            int coutMana = floor((proprio->getManaActuel()*this->valeurSoin)/100);
            proprio->diminuerMana(coutMana);
            sortExecutant->setCoutManaParCase(coutMana);

        }
        else
        {
            proprio->diminuerMana(this->valeurSoin);
            sortExecutant->setCoutManaParCase(this->valeurSoin);
        }
    }
}

void AppliqueConsommerMana::retirerSortDeCase(Case &cible, Sort* sortExecutant)
{
    if(this->retrait == true)
    {
        Joueur* proprio = sortExecutant->getProprietaire();
        if(proprio == NULL)
        {
            return;
        }
        if(this->type == true)
        {
            int coutMana = floor((proprio->getManaActuel()*this->valeurSoin)/100);
            proprio->diminuerMana(coutMana);
            sortExecutant->setCoutManaParCase(coutMana);

        }
        else
        {
            proprio->diminuerMana(this->valeurSoin);
            sortExecutant->setCoutManaParCase(this->valeurSoin);
        }
    }
}
