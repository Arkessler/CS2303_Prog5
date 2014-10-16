
//By Max
#ifndef ITEM_CPP
#define ITEM_CPP

#include "globals.h"
#include "store_functions.cpp"
#include "globalItem.h"

//Constructors.

GlobalItem::GlobalItem(){
  name = "NULL";
  stores = NULL;
  left = NULL;
  right = NULL;
}


GlobalItem::GlobalItem(string newName){
  name = newName;
  stores = new StorePtr();
  *stores = NULL;
  left = NULL;
  right = NULL;
}

//Compares the member item to a new item.
//returns -1 new item is earlier than the current item, 0 if they are the same
// and 1 if new item is later than current item.
int GlobalItem::id_compare(GlobalItemPtr newGlobalItem){
  string current = getName();
  if(newGlobalItem != NULL){
    string new_id = newGlobalItem->getName();
    
    if ( current.compare(new_id) < 0){  //if new is lower than current
      return 1;
    }
    else if(current.compare(new_id) == 0){ // if new is the same as current
      return 0;
    }
    else {  //if new is higher than current
      return -1;
    }
  }
  else{
    return -5;
  }
}

//Setters and getters
string GlobalItem::getName(){
  return name;
}

void GlobalItem::setName(string newName){
  name = newName;
}

GlobalItemPtr GlobalItem::getLeft(){
  return left;
}

GlobalItemPtr GlobalItem::getRight(){
  return right;
}

void GlobalItem::setLeft(GlobalItemPtr newPtr){
  left = newPtr;
}

void GlobalItem::setRight(GlobalItemPtr newPtr){
  right = newPtr;
}

StorePtr *GlobalItem::getStores(){
	if (stores != NULL){
		return stores;
	} else {
		return NULL;
	}
}

void GlobalItem::setStores(StorePtr *store){
  stores = store;
}

void GlobalItem::printGlobalItem(){
	cout<<"Name of GlobalItem is:" << name << endl;
	printStoreList(stores);
}

//This is really expensive,
GlobalItem *GlobalItem::findItem(LocalItem *toFind){
  if(toFind != NULL){
    GlobalItem *newFind = new GlobalItem(toFind->getName());
    if(id_compare(newFind) == 0){
      return this;
    }
    else if(id_compare(newFind) == -1){
      return getLeft()->findItem(toFind);
    }
    else if(id_compare(newFind) == 1){
      return getRight()->findItem(toFind);
    }
    else return NULL;
  }
  else return NULL;
}

#endif
