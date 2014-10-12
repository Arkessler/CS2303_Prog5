/* externals.h

The list of the three globals that are in main but
external to all other components and the global defs.      */

#include "globals.h"
#include "tile.h"
#include "robot.h"
//#include "destination.h"

extern Tile Mall[MAX+1][MAX+1][2];
//extern Dest Dests[20];
extern int simTime;
extern Robot RobotsNotInSim[MAX_ROBOTS];

