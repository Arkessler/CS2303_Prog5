//By Max
#ifndef ITEM_CPP
#define ITEM_CPP

#include "global.h"
#include "store_functions.cpp"
#include "item.h"

//Constructors.

LocalItem::LocalItem(){
  name = "NULL";
  stores = NULL;
  left = NULL;
  right = NULL;
}


LocalItem::LocalItem(string newName){
  name = newName;
  stores = new StorePtr();
  *stores = NULL;
  left = NULL;
  right = NULL;
}

//Compares the member item to a new item.
//returns -1 new item is earlier than the current item, 0 if they are the same
// and 1 if new item is later than current item.
int LocalItem::id_compare(LocalItemPtr newLocalItem){
  string current = getName();
  string new_id = newLocalItem->getName();

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

//Setters and getters
string LocalItem::getName(){
  return name;
}

void LocalItem::setName(string newName){
  name = newName;
}

LocalItemPtr LocalItem::getLeft(){
  return left;
}

LocalItemPtr LocalItem::getRight(){
  return right;
}

void LocalItem::setLeft(LocalItemPtr newPtr){
  left = newPtr;
}

void LocalItem::setRight(LocalItemPtr newPtr){
  right = newPtr;
}

StorePtr *LocalItem::getStores(){
	if (stores != NULL){
		return stores;
	} else {
		return NULL;
	}
}

void LocalItem::setStores(StorePtr *store){
  stores = store;
}

void LocalItem::printLocalItem(){
	cout<<"Name of LocalItem is:" << name << endl;
	printStoreList(stores);
}

#endif
