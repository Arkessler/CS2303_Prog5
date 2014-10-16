#ifndef BINTREE_H
#define BINTREE_H
#include "globals.h"
#include "globalItem.h"

class Tree{
	private:
		GlobalItemPtr root;
	public:
		Tree();
		bool isEmpty();
		bool addItem(GlobalItemPtr newItem, StorePtr newStore);
		void PrintItem(GlobalItemPtr item);
		void PrintTree();
		GlobalItemPtr getRoot();
	private:
		void PrintAll(GlobalItemPtr item);
		int test;
};

#endif
