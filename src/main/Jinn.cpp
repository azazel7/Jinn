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

using namespace std;

int main()
{
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
    Position *a, *b;
    a = Position::fabriquePosition(0,0);
    b = Position::fabriquePosition(2,2);
    cout << Position::distance(*a, *b) << endl;

    Sort* c = UsineSort::fabriqueSort("Sceau de Controle");
    cout << c->description() << endl;
    cout << c->getNom() << endl;
	return 0;
}
