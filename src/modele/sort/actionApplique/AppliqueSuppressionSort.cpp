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
    list<int> listId, listEligible;
    int i = 0, indiceAlea, j = 0;
    auto listeSort = cible.getListSort();
    for(auto it = listeSort.begin(); i < listeSort.size(); i++, it++)
    {
        if(PredicatCompterSort::estEligible(this->sortEnnemi, it->second, sortExecutant) == true)
        {
            listEligible.push_front(it->second->getId());
        }
    }
    for(i = 0; i < this->nombreSort && listEligible.size() > 0; i++)
    {
        indiceAlea = rand()%listEligible.size();
        listId.push_front(AppliqueSuppressionSort::indiceConteneur(listEligible, indiceAlea));
        AppliqueSuppressionSort::deleteIndice(listEligible, indiceAlea);
    }
    for(auto it = listId.begin(); it != listId.end(); it++)
    {
        cible.retirerSortId(*it, true);
    }
}

void AppliqueSuppressionSort::deleteIndice(list<int> & liste, int indice)
{
    auto it = liste.begin();
    int i = 0;
    while(i != indice && it != liste.end())
    {
        it++;
    }
    if(it != liste.end())
    {
        liste.erase(it);
    }
}

int AppliqueSuppressionSort::indiceConteneur(list<int> liste, int indice)
{
    int i = 0;
    auto it = liste.begin();
    for(; i != indice; i++, it++)
    {
        if(it == liste.end())
        {
            throw exception();
        }
    }
    return *it;
}

PredicatCompterSort::PredicatCompterSort(bool sortEnnemi, Sort* sortExecutant, int taille)
{
    this->sortEnnemi = sortEnnemi;
    this->sortExecutant = sortExecutant;
    this->counter = 0;
    this->taille = taille;
}

bool PredicatCompterSort::operator()(pair<int, Sort*> const& paire)
{
    //FIXME le count_if renvoi au moins un élément en plus qui n'est pas set -> valeur incohérente
    if(this->counter < this->taille)
    {
        this->counter++;
        return PredicatCompterSort::estEligible(this->sortEnnemi, paire.second, sortExecutant);
    }
    return false;
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
