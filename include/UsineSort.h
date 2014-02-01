#ifndef UsineSort_h
#define UsineSort_h

#include "sort/Sort.h"
#include <dirent.h>
#include <map>

class Sort;
class RecetteSort;
/**
 * @brief Classe UsineSort
 */
class UsineSort
{

public:
    /**
     * @brief fabriqueSort
     *  Permet de créer un sort via son nom
     * @param nom nom du sort à créer
     * @return Un pointeur vers le sort créé
     */
    static Sort* fabriqueSort(string nom);
    /**
     * @brief fabriqueSort
     *  Permet de dupliquer un sort à partir d'un autre
     * @param sortModele Le sort initial
     * @return Un pointeur vers un sort qui est la copie de celui passé en argument
     */
    static Sort* fabriqueSort(Sort* sortModele);
    /**
     * @brief liste
     *  Liste les sorts que la classe peut générer
     * @return Un vector de string contenant les noms des sorts disponible
     */
    static vector<string> liste();

    static void chargerConfiguration(string nomDossier);

    static void libererConfiguration();

private:
    static map<string, RecetteSort> listeSort;
};
#endif // UsineSort
