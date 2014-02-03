#include "sort/actionApplique/AppliqueBaseProtection.h"

AppliqueBaseProtection::AppliqueBaseProtection(NoeudRecetteSort* n)
{
    this->valeur = n->getValeurFilsInt("defense");
    this->type = n->getValeurFilsBool("percent");
}

void AppliqueBaseProtection::appliquerSortSurCase(Case &cible, Sort* sortExecutant)
{
    if(type == true)//pourcentage
    {
        this->valeur = floor((cible.getDefenseInitiale()*this->valeur)/100);
    }
    cible.modifierDefenseReel(this->valeur);
}
void AppliqueBaseProtection::retirerSortDeCase(Case &cible, Sort* sortExecutant)
{
    this->valeur = floor((cible.getDefenseInitiale()*this->valeur)/100);
    cible.modifierDefenseReel(-this->valeur);
}
