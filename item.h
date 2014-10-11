//This part was a joint effort.
#ifndef ITEM_H
#define ITEM_H
#include "global.h"

class Item{
  friend void addStore(StorePtr *sPtr, StorePtr newStore);
	public:
		Item();
		Item(string newName);
		int id_compare(Item *newNode);

		string getName();
		void setName(string);
		Item *getLeft();
		Item *getRight();
		void setLeft(Item *);
		void setRight(Item *);
		StorePtr *getStores();
		void setStores(StorePtr *);
		void printItem();
		
	private:
		string name;
		StorePtr *stores;
		Item *left;
		Item *right;
};

typedef Item *ItemPtr; 

#endif
