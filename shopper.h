/* A class header for the shoppers that purchase items in program 5
Author: Alexi Kessler */
#ifndef SHOPPER_H
#define SHOPPER_H
#include "tile.h"

class Shopper
{
	public:
		Shopper();
		Shopper(int id);
		Shopper(int id, int stores);
		
		int getID();
		void setID(int);
		int getR();
		void setR(int);
		int getC();
		void setC(int);
		int getF();
		void setF(int);
		//Item list functions
		Tile *getDest(int);
		void addDest(tilePtr);

		//Takes simple list of items that were scanned in, adds store to dest.
		void shopperApp(LocalItemPtr);
	private:
		int ID;
		int r, c, f;
		int numStore;
		//Item list of some kind
		tilePtr Dests;
};

#endif
