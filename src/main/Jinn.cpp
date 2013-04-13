//============================================================================
// Name        : Jinn.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Position.h"
#include "Case.h"
#include "Position.h"
#include "UsineSort.h"
#include "Partie.h"
#include "Joueur.h"
using namespace std;

int main()
{
    list<string> tab;

    //Un tableau de mots
    tab.push_back("les"); //On ajoute deux mots dans le tableau
    tab.push_back("Zeros");
    tab.insert(tab.begin(), "Salut"); //On insère le mot "Salut" au

            //Affiche les mots donc la chaîne "Salut les Zeros"
    for(list<string>::iterator it=tab.begin(); it!=tab.end(); ++it)
    {
        cout << *it << " ";
        if((*it) == "les")
        {
            tab.erase(it);
        }
    }
    tab.erase(tab.begin()); //On supprime le premier mot
    cout << endl;
    //Affiche les mots donc la chaîne "les Zeros"
    for(list<string>::iterator it=tab.begin(); it!=tab.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
    return 0;

    Partie partie("Partie 1", 2, 2);
    Joueur j1, j2;
    Plateau *pl;
    Action action;
    partie.initialiser();
    partie.nouveauJoueur(j1);
    partie.nouveauJoueur(j2);
    cout << j1 << endl;
    cout << j2 << endl;

    partie.demarrerPartie();
    /*
    pl = partie.getPlateau();
    action = j1.effectuerAction(partie);
    pl->appliquerAction(action);
    cout <<  *pl->getCase(0, 0) << endl;
    cout <<  *pl->getCase(1, 1) << endl;

    action = j1.effectuerAction(partie);
    pl->appliquerAction(action);
    cout <<  *pl->getCase(0, 0) << endl;
    cout <<  *pl->getCase(1, 1) << endl;

    action = j1.effectuerAction(partie);
    pl->appliquerAction(action);
    cout <<  *pl->getCase(0, 0) << endl;
    cout <<  *pl->getCase(1, 1) << endl;*/
	return 0;
}
