#include "test.h"

void testMortJoueur()
{
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
    j2->diminuerMana(j2->getManaActuel());
    assert(j2->getManaActuel() == 0);
    partie.effectuerAction(action, j2);
    assert(j2->estMort() == true);
    assert(j2->getManaMaximum() == 0);
    assert(pl->getCase(0,0)->getDefenseActuelle() == pl->getCase(0,0)->getDefenseInitiale());
    delete action;
    delete sort;
    //TODO tout n'est pas libéré
}
