//This part was a joint effort.
#ifndef ITEM_H
#define ITEM_H
#include "globals.h"
class Tile;


class GlobalItem{
  friend void addStore(StorePtr *sPtr, StorePtr newStore);
	public:
		GlobalItem();
		GlobalItem(string newName);
		int id_compare(GlobalItem *newNode);

		string getName();
		void setName(string);
		GlobalItem *getLeft();
		GlobalItem *getRight();
		void setLeft(GlobalItem *);
		void setRight(GlobalItem *);
		StorePtr *getStores();
		void setStores(StorePtr *);
		void printGlobalItem();

		GlobalItem *findItem(LocalItem *);
		
	private:
		string name;
		StorePtr *stores;
		GlobalItem *left;
		GlobalItem *right;
};

typedef GlobalItem *GlobalItemPtr; 

#endif
