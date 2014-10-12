#ifndef ROBOT_CPP
#define ROBOT_CPP

#include <cstddef>
#include "robot.h"
#include "tile.h"
#include <iostream>
using namespace std;
//Constructors
Robot::Robot()
{
	cout<<"Running Robot Constructor\n";
	ID = r = c = f = numStore = 0;
	Dests=NULL;
}

Robot::Robot(int id)
{
	ID = id;
	r = c = f = numStore = 0;
	Dests=NULL;
}

Robot::Robot(int id, int stores)
{
	ID = id;
	numStore = stores;
	r = c = f =  0;
	Dests=NULL;
}

//Basic int getters and setters
int Robot::getID()
{
	return ID;
}
void Robot::setID(int id)
{
	ID = id;
}
int Robot::getR()
{
	return r;
}
void Robot::setR(int row)
{
	r = row;
}
int Robot::getC()
{
	return c;
}
void Robot::setC(int col)
{
	c = col;
}
int Robot::getF()
{
	return f;
}
void Robot::setF(int floor)
{
	f = floor;
}
//Tile getters and setter
Tile *Robot::getTile(int spot)
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
Tile Robot::addTile(Tile newTile)
{
	//Dests.add(newTile);
	*Dests = newTile;
}
#endif
