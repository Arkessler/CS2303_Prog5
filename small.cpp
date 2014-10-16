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

}
void instructions()
{
	cout<<"Choice 0 tests: Robot getter/setters Robot tileAdd\n";
	cout<<"Choice 1 tests: Scanning in Robots"<<endl;
	cout<<"Choice 2 tests: Travel function taking robotPtr"<<endl;
	cout<<"Choice 3 tests: deliverItem()"<<endl;
	cout<<"Choice 4 tests: deliverItems()"<<endl;
	cout<<"Choice 5 tests: EventList and EventNode"<<endl;
    cout<<"Choice 6 tests: scanRobots()"<<endl;
    cout<<"Choice 7 tests: checkState()"<<endl;
	cout<<"Choice 8 tests: runRobSim()"<<endl;
	cout<<"Choice 9 tests: tree"<<endl;
	cout<<"Choice 10 tests: shopperApp"<<endl;
	cout<<"Choice 11 tests: queues"<<endl;

	cout<<"Please enter test choice\n";
}
#endif
