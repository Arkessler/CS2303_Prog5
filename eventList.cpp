#include "linkedList.h"
#include "Robot.h"
#include "Shopper.h"

EventNode::EventNode()
  :time(0), robID(NULL), shopperID(NULL), eType(0)
{}

EventNode::EventNode(int newTime, Robot *robIn, int type)
  :time(newTime), robID(robIn),shopperID(NULL), eType(type)
{}

EventNode::EventNode(int newTime, Shopper *shopIn, int type)
  :time(newTime), robID(NULL), shopperID(shopIn), eType(type)
{}

void EventNode::print(){
  //cout<< "Printing Node:" <<endl;
  cout<<"Time of Event: " << getTime()<<endl;
  (getRobotID()!=NULL)?(cout<<"Name of robot: " << getRobID()->getID() <<endl;):((getShopperID() != NULL) ? (cout<<"Name of shopper: " <<getShopID()->getID()<<endl;):cout<<"Invalid"<<endl;);  
  cout<<"Node Type:" << getEType()<<endl<<endl;
}

int EventNode::getTime(){
  return time;
}

Robot *EventNode::getRobotID(){
  return robotID;
}

Shopper *EventNode::getShopperID(){
  return shopperID;
}

int get_eType(){
  return eType;
}

///////////////////////////////////////////////////////////////////////////////////
// default constructor  
 EventList::EventList() 
   : firstPtr( 0 ), lastPtr( 0 ) 
{ 
  // empty body 
} // end List constructor 

// destructor 
 EventList::~EventList() 
{ 
  if ( !isEmpty() ) // List is not empty 
    { 
      cout << "Destroying nodes ...\n"; 

      EventNode *currentPtr = firstPtr; 
      EventNode *tempPtr; 

      while ( currentPtr != 0 ) // delete remaining nodes 
	{ 
	  tempPtr = currentPtr; 
	  //cout << tempPtr->data << '\n'; 
	  currentPtr = currentPtr->nextPtr; 
	  delete tempPtr; 
	} // end while 
    } // end if 

  cout << "All nodes destroyed\n\n"; 
} // end List destructor 

void EventList::addNode(EventNode *newNode){
  EventNode *cur = getFirstPtr();
  EventNode *prev = NULL;
  EventNode *last = getLastPtr();

  while(cur != NULL && cur->getTime() < newNode->getTime()){
    prev = cur;
    cur = cur->getNext();
  }
  if(cur == NULL){
    prev->setNext(newNode);
  }
  else{
    prev->setNext(newNode);
    newNode->setNext(cur);
  }
}

void EventList::addNewEvent(int time, Robot *newR, int type){
  EventNode *newEvent = new EventNode(time, newR, type);
  addNode(newEvent);
}

void EventList::addNewEvent(int time, Shopper *newShop, int type){
  EventNode *newEvent = new EventNode(time, newShop, type);
  addNode(newEvent);
}

void EventList::print(){
  EventNode *cur = getFirstPtr();
  while(cur != getLastPtr()){
    cur->print();
    cur = cur->getNext();
  }
  getLastPtr()->print();

}
