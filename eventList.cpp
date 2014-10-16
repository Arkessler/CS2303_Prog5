#ifndef EVENTLIST_CPP
#define EVENTLIST_CPP

#include "eventList.h"
#include "robot.h"
#include "shopper.h"
#include "externals.h"
#include <iostream>

#define DEBUGSTATE 1

//extern EventList *MallEvents;
int travel (robotPtr robot, int size);

//EventList *MallEvents = new EventList();

using std::cout;

#define DBG 0


EventNode::EventNode()
  :time(0), robotID(NULL), shopperID(NULL), eType(0), nextPtr(NULL)
{}

EventNode::EventNode(int newTime, Robot *robIn, int type)
  :time(newTime), robotID(robIn),shopperID(NULL), eType(type), nextPtr(NULL)
{}

EventNode::EventNode(int newTime, Shopper *shopIn, int type)
  :time(newTime), robotID(NULL), shopperID(shopIn), eType(type), nextPtr(NULL)
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
	//tilePtr entrance = &(Mall[8][16][0]);
  if(getRobotID() != NULL){
    switch(eType){
    case 0:
		{
		//Travel here
		int travelTime = travel(getRobotID(), SIZE);
		int newTime = (getTime()+ travelTime);
		//add arrival case
		mallEvents->addNewEvent( newTime, getRobotID(), 1); //Not sure what time goes in here, depends on travel 
		break;
		}
    case 1:
		{
		//deliver all items
		//add event case 2
		if (DEBUGSTATE)
			{
			cout<<"Robot's delivery inventory: "<<endl;
			getRobotID()->getDests()->printInventory();
			}
		int newTime = getRobotID()->deliverItems(getTime());
		if (DEBUGSTATE)
			cout<<"adding new event of type 2"<<endl;
		mallEvents->addNewEvent(newTime, getRobotID(), 2);
		cout<<"deliverItems went fine, time taken: "<<newTime<<endl;
		getRobotID()->removeDest();
		
		break;
		}
    case 2:
		{
		tilePtr entrance = new Tile();
		*entrance = Mall[8][16][0];
		entrance->printTile();
		//Check eventlist
		if(getRobotID()->checkDestsEmpty())//Evaluates to true if dests is empty
		{ 
			//Move towards entrance
			entrance->printTile();
			getRobotID()->addDest(entrance);
			if (DEBUGSTATE){
				cout<<"Robot's destination list now: "<<endl;
				getRobotID()->printDests();
			}
			int exitTime = (getTime() + travel(getRobotID(), SIZE));
			// add new event 3
			mallEvents->addNewEvent(exitTime, getRobotID(), 3);
		} else {
		//move towards dests (might remove front of dests first?) 
		int travelTime = travel(getRobotID(), SIZE);
		int newTime = travelTime + (getTime());
		//add event 1
		mallEvents->addNewEvent(newTime, getRobotID(), 1);
		}
		break;
		}
    case 3:
		{
		cout << "Robot " << getRobotID()->getID() << " has left the simulateion" << endl;
		break;
		}
    default:
		{
		cout<<"INVALID CASE" <<endl;
		break;
		}
    }
	mallEvents->setFirstPtr((mallEvents->getFirstPtr())->getNext());
  }
	
  else{ // if shopper != NULL
    switch(eType){
    case 0:
      //run shopperApp
      while(getShopperID()->getDest()->getInventory() != NULL){
	getShopperID()->shopperApp(getShopperID()->getDest()->getInventory()); //FIGURE OUT SHOPPER APP
      }
      //Travel here
      break;
    case 1:
      //run queue work
      break;
    case 2:
      //Check eventlist
      if(0){} //if condition then leave
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

  if(cur == NULL){ //at end of 
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
  getFirstPtr();
  if(DEBUGSTATE) cout<< "in print eventlist"<<endl;
  
  EventNode *cur = getFirstPtr();
  if (cur == NULL) return;
  while(cur != NULL){
    if(DEBUGSTATE) cout<<"in while"<<endl;
    cur->print();
	//(cur->getRobotID())->printRobot();
    cur = cur->getNext();
  }
  //getLastPtr()->print();

}
bool EventList::isEmpty() const{
  return firstPtr == 0;
}

//doesn't set last ptr (I don't think we use last ptr)
EventList *EventList::getShopperEvents(){
  EventList *alteredList = new EventList();

  EventNode *cur = getFirstPtr();
  EventNode *prev = NULL;

  while (cur != NULL && cur->getShopperID() == NULL){
    prev = cur;
    cur = cur->getNext();
  }
  if(cur == NULL) return NULL;
  else{
    alteredList->setFirstPtr(cur);
    return alteredList;
  }

}


#endif
