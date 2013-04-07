#ifndef Position_h
#define Position_h

#include "Position.h"
#include <map>
#include <iostream>
#include <cmath>

using namespace std;


class Position
{

public:

	static Position* fabriquePosition(int x, int y);
	static int codePosition(int x, int y);
	int getX() const;
	int getY() const;
	bool operator==(Position const& a) const;
	static int distance(Position const& a, Position const& b);

private:

	Position(int x, int y);

private:
	int x;
	int y;
	static map<int, Position*> listePosition;

};

ostream& operator<<( ostream &flux, Position const& pos);
#endif // Position_h
