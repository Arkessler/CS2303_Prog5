// Set of  small useful functions
#ifndef SMALL_C
#define SMALL_C
#include <iostream>
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

bool RobNotInEmpty()
{
	bool empty;
	empty = true;
	int counter;
	for (counter = 0; counter<MAX_ROBOTS; counter++)
	{
		if (&(RobotsNotInSim[counter])!=NULL)
			empty = false;
	}
	return empty;
}
void instructions()
{
	cout<<"Choice 0 tests: Robot getter/setters Robot tileAdd\n";
	cout<<"Choice 1 tests: Scanning in Robots"<<endl;
	cout<<"Choice 2 tests: Travel function taking robotPtr"<<endl;
	cout<<"Choice 4 tests: EventList inserting"<<endl;
	cout<<"Please enter test choice\n";
}
#endif
