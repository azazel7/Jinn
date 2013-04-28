#include "test.h"
#include "assert.h"

int main()
{
    assert(testFabriqueIdentique());
    assert(testFabriqueDifferente());
    assert(testDistance());
    assert(testDistance2());
    assert(testOperatorEgalite());
    assert(testAjoutSort());
    testRetirerJoueur();
    testRetirerSort();
        testDefense();
}
