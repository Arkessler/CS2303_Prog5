#ifndef MALLHEAD_H
/* Main header for prog5.cpp, initializes externs and declares some function prototypes
Author: Alexi Kessler */
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

int move (int cur[], int des[], int size);
int travel (robotPtr robot, int size);
void printtravel(int tsimTime [][2], int robots);

void printloc (int []);
bool IsEqual (int [], int []);
void d1(int [], int); 
void d2(int [], int[], int);
void d3(int [], int[], int);  
void next(int [], int [], int);
void twoway(int [], int [], int);
void elevator(int [], int[], int);
Tree *globalTree = new Tree();

bool debugRead = false;
void scanRobots();
int runRobSim();

int RobInSim = 0;
int RobNotInSim = 0;
int ShInSim = 0;
int ShNotInSim = 0;

#endif
