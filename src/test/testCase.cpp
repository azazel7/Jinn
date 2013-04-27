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
