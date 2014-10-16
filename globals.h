/* globals.h

definitions used throughout the RoboMall program. */


#ifndef GLOBALS_H
#define GLOBALS_H

#include "tile.h"
#include <iostream>
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
#define MAX_SHOPPERS 10
#define MAX_STORES 20
#define MAX_PATH  200 
#define STIME 0
#define ETIME 1
using namespace std;

enum Choices    {Invalid, One, Two, Three, Next, TwoWay, Elevator, Store};
enum Coordinate {Row, Col, Floor};
enum Direction  {North, NorthEast, East, SouthEast,
		 South, SouthWest, West, NorthWest};
enum Floors     {First, Second};

typedef struct store{
  int x, y, z, iCount;
  struct store *nextStore;
} store;


typedef store *StorePtr;

StorePtr newStore(int xPos, int yPos, int zPos, int count, StorePtr next);

  /*
  StorePtr nStore = new store();
  nStore->x = xPos;
  nStore->y = yPos;
  nStore->z = zPos;
  nStore->itemCount = count;
  nStore->nextStore = next;
  return nStore;
}
  */


int store_compare(StorePtr currentStore, StorePtr newStore);

void removeStore(StorePtr *sPtr,StorePtr toRemove);

void printStore(StorePtr store);

void printStoreList(StorePtr *store); 

#endif
