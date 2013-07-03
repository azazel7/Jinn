#include <iostream>
#include "Position.h"
#include "Case.h"
#include "Position.h"
#include "UsineSort.h"
#include "Partie.h"
#include "Joueur.h"
#include "reseau/ReceptionServeur.h"
#include "sort/Sort.h"
#include <signal.h>

using namespace std;

ReceptionServeur *serveur = NULL;
void traitement_sigint(int sig)
{
    cout << "Reception du signal " << sig << endl;
    if(sig == SIGINT)
    {
        if(serveur != NULL)
        {
            serveur->finirServeur();
            serveur->fermerServeur();
            delete serveur;
            serveur = NULL;
            GestionnaireLogger::viderRegistre();
            Position::libererPositions();

            exit(0);
        }
    }
}
int main()
{
    signal(SIGINT, &traitement_sigint);
    Logger *logger = new LoggerFileDescriptor(1, false);
    GestionnaireLogger::ajouterRegistre(logger);
    Partie *p = new Partie("p1", 2, 2);
    p->initialiser();
    serveur = new ReceptionServeur(p);
    serveur->initialiserServeur();
    serveur->miseEnEcoute();
    serveur->fermerServeur();
    delete serveur;
    serveur = NULL;
    GestionnaireLogger::viderRegistre();
    Position::libererPositions();
    return 0;

    /*
    Partie partie("Partie 1", 2, 2);
    Joueur *j1 = NULL, *j2 = NULL;
    Plateau *pl = NULL;
    Action *action = new Action();
    Sort *sort = NULL;
    vector<string> listeSort;
    listeSort.push_back("Boule de Feu");
    listeSort.push_back("Sceau de Controle");
    partie.initialiser();
    j1 =  partie.ajouterJoueur("Tarte", "pika", listeSort);
    j2 =  partie.ajouterJoueur("Platon", "Sala", listeSort);
    partie.demarrerPartie();
    pl = partie.getPlateau();
    sort = UsineSort::fabriqueSort("Boule de Feu");
    sort->setProprietaire(j2);
    action->setOrigine(NULL);
    action->setSort(sort);
    action->ajouterCible(pl->getCase(0,0));
        j2->diminuerMana(105);
        cout << "Fin loop" << endl;
        cout << j2->getManaActuel() << endl;

                partie.effectuerAction(action, j2);
                partie.effectuerAction(action, j2);
                partie.effectuerAction(action, j2);
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

