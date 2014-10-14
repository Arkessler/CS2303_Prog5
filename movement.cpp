#ifndef MOVEMENT_CPP
#define MOVEMENT_CPP

#include <iostream>
#include "externals.h"
//#include "tile.h"
//#include "decide.cpp"

void printloc (int []);
bool IsEqual (int [], int []);
void d1(int [], int); 
void d2(int [], int[], int);
void d3(int [], int[], int);  
void next(int [], int [], int);
void twoway(int [], int [], int);
void elevator(int [], int[], int);


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
                    (Mall[cur[ROW]][cur[COL]][cur[FLOOR]]).getType());
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

#endif
