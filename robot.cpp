/* Class implementation for the robots that deliver items in program 5
Author of functions: Alexi Kessler unless stated otherwise*/
#ifndef ROBOT_CPP
#define ROBOT_CPP

#include <cstddef>
#include "robot.h"
#include "tile.h"
#include "localItem.h"
#include "externals.h"
#include "globalItem.h"

#define DELIVER 0
#define DEBUGDELIVER 0 

#include <iostream>
using namespace std;



//Constructors
Robot::Robot()
{
	//cout<<"Running Robot Constructor\n";
	ID = 0;
	r = 8;
	c = 16;
	f = 0;
	numStore = 0;
	Dests=NULL;
}

Robot::Robot(int id)
{
	ID = id;
	r = 8;
	c = 16;
	f = 0;
	numStore = 0;
	Dests=NULL;
}

Robot::Robot(int id, int stores)
{
	ID = id;
	numStore = stores;
	r = 8;
	c = 16;
	f =  0;
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

bool Robot::checkDestsEmpty()
{
	return (Dests==NULL);
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

		  StorePtr tempStore = newStore(r, c, f, time, NULL);
		  GlobalItem *tempItem = new GlobalItem(itemToAdd->getName());
		  globalTree->addItem(tempItem, tempStore);

		cout<<"to store inventory\n"<<endl;
		Mall[r][c][f].printInventory();
	}
	Mall[r][c][f].addToInventory(itemToAdd);  //Add to local inventory
	if (DEBUGDELIVER)
	{
		cout<<"\nAdded item to store inventory"<<endl;
		//printing Mall Store inventory after addition"<<endl;
		//Mall[r][c][f].printInventory();
	}
	return time;
}
int Robot::deliverItems(int startTime) //Alexi
{
	int totalTime = 0;
	int singleTime = 0;
	int counter = 0;
	int numItems;
	numItems = Dests->sizeInventory();
	if (DELIVER)
		{
		//printDests();
		cout<<"numItems: "<<numItems<<endl;
		}
	tilePtr dest = getDests();
	LocalItemPtr invPtr = dest->getInventory();
	cout<<"Robot "<<ID<<" delivers the following items to store ( "<<dest->getRow()<<" ,"<<dest->getCol()<<" ) at time "<<startTime<<endl;
	dest->printInventory();
	for (counter = 0; counter<numItems; counter++)
	{
		
		singleTime = deliverItem();
		if (DELIVER) 
			cout<<"Amount of time taken to deliver individual item: "<<singleTime<<endl;
		Dests->removeInventoryItem();
		totalTime+=singleTime;
		if (DELIVER) 
			cout<<"Total time after delivery of item: "<<totalTime<<endl;
	}
	if (DELIVER)
		cout<<"Deliver Items exiting normally"<<endl;
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
	cout<<"Inventory of Dest:"<<endl;
	curr->printInventory();
	prev = curr;
	curr = curr->getNextTile();
      }
    cout<< "\nEnd of Destination List" <<endl<<endl<<endl;

  }
}
#endif
