#include "eventList.h"
#include "robot.h"
#include "shopper.h"

#include <iostream>
using std::cout;

#define DBG 0

EventNode::EventNode()
  :time(0), robotID(NULL), shopperID(NULL), eType(0)
{}

EventNode::EventNode(int newTime, Robot *robIn, int type)
  :time(newTime), robotID(robIn),shopperID(NULL), eType(type)
{}

EventNode::EventNode(int newTime, Shopper *shopIn, int type)
  :time(newTime), robotID(NULL), shopperID(shopIn), eType(type)
{}

void EventNode::print(){
  //cout<< "Printing Node:" <<endl;
  cout<<"Time of Event: " << getTime()<<endl;
  std::string toPrint =
    (getRobotID()!=NULL)
    ?("ID of robot: ")         // <<  getRobotID()->getID() <<endl;)
    :
    ((getShopperID() != NULL) 
     ? ("Name of shopper: ")       //<<getShopID()->getID()<<endl;)
     :"Invalid");

  int printID = (getRobotID() != NULL) ? getRobotID()->getID() : ((getShopperID() != NULL) ? getShopperID()->getID() : -1);

  cout<<toPrint<<printID<<endl;

  cout<<"Node Type:" << get_eType()<<endl<<endl;
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

int EventNode::get_eType(){
  return eType;
}

void EventNode::checkState(){
  if(getRobotID() != NULL){
    switch(eType){
    case 0:
      //Travel here

      //add arrival case
      ////addNewEvent( ========  , getRobotID(), 1); //Not sure what time goes in here, depends on travel      
      break;
    case 1:
      //run addItems
      //add event case 2
      addNewEvent(getRobotID()->deliverItems(getTime()), getRobotID(), 2);

      break;
    case 2:
      //Check eventlist
      if(getRobotID()->checkDestsEmpty()){ //Evaluates to true if dests is empty
	//Move towards entrance

	// add new event 3
	////addNewEvent(=======, getRobotID(), 3);
      }
      else{
	//move towards dests (might remove front of dests first?

	//add event 1
	////addNewEvent(========, getRobotID(), 1);
      }

	break;
    case 3:
      cout << "Robot " << getRobotID()->getID() << " has left the simulateion" << endl;
      break;
    default:
      cout<<"INVALID CASE" <<endl;
      break;
    }
  }

  else{ // if shopper
    switch(eType){
    case 0:
      //Travel here
      break;
    case 1:
      //run addItems
      break;
    case 2:
      //Check eventlist
      if()
        break;
    case 3:
      break;
    case 4:
      break;
    default:
      break;
    }
}

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
	  currentPtr = currentPtr->getNext(); 
	  delete tempPtr; 
	} // end while 
    } // end if 

  cout << "All nodes destroyed\n\n"; 
} // end List destructor 


void EventList::addNode(EventNode *newNode){
  EventNode *cur = getFirstPtr();
  EventNode *prev = NULL;
  
  if(DBG) cout<<"passed initial assignment"<<endl;

  if(cur == NULL && prev == NULL)
    {
      //newNode->setNext(getFirstPtr());
      setFirstPtr(newNode);
      return;
    }
  
  while((cur != NULL) && (cur->getTime() < newNode->getTime())){
    prev = cur;
    cur = cur->getNext();
    if(DBG) cout<<"in traversal"<<endl;
  }

  if(DBG) cout<<"out of traversal"<<endl;

  if(cur == NULL){
    prev->setNext(newNode);
    //newNode->setNext(getFirstPtr());
    //setFirstPtr(newNode);
  }
  else if (cur->getTime() >= newNode->getTime() && prev != NULL){
    prev->setNext(newNode);
    if(DBG) cout<< "first assignment correct"<<endl;
    newNode->setNext(cur);
  }
  else if(prev == NULL){
    newNode->setNext(cur);
    setFirstPtr(newNode);
  }
  else{
    cout<<"unconsidered condition"<<endl;
  }
  if(DBG) cout<< "End of addNode"<<endl;
}

void EventList::addNewEvent(int time, Robot *newR, int type){
  EventNode *newEvent = new EventNode(time, newR, type);
  if(DBG) newEvent->print();
  addNode(newEvent);
}

void EventList::addNewEvent(int time, Shopper *newShop, int type){
  EventNode *newEvent = new EventNode(time, newShop, type);
  if(DBG) newEvent->print();
  addNode(newEvent);
}

void EventList::print(){
  EventNode *cur = getFirstPtr();
  while(cur != getLastPtr()){
    cur->print();
    cur = cur->getNext();
  }
  //getLastPtr()->print();

}
bool EventList::isEmpty() const{
  return firstPtr == 0;
}
