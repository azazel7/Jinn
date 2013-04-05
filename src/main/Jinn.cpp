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

using namespace std;

int main()
{
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	std::vector<Case*> b;
	Action *a = new Action(NULL, NULL, b);
	delete a;
	cout << a << endl;
	delete a;
	cout << a << endl;
	cout << Position::fabriquePosition(4, 5) << endl;
	cout << Position::fabriquePosition(3, 5) << endl;
	cout << Position::fabriquePosition(4, 5) << endl;
	return 0;
}
