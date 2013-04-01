#ifndef Position_h
#define Position_h

#include "Position.h"
#include <map>

using namespace std;

class Position
{

public:

	static Position* fabriquePosition(int x, int y);
	static int codePosition(int x, int y);
	int getX() const;
	int getY() const;

private:

	Position(int x, int y);

private:
	int x;
	int y;
	static map<int, Position*> listePosition;

};

#endif // Position_h
