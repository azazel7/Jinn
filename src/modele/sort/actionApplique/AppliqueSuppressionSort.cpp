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
    cout << "Compte : " << cible.getListSort().size() << endl;
    int compteurSortEligible = count_if(cible.getListSort().begin(), cible.getListSort().end(), PredicatCompterSort(this->sortEnnemi, sortExecutant));
    int nombreASortSuppr = this->nombreSort;
    list<int> listId;
    //Pour tous les sorts
    auto listeSort = cible.getListSort();
    for(auto it = listeSort.begin(); it != listeSort.end(); it++)
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
                    listId.push_front(it->second->getId());
                    nombreASortSuppr--;
                }
            }
            else
            {
                    listId.push_front(it->second->getId());
                nombreASortSuppr--;
            }
            compteurSortEligible--;
        }
    }
    for(auto it = listId.begin(); it != listId.end(); it++)
    {
        cible.retirerSortId(*it, true);
    }
    //Si eligible et (nombre sort restant à supprimer < nombre de sort eligible restant), tester suppression
    //Si eligible et (nombre sort restant à supprimer >= nombre de sort eligible restant), supprime
}

PredicatCompterSort::PredicatCompterSort(bool sortEnnemi, Sort* sortExecutant)
{
    this->sortEnnemi = sortEnnemi;
    this->sortExecutant = sortExecutant;
    this->counter = 0;
}

bool PredicatCompterSort::operator()(pair<int, Sort*> const& paire)
{
    //FIXME le count_if renvoi au moins un élément en plus qui n'est pas set -> valeur incohérente
    cout << paire.first << endl;
    return PredicatCompterSort::estEligible(this->sortEnnemi, paire.second, sortExecutant);
}

bool PredicatCompterSort::estEligible(bool sortEnnemi, Sort* sortSurCase, Sort* sortExecutant)
{
    if(sortEnnemi == false)
    {
        return true;
    }
    cout << sortSurCase->getNom() << endl;
    //FIXME bug sur le getNomEquipe
    if(sortSurCase->getProprietaire()->getNomEquipe() == sortExecutant->getProprietaire()->getNomEquipe())
    {
        return false;
    }
    return true;
}
