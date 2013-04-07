#include "test.h"
#include "Position.h"

bool testFabriqueIdentique()
{
    Position *a, *b;
    a = Position::fabriquePosition(0, 0);
    b = Position::fabriquePosition(0, 0);
    return a == b;
}

bool testFabriqueDifferente()
{
    Position *a, *b;
    a = Position::fabriquePosition(0, 0);
    b = Position::fabriquePosition(0, 1);
    return a != b;
}

bool testDistance()
{
    Position *a, *b;
    a = Position::fabriquePosition(0, 0);
    b = Position::fabriquePosition(0, 10);
    return 10 == Position::distance(*a, *b);
}

bool testDistance2()
{
    Position *a, *b;
    a = Position::fabriquePosition(0, 0);
    b = Position::fabriquePosition(7, 0);
    return 7 == Position::distance(*a, *b);
}

bool testOperatorEgalite()
{
    Position &a = *Position::fabriquePosition(0, 0);
    Position &b = *Position::fabriquePosition(0, 0);
    return a == b;
}
