#include "test.h"

bool testAjoutSort()
{
        Joueur* joueur = new Joueur();
        Sort* testDuree = new SortTestDuree();
        testDuree->setProprietaire(joueur);
        Case square(0, 0, 0, 0, 0, 0, 0, Position::fabriquePosition(0, 0));
        testDuree->appliquerSortSurCase(square);
        assert(square.nombreDeSortEnCour() == 1);
        square.retirerSortEcoule();
        assert(square.nombreDeSortEnCour() == 1);
        square.retirerSortEcoule();
        assert(square.nombreDeSortEnCour() == 1);
        square.retirerSortEcoule();
        assert(square.nombreDeSortEnCour() == 0);
        return true;
}

void testRetirerJoueur()
{
        Joueur* joueur = new Joueur();
        Sort* testDuree = new SortTestDuree();
        testDuree->setProprietaire(joueur);
        Case square(0, 0, 0, 0, 0, 0, 0, Position::fabriquePosition(0, 0));
        testDuree->appliquerSortSurCase(square);
        square.setProprietaire(joueur);
        assert(square.getProprietaire() == joueur);
        assert(square.nombreDeSortEnCour() == 1);
        square.retirerJoueur(joueur);
        assert(square.getProprietaire() == NULL);
        assert(square.nombreDeSortEnCour() == 0);
}

void testRetirerSort()
{
        Joueur* joueur = new Joueur();
        Sort* testDuree = new SortTestDuree();
        testDuree->setProprietaire(joueur);
        Case square(0, 0, 0, 0, 0, 0, 0, Position::fabriquePosition(0, 0));
        testDuree->appliquerSortSurCase(square);
        testDuree->appliquerSortSurCase(square);
        assert(square.nombreDeSortEnCour() == 2);
        testDuree->appliquerSortSurCase(square);
        assert(square.nombreDeSortEnCour() == 3);
        square.retirerSort(1);
        assert(square.nombreDeSortEnCour() == 2);
        square.retirerSort(1);
        assert(square.nombreDeSortEnCour() == 1);
        square.retirerSort(0);
        assert(square.nombreDeSortEnCour() == 0);
}

void testDefense()
{
        Case square(10, 0, 0, 0, 0, 0, 0, Position::fabriquePosition(0, 0));
        assert(square.getDefenseActuelle() == 10);
        assert(square.getDefenseReel() == 10);
        square.modifierDefense(1);
        assert(square.getDefenseActuelle() == 10);
        assert(square.getDefenseReel() == 10);
        square.modifierDefense(-1);
        assert(square.getDefenseReel() == 10);
        assert(square.getDefenseActuelle() == 9);
        square.modifierDefenseReel(1);
        assert(square.getDefenseReel() == 11);
        assert(square.getDefenseActuelle() == 9);
        square.modifierDefenseReel(-10);
        assert(square.getDefenseReel() == 1);
        assert(square.getDefenseActuelle() == 1);
        square.modifierDefenseReel(-6);
        assert(square.getDefenseReel() == 0);
        assert(square.getDefenseActuelle() == 0);
        square.modifierDefenseReel(3);
        assert(square.getDefenseReel() == 0);
        assert(square.getDefenseActuelle() == 0);
        square.modifierDefenseReel(4);
        assert(square.getDefenseReel() == 2);
        assert(square.getDefenseActuelle() == 0);
}
