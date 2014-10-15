/* class definition for local item, which is to be used to represent the local item stock of a store in program 5
Author:Alexi Kessler */
#ifndef LOCALITEM_H
#define LOCALITEM_H

#include <string>
#include "globals.h"


class LocalItem{
	public:
		LocalItem();
		LocalItem(std::string newName);
		LocalItem(std::string newName, int count);
		
		int id_compare(LocalItem *newNode);

		std::string getName();
		void setName(std::string);
		int getCount();
		void setCount(int);
		LocalItem *getNext();
		void setNext(LocalItem *);
		void printLocalItem();
		
	private:
		std::string name;
		int localCount;
		LocalItem *nextItem;
};

typedef LocalItem *LocalItemPtr; 

#endif
