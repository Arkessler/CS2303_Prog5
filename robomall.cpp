//  RoboMall Program

/* This is Program 2 for CS2303 in A14.
   Adapted from code Authored by Bob Kinicki
   Adapted by Alexi Kessler

This file contains the main function and
help functions: move, travel and printtravel

                                             */

#include <stdio.h>
#include "globals.h"
#include "tile.h"


Tile Mall[MAX+1][MAX+1][2];
int type [MAX+1][MAX+1][2];
int step [MAX+1][MAX+1][2];
int time = 0;

int init_mall ();
void printloc (int []);
bool IsEqual (int [], int []);
void d1(int [], int); 
void d2(int [], int[], int);
void d3(int [], int[], int);  
void next(int [], int [], int);
void twoway(int [], int [], int);
void elevator(int [], int[], int);

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

  // Simulation time incremented here after one step!
  time++;
  /*  This is a debug print in case you want to see individual
      robot steps.  

    printf("Time: %d Robot at ", time);
    printloc(cur);                        
  */
  return;
}

/* travel function takes robot  from 'from' location to 'to' location */
void travel (int from[], int to[], int size)
{
  int cntr = 0;        // cntr used to check for infinite loop
   printf("Time: %d Robot leaves ", time);
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

void printtravel(int ttime [][2], int robots)
{
  int i;
  printf ("Robot   Start Time   Finish Time\n");

  for (i=0; i < robots; i++)
    printf ("%3d  %11d  %12d\n", i+1, ttime[i][STIME], ttime[i][ETIME]);
  return;
}

int main ()
{
    int i,j;
    int robotID;
    // R array holds robot location
    // S array holds next store location

    int robots, stores[MAX_STORES], R[3], S[3];

    // init_mall initializes type and step arrays
    init_mall();
	
	
    // read in number of robots in simulation
    scanf ("%d", &robots);
    printf("Simulation of %d robots in RoboMall\n",
           robots);

       //traveltime retains info to compute robot's
       //time spent in RoboMall                  
    int traveltime [robots][2];

    // read in number of stores each robot will visit
    for (i = 0; i < robots; i++)
    {
      scanf ("%d", &stores[i]);
      printf("Robot %d visits %d stores\n", i, stores[i]); 
    }
	
    // This is the main loop for the whole simulation.
    for (i = 0; i < robots; i++)
    {
      // All robots enter mall at A1
      R[FLOOR] = First;
      R[ROW] = MID;
      R[COL] = MAX;
      // record robot's arrival time
      traveltime [i][STIME] = time;
      robotID = i+1;
      printf("Time: %d Robot %d enters Mall\n",
	     time, robotID);

     //go through loop once for each store
	 //the ith robot visits                 
      for (j = 0; j < stores[i]; j++)
      {
	scanf("%d %d %d", &S[ROW], &S[COL], &S[FLOOR]);
	printf("Next store is at %d %d %d\n",
                S[ROW], S[COL], S[FLOOR]);

	// robot travels from current location to next store
	travel(R, S, SIZE);
	printf("Time: %d Robot %d arrived at %d %d %d \n",
	       time, robotID, S[ROW], S[COL], S[FLOOR]);

	// bump up time to account for delay in store
	time = time + 1 + S[FLOOR];
      }

       //robot has visited all its stores. Set store location
       // to A1 and then robot travels to exit mall         

      // use S to send robot to A1 exit from RoboMall
      S[ROW] = MID;
      S[COL] = MAX;
      S[FLOOR] = First;
      travel(R, S, SIZE);

      // record robot departure time from RoboMall
      traveltime [i][ETIME] = time;
      printf("Time: %d Robot %d leaves the mall!\n",
	     time, robotID); 
      time++;  //bump up clock by one for next robots entry
    } //end large for loop

    time--;   //no more robots coming - set time back one 
    printf("Time: %d Simulation Ends\n", time);

    // printtravel prints final robot time in RoboMall
    printtravel (traveltime, robots); 
    return 0;
}
