#ifndef TILE_H
#define TILE_H
//#include "globals.h"

class Tile
{
	public:
		Tile();
		
		void setType(int);
		int getType();
		void setStep(int);
		int getStep();
		void setPosition(int, int, int);
		int getRow();
		int getCol();
		int getFloor();

	private:
		int type;
		int step;
		int r, c, f;
};

#endif
