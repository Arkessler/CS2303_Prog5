/* Implementation of tile functions
Author: Alexi Kessler */
#ifndef TILE_CPP
#define TILE_CPP

#include "globals.h"
#include "tile.h"
#include <iostream>
using namespace std;

//Constructor

Tile::Tile()
{
	type = step = r = c = f = 0;
	nextTile=NULL;
}

Tile::Tile(int t, int s, int row, int col, int floor)
{
	type = t;
	step = s;
	r = row;
	c = col;
	f = floor;
	nextTile=NULL;
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

void Tile::setNextTile(Tile *newTilePtr)
{
	nextTile = newTilePtr;
}

Tile * Tile::getNextTile()
{
	return nextTile;
}
void Tile::printTile()
{
	cout<<"\nPrinting Tile\n";
	cout<<"---------------\n";
	cout<<"Tile type: "<<type<<endl;
	cout<<"Tile step: "<<step<<endl;
	cout<<"Tile position: Row: "<<r<<" Col: "<<c<<" Floor: "<<f<<endl;
	/*
	if (nextTile==NULL)
	{
		cout<<"Not connected to any other tile\n";
	}
	else 
	{
		cout <<"There is a tile after this one\n";
	} */
}

#endif
