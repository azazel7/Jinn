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
    cout << *Position::fabriquePosition(0,0) << endl;
    Partie partie("Partie 1", 2);
    Joueur j1, j2;
    Plateau *pl;
    Action action;
    partie.initialiser();
    cout << "narval" << endl;
    partie.nouveauJoueur(j1);
    cout << "narval 1" << endl;
    partie.nouveauJoueur(j2);
    cout << j1 << endl;
    cout << j2 << endl;
    pl = partie.getPlateau();
    cout <<  *pl->getCase(0, 0) << endl;
    cout <<  *pl->getCase(1, 1) << endl;
    cout << "pl " << pl << endl; action = j1.effectuerAction(partie);
    cout << action.getSort()->getNom() << endl;
    cout << action.getSort()->getProprietaire()->getNom() << endl;
    cout << action.getCible()[1] << " " << pl->getCase(1, 1) << endl;
    pl->appliquerAction(action);
    cout <<  *pl->getCase(0, 0) << endl;
    cout <<  *pl->getCase(1, 1) << endl;//FIXME Le nouveau propri n'est pas correctement mis à jour
	return 0;
}
