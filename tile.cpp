/* Implementation of tile functions
Author of functions: Alexi Kessler unless stated otherwise */
#ifndef TILE_CPP
#define TILE_CPP

#include "globals.h"
#include "tile.h"
#include <iostream>

#define DEBUGTILE 0

using namespace std;

//Constructor

Tile::Tile()
{
	type = step = r = c = f = 0;
	nextTile=NULL;
	inventory = NULL;
}

Tile::Tile(int t, int s, int row, int col, int floor)
{
	type = t;
	step = s;
	r = row;
	c = col;
	f = floor;
	nextTile=NULL;
	inventory = NULL;
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

void Tile::setRow(int row)
{
	r = row;
}

void Tile::setCol(int col)
{
	c = col;
}

void Tile::setFloor(int floor)
{
	f = floor;
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

LocalItemPtr Tile::getInventory(){ //Max
  return inventory;
}

void Tile::setInventory(LocalItemPtr newInventory){ //Max
  inventory = newInventory;
}

int Tile::sizeInventory()
{
	LocalItemPtr curr = NULL;
	LocalItemPtr prev = NULL;
	curr = inventory;
	int count = 0;
	if (curr == NULL)
	{
		return 0;
	} else {
		while (curr!=NULL)
		{
			prev = curr;
			curr = curr->getNext();
			count++;
		}
		return count;
	}
}
void Tile::addToInventory(LocalItemPtr toAdd){ //Max
  //If inventory is null, set inventory to toAdd.
	
	if(DEBUGTILE)cout<<"Currently running addToInventory"<<endl;

	if(getInventory() == NULL) //Inventory empty
	{
		if(DEBUGTILE) cout<<"Inventory empty, adding item"<<endl;
		inventory = toAdd;
		toAdd = toAdd->getNext();
		//inventory->setNext(NULL);
	return;
	}

  else{
    if(DEBUGTILE) cout<<"else"<<endl;
    LocalItemPtr curr = NULL;
    LocalItemPtr prev = NULL;
    curr = inventory;
    
    //if(DEBUGTILE) cout<<"after init"<<endl;

	if(curr->getNext() == NULL){
      //cout<<"HERE, getNext null"<<endl;
      inventory->setNext(toAdd);
    }
    else{
      //cout<<(toAdd->getName())<<" vs ";
      //cout<<(curr == NULL)<<endl;
      //Currently adding to end of list, unsorted.  Can sort using id_compare(newItem)=> returns 0 if same, 1 if new is lower in 
      while (curr != NULL && curr->id_compare(toAdd) != 0 && curr->getNext() != NULL){
	prev = curr;
	//if(DEBUGTILE) cout<<"before getNext"<<endl;
	curr = curr->getNext();
	//if(DEBUGTILE) cout<<"end of while"<<endl;
      }
      
      if(DEBUGTILE) cout<<"after while addToInventory"<<endl;
      
      if(curr == NULL){
	if(DEBUGTILE) cout << "prev->setNext(toAdd)"<<endl;
	prev->setNext(toAdd);
	//toAdd->setNext(inventory);
      //setInventory(toAdd);
      }
      else if(curr->getNext() == NULL){
	if(DEBUGTILE)cout<< "curr->getNext() == NULL"<<endl;
	curr->setNext(toAdd);
      }
      else{
	if(DEBUGTILE) cout<< "curr->id_compare != 0"<<endl;
	curr->setCount(curr->getCount() + toAdd->getCount());
      }
    }
  }
}

void Tile::removeInventoryItem() //Alexi
{
	if(!inventory)
	{
		cout<<"The inventory is empty, can't remove anything!"<<endl;
	}
	else 
	{
	  cout<<"removing item"<<endl;
		LocalItemPtr curr = NULL;
		LocalItemPtr prev = NULL;
		curr = inventory;
		prev = curr;
		curr = curr->getNext();
		inventory = curr;
		prev -> setNext(NULL);
	}
}

void Tile::printInventory() //Alexi
{
	if (inventory==NULL){
		cout<<"Can't print Inventory, it is empty"<<endl;
	} else {
		LocalItemPtr curr = NULL;
		curr = inventory;
		if(curr->getNext() == NULL){
		  curr->printLocalItem();
		}
		else{
		  while (curr != NULL)
		    {
		      curr->printLocalItem();
		      curr = curr->getNext();
		    }
		}
		cout<<"End of inventory list\n"<<endl;
	}
}
#endif
