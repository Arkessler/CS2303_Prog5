#ifndef MALLHEAD_H
#define MALLHEAD_H
#include "externals.h"

Tile Mall[MAX+1][MAX+1][2];
int type [MAX+1][MAX+1][2];
int step [MAX+1][MAX+1][2];
Robot RobotsNotInSim[MAX_ROBOTS];
int simTime = 0;

void instructions();
bool RobNotInEmpty();
int init_mall ();
void printloc (int []);
bool IsEqual (int [], int []);
void d1(int [], int); 
void d2(int [], int[], int);
void d3(int [], int[], int);  
void next(int [], int [], int);
void twoway(int [], int [], int);
void elevator(int [], int[], int);

bool debugRead = false;
void scanRobots();
#endif
