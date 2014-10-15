/* Class implementation for the robots that deliver items in program 5
Author: Alexi Kessler */
#ifndef ROBOT_CPP
#define ROBOT_CPP

#include <cstddef>
#include "robot.h"
#include "tile.h"
#include "localItem.h"
#include "externals.h"
#define DELIVER 1

#include <iostream>
using namespace std;

int DEBUGDELIVER =1;

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

Robot::Robot(int id, int stores, int row, int col, int floor)
{
	ID = id;
	numStore = stores;
	r = row;
	c = col;
	f = floor;
	Dests=NULL;
}

Robot::Robot(int id, int stores, int row, int col, int floor, tilePtr dest)
{
	ID = id;
	numStore = stores;
	r = row;
	c = col;
	f = floor;
	Dests=dest;
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
Tile *Robot::getTile(int spot) //Alexi
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
Tile *Robot::getDests() //Alexi
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
void Robot::addDest(tilePtr newTile) //Alexi
{
	if (Dests==NULL)
	{
		Dests = newTile;
		//Don't forget to remove
		cout<< "dests is null, adding as first dest" <<endl;
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
void Robot::removeDest() //Alexi
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
		Dests = curr;
		delete(temp);
	}
}
int Robot::deliverItem() //Alexi 
{
	//add to global
	int r, c, f, time;
	r = Dests->getRow();
	c = Dests->getCol();
	f = Dests->getFloor();
	LocalItemPtr itemToAdd = Dests->getInventory();

	time = itemToAdd->getCount();
	if (DEBUGDELIVER){
		cout<<"\nAdding item: "<<endl;
		itemToAdd->printLocalItem();
		cout<<"to store inventory\n"<<endl;
		Mall[r][c][f].printInventory();
	}
	Mall[r][c][f].addToInventory(itemToAdd);  //Add to local inventory
	if (DEBUGDELIVER)
		cout<<"\nAdded item to store inventory, printing Mall Store inventory after addition"<<endl;
		Mall[r][c][f].printInventory();

	return time;
}
int Robot::deliverItems(int startTime) //Alexi
{
	int totalTime;
	int singleTime;
	tilePtr dest = getDests();
	LocalItemPtr invPtr = dest->getInventory();
	LocalItemPtr curr;
	LocalItemPtr prev;
	curr = invPtr;
	while (curr!= NULL)
	{
	  if(DELIVER) cout<< "in while for deliver items" <<endl;
		curr = curr->getNext();
		singleTime = deliverItem();
		totalTime+=singleTime;
	}
	//CREATE EVENT
	return (totalTime+startTime);
}

//Print Functions
void Robot::printRobot() //Alexi
{
	cout<<"Printing data for Robot"<<ID<<endl;
	cout<<"Position: Row: "<<r<<" Col: "<<c<<" Floor: "<<f<<endl;
	cout<<"Number of Destinations: "<<numStore<<endl;
	printDests();
}
void Robot::printDests(){ //Alexi
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
