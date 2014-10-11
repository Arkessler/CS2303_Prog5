// Set of  small useful functions
#ifndef SMALL_C
#define SMALL_C
#include "externals.h"

// debug function 
void printloc(int cell[])
{
  printf("row = %d col = %d floor = %d\n",
	 cell[0], cell[1], cell[2]);
  return;
}

/* IsEqual tests to see if robot has
   arrived at destination.          */
bool IsEqual(int now[], int des[])
{
  if ((now[0] == des[0]) &&
      (now[1] == des[1]) &&
      (now[2] == des[2]))
    return true;
  else
    return false;
}
#endif
