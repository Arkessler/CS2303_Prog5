/* Decision logic for movement. Originally coded by Professor Robert Kinicki, adapted by Alexi.
Functions are: d1,d2,d3,next,twoway and elevator.
*/
#ifndef DECIDE_CPP
#define DECIDE_CPP
#include "externals.h"
#include "tile.h"
#define EL_DELAY 3
#define DEBUGDECIDE 0
void printloc (int []);


/* d1 is called when there is ONLY one choice
   for robot to make. That choice is held in step array  */

void d1(int c[], int size)
{
	if (DEBUGDECIDE==1){
		printf("\n At simTime %d: Making decision 1 at %d %d %d", simTime, c[ROW],c[COL],c[FLOOR]);
		printf(" Step value at %d %d %d is %d\n", c[ROW], c[COL], c[FLOOR], (Mall[c[ROW]][c[COL]][c[FLOOR]]).getStep());
	}
  switch ((Mall[c[ROW]][c[COL]][c[FLOOR]]).getStep())
  {
    case NorthWest: c[COL]--; 
    case North:     c[ROW]--; 
                    break;
    case SouthWest: c[ROW]++;
    case West:      c[COL]--; 
                    break;
    case SouthEast: c[COL]++; 
    case South:     c[ROW]++; 
                    break;
    case NorthEast: c[ROW]--; 
    case East:      c[COL]++;
                    break;
    case INVALID:
    default:
         printloc(c);
	 printf("d1: lost in Mall!!");
         exit(EXIT_FAILURE);
  }
  return;
}

/* d2 is called when there are two possible directions
   for robot to choose. This is very specialized code
   based on step value. The key point is d2 only happens
   when direction is West or South.                     */

void d2(int c[], int d[], int size)
{
	if (DEBUGDECIDE==1)
		printf("Making decision 2 at %d %d %d\n", c[ROW],c[COL],c[FLOOR]);
  int i,j;

  /* d2 decides whether the robot needs to turn or not.
     The default is to turn because this has higher
     likelihood given one-way restrictions.          */

  bool turn = true;

    switch ((Mall[c[ROW]][c[COL]][c[FLOOR]]).getStep())
    {
      case West: 

	if (c[FLOOR])
	{
	   if((d[ROW] == 12) &&
	      (d[COL]   == 4) &&
	      (d[FLOOR] == c[FLOOR]))
	      turn = false;
	}
	else
	{
	  for(j = 0;  j <=  6; j = j+6)
	  {
	    for(i = 4; i <= 6; i = i+2)
            {
              {
	      if((d[ROW]   == i+j) &&
	         (d[COL]   == 4) &&
	         (d[FLOOR] == c[FLOOR]))
	        turn = false;
	      }
	    }
	  }
	}
	// This is adjustment when turning.
	if(turn)
        {
          if (c[FLOOR])
	    c[ROW]--;
          else
	    c[ROW]++;
        }
        break;

      case South:
	for(j = 0;  j <=  6; j = j+6)
	{
	  for(i = 4; i <= 6; i = i+2)
          {
            if((d[ROW]   == 12) &&
	       (d[COL]   == i+j) &&
	       (d[FLOOR] == c[FLOOR]))
	        turn = false;
	  }
	}
	// This is adjustment when turning.
	if(turn)
        {
          if (c[FLOOR])
	    c[COL]--;
          else
	    c[COL]++;
        }
        break;
    case INVALID:
    default:
         printloc(c);
	 printf("d2: lost in Mall!!");
         exit(EXIT_FAILURE);
  }
  // When not turning, simply call d1!
  if (!turn) d1(c,SIZE);
  return;
}

/* d3 is called when there are three direction choices
   for robot to make. That choice is held in step array.  */

void d3(int c[], int d[], int size)
{
	if (DEBUGDECIDE==1)
		printf("Making decision 3 at %d %d %d\n", c[ROW],c[COL],c[FLOOR]);
  int i,j;

  /* d3 decides whether the robot needs to turn or not.
     The default is to not turn because this has higher
     likelihood d3 cases apply to internal stores ONLY.    */

  bool turn = false;

  switch ((Mall[c[ROW]][c[COL]][c[FLOOR]]).getStep())
  {
    /* if destination is internal store,
       make turn and set to true.       */ 
    case North:     
    case South:
	for (j = 6; j <= 10; j = j+4)
	{
            if((d[ROW]   == c[ROW]) &&
               (d[COL]   == j)      &&
	       (d[FLOOR] == c[FLOOR]))
	    {
              if (j ==  6) c[COL]--;
	      if (j == 10) c[COL]++;
	      turn = true;
	    }
        }
      break;
    case East:      
    case West:
        for (i = 6; i <= 10; i = i+4)
	{
            if((d[ROW]   == i) &&
               (d[COL]   == c[COL]) &&
	       (d[FLOOR] == c[FLOOR]))
	    {
              if (i ==  6) c[ROW]--;
	      if (i == 10) c[ROW]++;
	      turn = true;
	    }
	 }
      break;

    case INVALID:
    default:
         printloc(c);
	 printf("d3: lost in Mall!!");
         exit(EXIT_FAILURE);
  }
  // if not turn, simply call d1!
  if (!turn) d1(c,SIZE);
  return;
}

/* next is the function that deals with stores
   that are right next to path on outside mall path. */

void next(int c[], int d[], int size)
{
	if (DEBUGDECIDE==1)
		printf("Making decision next at %d %d %d\n", c[ROW],c[COL],c[FLOOR]);
  // special local arrays 
  int NW[2][2] = { {4, 12},{12, 4}};
  int SW[2][2] = {{ 4,  4},{12,12}};
  int SE[2][2] = {{12,  4},{ 4,12}};
  int NE[2][2] = {{12, 12},{ 4, 4}};

  // default is no find
  bool find = false;

  // case when store is on the other floor
  if (c[FLOOR] != d[FLOOR])
  {
    d1(c, size);
    return;
  } 
  else
  {
	if (DEBUGDECIDE==1)
		printf("Step value at %d %d %d is %d", c[ROW], c[COL], c[FLOOR], (Mall[c[ROW]][c[COL]][c[FLOOR]]).getStep());
    switch ((Mall[c[ROW]][c[COL]][c[FLOOR]]).getStep())
    {
     case NorthWest:
          if((NW[c[FLOOR]][ROW] == d[ROW]) &&
             (NW[c[FLOOR]][COL] == d[COL]) )
	    find = true;
	  break;
      case SouthWest:
	  if((SW[c[FLOOR]][ROW] == d[ROW]) &&
             (SW[c[FLOOR]][COL] == d[COL]) )
	    find = true;
          break;
      case SouthEast:
	  if((SE[c[FLOOR]][ROW] == d[ROW]) &&
             (SE[c[FLOOR]][COL] == d[COL]) )
	    find = true;
          break;
      case NorthEast: 
          if((NE[c[FLOOR]][ROW] == d[ROW]) &&
             (NE[c[FLOOR]][COL] == d[COL]) )
	    find = true;
          break;
      case INVALID:
      default:
         printloc(c);
	 printf("Next: Lost in Mall at");
         exit(EXIT_FAILURE);
    } //end switch
  } //end else

  /* if store is next to current location,
     move robot into store.             */
  if (find)
  {
     c[ROW] = d[ROW];
     c[COL] = d[COL]; 
  }
  else
    // otherwise call d1!
    d1(c, size);
  return;
}

/* twoway handles those locations where
   robot can move in both directions.
   But these locations are ALL next to stores. */

void twoway(int c[], int d[], int size)
{
	if (DEBUGDECIDE==1)
		printf("Making decision twoway at %d %d %d\n", c[ROW],c[COL],c[FLOOR]);
  bool find = false;

  // case when store is on the other floor
  if (c[FLOOR] != d[FLOOR])
  {
    d1(c, size);  //then call d1
    return;
  } 
  else
  {
    switch ((Mall[c[ROW]][c[COL]][c[FLOOR]]).getStep())
    {
     case North:
	  if(d[ROW] == 10) find = true;
	  break;
      case South:
	  if(d[ROW] ==  6) find = true;
          break;
      case East:
	  if(d[COL] ==  6) find = true;
          break;
      case West: 
	  if(d[COL] == 10) find = true; 
          break;
      case INVALID:
      default:
	 printf("TwoWay: Lost in Mall at");
         printloc(c);
         break;
    } //end switch
  } //end else

  /* If robot is at a twoway space which is
     entrance to his next store. Put robot
     in the store.                      */
  if (find)
  {
     c[ROW] = d[ROW];
     c[COL] = d[COL]; 
  }
  else
    d1(c, size);  //otherwise call d1
  return;
}

// function to move robot through elevator
void take_el(int c[], int d[], int size)
{
	if (DEBUGDECIDE)
		printf ("Robot taking elevator at %d\n", simTime);
	simTime = simTime + EL_DELAY;
	c[FLOOR] = d[FLOOR];
	return;
}

/* elevator handles robot on elevator square,
   but not taking elevator.                */
void elevator(int c[], int d[], int size)
{
	if (DEBUGDECIDE)
		printf("\nAt simTime %d: On Elevator. Making elevator decision.", simTime);
  if (c[FLOOR] != d[FLOOR])
  {
    take_el(c, d, SIZE);
  }

  /* code is specialized to those cases
     when robot turns. This code takes
     advantage of the symmetry of the
     choices.                      */
  switch (c[FLOOR])
  {
    case First:
      if ((d[ROW] == 12) &&
	  ((d[COL] ==  6) ||
           (d[COL] == 10) ||
           (d[COL] == 12)   ))
	c[ROW]++;    //robot turns.
      else
	d1(c,SIZE);  //no turn - call d1!
      break;
    case Second:
      if ((d[COL] == 4) &&
	  ((d[ROW] ==  4) ||
           (d[ROW] ==  6) ||
           (d[ROW] == 10)   ))
	d1(c,SIZE);  //no turn - call d1!
      else
	c[ROW]--;    //robot turns.
      break;
    case INVALID:
    default:
       printf("El: Lost in Mall at");
       printloc(c);
  } //end switch
  return;
}
#endif
