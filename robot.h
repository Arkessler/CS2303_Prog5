/* A class header for the robots that deliver items in program 5
Author: Alexi Kessler */
#ifndef ROBOT_H
#define ROBOT_H
#include "tile.h"

class Robot
{
	public:
		Robot();
		Robot(int id);
		Robot(int id, int stores);
		
		int getID();
		void setID(int);
		int getR();
		void setR(int);
		int getC();
		void setC(int);
		int getF();
		void setF(int);
		Tile *getTile(int);
		void addDest(tilePtr);
	private:
		int ID;
		int r, c, f;
		int numStore;
		tilePtr Dests;
};

#endif
