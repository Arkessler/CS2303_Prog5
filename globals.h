/* globals.h

definitions used throughout the RoboMall program. */


#ifndef GLOBALS_H
#define GLOBALS_H
#include "tile.h"

/*
#if !defined(NULL)
  #define NULL 0
#endif*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define ROW    0
#define COL    1
#define FLOOR  2
#define SIZE   3
#define MIN    0
#define MID    8
#define MAX   16
#define INVALID 9
#define MAX_ROBOTS  9
#define MAX_STORES 20
#define MAX_PATH  200 
#define STIME 0
#define ETIME 1

//Tile Mall [MAX+1][MAX+1][2];
enum Choices    {Invalid, One, Two, Three, Next, TwoWay, Elevator, Store};
enum Coordinate {Row, Col, Floor};
enum Direction  {North, NorthEast, East, SouthEast,
		 South, SouthWest, West, NorthWest};
enum Floors     {First, Second};

#endif
