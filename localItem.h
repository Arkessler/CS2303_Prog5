//This part was a joint effort.
#ifndef ITEM_H
#define ITEM_H
#include "global.h"

class LocalItem{
  friend void addStore(StorePtr *sPtr, StorePtr newStore);
	public:
		LocalItem();
		LocalItem(string newName);
		int id_compare(LocalItem *newNode);

		string getName();
		void setName(string);
		LocalItem *getLeft();
		LocalItem *getRight();
		void setLeft(LocalItem *);
		void setRight(LocalItem *);
		StorePtr *getStores();
		void setStores(StorePtr *);
		void printLocalItem();
		
	private:
		string name;
		StorePtr *stores;
		LocalItem *left;
		LocalItem *right;
};

typedef LocalItem *LocalItemPtr; 

#endif
