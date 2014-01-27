#include "NoeudRecetteSort.h"

NoeudRecetteSort::NoeudRecetteSort(NoeudRecetteSort *pere)
{
    this->pere = pere;
}

string NoeudRecetteSort::getAttribut()
{
    return this->attribut;
}

string NoeudRecetteSort::getValeur()
{
    return this->valeur;
}

NoeudRecetteSort* NoeudRecetteSort::getPere()
{
    return this->pere;
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
        throw new string("Erreur");
    }
    return fils->getValeur();
}

int NoeudRecetteSort::getValeurFilsInt(string attribut)
{
    return std::stoi(getValeurFils(attribut));
}

bool NoeudRecetteSort::getValeurFilsBool(string attribut)
{
    return getValeurFils(attribut)[0] == 1;
}

vector<NoeudRecetteSort*>const& NoeudRecetteSort::getListFils()
{
    return fils;
}

void NoeudRecetteSort::addFils(NoeudRecetteSort* n)
{
    fils.push_back(n);
}
