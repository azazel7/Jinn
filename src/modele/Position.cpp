/*
 * Position.cpp
 *
 *  Created on: 31 mars 2013
 *      Author: magoa
 */

#include "Position.h"
#include <iostream>

using namespace std;

Position::Position(int x, int y)
{
	this->x = x;
	this->y = y;
}
map<int, Position*> Position::listePosition;

Position* Position::fabriquePosition(int x, int y)
{
	int code = codePosition(x, y);
	if(listePosition[code] == NULL)
	{
		listePosition[code] = new Position(x, y);
	}
	return listePosition[code];
}

int Position::codePosition(int x, int y)
{
	int xx = x * 2;
	if (x < 0)
	{
		xx = -x * 2 + 1;
	}
	int yy = y * 2;
	if (y < 0)
	{
		yy = -y * 2 + 1;
	}
	return (xx + yy) * (xx + yy + 1) / 2 + yy;
}

int Position::getX() const
{
	return x;
}

int Position::getY() const
{
	return y;
}

bool Position::operator==(Position const& a) const
{
	if(a.getX() == x && a.getY() == y)
	{
		return true;
	}
	return false;
}

int Position::distance(Position const& a, Position const& b)
{

	return a.getX() - b.getY()
}
