#include "NoeudRecetteSort.h"
#include <algorithm>


NoeudRecetteSort::NoeudRecetteSort()
{
}
NoeudRecetteSort::NoeudRecetteSort(NoeudRecetteSort* n)
{
    this->attribut = n->attribut;
    this->valeur = n->valeur;
    for(NoeudRecetteSort* enfant : n->fils)
    {
        fils.push_back(new NoeudRecetteSort(enfant));
    }
}

string NoeudRecetteSort::getAttribut()
{
    return this->attribut;
}

string NoeudRecetteSort::getValeur()
{
    return this->valeur;
}

NoeudRecetteSort* NoeudRecetteSort::getFils(string attribut)
{
    for(NoeudRecetteSort* enfant : fils)
    {
        if(enfant->getAttribut() == attribut)
        {
            return enfant;
        }
    }
    return NULL;
}

void NoeudRecetteSort::setAttribut(string a)
{
    this->attribut = a;
}

void NoeudRecetteSort::setValeur(string a)
{
    this->valeur = a;
}

string NoeudRecetteSort::getValeurFils(string attribut)
{
    NoeudRecetteSort* fils = getFils(attribut);
    if(fils == NULL)
    {
        throw invalid_argument("Attribut inexistant");
    }
    return fils->getValeur();
}

int NoeudRecetteSort::getValeurFilsInt(string attribut)
{
    return std::stoi(getValeurFils(attribut));
}

bool NoeudRecetteSort::getValeurFilsBool(string attribut)
{
    return getValeurFils(attribut)[0] == '1';
}

vector<NoeudRecetteSort*>const& NoeudRecetteSort::getListFils()
{
    return fils;
}

void NoeudRecetteSort::addFils(NoeudRecetteSort* n)
{
    fils.push_back(n);
}

NoeudRecetteSort::~NoeudRecetteSort()
{
    for(NoeudRecetteSort* enfant : fils)
    {
        delete enfant;
    }
}
