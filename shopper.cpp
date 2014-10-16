/* Class implementation for the shoppers that purchase items in program 5
Author: Alexi Kessler */
#ifndef SHOPPER_CPP
#define SHOPPER_CPP

#include <cstddef>
#include "robot.h"
#include "tile.h"
#include "shopper.h"
#include "globals.h"
#include "globalItem.h"
#include "localItem.h"
#include "binTree.h"
#include "externals.h"

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
Tile *Shopper::getDest()
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

//Written by Max

void Shopper::shopperApp(){

  //return NULL;  

  LocalItem *listInv = Dests->getInventory();
  LocalItem *curr = listInv;
  LocalItem *prev = NULL;
  //LocalItem *newList = new LocalItem();

  if(listInv == NULL){
    cout << "Calling shopperApp with no items"<<endl;
  }

  else{
    while(curr != NULL){
      GlobalItem *search = globalTree->getRoot()->findItem(curr);
      if(search != NULL && (*(search->getStores())->iCount) > (curr->getCount())){
	LocalItem *itemAdd = new LocalItem(curr->getName(), search->getStores()->iCount);
	Tile *storeTile =Mall[search->getStores()->x][search->getStores()->y][search->getStores()->z];
	Tile *tileAdd = new Tile(storeTile->getType(), storeTile->getStep(), storeTile->getRow(), storeTile->getCol(), storeTile->getFloor());
	tileAdd->addToInventory(itemAdd);
	addDest(tileAdd);
      }
      prev = curr;
      curr = curr->getNext();
    }
  }


  
  /*
int numItems;
  if(itemList == NULL){
    cout << "invalid input to shopperApp"<<endl;
    return NULL;
  }
  else{
    LocalItemPtr curr = itemList;
    //LocalItemPtr prev = NULL;
    while(curr != NULL){
      numItems++;
      curr = curr->getNext();
    }

    //For each item to look, traverse the global item tree and find a store
    //for(int i = 0; i < numItems; i++){

    Tile *locations = new Tile();

      if(itemTree->findItem(itemList)){
	storePtr curStore = itemTree->findItem(itemList)->getStores();
	
	if(curStore != NULL && curStore->numItems >= itemList->getCount()){
	  locations->setPosition(curStore->x, curStore->y, curStore->z);
	  locations->addToInventory(itemList);
	}//end storeItems > item count

      }//end in tree
      //Advance item in that list.
      itemList = itemList->getNext();
      return locations;



    //}//end for each

  } //end while

  */
}

#endif
