/* Class implementation for the shoppers that purchase items in program 5
Author: Alexi Kessler */
#ifndef ROBOT_CPP
#define ROBOT_CPP

#include <cstddef>
#include "robot.h"
#include "tile.h"
#include <iostream>
using namespace std;
//Constructors
Shopper::Shopper()
{
	cout<<"Running Shopper Constructor\n";
	ID = r = c = f = numStore = 0;
	Dests=NULL;
}

Shopper::Shopper(int id)
{
	ID = id;
	r = c = f = numStore = 0;
	Dests=NULL;
}

Shopper::Shopper(int id, int stores)
{
	ID = id;
	numStore = stores;
	r = c = f =  0;
	Dests=NULL;
}

//Basic int getters and setters
int Shopper::getID()
{
	return ID;
}
void Shopper::setID(int id)
{
	ID = id;
}
int Shopper::getR()
{
	return r;
}
void Shopper::setR(int row)
{
	r = row;
}
int Shopper::getC()
{
	return c;
}
void Shopper::setC(int col)
{
	c = col;
}
int Shopper::getF()
{
	return f;
}
void Shopper::setF(int floor)
{
	f = floor;
}
//Tile getters and setter
Tile *Shopper::getDest(int spot)
{
	//return (*Dests).traverse(spot);
	if ((Dests)==NULL)
	{
		return NULL;
	}
	else 
	{
		return Dests;
	}
}
void Shopper::addDest(tilePtr newTile)
{
	if (Dests==NULL)
	{
		Dests = newTile;
	}
	else
	{
		tilePtr curr = NULL;
		tilePtr prev = NULL;
		curr = Dests;
		while (curr!=NULL)
		{
			prev = curr;
			curr = curr->getNextTile();
		}
		prev->setNextTile(newTile);
	}
}
#endif
