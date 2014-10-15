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
		Robot(int id, int stores, int row, int col, int floor);
		Robot(int id, int stores, int row, int col, int floor, tilePtr dest);
		
		int getID();
		void setID(int);
		int getR();
		void setR(int);
		int getC();
		void setC(int);
		int getF();
		void setF(int);
		int getNumStore();
		void setNumStore(int);
		Tile *getTile(int);
		
		tilePtr getDests();
		void addDest(tilePtr);
		void removeDest();
		bool checkDestsEmpty();
		
		int deliverItem();
		int deliverItems(int);
		
		void printRobot();
		void printDests();
	private:
		int ID;
		int r, c, f;
		int numStore;
		tilePtr Dests;
};

typedef Robot *robotPtr;

#endif
