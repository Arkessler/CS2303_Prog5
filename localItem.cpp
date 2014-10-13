/* class implementation for local item, which is to be used to represent the local item stock of a store in program 5
Author:Alexi Kessler */
#ifndef LOCALITEM_CPP
#define LOCALITEM_CPP

#include "globals.h"
#include "localItem.h"

//Constructors.

LocalItem::LocalItem(){
  name = "NULL";

}


LocalItem::LocalItem(string newName){
  name = newName;
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

int LocalItem::getCount(){
	return localCount;
}

void LocalItem::setCount(int c){
	localCount=c;
}

LocalItemPtr LocalItem::getNext(){
  return nextItem;
}

void LocalItem::setNext(LocalItemPtr newPtr){
  nextItem = newPtr;
}

void LocalItem::printLocalItem(){
	cout<<"Name of LocalItem is:" << name << endl;
	cout<<"Local item count is: " << localCount << endl;
}

#endif
