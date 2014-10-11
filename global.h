#ifndef GLOBAL_H
#define GLOBAL_H

#include <iostream>
#include <string>
using namespace std;

#define GLOBALDEBUG 1

typedef struct store{
  int x, y, z, itemCount;
  struct store *nextStore;
} Store;

typedef Store *StorePtr;

int store_compare(StorePtr currentStore, StorePtr newStore);

//void addStore(StorePtr *sPtr, StorePtr newStore);

//void addStore(ItemPtr itPtr, StorePtr newStore);

void removeStore(StorePtr *sPtr,StorePtr toRemove);

void printStore(StorePtr store);

void printStoreList(StorePtr *store);

#endif
