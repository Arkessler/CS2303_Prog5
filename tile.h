/* A tile class to hold individual nodes of the Mall, be they path or store
Author: Alexi Kessler */
#ifndef TILE_H
#define TILE_H
#include "localItem.h"

class Tile
{
	public:
		Tile();
		Tile(int t, int s, int row, int col, int floor);
		
		void setType(int);
		int getType();
		void setStep(int);
		int getStep();
		void setPosition(int, int, int);
		int getRow();
		int getCol();
		int getFloor();
		
		void addToInventory(LocalItemPtr);
		void removeInventoryItem();
		LocalItemPtr getInventory();
		void setInventory(LocalItemPtr);
		
		void setNextTile(Tile *newTilePtr);
		Tile *getNextTile();
		void printInventory();
		void printTile();
	private:
		int type;
		int step;
		int r, c, f;
		Tile *nextTile;
		LocalItemPtr inventory;
		
};

typedef Tile *tilePtr;

#endif
