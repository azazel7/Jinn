#ifndef NOEUDRECETTESORT_H
#define NOEUDRECETTESORT_H

#include <vector>
#include <iostream>

using namespace std;

class NoeudRecetteSort
{
public:
    NoeudRecetteSort(NoeudRecetteSort* pere);
    string getAttribut();
    string getValeur();
    void setAttribut(string a);
    void setValeur(string a);
    NoeudRecetteSort* getPere();
    NoeudRecetteSort* getFils(string attribut);
    string getValeurFils(string attribut);
    int getValeurFilsInt(string attribut);
    bool getValeurFilsBool(string attribut);
    vector<NoeudRecetteSort*>const& getListFils();
    void addFils(NoeudRecetteSort* n);
private:
    vector<NoeudRecetteSort*> fils;
    NoeudRecetteSort* pere;
    string attribut;
    string valeur;
};

#endif // NOEUDRECETTESORT_H
