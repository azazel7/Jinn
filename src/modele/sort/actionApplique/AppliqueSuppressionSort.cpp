#include "sort/actionApplique/AppliqueSuppressionSort.h"

AppliqueSuppressionSort::AppliqueSuppressionSort(int nombreSort, bool ajout, bool retrait, bool sortEnnemi, int probabilite)
{
    this->nombreSort = nombreSort;
    this->probabilite = probabilite;
    this->ajout = ajout;
    this->retrait = retrait;
    this->sortEnnemi = sortEnnemi;
}

void AppliqueSuppressionSort::appliquerSortSurCase(Case &cible, Sort* sortExecutant)
{
    if(this->ajout == false)
    {
        return;
    }
    this->infliger(cible, sortExecutant);
}
void AppliqueSuppressionSort::retirerSortDeCase(Case &cible, Sort* sortExecutant)
{
    if(this->retrait == false)
    {
        return;
    }
    this->infliger(cible, sortExecutant);
}

void AppliqueSuppressionSort::infliger(Case &cible, Sort* sortExecutant)
{
    //compter le nombre de sort eligible
    int compteurSortEligible = count_if(cible.getListSort().begin(), cible.getListSort().end(), PredicatCompterSort(this->sortEnnemi, sortExecutant));
    int nombreASortSuppr = this->nombreSort;
    //Pour tous les sorts
    auto listeSort = cible.getListSort();
    for(auto it = listeSort.begin(); it != listeSort.end();)
    {
        if(compteurSortEligible == 0 || nombreASortSuppr == 0)
        {
            break;
        }
        //Si un sort peut être supprimmé, on compare le nombre de sort restant à supprier et le nombre de sort encore supprimable
        if(PredicatCompterSort::estEligible(this->sortEnnemi, it->second, sortExecutant) == true)
        {
            //Si il reste plus de sort supprimable, on fait un test sinon, on les supprime d'office
            if(nombreASortSuppr < compteurSortEligible)
            {
                if(Sort::testerReussite(this->probabilite) == true)
                {
                    listeSort.erase(it++);
                    nombreASortSuppr--;
                }
            }
            else
            {
                listeSort.erase(it++);
                nombreASortSuppr--;
            }
            compteurSortEligible--;
        }
        else
        {
            it++;
        }
    }
    //Si eligible et (nombre sort restant à supprimer < nombre de sort eligible restant), tester suppression
    //Si eligible et (nombre sort restant à supprimer >= nombre de sort eligible restant), supprime
}

PredicatCompterSort::PredicatCompterSort(bool sortEnnemi, Sort* sortExecutant)
{
    this->sortEnnemi = sortEnnemi;
    this->sortExecutant = sortExecutant;
}

bool PredicatCompterSort::operator()(pair<int, Sort*> const& paire) const
{
    return PredicatCompterSort::estEligible(this->sortEnnemi, paire.second, sortExecutant);
}

bool PredicatCompterSort::estEligible(bool sortEnnemi, Sort* sortSurCase, Sort* sortExecutant)
{
    if(sortEnnemi == false)
    {
        return true;
    }
    //FIXME bug sur le getNomEquipe
    if(sortSurCase->getProprietaire()->getNomEquipe() == sortExecutant->getProprietaire()->getNomEquipe())
    {
        return false;
    }
    return true;
}
