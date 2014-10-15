/* externals.h

The list of the three globals that are in main but
external to all other components and the global defs.      */

#include "globals.h"
#include "tile.h"
//#include "globalItem.h"
#include "robot.h"
#include "shopper.h"
#include "eventList.h"

extern Tile Mall[MAX+1][MAX+1][2];
extern int simTime;
extern EventList *mallEvents;

extern Robot RobotsNotInSim[MAX_ROBOTS];
extern Shopper ShoppersNotInSim[MAX_SHOPPERS];

//extern Tree *ItemTree;
