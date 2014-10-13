#ifndef PROG5_CPP
#define PROG5_CPP

#include <iostream>
#include <string.h>
#include "globals.h"
#include "mallHead.h"
#include "tile.h"
#include "robot.h"


#define DEBUG 1

//#include "binTree.h"
//#include "item.h"
//#include "binTree.cpp"
//#include "store_functions.cpp"

//#include "small.cpp"

// move function controls robot's steps  
void move (int cur[], int des[], int size)
{

/* Choices {Invalid, One, Two, Three, Next, 
   TwoWay, Elevator,Store}              

   The main idea is to categorize the type of
   choice the robot has and use switch to process
   that choice.  type array keeps choice type for
   all mall locations.

*/
	printf ("   type is %d", (Mall[cur[ROW]][cur[COL]][cur[FLOOR]]).getType());
  switch ((Mall[cur[ROW]][cur[COL]][cur[FLOOR]]).getType())
  
  {
    case Store:    
    case One:      d1(cur, SIZE);
                   break;
    case Two:      d2(cur,des,SIZE);
                   break;
    case Three:    d3(cur,des,SIZE);
                   break;
    case Next:     next(cur,des,SIZE);
                   break;
    case TwoWay:   twoway(cur,des,SIZE);
                   break;
    case Elevator: elevator(cur,des,SIZE);
                   break;
    case INVALID:
    default:
                   printf("M: Lost in Mall at ");
                   printloc(cur);
		   printf("Type = %d\n",
                    type[cur[ROW]][cur[COL]][cur[FLOOR]]);
                   exit(EXIT_FAILURE);
  } //end switch

  // Simulation simTime incremented here after one step!
  simTime++;
  /*  This is a debug print in case you want to see individual
      robot steps.  

    printf("Time: %d Robot at ", simTime);
    printloc(cur);                        
  */
  return;
}

/* travel function takes robot  from 'from' location to 'to' location */
void travel (int from[], int to[], int size)
{
  int cntr = 0;        // cntr used to check for infinite loop
   printf("Time: %d Robot leaves ", simTime);
   printloc(from);

   // Loop until robot arrives at store or A1
   while(!IsEqual(from,to) &&
         (cntr < MAX_PATH))
   {
     // move controls robot's steps
     move(from,to, SIZE);
     cntr++;
   }
   if (cntr == MAX_PATH) 
   {
     printf ("\n Infinite Loop"); 
     exit(EXIT_FAILURE);
   }
   return;
 }

void printtravel(int tsimTime [][2], int robots)
{
  int i;
  printf ("Robot   Start Time   Finish Time\n");

  for (i=0; i < robots; i++)
    printf ("%3d  %11d  %12d\n", i+1, tsimTime[i][STIME], tsimTime[i][ETIME]);
  return;
}

//use mainly as a driver function
int main () //Author: Alexi
{
	int i,j, choice;
    int robotID;
    // R array holds robot location
    // S array holds next store location

    int robots, nextS[3];
	//stores[MAX_STORES];
	
	init_mall();
	
	instructions();
	cin>>choice;
	tilePtr tile0 = new Tile(2, 5, 12, 4, 3);
	
	switch (choice)
	{
		case 0: //Test robot class
			{
			Robot R = *(new Robot(45));
			cout<<"New robot's ID: "<<R.getID()<<endl;
			cout<<"New robot's floor position: "<<R.getF()<<endl;
			R.setF(6);
			cout<<"Robot's floor position after setter: "<<R.getF()<<endl;
			cout<<"Robot's destination list before setter:\n";
			tilePtr testTile = new Tile();
			testTile = (R.getTile(1));
			if (testTile == NULL)
			{
				cout<<"Tile is null!\n";
			}
			else
			{
				(*testTile).printTile();
			}
			cout<<"Adding tile0 to destination list\n";
			R.addDest(tile0);
			testTile = (R.getTile(1));
			cout<<"Robot's destination list after setter:\n";
			if (testTile == NULL)
			{
				cout<<"Tile is null!\n";
			}
			else
			{
				(*testTile).printTile();
			}
			break;
			}
			//weird spacing problems
		case 1:
			{
			scanRobots(); 
			(RobotsNotInSim[0]).printRobot();
			bool EMP = RobNotInEmpty();
			cout<<"Check for whether or not RobotsNotInSim is empty: "<<EMP<<endl;
			break;
			}
		default:
			cout<<"Improper or no test input";
			break;
	}
}

void scanRobots(){
  int numBots = 0, i = 0, j = 0, numItems;

  if(DEBUG) cout << "Type number of bots" <<endl;
  cin >> numBots;
  int storeCounts[numBots];

  for (i = 0; i < numBots; i++){
    int tempStoreCnt;
    if(DEBUG) cout<<"Type number of stores for robot "<< i <<endl;
    cin >> tempStoreCnt;
    RobotsNotInSim[i].setNumStore(tempStoreCnt);
    if(DEBUG) cout << "Scanned Robot " << i <<endl;
  } 

  for(i = 0; i < numBots; i++){
    for (j = 0; j < RobotsNotInSim[i].getNumStore(); j++){
      int rowIn, colIn, floorIn;
      if(DEBUG) cout <<"input location of store " << j <<" r, c, f:"<<endl;
      cin >> rowIn;
      cin >> colIn;
      cin >> floorIn;
      //cout << row << col << floor;
      RobotsNotInSim[i].addDest(new Tile(Mall[rowIn][colIn][floorIn].getType(), Mall[rowIn][colIn][floorIn].getStep(),rowIn, colIn, floorIn));
      //RobotsNotInSim[i].getTile(i)->setPosition(rowIn,colIn,floorIn);
      cout<< RobotsNotInSim[i].getTile(1)->getRow() << "~" << RobotsNotInSim[i].getTile(1)->getCol()<<endl;
      if(DEBUG) cout << "scanned store " << j << " for robot " << i << endl;
    }
  }

  if(DEBUG) {
    cout<<endl;
    for(i = 0; i < numBots; i++){
      RobotsNotInSim[i].printDests();
      cout<<endl;
    }
  }
}
  
#endif
