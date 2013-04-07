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
    partie.nouveauJoueur(j1);
    partie.nouveauJoueur(j2);
    cout << j1.getNom() << endl;
    cout << j2.getNom() << endl;
    pl = partie.getPlateau();
    cout << "0;0 " << pl->getCase(0, 0)->getProprietaire() << endl;
    cout << "1;1 " << pl->getCase(1, 1)->getProprietaire() << endl;
    action = j1.effectuerAction(partie);
    cout << action.getSort()->getNom() << endl;
    cout << action.getSort()->getProprietaire()->getNom() << endl;
    cout << action.getCible()[1] << " " << pl->getCase(1, 1) << endl;
    pl->appliquerAction(action);
    cout << "0;0 " << pl->getCase(0, 0)->getProprietaire() << endl;
    cout << "1;1 " << pl->getCase(1, 1)->getProprietaire() << endl; //FIXME Le nouveau propri n'est pas correctement mis à jour
	return 0;
}
