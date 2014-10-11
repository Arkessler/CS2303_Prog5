/* externals.h

The list of the three globals that are in main but
external to all other components and the global defs.      */

#include "globals.h"
#include "tile.h"

extern Tile Mall[MAX+1][MAX+1][2];
extern int type  [MAX+1][MAX+1][2];
extern int step  [MAX+1][MAX+1][2];
extern int time;



