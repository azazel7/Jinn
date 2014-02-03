#ifndef RECETTESORT_H
#define RECETTESORT_H

#define APPLICATION_CHAINE "application"
#define CHRONIQUE_CHAINE "chronique"

class NoeudRecetteSort;
class Sort;

class RecetteSort
{
public:
    RecetteSort();
    RecetteSort(string const& nomFichier);
    Sort* creerSort();
    bool chargerRecette();
    void setNomFichier(const string n);
    string getNomSort();
    void setRacine(NoeudRecetteSort* n);
    void printArbreRecette();
    void printArbreRecetteRecursive(NoeudRecetteSort* n, string s);
    RecetteSort& operator=(const RecetteSort& r);
    ~RecetteSort();
private:
    string nomFichier;
    NoeudRecetteSort* racine;

};

#endif // RECETTESORT_H