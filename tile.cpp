#ifndef TILE_CPP
#define TILE_CPP

#include "globals.h"
#include "tile.h"

//Constructor

Tile::Tile()
{
	type = step = r = c = f = 0;
}

void Tile::setType(int t)
{
	type = t;
}

int Tile::getType()
{
	return type;
}

void Tile::setStep(int s)
{
	step = s;
}

int Tile::getStep()
{
	return step;
}

void Tile::setPosition(int row, int col, int floor)
{
	r = row;
	c = col;
	f = floor;
}

int Tile::getRow()
{
	return r;
}

int Tile::getCol()
{
	return c;
}

int Tile::getFloor()
{
	return f;
}

#endif
