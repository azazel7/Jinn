#include "test.h"

bool testAjoutSort()
{
        Joueur* joueur = new Joueur();
        Sort* testDuree = UsineSort::fabriqueSort("Sort Test Duree");
        testDuree->setProprietaire(joueur);
        Case square(0, 0, 0, 0, 0, 0, 0, Position::fabriquePosition(0, 0));
        testDuree->appliquerSortSurCase(square);
        if(square.nombreDeSortEnCour() != 1)
        {
                return false;
        }
        square.retirerSortEcoule();
        if(square.nombreDeSortEnCour() != 1)
        {
                return false;
        }
        square.retirerSortEcoule();
        if(square.nombreDeSortEnCour() != 1)
        {
                return false;
        }
        square.retirerSortEcoule();
        if(square.nombreDeSortEnCour() != 1)
        {
                return false;
        }
        square.retirerSortEcoule();
        if(square.nombreDeSortEnCour() != 0)
        {
                return false;
        }
        return true;
}
