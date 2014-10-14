/* Class implementation for the robots that deliver items in program 5
Author: Alexi Kessler */
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
int Robot::getNumStore(){
  return numStore;
}
void Robot::setNumStore(int store){
  numStore = store;
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
void Robot::addDest(tilePtr newTile)
{
	if (Dests==NULL)
	{
		Dests = newTile;
		//Don't forget to remove
		cout<< "dests is null" <<endl;
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
void Robot::removeDest()
{
	if (Dests==NULL) //Shouldn't ever happen
	{
		cout<<"Dests is empty, impossible to remove destination!\n";
	} 
	else 
	{
		tilePtr curr = NULL;
		tilePtr temp = NULL;
		temp = Dests;
		curr = Dests->getNextTile();
		delete(temp);
	}
}
void Robot::incrementRobot() //meant to move robot one step closer to destination
{
	
}
//Print Functions
void Robot::printRobot()
{
	cout<<"Printing data for Robot"<<ID<<endl;
	cout<<"Position: Row: "<<r<<" Col: "<<c<<" Floor: "<<f<<endl;
	cout<<"Number of Destinations: "<<numStore<<endl;
	printDests();
}
void Robot::printDests(){
  if(Dests==NULL){
    cout<< "NULL" << endl;
  }
  else{
    tilePtr curr = NULL;
    tilePtr prev = NULL;
    curr = Dests;
    while (curr!=NULL)
      {
	curr->printTile();
	prev = curr;
	//curr->printTile();
	curr = curr->getNextTile();
      }
    cout<< "\nEnd of Destination List" <<endl<<endl<<endl;

  }
}
#endif
