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
