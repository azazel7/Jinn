#include "sort/Sort.h"
#include "NoeudRecetteSort.h"
#include "RecetteSort.h"
#include <fstream>

RecetteSort::RecetteSort()
{
    this->racine = NULL;
}

RecetteSort::RecetteSort(const string &nomFichier)
{
    this->nomFichier = nomFichier;
    this->racine = NULL;
}

Sort* RecetteSort::creerSort()
{
    //name, mana, type, elite, reach, counttarget
    string name = racine->getValeurFils("name");
    string description = racine->getValeurFils("description");
    int mana = racine->getValeurFilsInt("mana");
    int reach = racine->getValeurFilsInt("reach");
    int counttarget = racine->getValeurFilsInt("counttarget");
    int reussite = racine->getValeurFilsInt("successRate");
    bool elite = racine->getValeurFilsBool("elite");
    Sort* retour = new Sort(name, mana, elite, reach, reussite,counttarget, 0, 0, 1, 0, 0, FEU);
    retour->setDescription(description);
    vector<NoeudRecetteSort*> const& fils = racine->getListFils();
    for(NoeudRecetteSort* enfant : fils)
    {
        if(enfant->getAttribut() == APPLICATION_CHAINE)
        {
            if(SortAppliquerSurCaseFactory::getListe().count(enfant->getValeur()) == 1)
            {
                SortAppliquerSurCase* s = SortAppliquerSurCaseFactory::getListe()[enfant->getValeur()]->getNewInstance(enfant);
                retour->ajouterApplication(s);
            }
        }
        else if(enfant->getAttribut() == CHRONIQUE_CHAINE)
        {
            SortActionChronique* s = NULL;
            retour->ajouterActionChronique(s);
        }
    }
    return retour;
}

bool RecetteSort::chargerRecette()
{
    ifstream fichier(nomFichier, ios::in);

    string line;

    while(getline(fichier, line))
    {
        for(int i = 0; i < line.length(); i++)
        {
            //Si rien, on empile sur le nom de l'attribu
            //Dès que l'on a un '=' on empile sur la valeur
            //TODO accolade
            //
        }
    }
    fichier.close();
    return false;
}

void RecetteSort::setNomFichier(string const n)
{
    nomFichier = n;
}

string RecetteSort::getNomSort()
{
    NoeudRecetteSort* tmp = racine->getFils("name");
    if(tmp == NULL)
    {
        return "";
    }
    return tmp->getValeur();
}

void RecetteSort::setRacine(NoeudRecetteSort* n)
{
    racine = n;
}
