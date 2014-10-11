#ifndef BINTREE_H
#define BINTREE_H
#include "global.h"
#include "item.h"

class Tree{
	private:
		ItemPtr root;
	public:
		Tree();
		bool isEmpty();
		bool addItem(ItemPtr newItem, StorePtr newStore);
		void PrintItem(ItemPtr item);
		void PrintTree();
		ItemPtr getRoot();
	private:
		void PrintAll(ItemPtr item);
		int test;
};

#endif
