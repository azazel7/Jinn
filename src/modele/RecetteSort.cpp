#include "sort/Sort.h"
#include "NoeudRecetteSort.h"
#include "RecetteSort.h"
#include <fstream>
#include <stack>
#include "Tools.h"

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
    cerr << nomFichier << endl;
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
            cout << "Attribut appli : " << enfant->getValeur() << endl;
            cout << "Taille :" << SortAppliquerSurCaseFactory::getListe().size() << endl;
            if(SortAppliquerSurCaseFactory::getListe().count(enfant->getValeur()) == 1)
            {
                cout << "Valide Attribut appli : " << enfant->getValeur() << endl;
                SortAppliquerSurCase* s = SortAppliquerSurCaseFactory::getListe()[enfant->getValeur()]->getNewInstance(enfant);
                retour->ajouterApplication(s);
            }
        }
        else if(enfant->getAttribut() == CHRONIQUE_CHAINE)
        {
            cout << "Attribut : " << enfant->getValeur() << endl;
            cout << "Taille :" << SortActionChroniqueFactory::getListe().size() << endl;
            if(SortActionChroniqueFactory::getListe().count(enfant->getValeur()) == 1)
            {
                cout << "Validé Attribut : " << enfant->getValeur() << endl;
                SortActionChronique* s = SortActionChroniqueFactory::getListe()[enfant->getValeur()]->getNewInstance(enfant);
                retour->ajouterActionChronique(s);
            }
        }
    }
    return retour;
}

bool RecetteSort::chargerRecette()
{
    ifstream fichier(nomFichier, ios::in);
    if( ! fichier.is_open())
    {
        return false;
    }
    string line;
    string attribut, valeur;
    string* currentBuffer = &attribut;
    NoeudRecetteSort* racine = new NoeudRecetteSort(NULL);
    NoeudRecetteSort* fils = NULL;
    stack<NoeudRecetteSort*> pile;
    while(getline(fichier, line))
    {
        for(int i = 0; i < line.length(); i++)
        {
            if(line[i] == '=')
            {
                currentBuffer = &valeur;
            }
            else if(line[i] == ',' || line[i] == '{' || (line[i] == '}' && ! pile.empty()))
            {
                if(! attribut.empty() && ! valeur.empty())
                {
                    fils = new NoeudRecetteSort(racine);
                    attribut = Tools::trim(attribut);
                    valeur = Tools::trim(valeur);
                    fils->setAttribut(attribut);
                    fils->setValeur(valeur);
                    racine->addFils(fils);
                    attribut.clear();
                    valeur.clear();
                    //Ajouter le nouveau noeud
                    currentBuffer = &attribut;
                }
            }
            else
            {
                currentBuffer->push_back(line[i]);
            }
            if(line[i] == '{')
            {
                pile.push(racine);
                racine = fils;
            }
            if(line[i] == '}' && ! pile.empty())
            {
                fils = racine;
                racine = pile.top();
                pile.pop();
            }
        }
    }
    this->racine = racine;
    fichier.close();
    if(racine->getListFils().size() == 0)
    {
        delete racine;
        return false;
    }
    return true;
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


void RecetteSort::printArbreRecette()
{
    printArbreRecetteRecursive(racine, "");
}

void RecetteSort::printArbreRecetteRecursive(NoeudRecetteSort* n, string s)
{
    cout << s << n->getAttribut() << " = " << n->getValeur() << endl;
    for(NoeudRecetteSort* enfant : n->getListFils())
    {
        if(enfant->getListFils().size() == 0)
        {
            cout << s << "\t" << enfant->getAttribut() << " = " << enfant->getValeur() << endl;
        }
        else
        {
            printArbreRecetteRecursive(enfant, s + "\t");
        }
    }
}
