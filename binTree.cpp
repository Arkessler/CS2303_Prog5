decide.cpp                                                                                          0000644 0027600 0027600 00000021142 12417637071 013563  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              /* Decision logic for movement. Originally coded by Professor Robert Kinicki, adapted by Alexi.
Functions are: d1,d2,d3,next,twoway and elevator.
*/
#ifndef DECIDE_CPP
#define DECIDE_CPP
#include "externals.h"
#include "tile.h"
#define EL_DELAY 3
#define DEBUGDECIDE 0
void printloc (int []);


/* d1 is called when there is ONLY one choice
   for robot to make. That choice is held in step array  */

void d1(int c[], int size)
{
	if (DEBUGDECIDE==1){
		printf("\n At simTime %d: Making decision 1 at %d %d %d", simTime, c[ROW],c[COL],c[FLOOR]);
		printf(" Step value at %d %d %d is %d\n", c[ROW], c[COL], c[FLOOR], (Mall[c[ROW]][c[COL]][c[FLOOR]]).getStep());
	}
  switch ((Mall[c[ROW]][c[COL]][c[FLOOR]]).getStep())
  {
    case NorthWest: c[COL]--; 
    case North:     c[ROW]--; 
                    break;
    case SouthWest: c[ROW]++;
    case West:      c[COL]--; 
                    break;
    case SouthEast: c[COL]++; 
    case South:     c[ROW]++; 
                    break;
    case NorthEast: c[ROW]--; 
    case East:      c[COL]++;
                    break;
    case INVALID:
    default:
         printloc(c);
	 printf("d1: lost in Mall!!");
         exit(EXIT_FAILURE);
  }
  return;
}

/* d2 is called when there are two possible directions
   for robot to choose. This is very specialized code
   based on step value. The key point is d2 only happens
   when direction is West or South.                     */

void d2(int c[], int d[], int size)
{
	if (DEBUGDECIDE==1)
		printf("Making decision 2 at %d %d %d\n", c[ROW],c[COL],c[FLOOR]);
  int i,j;

  /* d2 decides whether the robot needs to turn or not.
     The default is to turn because this has higher
     likelihood given one-way restrictions.          */

  bool turn = true;

    switch ((Mall[c[ROW]][c[COL]][c[FLOOR]]).getStep())
    {
      case West: 

	if (c[FLOOR])
	{
	   if((d[ROW] == 12) &&
	      (d[COL]   == 4) &&
	      (d[FLOOR] == c[FLOOR]))
	      turn = false;
	}
	else
	{
	  for(j = 0;  j <=  6; j = j+6)
	  {
	    for(i = 4; i <= 6; i = i+2)
            {
              {
	      if((d[ROW]   == i+j) &&
	         (d[COL]   == 4) &&
	         (d[FLOOR] == c[FLOOR]))
	        turn = false;
	      }
	    }
	  }
	}
	// This is adjustment when turning.
	if(turn)
        {
          if (c[FLOOR])
	    c[ROW]--;
          else
	    c[ROW]++;
        }
        break;

      case South:
	for(j = 0;  j <=  6; j = j+6)
	{
	  for(i = 4; i <= 6; i = i+2)
          {
            if((d[ROW]   == 12) &&
	       (d[COL]   == i+j) &&
	       (d[FLOOR] == c[FLOOR]))
	        turn = false;
	  }
	}
	// This is adjustment when turning.
	if(turn)
        {
          if (c[FLOOR])
	    c[COL]--;
          else
	    c[COL]++;
        }
        break;
    case INVALID:
    default:
         printloc(c);
	 printf("d2: lost in Mall!!");
         exit(EXIT_FAILURE);
  }
  // When not turning, simply call d1!
  if (!turn) d1(c,SIZE);
  return;
}

/* d3 is called when there are three direction choices
   for robot to make. That choice is held in step array.  */

void d3(int c[], int d[], int size)
{
	if (DEBUGDECIDE==1)
		printf("Making decision 3 at %d %d %d\n", c[ROW],c[COL],c[FLOOR]);
  int i,j;

  /* d3 decides whether the robot needs to turn or not.
     The default is to not turn because this has higher
     likelihood d3 cases apply to internal stores ONLY.    */

  bool turn = false;

  switch ((Mall[c[ROW]][c[COL]][c[FLOOR]]).getStep())
  {
    /* if destination is internal store,
       make turn and set to true.       */ 
    case North:     
    case South:
	for (j = 6; j <= 10; j = j+4)
	{
            if((d[ROW]   == c[ROW]) &&
               (d[COL]   == j)      &&
	       (d[FLOOR] == c[FLOOR]))
	    {
              if (j ==  6) c[COL]--;
	      if (j == 10) c[COL]++;
	      turn = true;
	    }
        }
      break;
    case East:      
    case West:
        for (i = 6; i <= 10; i = i+4)
	{
            if((d[ROW]   == i) &&
               (d[COL]   == c[COL]) &&
	       (d[FLOOR] == c[FLOOR]))
	    {
              if (i ==  6) c[ROW]--;
	      if (i == 10) c[ROW]++;
	      turn = true;
	    }
	 }
      break;

    case INVALID:
    default:
         printloc(c);
	 printf("d3: lost in Mall!!");
         exit(EXIT_FAILURE);
  }
  // if not turn, simply call d1!
  if (!turn) d1(c,SIZE);
  return;
}

/* next is the function that deals with stores
   that are right next to path on outside mall path. */

void next(int c[], int d[], int size)
{
	if (DEBUGDECIDE==1)
		printf("Making decision next at %d %d %d\n", c[ROW],c[COL],c[FLOOR]);
  // special local arrays 
  int NW[2][2] = { {4, 12},{12, 4}};
  int SW[2][2] = {{ 4,  4},{12,12}};
  int SE[2][2] = {{12,  4},{ 4,12}};
  int NE[2][2] = {{12, 12},{ 4, 4}};

  // default is no find
  bool find = false;

  // case when store is on the other floor
  if (c[FLOOR] != d[FLOOR])
  {
    d1(c, size);
    return;
  } 
  else
  {
	if (DEBUGDECIDE==1)
		printf("Step value at %d %d %d is %d", c[ROW], c[COL], c[FLOOR], (Mall[c[ROW]][c[COL]][c[FLOOR]]).getStep());
    switch ((Mall[c[ROW]][c[COL]][c[FLOOR]]).getStep())
    {
     case NorthWest:
          if((NW[c[FLOOR]][ROW] == d[ROW]) &&
             (NW[c[FLOOR]][COL] == d[COL]) )
	    find = true;
	  break;
      case SouthWest:
	  if((SW[c[FLOOR]][ROW] == d[ROW]) &&
             (SW[c[FLOOR]][COL] == d[COL]) )
	    find = true;
          break;
      case SouthEast:
	  if((SE[c[FLOOR]][ROW] == d[ROW]) &&
             (SE[c[FLOOR]][COL] == d[COL]) )
	    find = true;
          break;
      case NorthEast: 
          if((NE[c[FLOOR]][ROW] == d[ROW]) &&
             (NE[c[FLOOR]][COL] == d[COL]) )
	    find = true;
          break;
      case INVALID:
      default:
         printloc(c);
	 printf("Next: Lost in Mall at");
         exit(EXIT_FAILURE);
    } //end switch
  } //end else

  /* if store is next to current location,
     move robot into store.             */
  if (find)
  {
     c[ROW] = d[ROW];
     c[COL] = d[COL]; 
  }
  else
    // otherwise call d1!
    d1(c, size);
  return;
}

/* twoway handles those locations where
   robot can move in both directions.
   But these locations are ALL next to stores. */

void twoway(int c[], int d[], int size)
{
	if (DEBUGDECIDE==1)
		printf("Making decision twoway at %d %d %d\n", c[ROW],c[COL],c[FLOOR]);
  bool find = false;

  // case when store is on the other floor
  if (c[FLOOR] != d[FLOOR])
  {
    d1(c, size);  //then call d1
    return;
  } 
  else
  {
    switch ((Mall[c[ROW]][c[COL]][c[FLOOR]]).getStep())
    {
     case North:
	  if(d[ROW] == 10) find = true;
	  break;
      case South:
	  if(d[ROW] ==  6) find = true;
          break;
      case East:
	  if(d[COL] ==  6) find = true;
          break;
      case West: 
	  if(d[COL] == 10) find = true; 
          break;
      case INVALID:
      default:
	 printf("TwoWay: Lost in Mall at");
         printloc(c);
         break;
    } //end switch
  } //end else

  /* If robot is at a twoway space which is
     entrance to his next store. Put robot
     in the store.                      */
  if (find)
  {
     c[ROW] = d[ROW];
     c[COL] = d[COL]; 
  }
  else
    d1(c, size);  //otherwise call d1
  return;
}

// function to move robot through elevator
void take_el(int c[], int d[], int size)
{
	if (DEBUGDECIDE)
		printf ("Robot taking elevator at %d\n", simTime);
	simTime = simTime + EL_DELAY;
	c[FLOOR] = d[FLOOR];
	return;
}

/* elevator handles robot on elevator square,
   but not taking elevator.                */
void elevator(int c[], int d[], int size)
{
	if (DEBUGDECIDE)
		printf("\nAt simTime %d: On Elevator. Making elevator decision.", simTime);
  if (c[FLOOR] != d[FLOOR])
  {
    take_el(c, d, SIZE);
  }

  /* code is specialized to those cases
     when robot turns. This code takes
     advantage of the symmetry of the
     choices.                      */
  switch (c[FLOOR])
  {
    case First:
      if ((d[ROW] == 12) &&
	  ((d[COL] ==  6) ||
           (d[COL] == 10) ||
           (d[COL] == 12)   ))
	c[ROW]++;    //robot turns.
      else
	d1(c,SIZE);  //no turn - call d1!
      break;
    case Second:
      if ((d[COL] == 4) &&
	  ((d[ROW] ==  4) ||
           (d[ROW] ==  6) ||
           (d[ROW] == 10)   ))
	d1(c,SIZE);  //no turn - call d1!
      else
	c[ROW]--;    //robot turns.
      break;
    case INVALID:
    default:
       printf("El: Lost in Mall at");
       printloc(c);
  } //end switch
  return;
}
#endif
                                                                                                                                                                                                                                                                                                                                                                                                                              eventList.cpp                                                                                       0000750 0027600 0027600 00000020654 12417637461 014333  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              /* Class implementation for eventList and eventNode  used Pearson Copyright 2008
All functions written by Max Li unless otherwise stated */
#ifndef EVENTLIST_CPP
#define EVENTLIST_CPP

#include "eventList.h"
#include "robot.h"
#include "shopper.h"
#include "externals.h"
#include <iostream>

#define DEBUGSTATE 0

int travel (robotPtr robot, int size);

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
    case 0: //Mall arrival Author:Alexi
		{
		//Travel here
		int travelTime = travel(getRobotID(), SIZE);
		int newTime = (getTime()+ travelTime);
		//add arrival case
		mallEvents->addNewEvent( newTime, getRobotID(), 1); //Not sure what time goes in here, depends on travel 
		cout << "\nRobot " << getRobotID()->getID() << " enters mall at time: " << getTime() <<endl;
		break;
		}
    case 1: //Store arrival Author:Alexi 
		{
		//deliver all items
		//add event case 2
		if (DEBUGSTATE)
		{
			cout<<"\nRobot's delivery inventory: "<<endl;
			getRobotID()->getDests()->printInventory();
		}
		int newTime = getRobotID()->deliverItems(getTime());
		if (DEBUGSTATE)
			cout<<"adding new event of type 2"<<endl;
		mallEvents->addNewEvent(newTime, getRobotID(), 2);
		cout<<"\nRobot "<< getRobotID()->getID() << " arrives at store ( "<<getRobotID()->getDests()->getRow()<<", "<<getRobotID()->getDests()->getCol()<<" ) on Floor "<<((getRobotID()->getDests()->getFloor())+1)<<" at time "<<getTime()<<endl;
		getRobotID()->removeDest();
		
		break;
		}
    case 2: //Store departure Author: Alexi
		{
		tilePtr entrance = new Tile();
		*entrance = Mall[8][16][0];
		//Check eventlist
		cout<<"\nRobot "<<getRobotID()->getID()<<" leaves store ( "<<getRobotID()->getR()<<", "<<getRobotID()->getC()<<" ) on Floor "<<((getRobotID()->getF())+1)<<" at time: "<<getTime()<<endl;
		if(getRobotID()->checkDestsEmpty())//Evaluates to true if dests is empty
		{ 
			//Move towards entrance
			getRobotID()->addDest(entrance);
			if (DEBUGSTATE){
				//cout<<"Robot's destination list now: "<<endl;
				//getRobotID()->printDests();
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
    case 3: //Mall departure Author: Alexi
		{
		cout << "\nRobot " << getRobotID()->getID() << " has left the simulation at time: " <<getTime()<< endl;
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
		while(getShopperID()->getDest()->getInventory() != NULL)
		{
			getShopperID()->shopperApp(); //FIGURE OUT SHOPPER APP	  
		}
	  	{
		//Travel here
		int travelTime = travel(getRobotID(), SIZE);
		int newTime = (getTime()+ travelTime);
		//add arrival case
		mallEvents->addNewEvent( newTime, getRobotID(), 1); //Not sure what time goes in here, depends on travel 
		cout << "\nRobot " << getRobotID()->getID() << " enters mall at time: " << getTime() <<endl;
		break;
		}
      break;
    case 1:
      //run queue work
      break;
    case 2:
		{
	  	tilePtr entrance = new Tile();
		*entrance = Mall[8][16][0];
		//Check eventlist
		cout<<"\nShopper "<<getShopperID()->getID()<<" leaves store ( "<<getShopperID()->getR()<<", "<<getShopperID()->getC()<<" ) on Floor "<<((getShopperID()->getF())+1)<<" at time: "<<getTime()<<endl;
		if(getRobotID()->checkDestsEmpty())//Evaluates to true if dests is empty
		{ 
			//Move towards entrance
			getRobotID()->addDest(entrance);
			if (DEBUGSTATE){
				//cout<<"Robot's destination list now: "<<endl;
				//getRobotID()->printDests();
			}
			int exitTime = (getTime() + travel(getRobotID(), SIZE));
			// add new event 3
			mallEvents->addNewEvent(exitTime, getRobotID(), 3);
		} else {
		//move towards dests 
		int travelTime = travel(getRobotID(), SIZE);
		int newTime = travelTime + (getTime());
		//add event 1
		mallEvents->addNewEvent(newTime, getRobotID(), 1);
		}
		break;
		}
    case 3:
      break;
    case 4:
      	{
			cout << "\nShopper " << getShopperID()->getID() << " has left the simulation at time: " <<getTime()<< endl;
			break;
		}
    default:
      break;
    }
}

}

///////////////////////////////////////////////////////////////////////////////////
// default constructor  
 EventList::EventList() 
   : firstPtr( 0 ), lastPtr( 0 ), startPtr( 0 )
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
	  setStartPtr(newNode);
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
  EventNode *cur = getFirstPtr();
  while(cur != getLastPtr()){
    cur->print();
	//(cur->getRobotID())->printRobot();
    cur = cur->getNext();
  }
  //getLastPtr()->print();

}

void EventList::printFull(){
  EventNode *cur = getStartPtr();
  while(cur != getLastPtr()){
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
                                                                                    fcfs.cpp                                                                                            0000750 0027600 0027600 00000006421 12416604430 013260  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              #include <stdlib.h>
#include <iostream>
using namespace std;
#include "fcfs.h"
#include "queue.h"
#include "process.h"
#include "util.h"

// Forward Declarations
//void checkTimings(fcfs *toRun, process *proc);

// Initializes an FCFS scheduling simulator with the given
// list of processes to run.
fcfs::fcfs():queue(){
  set_curTime(0);
  set_finishedProcesses(new queue());
}

fcfs::fcfs(process *proc):queue(new queueNode(proc)){
  set_curTime(0);
  set_finishedProcesses(new queue());
}


// Runs a FCFS Simulation until completion, printing output
// to the console
void fcfs::run_fcfs() {
  // Will control whether to continue the simulation
  int running = 1;
  // Info printf
  cout<< "Starting FCFS scheduling simulation\n";

  while (running) {

    if(DEBUG1) cout<< "check if still running" <<endl;
    // See if the next process is null. If so, set running to 0 and break
    if (!get_front()) {
      running = 0;
      if(DEBUG1) cout<<"no longer running" <<endl;
      break;
    }
    if(DEBUG1)cout<<"still running" <<endl;
  
    // Pop the next process off of the scheduling queue 
    process *nextProc;
    pop(&nextProc);
  
    if(DEBUG1) cout<< "nextProc id: " << nextProc->get_pid()<<endl;

    ///////From here gonna update
    if(DEBUG1) cout<< "FCFS: Process "<< nextProc->get_pid()<< " started";
      
    // Check the timings so that the simulation time and wait times are correct
    checkTimings(nextProc);
  
    // Output starting stats to the file
    cout << "Process "<< nextProc->get_pid() << " started at " << get_curTime() * 100  << " ms, waited for " <<nextProc->get_waitTime() * 100 << ".\n";
  
    // Increment the clock, then add the process to the finished queue
    set_curTime(get_curTime() + nextProc->get_cpuTime());
    if(DEBUG1) cout<< "set curtime" <<endl;

    set_finishedProcesses(get_finishedProcesses()->enqueue(nextProc));

    if(DEBUG1)cout<<"set finished processes" <<endl;
  
    // Print the final leaving time
    cout << "Process " << nextProc->get_pid() << " finished at "<< get_curTime() * 100 <<" ms.\n";
  }

  DEBUG_PRINT("Ended main fcfs loop, starting averaging");

  // Output a couple of new lines to the output for formatting
  cout<<"\n\n--------SIMULATION COMPLETE---------\n";

  processesStats(finishedProcesses);

  // Flush and close the file
  cout<<"Ended FCFS simulation\n";
}

// Destroys a given FCFS scheduling simulator, freeing all
// remaining resources.
fcfs::~fcfs() {
  // Destory any remaining schedule queue elements
  delete finishedProcesses;
}

// Checks the timings of the incoming process.
// If there is still time before the process arrives,
// increment the clock to that point.
// If the process is past due, increment the wait
// time of the process appropriately
void fcfs::checkTimings(process *proc) {
  if (get_curTime() < proc->get_aTime()) set_curTime(proc->get_aTime());
  else proc->set_waitTime(get_curTime() - proc->get_aTime());
}


int fcfs::get_curTime(){ // converted by Max.
  return curTime;
}

void fcfs::set_curTime(int time){
  curTime = time;
}

queue *fcfs::get_finishedProcesses(){
  return finishedProcesses;
}

void fcfs::set_finishedProcesses(queue *newQueue){
  finishedProcesses = newQueue;
}
                                                                                                                                                                                                                                               globalItem.cpp                                                                                      0000750 0027600 0027600 00000004135 12417637266 014434  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              /* class implementation for global items
Author:Max Li*/
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
                                                                                                                                                                                                                                                                                                                                                                                                                                   init_mall.cpp                                                                                       0000644 0027600 0027600 00000012675 12417604233 014323  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              //  RoboMall Program
/* 
	Originally coded by Professor Robert Kinicki, adapted to C++ and the use of objects by Alexi Kessler
	
	init_mall fills in specific characteristics of all the locations on the First and Second Floors of RoboMall 
*/

#include<stdio.h>
#include "externals.h"


void printType(){
int i,j,k ;
char cell;

 for (k = First; k <= Second; k++)
 {
   printf("      ");
   for (j = MIN; j <= MAX; j++)
     printf("%2d",j);
   
   for (i = MIN; i <= MAX; i++)
   {
     printf("\n %2d   ",i);

     for (j = MIN; j <= MAX; j++)
     {
       if ((Mall[i][j][k]).getType() == INVALID)
	 cell = ' ';
       else
	 cell = 48 + (Mall[i][j][k]).getType();
       printf(" %c", cell);
     }
   }
   printf("\n                %d Floor Types\n\n", k);
 }
 return;
}

/* This print function serves to print out the settings
   of the step array by init_mall. This is useful to make
   sure this property has been set correctly.              */
   
void printStep(){
int i,j,k ;
char cell;

 for (k = First; k <= Second; k++)
 {
   printf("      ");
   for (j = MIN; j <= MAX; j++)
     printf("%2d",j);
   
   for (i = MIN; i <= MAX; i++)
   {
     printf("\n %2d   ",i);

     for (j = MIN; j <= MAX; j++)
     {
       if ((Mall[i][j][k].getStep()) == INVALID)
	 cell = ' ';
       else
	 cell = 48 + (Mall[i][j][k]).getStep();
       printf(" %c", cell);
     }
   }
   printf("\n                %d Floor Steps\n\n", k);
 }
 return;
}

/* init_mall initializes type and step
   based on characteristics of the two floors of RoboMall  */

void init_mall()
{
int i,j,k ;
int dir[8];

// First initialize sparse arrays type and step

 for (k = First; k <= Second; k++)
   for (i = MIN; i <= MAX+1; i++)
   for (j = MIN; j <= MAX+1; j++)

   //  INVALID means the robot should never go here!
   {
       (Mall[i][j][k]).setType(INVALID);
       (Mall[i][j][k]).setStep(INVALID);
	   (Mall[i][j][k]).setRow(i);
	   (Mall[i][j][k]).setCol(j);
	   (Mall[i][j][k]).setFloor(k);
	   
   }

 for (k = First; k <= Second; k++)
 {
   // The directions for the two floors differ
   if (k == First)
   {
     for (i = 0; i <= 7; i++)
       dir[i] = i;
   }
   else
   {
     for (i = 0; i <= 7; i++)
       dir[i] = (i+4)%8;
   }

   for (j = 6; j < 11; j++)
   { 
	 (Mall[MIN][j][k]).setType(One);
	 (Mall[MAX][j][k]).setType(One);
	 (Mall[j][MIN][k]).setType(One);
	 (Mall[j][MAX][k]).setType(One);

     (Mall[MIN][j][k]).setStep(dir[6]);
     (Mall[MAX][j][k]).setStep(dir[2]);
     (Mall[j][MIN][k]).setStep(dir[4]);
     (Mall[j][MAX][k]).setStep(dir[0]);
   }

   for (j = 1; j <= 13; j = j+3)
   {
     for (i = 0; i <= 2; i++)
     {
       (Mall[MID][j+i][k]).setType(One);
       (Mall[j+i][MID][k]).setType(One);

       (Mall[MID][j+i][k]).setStep(dir[2]);
       (Mall[j+i][MID][k]).setStep(dir[4]);
     }
   }

   for (i = 4; i <= 12; i = i+8)
   {
     (Mall[i][4][k]).setType(Store); 
	 (Mall[i][12][k]).setType(Store);
     (Mall[i][6][k]).setType(Store);
	 (Mall[i][10][k]).setType(Store);
     (Mall[6][i][k]).setType(Store);
	 (Mall[10][i][k]).setType(Store);
     (Mall[i][7][k]).setType(TwoWay);
	 (Mall[i] [9][k]).setType(TwoWay);
     (Mall[7][i][k]).setType(TwoWay);
	 (Mall[9][ i][k]).setType(TwoWay);
     (Mall[i][MID][k]).setType(Three);
	 (Mall[MID][i][k]).setType(Three);

     (Mall[i][MID][k]).setStep(dir[4]);
     (Mall[MID][i][k]).setStep(dir[2]);
   }

   (Mall[MID][MID][k]).setStep(dir[2]);
   for (j = 5; j >= 1; j--)
   {
     (Mall[6-j][j][k]).setType(One);
	 (Mall[16-j][10+j][k]).setType(One);

     (Mall[6-j][j][k]).setStep(dir[5]);
     (Mall[16-j][10+j][k]).setStep(dir[1]);
   }
	//bottom left, top right diagonals
   for (i = 1; i <= 5; i++)
   {
     (Mall[i][10+i][k]).setType(One);
	 (Mall[10+i][i][k]).setType(One);

     (Mall[i][10+i][k]).setStep(dir[7]);
     (Mall[10+i][i][k]).setStep(dir[3]);   
   }

   for (i = 3; i <= 13; i = i+10)
    (Mall[i][i][k]).setType(Next);
	(Mall[3][13][k]).setType(Next);
	(Mall[13][3][k]).setType(Next);
	(Mall[MID][MID][k]).setType(Elevator);
 } //end first large for loop
 
// printf("\nInit 2");
 (Mall[MIN][MID][First]).setType(Two);
 (Mall[MID][MIN][First]).setType(Two);
 (Mall[MID][MAX][Second]).setType(Two);
 (Mall[MAX][MID][Second]).setType(Two);

 for (i = 0; i <= 7; i++)
   dir[i] = i;

 for (k = First; k <= Second; k++)
 {
   (Mall[ 4][ 4][k]).setStep(dir[7]);
   (Mall[ 4][12][k]).setStep(dir[1]);
   (Mall[12][ 4][k]).setStep(dir[5]);
   (Mall[12][12][k]).setStep(dir[3]);

   for (j = 4; j <= 12; j = j+8)
   {
     (Mall[ 6][ j][k]).setStep(dir[4]);
	 (Mall[ 7][ j][k]).setStep(dir[4]);
     (Mall[ 9][ j][k]).setStep(dir[0]);
	 (Mall[10][ j][k]).setStep(dir[0]);
     (Mall[ j][ 6][k]).setStep(dir[2]);
	 (Mall[ j][ 7][k]).setStep(dir[2]);
     (Mall[ j][ 9][k]).setStep(dir[6]);
	 (Mall[ j][10][k]).setStep(dir[6]);
   }
 }
 (Mall[MIN][6] [First]).setStep(dir[5]);
 (Mall[10][MAX][Second]).setStep(dir[5]);
 (Mall[10][MIN][First]).setStep(dir[3]);
 (Mall[MIN][10][Second]).setStep(dir[3]);
 (Mall[MAX][10][First]).setStep(dir[1]);
 (Mall[6][MIN][Second]).setStep(dir[1]);
 (Mall[6][MAX][First]).setStep(dir[7]);
 (Mall[MAX][6][Second]).setStep(dir[7]);

 /* These two print functions show that type and step
    are correct.  They can be commented out once program */

 printType();
 printStep();

 return;
}  //end init_mall
                                                                   localItem.cpp                                                                                       0000640 0027600 0027600 00000003665 12417567424 014271  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              /* class implementation for local item, which is to be used to represent the local item stock of a store in program 5
Author of functions:Alexi Kessler */
#ifndef LOCALITEM_CPP
#define LOCALITEM_CPP

#include "globals.h"
#include "localItem.h"
#include <cstring>
//Constructors.

LocalItem::LocalItem(){
  name = "NULL";

}

LocalItem::LocalItem(string newName){
  name = newName;
}

LocalItem::LocalItem(string newName, int count){
  name = newName;
  localCount = count;
}

//Compares the member item to a new item.
//returns -1 new item is earlier than the current item, 0 if they are the same
// and 1 if new item is later than current item.
int LocalItem::id_compare(LocalItemPtr newLocalItem){

  if (newLocalItem == NULL){
    //cout<<"item to add is NULL !!!!!!!!!!!!!!!"<<endl;
    return -1;
  }
  else{
    //cout<<"Normal function"<<endl;
    string current = getName();
    
    string compare = newLocalItem->getName();

    //cout<<(newLocalItem == NULL)<<endl;

    std::string new_id = newLocalItem->getName();
    
    //cout<<"correctly works idcompare"<<endl<<flush;
    
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
}

//Setters and getters
string LocalItem::getName(){
  //cout<<name<<endl;
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
                                                                           movement.cpp                                                                                        0000644 0027600 0027600 00000006633 12417621446 014207  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              /* Functions for movement of robots in mall. Originally adapted from code by Professor Robert Kinicki, but now
modified to fit the new models.
Author: Alexi Kessler */

#ifndef MOVEMENT_CPP
#define MOVEMENT_CPP

#include <iostream>
#include "externals.h"
#include "robot.h"
//#include "decide.cpp"
#include "tile.h"

#define DEBUGTRAVEL 0
void printloc (int []);
bool IsEqual (int [], int []);
void d1(int [], int); 
void d2(int [], int[], int);
void d3(int [], int[], int);  
void next(int [], int [], int);
void twoway(int [], int [], int);
void elevator(int [], int[], int);

int move (int cur[], int des[], int size)
{

/* Choices {Invalid, One, Two, Three, Next, 
   TwoWay, Elevator,Store}              

   The main idea is to categorize the type of
   choice the robot has and use switch to process
   that choice.  type array keeps choice type for
   all mall locations.

*/
	int time = 0;
	//printf ("   type is %d", (Mall[cur[ROW]][cur[COL]][cur[FLOOR]]).getType());
	
	switch ((Mall[cur[ROW]][cur[COL]][cur[FLOOR]]).getType())
	{
    case Store:    
    case One:      d1(cur, SIZE);
                   break;
    case Two:      d2(cur,des,SIZE);
                   break;
    case Three:    d3(cur,des,SIZE);
                   break;
    case Next:     next(cur,des,SIZE);
                   break;
    case TwoWay:   twoway(cur,des,SIZE);
                   break;
    case Elevator: elevator(cur,des,SIZE);
                   break;
    case INVALID:
    default:
		printf("M: Lost in Mall at ");
		printloc(cur);
		printf("Type = %d\n",
        (Mall[cur[ROW]][cur[COL]][cur[FLOOR]]).getType());
        exit(EXIT_FAILURE);
  } //end switch
	
	time++;
	//Sim time used to be incremented here
	
  /*  This is a debug print in case you want to see individual
      robot steps.  

    printf("Time: %d Robot at ", simTime);
    printloc(cur);                        
  */
  return time;
}

/* travel function takes robot  from 'from' location to 'to' location */
int travel (robotPtr robot, int size)
{
	int from[SIZE];
	int to[SIZE];
	from[ROW] = robot->getR();
	from[COL] = robot->getC();
	from[FLOOR] = robot->getF();
	to[ROW] = (robot->getDests())->getRow();
	to[COL] = (robot->getDests())->getCol();
	to[FLOOR] = (robot->getDests())->getFloor();
	if (DEBUGTRAVEL)
	{
		cout<<"\nFrom Position: Row: "<<from[ROW]<<" Col: "<<from[COL]<<" Floor: "<<from[FLOOR]<<endl;
		cout<<"To Position: Row: "<<to[ROW]<<" Col: "<<to[COL]<<" Floor: "<<to[FLOOR]<<endl;
	}
	int cntr = 0;        // cntr used to check for infinite loop
	if (DEBUGTRAVEL)
	{
		printf("Time: %d Robot leaves ", simTime);
	}
	//printloc(from);

	// Loop until robot arrives at store or A1
	while(!IsEqual(from,to) &&
		(cntr < MAX_PATH))
	{
     // move controls robot's steps
     int t = move(from,to, SIZE);
     cntr++;
	}
	if (DEBUGTRAVEL)
	cout<<"Time to move to destination: "<<cntr<<endl<<endl;
	robot->setR(to[ROW]);
	robot->setC(to[COL]);
	robot->setF(to[FLOOR]);
	//robot->removeDest();
	if (cntr == MAX_PATH) //If caught in infinite loop
	{
     printf ("\n Infinite Loop"); 
     exit(EXIT_FAILURE);
	}
	return cntr;
 }
 
void printtravel(int tsimTime [][2], int robots)
{
  int i;
  printf ("Robot   Start Time   Finish Time\n");

  for (i=0; i < robots; i++)
    printf ("%3d  %11d  %12d\n", i+1, tsimTime[i][STIME], tsimTime[i][ETIME]);
  return;
}

#endif
                                                                                                     process.cpp                                                                                         0000750 0027600 0027600 00000004252 12417634026 014022  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              #ifndef PROCESS_CPP_
#define PROCESS_CPP_

//#include <stdlib.h>
//#include <stdio.h>
#include "process.h"
#include "util.h"
#include <iostream>
using std::cout;
using std::endl;
using std::flush;

// Mallocs space for a new process
process::process(int new_pid, int new_aTime, int new_cpuTime, int new_io) {;
  pid = new_pid;
  aTime = new_aTime;
  cpuTime = new_cpuTime;
  waitTime = 0;
  ioTime = new_io;
  remainTime = new_cpuTime;
}

process::process(){
  pid = -1;
  aTime = -1;
  cpuTime = -1;
  waitTime = -1;
  remainTime = -1;
}

// Compares two processes, returning 0 if the old
// process comes before the new process, 1 otherwise
int process::procLessThan(process *old) {
  if(DEBUG) {
    cout<< "in procCompare, aTime "<< get_aTime() <<endl<<flush;
    cout<< " old aTime "<<old->get_aTime()<<endl<<flush;
  }
  return get_aTime() <= old->get_aTime();
}


// Gets the difference between this wait time and the average wait time
float process::getDifference(float avg) {
  return get_waitTime() - avg;
}

// Creates a clone of the given process. This is malloced,
// be sure to free it later
process* process::cloneProc() {
  process *newProc = new process();
  newProc->set_pid(get_pid());
  newProc->set_aTime(get_aTime());
  newProc->set_cpuTime(get_cpuTime());
  newProc->set_waitTime(get_waitTime());
  newProc->set_remainTime(get_remainTime());
  return newProc;
}

int process::get_pid(){
  return pid;
}

int process::get_ioTime(){
  return ioTime;
}

void process::set_ioTime(int newTime){
  ioTime = newTime;
}

int process::get_aTime(){
  return aTime;
}

int process::get_cpuTime(){
  return cpuTime;
}

int process::get_waitTime(){
  return waitTime;
}

int process::get_remainTime(){
  return remainTime;
}

void process::set_pid(int newPid){
  pid = newPid;
}

void process::set_aTime(int newA){
  aTime = newA;
}

void process::set_cpuTime(int newC){
  cpuTime = newC;
}

void process::set_waitTime(int newW){
  waitTime = newW;
}

void process::set_remainTime(int newR){
  remainTime = newR;
}

process::~process(){
  if(DEBUG1) cout<< "in delete for process" <<endl;
}
#endif
                                                                                                                                                                                                                                                                                                                                                      prog5.cpp                                                                                           0000771 0027600 0027600 00000034514 12417636320 013406  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              #ifndef PROG5_CPP
#define PROG5_CPP

#include <iostream>
#include <string.h>
#include "globals.h"
#include "mallHead.h"
#include "tile.h"
#include "robot.h"
#include "localItem.h"
#include "eventList.h"
#include "externals.h"
#include "binTree.h"
#include "process.h"
#include "fcfs.h"
#include "rr.h"
#include "queue.h"
#include "util.h"
#include "queue.h"

#define DEBUG 0
#define DEBUGROBSIM 0

//#include "binTree.h"
//#include "item.h"
//#include "binTree.cpp"
//#include "store_functions.cpp"

//#include "small.cpp"
EventList *mallEvents = new EventList();

int main () //Author: Alexi
{
	int i,j, choice;
    int robotID;
    //EventList *mallEvents = new EventList();

    // R array holds robot location
    // S array holds next store location

    int robots, nextS[3];
	//stores[MAX_STORES];
	
	init_mall();
	instructions();
	cin>>choice;
	tilePtr tile0 = new Tile(2, 5, 12, 4, 3);
	
	switch (choice)
	{
		case 0: //Test robot class Author: Alexi
			{
				Robot R = *(new Robot(45));
				cout<<"New robot's ID: "<<R.getID()<<endl;
				cout<<"New robot's floor position: "<<R.getF()<<endl;
				R.setF(6);
				cout<<"Robot's floor position after setter: "<<R.getF()<<endl;
				cout<<"Robot's destination list before setter:\n";
				tilePtr testTile = new Tile();
				testTile = (R.getTile(1));
				if (testTile == NULL)
				{
					cout<<"Tile is null!\n";
				}
				else
				{
					(*testTile).printTile();
				}
				cout<<"Adding tile0 to destination list\n";
				R.addDest(tile0);
				testTile = (R.getTile(1));
				cout<<"Robot's destination list after setter:\n";
				if (testTile == NULL)
				{
					cout<<"Tile is null!\n";
				}
				else
				{
					(*testTile).printTile();
				}
				break;
			}
			//weird spacing problems
		case 1:
			{
				cout<<"Check Robots in RobotsNotInSim: "<<RobNotInSim<<endl;
				scanRobots(); 
				(RobotsNotInSim[0]).printRobot();
				cout<<"Check Robots in RobotsNotInSim: "<<RobNotInSim<<endl;
				break;
			}
		case 2: //Test robot movement Author: Alexi
			{
				tilePtr testDest1 = new Tile(7, 7, 4, 4, 1);
				tilePtr testDest2 = new Tile(7, 4, 6, 4, 0);
				robotPtr testRob = new Robot(32, 1, 8, 16, 0, testDest1);
				testRob->addDest(testDest2);
				
				int t1 = travel(testRob, SIZE);
				int t2 = travel(testRob, SIZE);
				break;
			}
		case 3: //Test deliverItem Author: Alexi
			{
				tilePtr testDest1 = new Tile(7, 7, 4, 4, 1);
				tilePtr testDest2 = new Tile(7, 4, 6, 4, 0);
				
				LocalItemPtr testItem1 = new LocalItem("A5", 5);
				LocalItemPtr testItem2 = new LocalItem("L7", 1);
				LocalItemPtr testItem3 = new LocalItem("D8", 10);
				LocalItemPtr testItem4 = new LocalItem("Z2", 7);
				
				testDest1->addToInventory(testItem1);
				testDest1->addToInventory(testItem2);
				testDest1->addToInventory(testItem3);
				testDest2->addToInventory(testItem4);
				
				robotPtr testRob = new Robot(32, 1, 8, 16, 0, testDest1);
				testRob->addDest(testDest2);
				
				//(testRob->getDests())->printInventory();

				//Test that item inventory initialized correctly
				cout<<"Printing out Robot's dest1 inventory delivery:"<<endl;
				(testRob->getDests())->printInventory();
				cout<<"size of delivery list: "<<((testRob->getDests())->sizeInventory())<<endl;
				
				//Travel to first destination
				int t1 = travel(testRob, SIZE);
			
				//See how long it takes to deliver first item
				int deliveryTime;
				deliveryTime = testRob->deliverItem();
				(testRob->getDests())->removeInventoryItem();
				cout<<"Mall Store Inventory after delivery: "<<endl;
				Mall[4][4][1].printInventory();
				cout<<"Time that the robot will finish delivering its first item: "<<deliveryTime<<endl;
				
				//Remove first item from inventory list			
				cout<<"\nRemoved delivered items from dest Inventory"<<endl;
				cout<<"Checking for successful removal. Current Item list: "<<endl;
				(testRob->getDests())->printInventory();
				cout<<"Inventory at store:"<<endl;
				Mall[(testDest1->getRow())][(testDest1->getCol())][(testDest1->getFloor())].printInventory();
				
				//See how long it takes to deliver second item
				deliveryTime = testRob->deliverItem();
				(testRob->getDests())->removeInventoryItem();
				cout<<"Mall Store Inventory after delivery: "<<endl;
				Mall[4][4][1].printInventory();
				cout<<"Time that the robot will finish delivering its second item: "<<deliveryTime<<endl;
				
				//Remove second item from inventory list			
				cout<<"\nRemoved delivered items from dest Inventory"<<endl;
				cout<<"Checking for successful removal. Current Item list: "<<endl;
				(testRob->getDests())->printInventory();
				cout<<"Inventory at store:"<<endl;
				Mall[(testDest1->getRow())][(testDest1->getCol())][(testDest1->getFloor())].printInventory();
				
				//See how long it takes to deliver third item
				deliveryTime = testRob->deliverItem();
				(testRob->getDests())->removeInventoryItem();
				cout<<"Mall Store Inventory after delivery: "<<endl;
				Mall[4][4][1].printInventory();
				cout<<"Time that the robot will finish delivering its third item: "<<deliveryTime<<endl;
				
				//Remove third item from inventory list			
				cout<<"\nRemoved delivered items from dest Inventory"<<endl;
				cout<<"Checking for successful removal. Current Item list: "<<endl;
				(testRob->getDests())->printInventory();
				cout<<"Inventory at store:"<<endl;
				Mall[(testDest1->getRow())][(testDest1->getCol())][(testDest1->getFloor())].printInventory();
				//After checking that it's ok to remove destination, do so
				testRob->removeDest();
				
				//Move to second location
				cout<<"Moving to second destination:"<<endl;
				int t2 = travel(testRob, SIZE);
				
				//Try delivering item at new destination
				deliveryTime = testRob->deliverItem();
				(testRob->getDests())->removeInventoryItem();
				cout<<"Mall Store Inventory after delivery: "<<endl;
				Mall[(testDest2->getRow())][(testDest2->getCol())][(testDest2->getFloor())].printInventory();
				cout<<"Time that the robot will finish delivering its first item: "<<deliveryTime<<endl;
				
				//Remove first item from inventory list			
				cout<<"\nRemoved delivered items from dest Inventory"<<endl;
				cout<<"Checking for successful removal. Current Item list: "<<endl;
				(testRob->getDests())->printInventory();
				cout<<"Inventory at store:"<<endl;
				Mall[(testDest2->getRow())][(testDest2->getCol())][(testDest2->getFloor())].printInventory();
				break;
			}
		case 4: //Test of deliverItems() Author: Alexi
			{
				int deliveryTime;
				tilePtr testDest1 = new Tile(7, 4, 6, 4, 1);
				tilePtr testDest2 = new Tile(7, 4, 6, 4, 0);
				
				LocalItemPtr testItem1 = new LocalItem("A5", 5);
				LocalItemPtr testItem2 = new LocalItem("L7", 1);
				LocalItemPtr testItem3 = new LocalItem("D8", 10);
				LocalItemPtr testItem4 = new LocalItem("Z2", 7);
				
				testDest1->addToInventory(testItem1);
				testDest1->addToInventory(testItem2);
				testDest1->addToInventory(testItem3);
				testDest2->addToInventory(testItem4);
				
				robotPtr testRob = new Robot(40, 1, 8, 16, 0, testDest1);
				testRob->addDest(testDest2);
				
				int t1 = travel(testRob, SIZE);
				deliveryTime = testRob->deliverItems(t1);
				
				cout<<"Time taken to deliver all first destination items: "<<deliveryTime<<endl;
				cout<<"Checking for successful removal. Current Item list: "<<endl;
				(testRob->getDests())->printInventory();
				cout<<"Inventory at store:"<<endl;
				Mall[(testDest1->getRow())][(testDest1->getCol())][(testDest1->getFloor())].printInventory();
				
				break;
			}
		case 5: //Test of EventList and EventNode Author: Max
			{
				EventList *testList = new EventList();
				Robot *testRobot = new Robot(5);
				Shopper *testShopper = new Shopper(7);
				
				//if(DEBUG) cout<< "passed assignment"<<endl;
				/*
				testList->addNewEvent(0, testRobot, 0);
				testList->addNewEvent(0, testShopper, 1);
				testList->addNewEvent(5, testRobot, 0);
				testList->addNewEvent(4, testShopper, 3);
				testList->addNewEvent(7, testRobot, 2);
				*/
				scanRobots();

				if(DEBUG) cout<<"Passed adding"<<endl;
				testList->print();
				break;
			}
		case 6://test scanRobots Author: Alexi
			{
				scanRobots();
				mallEvents->print();
				break;
			}
		case 7: //Test checkState Author: Alexi
			{
				scanRobots();
				//need to checkState
				(mallEvents->getFirstPtr())->checkState();
				mallEvents->print();
				(mallEvents->getFirstPtr())->checkState();
				mallEvents->print();
				//runRobSim();
			break;
			}
		case 8: //Test robSim Author: Alexi
			{
				scanRobots();
				runRobSim();
				//mallEvents->getStartPtr()->print();
				//mallEvents->getStartPtr()->getNext()->print();
				//mallEvents->getStartPtr()->getNext()->getNext()->print();
				//mallEvents->getStartPtr()->getNext()->getNext()->getNext()->print();
				//mallEvents->printFull();
				break;
			}
			
			case 9: //Test tree functionality Author: Max
			
			{
				Tree *testTree = new Tree();
				GlobalItem *base = new GlobalItem("L1");
				GlobalItem *node1 = new GlobalItem("F2");
				GlobalItem *node2 = new GlobalItem ("X1");

				StorePtr store1 = newStore(1, 2, 0, 3, NULL);
				StorePtr store2 = newStore(2, 4, 1, 10, NULL);
				StorePtr store3 = newStore(3, 1, 4, 100, NULL);
				StorePtr store4 = newStore(1, 9, 13, 50, NULL);

				testTree->addItem(base, store1);
				testTree->addItem(node1, store1);
				testTree->addItem(node1, store2);
				testTree->addItem(node2, store3);
				testTree->addItem(node2, store4);
				cout<< "After 9!"<<endl;
				break;
			} 
			
		case 10: //Test ShopperApp Author:Alexi
			{
			LocalItemPtr testItem1 = new LocalItem("A5", 5);
			LocalItemPtr testItem2 = new LocalItem("L7", 1);
			LocalItemPtr testItem3 = new LocalItem("D8", 10);
			LocalItemPtr testItem4 = new LocalItem("Z2", 7);
			
			Shopper *testShopper = new Shopper(34);
			tilePtr dummyTile = new Tile(-1, -1, -1, -1, -1);
			dummyTile->addToInventory(testItem1);
			dummyTile->addToInventory(testItem2);
			dummyTile->addToInventory(testItem3);
			dummyTile->addToInventory(testItem4);
			
			dummyTile->printInventory();
			testShopper->addDest(dummyTile);
			testShopper->printDests();
			testShopper->shopperApp();
			testShopper->printDests();
			
			break;
			}
		default:
				cout<<"Improper or no test input";
				break;
	}
}

void scanRobots(){ //scan in Robots Author: Max
  int numBots = 0, i = 0, j = 0, newItemCount;
  tilePtr toAdd;

  if(DEBUG) cout << "Type number of bots" <<endl;
  cin >> numBots;
  

  for (i = 0; i < numBots; i++){
    int tempStoreCnt;
    if(DEBUG) cout<<"Type number of stores for robot "<< i <<endl;
    cin >> tempStoreCnt;
    RobotsNotInSim[i].setNumStore(tempStoreCnt);
    RobotsNotInSim[i].setID(i);
    if(DEBUG) cout << "Scanned Robot " << i <<endl;
	RobNotInSim++;
  } 

  //To run for each robot
  for(i = 0; i < numBots; i++){

    //To run for each store
    for (j = 0; j < RobotsNotInSim[i].getNumStore(); j++){
      int rowIn, colIn, floorIn, numItems;
      std::string itemName;

      if(DEBUG) cout <<"input location of store " << j <<" r, c, f:"<<endl;
      cin >> rowIn;
      cin >> colIn;
      cin >> floorIn;

      if(DEBUG) cout << "input number of items" << endl;
      cin >> numItems;

      toAdd = new Tile(Mall[rowIn][colIn][floorIn].getType(), Mall[rowIn][colIn][floorIn].getStep(), rowIn, colIn, floorIn);
      
      //To run for each item in a store
      for (int k = 0; k < numItems; k++){

	if(DEBUG) cout<< "Input name and quantity of item number "<< k <<endl;
	cin >> itemName;
	cin >> newItemCount;
	LocalItemPtr newItem = new LocalItem(itemName);
	newItem->setCount(newItemCount);
	toAdd->addToInventory(newItem);
	if(DEBUG) cout<< "Item added!" << endl;
      }

      RobotsNotInSim[i].addDest(toAdd);
      //RobotsNotInSim[i].getTile(i)->setPosition(rowIn,colIn,floorIn);
      //cout<< RobotsNotInSim[i].getTile(1)->getRow() << "~" << RobotsNotInSim[i].getTile(1)->getCol()<<endl;
      if(DEBUG) cout << "scanned store " << j << " for robot " << i << endl;
    }
    //if(DEBUG) cout << RobotsNotInSim[i].getID()<<endl;
    //Robot *curRobot = new Robot();
    //*curRobot = RobotsNotInSim[i];
    mallEvents->addNewEvent(25*i, &RobotsNotInSim[i], 0);
	//cout << "Robot " << i << " enters mall at time: " <<(25*i)<<endl;
  }
  if(DEBUG) {
   // mallEvents->print();
  }
}


void readShoppers(){ //Reads in Shoppers Author: Max
  int numShoppers, arrival, numItems, itemCnt;
  std::string itemName;

  //-1 -1 -1 location, type, etc means hasn't been shopper-apped yet.
  Tile *shopperTile = new Tile(-1, -1, -1, -1, -1);
  
  cout<< "Input number of shoppers: "<<endl;
  cin >> numShoppers;
  for (int i = 0; i < numShoppers; i++){
    cout<< "Input arrival time: "<< endl;
    cin >> arrival;
    cout<<"Input number of items to buy" <<endl;
    cin >> numItems;
    
    Shopper *tempShopper = new Shopper(arrival, itemCnt);
    for (int j = 0; j < itemCnt; j++){
      
      cout << "Input item name:" <<endl;
      cin >>  itemName;
      cout << "input item count:" <<endl;
      cin >> itemCnt;
      
      LocalItem *newItem = new LocalItem(itemName, itemCnt);
      shopperTile->addToInventory(newItem);
    }
    tempShopper->addDest(shopperTile);
    mallEvents->addNewEvent(arrival, tempShopper, 0);
  }
  
}


//Returns the end time
int runRobSim(){
  EventList *robEvent = mallEvents;
  if(robEvent == NULL){
    cout << "Event list is empty!" <<endl;
    return -1;
  }
  else{
    EventNode *curr = robEvent->getFirstPtr();
    EventNode *prev = NULL;
    while(curr != NULL){
		curr->checkState();
		curr = curr->getNext();
		if (DEBUGROBSIM){
			cout<<"Operated on event. New event list is as follows"<<endl;
			if(mallEvents != NULL)
			  mallEvents->print();
		}
    }
    //return prev->getTime();
    return 1;
  }

}

int runShopSim(){
  EventList *shopEvent = mallEvents->getShopperEvents();
  if(shopEvent == NULL)
    {
      cout <<"Event list is empty!" <<endl;
      return -1;
    }
  else{
    EventNode *curr = shopEvent->getFirstPtr();
    EventNode *prev = NULL;
    while(curr != NULL){
      curr->checkState();
      curr = curr->getNext();
    }
    return prev->getTime();
  }

}

  
#endif
                                                                                                                                                                                    queue.cpp                                                                                           0000750 0027600 0027600 00000021553 12416604430 013466  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              #ifndef QUEUE_CPP_
#define QUEUE_CPP_

#include <iostream>
using std::endl;
using std::cout;
using std::flush;
#include <stdlib.h>
#include <math.h>
#include "queue.h"
#include "util.h"
#include "process.h"
#include "fcfs.h"
#include "rr.h"

#define DEBUG_DEL 1
// Pops the next element off of the queue
// This returns a pointer to the next head element,
// and stores a pointer to the process in the given
// out location. This frees the given queue element,
// so do not attempt to use it again. To just get the
// process element, use the peak method

queue* queue::pop(process **out) {
  if(DEBUG1) cout<< "in pop" <<endl<<get_front()<<endl <<flush;
  queueNode* next = get_front()->get_next();
  if(DEBUG1) cout<< "before peak" <<endl<<flush;
  peak(out);
  if(DEBUG1) cout << "Peaked in pop"<<endl<<flush;
  delete get_front();
  //set_front(next);
  if(DEBUG1) cout <<"after delete" <<endl;
  queue *nextQ = new queue(next);
  return nextQ;
}

// Peaks at the next element of the queue, and stores
// a pointer to the element at the given location.
void queue::peak(process **out) {
  if (get_front()) *out = (get_front())->get_proc();
}

// Enqueues an element in a given list, mallocing a new
// queueNode structure for the element. If null is passed 
// in for head, a new queue will be created
queue* queue::enqueue(process *proc) {
  if(DEBUG1) cout << "in enqueue"<< endl;

  //if(DEBUG1) cout <<"can use getfront()"<<endl<<(get_front())<<endl<<flush;

  if (get_front() == NULL) {
    if(DEBUG1) cout <<"no front" << endl<<flush;

    queueNode *newQ = new queueNode(proc);
    return new queue(newQ);
  } else {
    if(DEBUG1) cout<< "has front"<<endl<<flush;
    get_front()->set_next(get_front()->get_next()->enqueue(proc));
    return new queue(get_front());
  }
}

queueNode* queueNode::enqueue(process *proc){
  if(!this){
    return new queueNode(proc);
  }
  else{
    set_next(get_next()->enqueue(proc));
    return this;
  }
}


// Inserts the given proces into the queue, sorted by
// cpu time. Returns a pointer to the new head of the queue
queue* queue::sortedInsert(process *proc){
  if(DEBUG) {
    cout<< "in sorted Insert!"<< endl << flush;
  }
  if(DEBUG) cout<< "passed get_front assignment : "<<(get_front() == NULL) << endl <<flush;

  if (get_front()==NULL){
    if(DEBUG) cout<<"front is Null"<<endl<<flush;
    queueNode *newQ = new queueNode(proc);
    return new queue(newQ);
  }
  else if(proc->procLessThan(get_front()->get_proc())){
    if(DEBUG) {
      cout<<"new process less than front"<<endl << flush;
      fflush(stdout);
    }
    queueNode *newQ = new queueNode(proc);
    return new queue(newQ);
  }
  else{
    if(DEBUG) {
      cout <<"new process is greater than front"<<endl <<flush;
    }
    get_front()->set_next(get_front()->get_next()->sortedInsert(proc));
    return new queue(get_front());
  }
}



queueNode* sortedInsert(queueNode *head, process *proc_n){

  if(head) head->get_proc();
  if(DEBUG) cout<<"in new sort, head is null "<<(head == NULL)<<endl;//<<"process aTime is "<< head->get_proc()->get_aTime() <<endl<<flush; //   " proc is less than " <<(proc->procLessThan(head->get_proc())) <<endl<<flush;
  if(head == NULL){
    if(DEBUG) cout<<"no front" <<endl<<flush;
    queueNode *newQ = new queueNode(proc_n);
    if(DEBUG) cout << newQ->get_proc() <<endl; 
    return newQ;
  }
  else if(proc_n->procLessThan(head->get_proc())){
    if(DEBUG) cout<<"process is less than the front process" <<endl<<flush;
    queueNode *newQ = new queueNode(proc_n);
    newQ->set_next(head);
    return newQ;
  }
  else{
    if(DEBUG) cout<<"process is greater than front process"<<endl<<flush;
    head->set_next(sortedInsert(head->get_next(), proc_n));
    return head;
  }

}



queueNode* queueNode::sortedInsert(process *proc) {
  if(DEBUG) cout << "is this (ptr) null?  "<< (this == NULL) <<endl <<flush;
  if (this == NULL) {
    // Empty case, return a new element
    queueNode *newQ = new queueNode(proc);
    return newQ;
  } else if (proc->procLessThan(get_proc())) {
    queueNode *newQ = new queueNode(proc);
    newQ->set_next(this);
    return newQ;
  } else {
    // New process arrives after, insert after
    set_next(get_next()->sortedInsert(proc));
    return this;
  }
}

// Gets the average wait times of all the processes in the list
float queue::getQueueAverage(){
  queueNode *cur;
  int total = 0, count = 0;

  // Loop until we reach the tail of the list
  for (cur = get_front(); cur; cur = cur->get_next()) {
    total += cur->get_proc()->get_waitTime();
    count++;
  }

  return ((float) total)/count;
}

// Calculates the variance of the queue, given the average wait time
// The formula for variance is sum((waitTime_i - mean)^2)/n
float queue::getQueueVariance(float avg) {
  // Accumulators for the total and count
  float total = 0;
  int count = 0;
  queueNode *cur;

  // Loop until we reach the tail of the list
  for (cur = get_front(); cur; cur = cur->get_next()) {
    float diff = get_front()->get_proc()->getDifference(avg);
    total += pow(diff, 2);
    count++;
  }

  return total/count;
}

// Calculates the average and variance of all given processes. The forumla
// for response time is finish time - arrival time. The formula
// for variance is EX^2 - (EX)^2, where X is the average response
// time 
void queue::processEX(float *avg, float *var) {
  float x, x2;
  int count;
  queueNode *cur;

  for (cur = get_front(); cur; cur = cur->get_next()) {
    int repTime = cur->get_proc()->get_waitTime() + cur->get_proc()->get_cpuTime();
    x += repTime;
    x2 += pow(repTime, 2);
    count++;
  }

  (*avg) = x / count;
  (*var) = (x2 / count) - pow((*avg), 2);
}

// Gets the minimum wait time of the queue
int queue::getQueueMin() {
  // If head is null, just return 0
  if (!get_front()) {
    return 0;
  }
  
  int min = get_front()->get_proc()->get_waitTime() + get_front()->get_proc()->get_cpuTime();
  queueNode *cur;

  for (cur = get_front(); cur; cur = cur->get_next()) {
    min = min < cur->get_proc()->get_waitTime() + cur->get_proc()->get_cpuTime() ? min : cur->get_proc()->get_waitTime() + cur->get_proc()->get_cpuTime();
  }

  return min;
}

// Gets the maximum wait time of the queue
int queue::getQueueMax() {
  // If head is null, just return 0
  if (!get_front()) {
    return 0;
  }
  
  int max = get_front()->get_proc()->get_waitTime() + get_front()->get_proc()->get_cpuTime();
  queueNode *cur;

  for (cur = get_front(); cur; cur = cur->get_next()) {
    max = max > cur->get_proc()->get_waitTime() + cur->get_proc()->get_cpuTime() ? max : cur->get_proc()->get_waitTime() + cur->get_proc()->get_cpuTime();
  }

  return max;
}

// Clones the given queue, and the process elements within.
// These are malloced, be sure to free them later
queue* queue::cloneQueue(queue *sign) {
  if (get_front()) {
    if(DEBUG1) cout << "run clone" <<endl;
    queue* newQ = new queue(new queueNode(get_front()->get_proc()->cloneProc()));
    newQ->get_front()->set_next(get_front()->get_next()->cloneQueue());
    return newQ;
  } else {
    return NULL;
  }
}

fcfs* queue::cloneQueue(fcfs *sign){
  if (get_front()) {
    if(DEBUG1) cout << "run clone" <<endl;
    fcfs* newQ = new fcfs(get_front()->get_proc()->cloneProc());
    newQ->get_front()->set_next(get_front()->get_next()->cloneQueue());
    return newQ;
  } else {
    return NULL;
  }
}

rr* queue::cloneQueue(rr *sign, int slice){
  if (get_front()) {
    if(DEBUG1) cout << "run clone" <<endl;
    rr* newQ = new rr(get_front()->get_proc()->cloneProc(), slice);
    newQ->get_front()->set_next(get_front()->get_next()->cloneQueue());
    return newQ;
  } else {
    return NULL;
  }
}


 queueNode* queueNode::cloneQueue(){
   if(this){

     queueNode *newQ = new queueNode(get_proc()->cloneProc());
     if(DEBUG1) cout <<newQ->get_proc()->get_pid() <<endl;
     newQ->set_next(get_next()->cloneQueue());
     return newQ;
   }
     else{
       return NULL;
     }
 }

// Frees the entire queue, and the process elements contained within
queue::~queue() {
  if(DEBUG_DEL) cout<< " in delete for queue" <<endl;
  if (get_front()) {
    delete get_front()->get_next();
    if(DEBUG_DEL) cout<<" deleted next" <<endl;
  }
}

 queueNode::~queueNode(){
   if(DEBUG_DEL) cout << "in delete for queueNode"<<endl;
   // if(this){
   if(0){
   if(get_proc())
       delete get_proc();
   }
   //if(DEBUG_DEL) cout<< " deleted proc"<<endl;
 }

// Conveniece helper for creating new queue elements and 
// giving them a process
 queueNode::queueNode(process *proc) {
   set_next(NULL);
  set_proc(proc);
}

 queue::queue(queueNode *newQ){
   front = newQ;
}


queueNode *queueNode::get_next(){
  return next;
}

void queueNode::set_next(queueNode *newQ){
  next = newQ;
}

process *queueNode::get_proc(){
  return proc;
}

void queueNode::set_proc(process *newP){
  proc = newP;
}

queueNode *queue::get_front(){
  if(front == NULL)
    return NULL;
  else
    return front;
}

void queue::set_front(queueNode *newQ){
  front = newQ;
}

queue::queue(){
  front = NULL;
}

#endif
                                                                                                                                                     queueUtil.cpp                                                                                       0000750 0027600 0027600 00000001302 12416345031 014311  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              #include <iostream>
using namespace std;
#include "util.h"
#include "queue.h"

// Processes all of the stats for a given queue, and prints
// them to a given file
void processesStats(queue *stats) {
  float avg, var;
  
  // Calculate the average and variance
  stats->processEX(&avg, &var);
  
  // Print the average and variance
  cout << "The mean response time for all processes was "<<  avg * 100 << " ms\n";
  cout << "The response time variance for all processes was " << var * 100 << " ms\n";

  // Print the max and min wait times
  cout << "The shortest wait time was "<< stats->getQueueMin() *100 << " ms\n";
  cout << "The longest wait time was " << stats->getQueueMax() * 100 << " ms\n";
  
}
                                                                                                                                                                                                                                                                                                                              robot.cpp                                                                                           0000750 0027600 0027600 00000011233 12417626513 013470  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              /* Class implementation for the robots that deliver items in program 5
Author of functions: Alexi Kessler unless stated otherwise*/
#ifndef ROBOT_CPP
#define ROBOT_CPP

#include <cstddef>
#include "robot.h"
#include "tile.h"
#include "localItem.h"
#include "externals.h"

#define DELIVER 0
#define DEBUGDELIVER 0 

#include <iostream>
using namespace std;



//Constructors
Robot::Robot()
{
	//cout<<"Running Robot Constructor\n";
	ID = 0;
	r = 8;
	c = 16;
	f = 0;
	numStore = 0;
	Dests=NULL;
}

Robot::Robot(int id)
{
	ID = id;
	r = 8;
	c = 16;
	f = 0;
	numStore = 0;
	Dests=NULL;
}

Robot::Robot(int id, int stores)
{
	ID = id;
	numStore = stores;
	r = 8;
	c = 16;
	f =  0;
	Dests=NULL;
}

Robot::Robot(int id, int stores, int row, int col, int floor)
{
	ID = id;
	numStore = stores;
	r = row;
	c = col;
	f = floor;
	Dests=NULL;
}

Robot::Robot(int id, int stores, int row, int col, int floor, tilePtr dest)
{
	ID = id;
	numStore = stores;
	r = row;
	c = col;
	f = floor;
	Dests=dest;
}

//Basic int getters and setters
int Robot::getID()
{
	return ID;
}
void Robot::setID(int id)
{
	ID = id;
}
int Robot::getR()
{
	return r;
}
void Robot::setR(int row)
{
	r = row;
}
int Robot::getC()
{
	return c;
}
void Robot::setC(int col)
{
	c = col;
}
int Robot::getF()
{
	return f;
}
void Robot::setF(int floor)
{
	f = floor;
}
int Robot::getNumStore(){
  return numStore;
}
void Robot::setNumStore(int store){
  numStore = store;
}

//Tile getters and setter
Tile *Robot::getTile(int spot) 
{
	//return (*Dests).traverse(spot);
	if ((Dests)==NULL)
	{
		return NULL;
	}
	else 
	{
		return Dests;
	}
}
Tile *Robot::getDests() 
{
	//return (*Dests).traverse(spot);
	if ((Dests)==NULL)
	{
		return NULL;
	}
	else 
	{
		return Dests;
	}
}
void Robot::addDest(tilePtr newTile)
{
	if (Dests==NULL)
	{
		Dests = newTile;
	}
	else
	{
		tilePtr curr = NULL;
		tilePtr prev = NULL;
		curr = Dests;
		while (curr!=NULL)
		{
			prev = curr;
			curr = curr->getNextTile();
		}
		prev->setNextTile(newTile);
	}
}
void Robot::removeDest() 
{
	if (Dests==NULL) //Shouldn't ever happen
	{
		cout<<"Dests is empty, impossible to remove destination!\n";
	} 
	else 
	{
		tilePtr curr = NULL;
		tilePtr temp = NULL;
		temp = Dests;
		curr = Dests->getNextTile();
		Dests = curr;
		delete(temp);
	}
}
//Check to see if there are any destinations left
bool Robot::checkDestsEmpty()
{
	return (Dests==NULL);
}

int Robot::deliverItem()
{
	//Space for add to global
	int r, c, f, time;
	r = Dests->getRow();
	c = Dests->getCol();
	f = Dests->getFloor();
	LocalItemPtr itemToAdd = Dests->getInventory();
	time = itemToAdd->getCount();
	if (DEBUGDELIVER){
		cout<<"\nAdding item: "<<endl;
		itemToAdd->printLocalItem();
		cout<<"to store inventory\n"<<endl;
		Mall[r][c][f].printInventory();
	}
	Mall[r][c][f].addToInventory(itemToAdd);  //Add to local inventory
	if (DEBUGDELIVER)
	{
		cout<<"\nAdded item to store inventory"<<endl;
		//printing Mall Store inventory after addition"<<endl;
		//Mall[r][c][f].printInventory();
	}
	return time;
}
int Robot::deliverItems(int startTime) 
{
	int totalTime = 0;
	int singleTime = 0;
	int counter = 0;
	int numItems;
	numItems = Dests->sizeInventory();
	if (DELIVER)
		{
		//printDests();
		cout<<"numItems: "<<numItems<<endl;
		}
	tilePtr dest = getDests();
	LocalItemPtr invPtr = dest->getInventory();
	cout<<"\nRobot "<<ID<<" delivers the following items to store ( "<<dest->getRow()<<" ,"<<dest->getCol()<<" ) at time "<<startTime<<endl;
	dest->printInventory();
	for (counter = 0; counter<numItems; counter++)
	{
		
		singleTime = deliverItem();
		if (DELIVER) 
			cout<<"Amount of time taken to deliver individual item: "<<singleTime<<endl;
		Dests->removeInventoryItem();
		totalTime+=singleTime;
		if (DELIVER) 
			cout<<"Total time after delivery of item: "<<totalTime<<endl;
	}
	if (DELIVER)
		cout<<"Deliver Items exiting normally"<<endl;
	return (totalTime+startTime);
}

//Print Functions
void Robot::printRobot() 
{
	cout<<"Printing data for Robot"<<ID<<endl;
	cout<<"Position: Row: "<<r<<" Col: "<<c<<" Floor: "<<f<<endl;
	cout<<"Number of Destinations: "<<numStore<<endl;
	printDests();
}
void Robot::printDests(){ 
  if(Dests==NULL){
    cout<< "NULL" << endl;
  }
  else{
    tilePtr curr = NULL;
    tilePtr prev = NULL;
    curr = Dests;
    while (curr!=NULL)
      {
	curr->printTile();
	cout<<"Inventory of Dest:"<<endl;
	curr->printInventory();
	prev = curr;
	curr = curr->getNextTile();
      }
    cout<< "\nEnd of Destination List" <<endl<<endl<<endl;

  }
}
#endif
                                                                                                                                                                                                                                                                                                                                                                     rr.cpp                                                                                              0000750 0027600 0027600 00000011712 12416604430 012761  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              #ifndef RR_CPP_
#define RR_CPP_

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

#include "rr.h"
#include "process.h"
#include "queue.h"
#include "util.h"

// Forward Declarations
void processArrive(rr *toRun);

// Initializes a RR scheduling simulator with the given
// list of processes to run
rr::rr(process *newProc, int sliceN):queue(new queueNode(newProc)) {
  curTime = 0;
  runningQueue = new queue();
  finishedProcesses = new queue();
  slice = sliceN;
}

// Runs a RR simulation until completion, printing output
// to the console
void rr::runRR(){
  // Controls the loop
  int running = 1;
  // Info printf
  cout << "Starting RR scheduling simulator\n";

  while (running) {
    
    //if(DEBUG1) cout<< get_schedQueue()<< endl;

    // Enqueue new processes
    processArrive();

    if(DEBUG1) cout<<"Processes Enqueued"<<get_runningQueue()<<endl;


    // If there are tasks on the queue, run them for the slice
    if (get_runningQueue()->get_front()) {
      // Get the next process from the queue
      process *next = new process();
      process **nextPtr = &next;
      if(DEBUG1) cout<<"before set running queue"<<endl<<get_runningQueue()->get_front()<<endl;

      set_runningQueue(get_runningQueue()->pop(nextPtr));
      if(DEBUG1) cout<< (*nextPtr)->get_pid()<<endl;
      next = *nextPtr;


      if(DEBUG1) cout<<"after set running queue" <<endl;

      // Increment the clock and decrement the remaining time. If time is > 0, then requeue the process
      // If not, then remove the process, add it to the finished queue, and increment its waitTime
      
      if(DEBUG1) cout << next <<endl;

      if ((next->get_remainTime() - get_slice()) > 0) {
	if(DEBUG1) cout<<"Process is not complete " << next->get_pid() << endl;

	next->set_remainTime( next->get_remainTime() - get_slice());
	if(DEBUG1) cout<<"remain time after" << get_slice() << "ms update " << next->get_remainTime();

	set_curTime( get_curTime() + get_slice());
	set_runningQueue(get_runningQueue()->enqueue(next));
	cout << "Process " << next->get_pid() << " has run for " << get_slice() * 100  << " ms, "<< next->get_remainTime() * 100  << " ms remaining\n";
	continue;
      } else {

	if(DEBUG1) cout<< "Process completed "<<  next->get_pid() <<endl;

	set_curTime( get_curTime() +  next->get_remainTime());
	next->set_remainTime(0);
	next->set_waitTime(get_curTime() - (next->get_aTime() + next->get_cpuTime()));

	if(DEBUG1) cout<< next->get_pid() <<endl;
	set_finishedProcesses(get_finishedProcesses()->enqueue(next));
	cout << "Process " <<next->get_pid() <<" finished at " << get_curTime() * 100  << " ms\n";
	continue;
      }
    } else {
      DEBUG_PRINT("No process in the queue");

      // If there are processes left, advance to that process's arrival time. Otherwise, we're done
      if (get_schedQueue()->get_front()) {
	process *next;
	get_schedQueue()->peak(&next);
	set_curTime(next->get_aTime());
	//DEBUG_PRINT("Advanced clock to %d ms", toRun->curTime * 100);
	continue; 
      } else {
	//DEBUG_PRINT("Finished RR scheduling at %d ms, now calculating stats", toRun->curTime * 100);
	running = 0;
	break;
      }
    }
  }

  // Output a couple of new lines to the output for formatting
  cout<< "\n\n--------SIMULATION COMPLETE---------\n";
  
  processesStats(finishedProcesses);

  // Flush and close the file
  cout<< "Ended RR simulation\n";
}

// Destroys a given RR scheduling simulator, freeing all
// remaining resources
rr::~rr() {
  // Free the scheduling queue
  delete schedQueue;
  delete runningQueue;
  delete finishedProcesses;
}

// Removes all arriving processes for the current time
// and adds them to the scheduling queue
void rr::processArrive() {

  int moreProcesses = get_schedQueue() ? 1 : 0;
  while (moreProcesses) {
    process *proc = NULL;
    get_schedQueue()->peak(&proc);
    if (proc && get_curTime() >= proc->get_aTime()) {
      if(DEBUG1) cout<< "Process has arrived at the scheduling queue"<<endl;

      set_schedQueue(get_schedQueue()->pop(&proc));

      //if(DEBUG1) cout<< get_schedQueue()->get_front() <<endl;
      set_runningQueue(get_runningQueue()->enqueue(proc));
    } else {
      moreProcesses = 0;
    }
  }
}


int rr::get_curTime(){
  return curTime;
}

int rr::get_slice(){
  return slice;
}

queue *rr::get_schedQueue(){
  return schedQueue;
}

queue *rr::get_runningQueue(){
  return runningQueue;
}

queue *rr::get_finishedProcesses(){
  return finishedProcesses;
}

rr *rr::set_curTime(int time){
  curTime = time;
  return this;
}

rr *rr::set_slice(int sliceTime){
  slice = sliceTime;
  return this;
}

rr *rr::set_schedQueue(queue *newQ){
  schedQueue = newQ;
  return this;
}

rr *rr::set_runningQueue(queue *newQ){
  runningQueue = newQ;
  return this;
}

rr *rr::set_finishedProcesses(queue *newQ){
  finishedProcesses = newQ;
  return this;
}

#endif
                                                      shopper.cpp                                                                                         0000640 0027600 0027600 00000007467 12417632201 014026  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              /* Class implementation for the shoppers that purchase items in program 5
Author: Alexi Kessler */
#ifndef SHOPPER_CPP
#define SHOPPER_CPP

#include <cstddef>
#include "robot.h"
#include "tile.h"
#include "shopper.h"
#include "globals.h"
#include "globalItem.h"
#include "localItem.h"
#include "binTree.h"
#include "externals.h"

#include <iostream>
using namespace std;
//Constructors
Shopper::Shopper()
{
	cout<<"Running Shopper Constructor\n";
	ID = r = c = f = numStore = 0;
	Dests=NULL;
}

Shopper::Shopper(int id)
{
	ID = id;
	r = c = f = numStore = 0;
	Dests=NULL;
}

Shopper::Shopper(int id, int stores)
{
	ID = id;
	numStore = stores;
	r = c = f =  0;
	Dests=NULL;
}

//Basic int getters and setters
int Shopper::getID()
{
	return ID;
}
void Shopper::setID(int id)
{
	ID = id;
}
int Shopper::getR()
{
	return r;
}
void Shopper::setR(int row)
{
	r = row;
}
int Shopper::getC()
{
	return c;
}
void Shopper::setC(int col)
{
	c = col;
}
int Shopper::getF()
{
	return f;
}
void Shopper::setF(int floor)
{
	f = floor;
}
//Tile getters and setter
Tile *Shopper::getDest()
{
	//return (*Dests).traverse(spot);
	if ((Dests)==NULL)
	{
		return NULL;
	}
	else 
	{
		return Dests;
	}
}
void Shopper::addDest(tilePtr newTile)
{
	if (Dests==NULL)
	{
		Dests = newTile;
	}
	else
	{
		tilePtr curr = NULL;
		tilePtr prev = NULL;
		curr = Dests;
		while (curr!=NULL)
		{
			prev = curr;
			curr = curr->getNextTile();
		}
		prev->setNextTile(newTile);
	}
}

//Written by Max

void Shopper::shopperApp(){

  //return NULL;  

  LocalItem *listInv = Dests->getInventory();
  LocalItem *curr = listInv;
  LocalItem *prev = NULL;
  //LocalItem *newList = new LocalItem();

  if(listInv == NULL){
    cout << "Calling shopperApp with no items"<<endl;
  }

  else{
    while(curr != NULL){
      GlobalItem *search = globalTree->getRoot()->findItem(curr);
      store *storeInsert = *(search->getStores());
      if(search != NULL && (storeInsert->iCount) > (curr->getCount())){
	LocalItem *itemAdd = new LocalItem(curr->getName(), storeInsert->iCount);
	Tile *storeTile =new Tile();
	*storeTile = Mall[storeInsert->x][storeInsert->y][storeInsert->z];
	Tile *tileAdd = new Tile(storeTile->getType(), storeTile->getStep(), storeTile->getRow(), storeTile->getCol(), storeTile->getFloor());
	tileAdd->addToInventory(itemAdd);
	addDest(tileAdd);
      }
      prev = curr;
      curr = curr->getNext();
    }
  }


  
  /*
int numItems;
  if(itemList == NULL){
    cout << "invalid input to shopperApp"<<endl;
    return NULL;
  }
  else{
    LocalItemPtr curr = itemList;
    //LocalItemPtr prev = NULL;
    while(curr != NULL){
      numItems++;
      curr = curr->getNext();
    }

    //For each item to look, traverse the global item tree and find a store
    //for(int i = 0; i < numItems; i++){

    Tile *locations = new Tile();

      if(itemTree->findItem(itemList)){
	storePtr curStore = itemTree->findItem(itemList)->getStores();
	
	if(curStore != NULL && curStore->numItems >= itemList->getCount()){
	  locations->setPosition(curStore->x, curStore->y, curStore->z);
	  locations->addToInventory(itemList);
	}//end storeItems > item count

      }//end in tree
      //Advance item in that list.
      itemList = itemList->getNext();
      return locations;



    //}//end for each

  } //end while

  */
}

void Shopper::printDests(){ 
  if(Dests==NULL){
    cout<< "NULL" << endl;
  }
  else{
    tilePtr curr = NULL;
    tilePtr prev = NULL;
    curr = Dests;
    while (curr!=NULL)
      {
	curr->printTile();
	cout<<"Inventory of Dest:"<<endl;
	curr->printInventory();
	prev = curr;
	curr = curr->getNextTile();
      }
    cout<< "\nEnd of Destination List" <<endl<<endl<<endl;

  }
}
#endif
                                                                                                                                                                                                         small.cpp                                                                                           0000750 0027600 0027600 00000002171 12417636035 013454  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              // Set of  small useful functions
#ifndef SMALL_C
#define SMALL_C
#include <iostream>
#include "externals.h"


// debug function 
void printloc(int cell[])
{
  printf("row = %d col = %d floor = %d\n",
	 cell[0], cell[1], cell[2]);
  return;
}

/* IsEqual tests to see if robot has
   arrived at destination.          */
bool IsEqual(int now[], int des[])
{
  if ((now[0] == des[0]) &&
      (now[1] == des[1]) &&
      (now[2] == des[2]))
    return true;
  else
    return false;
}

void instructions()
{
	cout<<"Choice 0 tests: Robot getter/setters Robot tileAdd\n";
	cout<<"Choice 1 tests: Scanning in Robots"<<endl;
	cout<<"Choice 2 tests: Travel function taking robotPtr"<<endl;
	cout<<"Choice 3 tests: deliverItem()"<<endl;
	cout<<"Choice 4 tests: deliverItems()"<<endl;
	cout<<"Choice 5 tests: EventList and EventNode"<<endl;
    cout<<"Choice 6 tests: scanRobots()"<<endl;
    cout<<"Choice 7 tests: checkState()"<<endl;
	cout<<"Choice 8 tests: runRobSim()"<<endl;
	cout<<"Choice 9 tests: tree"<<endl;
	cout<<"Choice 10 tests: shopperApp"<<endl;

	cout<<"Please enter test choice\n";
}
#endif
                                                                                                                                                                                                                                                                                                                                                                                                       stage1.cpp                                                                                          0000644 0027600 0027600 00000000700 12417254226 013524  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              #ifndef STAGE1_CPP
#define STAGE1_CPP

void stage1 ()
{
	//First need to read in all the robots 
	//Then begin by adding in the first robot at time 0
	//While loop, RobotsNotInSim is not empty
		//Increment Robots
	//While loop, Robots in Sim not empty
		//increment Robots
}

void incrementRobots()
{
	//For loop, every Robot in RobotsInSim
		//Move one step towards destination (incrementRobot?)
	//Increment simTime
}
#endif
                                                                store_functions.cpp                                                                                 0000750 0027600 0027600 00000012241 12417637573 015577  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              /* Functions to be used for stores in global Items
Author: joint effort*/
#ifndef STOREFUNCTION_CPP
#define STOREFUNCTION_CPP
#include "globals.h"
#include "globalItem.h"
//#include "item.cpp"
#define DEBUGSTORE 0
class GlobalItem;
bool debugAddStore = false;

// If stores are the same, return 0, if the new store has more items than the current store, return 
// 1 to tell the outer function to insert before the current store, if current store has less count 
// than new store then return -1 to tell the outer function to check the next store.  Any remaining 
// functionality yet to be implemented.

StorePtr newStore(int xPos, int yPos, int zPos, int count, StorePtr next)
{
  StorePtr nStore = new store();
  nStore->x = xPos;
  nStore->y = yPos;
  nStore->z = zPos;
  nStore->iCount = count;
  nStore->nextStore = next;
  return nStore;
}

int store_compare(StorePtr currentStore, StorePtr newStore){ //Author: Max
  if (currentStore == NULL){
	return 1;
  } else if (currentStore->x == newStore->x && currentStore->y == newStore->y && currentStore->z == newStore->z) {
    return 0;
  } else if((currentStore->iCount) <= (newStore->iCount)){
    return 1;
  }
  else if((currentStore->iCount) > (newStore->iCount))
    return -1;
 else return -5;
}

//Given a pointer to the head pointer, inserts a new store in
//decreasing item count order.
//void addStore(StorePtr *sPtr, StorePtr newStore) //Author: Max

void addStore(GlobalItem *itPtr, StorePtr newStore)
{
  int store_comp, storeExists = 0;
  StorePtr previousPtr = new store();
  StorePtr currentPtr = new store();
  StorePtr *sPtr;
  sPtr = itPtr->getStores();
  
  //iPtr->setStores(itPtr->getStores());

  previousPtr = NULL;
	if (debugAddStore){ //Test to see if sPtr is null
		cout<<"Printing sPtr:\n";
		if (sPtr == NULL){
			cout << "sPtr is Null\n";
		} else {
		  //printStore(*sPtr);
		}
		cout<<"Printing newStore:\n";
		printStore(newStore);
	}


	if (sPtr == NULL){ //if Null then Store ** is NULL so trying to use *sPtr, meaning a Store *, makes a seg fault
		*sPtr = new store();
		(*sPtr) = newStore;
		//cout<<"set beginning of list"<<endl;
	} 
	else {
	  
	  currentPtr = *sPtr;
	  
	  //Test traversal

	  while(currentPtr!= NULL){
	    if(store_compare(currentPtr, newStore) == 0)
	      {
		if(DEBUGSTORE) cout<< "found a repeat" <<endl;
		(newStore->iCount) += (currentPtr->iCount);
		removeStore(sPtr, currentPtr);
		itPtr->setStores(sPtr);
		addStore(itPtr, newStore);
		return;
	      }
	    if(DEBUGSTORE) cout<<"current store" << currentPtr->x << ' ' << currentPtr->y << ' ' << currentPtr->z<<endl;

	    previousPtr = currentPtr;
	    currentPtr = currentPtr->nextStore;
	  }

	  currentPtr = *sPtr;
	  previousPtr = NULL;

	  store_comp = store_compare(currentPtr, newStore);
	  //cout<<"store compare:"<<store_comp<<endl;
		
	  //test
	  if(DEBUGSTORE)cout<<"Current x, y, z: "<< currentPtr->x << currentPtr->y << currentPtr->z <<endl;
	  if(DEBUGSTORE)cout<<"new x, y, z: " << newStore->x << newStore->y << newStore->z<<endl;
	  if(DEBUGSTORE)cout<<"Store Compare: "<<store_comp<<endl;
			
	  while(store_comp == -1 && currentPtr != NULL ){
	    previousPtr = currentPtr;
	    currentPtr = currentPtr->nextStore;
	    store_comp = store_compare(currentPtr, newStore);
	    
	    //cout<<store_comp<<endl;
	  }
		//Check conditions for the while to end.
		//If at front of list (and not the same as the front of the list, place in the front.
		if(previousPtr == NULL && store_compare(currentPtr, newStore) != 0){
		newStore->nextStore = *sPtr;
		*sPtr = newStore;
		}
		//If the store location of the current store is the same as the new one,
		//add the number of items in the current store to the new store and
		//call the function


		//Elsewise, insert the store normally.
		else if(store_comp == 1){
		  previousPtr->nextStore = newStore;
		  newStore->nextStore = currentPtr;
		}
		else
		{
		  //cout<<"Something went wrong in addStore." << endl;
		  //cout<<endl;
		}
	}

	itPtr->setStores(sPtr);	
	//cout<<"end of add store"<<endl;
}

void removeStore(StorePtr *sPtr,StorePtr toRemove){ //author: Max
  StorePtr tempPtr;
  StorePtr previousPtr;
  StorePtr currentPtr;

  if(*sPtr == toRemove){
    tempPtr = *sPtr;
    *sPtr = (*sPtr)->nextStore;
    //delete tempPtr;
  }
  else{
    previousPtr = *sPtr;
    currentPtr = (*sPtr)->nextStore;

    while(currentPtr != NULL && currentPtr != toRemove){
      previousPtr = currentPtr;
      currentPtr = currentPtr->nextStore;
    }
    if(currentPtr != NULL){
      tempPtr = currentPtr;
      previousPtr->nextStore = currentPtr->nextStore;
      //delete tempPtr;
    }
  }
}

void printStore(StorePtr store){  //Author: Alexi
	if (store == NULL){
		cout<<"StorePtr is NULL"; 
	} else {
		cout<<"Store's Position is x:" << store->x <<" y:" << store->y <<" z:" << store->z <<endl;
		cout<<"Store's iCount is:" << store->iCount<<endl;
	}
}

void printStoreList(StorePtr *store){ //Author: Alexi
	StorePtr curr;
	StorePtr prev;
	
	prev = NULL;
	
	if ((*store) == NULL){
		cout << "Store List is empty\n";
	} else {
	  //cout<< "Store iCount:" << (*store)->iCount<<endl;
		curr = *store;
		while (curr!=NULL){
			printStore(curr);
			prev = curr;
			curr = curr->nextStore;
		}
		cout<< "Hit end of store list\n";
	}

}
#endif
                                                                                                                                                                                                                                                                                                                                                               tile.cpp                                                                                            0000750 0027600 0027600 00000010513 12417617573 013306  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              /* Implementation of tile functions
Author of functions: Alexi Kessler unless stated otherwise */
#ifndef TILE_CPP
#define TILE_CPP

#include "globals.h"
#include "tile.h"
#include <iostream>

#define DEBUGTILE 0
#define DEBUGREMOVE 0

using namespace std;

//Constructor

Tile::Tile()
{
	type = step = r = c = f = 0;
	nextTile=NULL;
	inventory = NULL;
}

Tile::Tile(int t, int s, int row, int col, int floor)
{
	type = t;
	step = s;
	r = row;
	c = col;
	f = floor;
	nextTile=NULL;
	inventory = NULL;
}

void Tile::setType(int t)
{
	type = t;
}

int Tile::getType()
{
	return type;
}

void Tile::setStep(int s)
{
	step = s;
}

int Tile::getStep()
{
	return step;
}

void Tile::setPosition(int row, int col, int floor)
{
	r = row;
	c = col;
	f = floor;
}

int Tile::getRow()
{
	return r;
}

int Tile::getCol()
{
	return c;
}

int Tile::getFloor()
{
	return f;
}

void Tile::setRow(int row)
{
	r = row;
}

void Tile::setCol(int col)
{
	c = col;
}

void Tile::setFloor(int floor)
{
	f = floor;
}
		
void Tile::setNextTile(Tile *newTilePtr)
{
	nextTile = newTilePtr;
}

Tile * Tile::getNextTile()
{
	return nextTile;
}
void Tile::printTile()
{
	cout<<"\nPrinting Tile\n";
	cout<<"---------------\n";
	cout<<"Tile type: "<<type<<endl;
	cout<<"Tile step: "<<step<<endl;
	cout<<"Tile position: Row: "<<r<<" Col: "<<c<<" Floor: "<<f<<endl;
	/*
	if (nextTile==NULL)
	{
		cout<<"Not connected to any other tile\n";
	}
	else 
	{
		cout <<"There is a tile after this one\n";
	} */
}

LocalItemPtr Tile::getInventory(){ //Max
  return inventory;
}

void Tile::setInventory(LocalItemPtr newInventory){ //Max
  inventory = newInventory;
}

int Tile::sizeInventory()
{
	LocalItemPtr curr = NULL;
	LocalItemPtr prev = NULL;
	curr = inventory;
	int count = 0;
	if (curr == NULL)
	{
		return 0;
	} else {
		while (curr!=NULL)
		{
			prev = curr;
			curr = curr->getNext();
			count++;
		}
		return count;
	}
}
void Tile::addToInventory(LocalItemPtr toAdd){ //Max
  //If inventory is null, set inventory to toAdd.
	
	if(DEBUGTILE)cout<<"Currently running addToInventory"<<endl;

	if(getInventory() == NULL) //Inventory empty
	{
		if(DEBUGTILE) cout<<"Inventory empty, adding item"<<endl;
		inventory = toAdd;
		toAdd = toAdd->getNext();
		//inventory->setNext(NULL);
	return;
	}

  else{
    if(DEBUGTILE) cout<<"else"<<endl;
    LocalItemPtr curr = NULL;
    LocalItemPtr prev = NULL;
    curr = inventory;
    
    //if(DEBUGTILE) cout<<"after init"<<endl;

	if(curr->getNext() == NULL){
      //cout<<"HERE, getNext null"<<endl;
      inventory->setNext(toAdd);
    }
    else{
      //Currently adding to end of list, unsorted.  Can sort using id_compare(newItem)=> returns 0 if same, 1 if new is lower in 
      while (curr != NULL && curr->id_compare(toAdd) != 0 && curr->getNext() != NULL){
	prev = curr;
	//if(DEBUGTILE) cout<<"before getNext"<<endl;
	curr = curr->getNext();
	//if(DEBUGTILE) cout<<"end of while"<<endl;
      }
      
      if(DEBUGTILE) cout<<"after while addToInventory"<<endl;
      
      if(curr == NULL){
	if(DEBUGTILE) cout << "prev->setNext(toAdd)"<<endl;
	prev->setNext(toAdd);
	//toAdd->setNext(inventory);
      //setInventory(toAdd);
      }
      else if(curr->getNext() == NULL){
	if(DEBUGTILE)cout<< "curr->getNext() == NULL"<<endl;
	curr->setNext(toAdd);
      }
      else{
	if(DEBUGTILE) cout<< "curr->id_compare != 0"<<endl;
	curr->setCount(curr->getCount() + toAdd->getCount());
      }
    }
  }
}

void Tile::removeInventoryItem() //Alexi
{
	if(!inventory)
	{
		cout<<"The inventory is empty, can't remove anything!"<<endl;
	}
	else 
	{
		if (DEBUGREMOVE)
			cout<<"removing item"<<endl;
		LocalItemPtr curr = NULL;
		LocalItemPtr prev = NULL;
		curr = inventory;
		prev = curr;
		curr = curr->getNext();
		inventory = curr;
		prev -> setNext(NULL);
	}
}

void Tile::printInventory() //Alexi
{
	if (inventory==NULL){
		cout<<"Can't print Inventory, it is empty"<<endl;
	} else {
		LocalItemPtr curr = NULL;
		curr = inventory;
		if(curr->getNext() == NULL){
		  curr->printLocalItem();
		}
		else{
		  while (curr != NULL)
		    {
		      curr->printLocalItem();
		      curr = curr->getNext();
		    }
		}
		cout<<"End of inventory list"<<endl;
	}
}
#endif
                                                                                                                                                                                     util.cpp                                                                                            0000750 0027600 0027600 00000001302 12417633200 013303  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              #include <iostream>
using namespace std;
#include "util.h"
#include "queue.h"

// Processes all of the stats for a given queue, and prints
// them to a given file
void processesStats(queue *stats) {
  float avg, var;
  
  // Calculate the average and variance
  stats->processEX(&avg, &var);
  
  // Print the average and variance
  cout << "The mean response time for all processes was "<<  avg * 100 << " ms\n";
  cout << "The response time variance for all processes was " << var * 100 << " ms\n";

  // Print the max and min wait times
  cout << "The shortest wait time was "<< stats->getQueueMin() *100 << " ms\n";
  cout << "The longest wait time was " << stats->getQueueMax() * 100 << " ms\n";
  
}
                                                                                                                                                                                                                                                                                                                              binTree.h                                                                                           0000750 0027600 0027600 00000000712 12417637011 013373  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              /* class header for itemTree adapted from Program 4 code
Max did the adaptation*/
#ifndef BINTREE_H
#define BINTREE_H
#include "globals.h"
#include "globalItem.h"

class Tree{
	private:
		GlobalItemPtr root;
	public:
		Tree();
		bool isEmpty();
		bool addItem(GlobalItemPtr newItem, StorePtr newStore);
		void PrintItem(GlobalItemPtr item);
		void PrintTree();
		GlobalItemPtr getRoot();
	private:
		void PrintAll(GlobalItemPtr item);
		int test;
};

#endif
                                                      eventList.h                                                                                         0000750 0027600 0027600 00000003514 12417637460 013773  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              // Fig. 20.3: Listnode.h Pearson Copyright 2008
// Template ListNode class definition. 
#ifndef LISTNODE_H 
#define LISTNODE_H
#include <iostream>
using std::cout;
using std::endl;
// forward declaration of class List required to announce that class 
// List exists so it can be used in the friend declaration at line 13 
class EventList; 
class Robot;
class Shopper;
 
class EventNode 
{ 
  friend class EventList; // make List a friend 
  
 public: 
   EventNode(); // constructor 
   EventNode(int, Robot *, int);
   EventNode(int, Shopper *, int);
   
   int getTime();
   Robot *getRobotID();
   Shopper *getShopperID();
   int get_eType();

   EventNode *getNext(){return nextPtr;}
   void setNext(EventNode *newNext){ 
     if (newNext != NULL)
       nextPtr = newNext;
     else {
       cout<<"passing NULL"<<endl;
       nextPtr = NULL;
     }
   }
   void print();

   void checkState();

 private: 
   int time;
   Robot *robotID;
   Shopper *shopperID;
   int eType;
   EventNode *nextPtr; // next node in list 
}; // end class ListNode 


 class EventList 
{ 
 public: 
  EventList(); // constructor 
  ~EventList(); // destructor 
  
  void addNewEvent(int, Robot *, int);
  void addNewEvent(int, Shopper *, int);

  void addNode(EventNode *newNode);
  EventNode *getFirstPtr(){return firstPtr;}
  EventNode *getLastPtr(){return lastPtr;}
  EventNode *getStartPtr(){return startPtr;}
  void setFirstPtr(EventNode *first){firstPtr = first;}
  void setLastPtr(EventNode *last){lastPtr = last;}
  void setStartPtr(EventNode *start){startPtr = start;}

		EventList *getShopperEvents();
		bool isEmpty() const; 
		void print(); 
		void printFull();
	private: 
		EventNode *firstPtr; // pointer to first node 
		EventNode *lastPtr; // pointer to last node 
		EventNode *startPtr;
  // utility function to allocate new node 
   
}; // end class List 

#endif
                                                                                                                                                                                    externals.h                                                                                         0000640 0027600 0027600 00000000764 12417637134 014023  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              // externals.h
/*The list of the globals that are in main but
external to all other components and the global defs.      */

#include "globals.h"
#include "tile.h"
//#include "globalItem.h"
#include "robot.h"
#include "shopper.h"
#include "eventList.h"
#include "binTree.h"

extern Tile Mall[MAX+1][MAX+1][2];
extern int simTime;
extern EventList *mallEvents;
extern Tree *globalTree;

extern Robot RobotsNotInSim[MAX_ROBOTS];
extern Shopper ShoppersNotInSim[MAX_SHOPPERS];

//extern Tree *ItemTree;
            fcfs.h                                                                                              0000750 0027600 0027600 00000001005 12416604430 012716  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              #ifndef FCFS_H_
#define FCFS_H_

//class queue;
//#include "queue.cpp"
#include "queue.h"

class fcfs : public queue{
 public:
  fcfs();
  fcfs(process*);
  void run_fcfs();
  void checkTimings(process *);

  int get_curTime();
  void set_curTime(int);
  //queue *get_schedQueue();
  //void set_schedQueue(queue *);
  queue *get_finishedProcesses();
  void set_finishedProcesses(queue *);
  ~fcfs();
 private:
  int curTime;
  //queue *schedQueue;
  queue *finishedProcesses;
};


#endif
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           globalItem.h                                                                                        0000750 0027600 0027600 00000001360 12417637322 014067  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              /* Class header for global items
This part was a joint effort. */
#ifndef ITEM_H
#define ITEM_H
#include "globals.h"
class Tile;


class GlobalItem{
  friend void addStore(StorePtr *sPtr, StorePtr newStore);
	public:
		GlobalItem();
		GlobalItem(string newName);
		int id_compare(GlobalItem *newNode);

		string getName();
		void setName(string);
		GlobalItem *getLeft();
		GlobalItem *getRight();
		void setLeft(GlobalItem *);
		void setRight(GlobalItem *);
		StorePtr *getStores();
		void setStores(StorePtr *);
		void printGlobalItem();

		GlobalItem *findItem(LocalItem *);
		
	private:
		string name;
		StorePtr *stores;
		GlobalItem *left;
		GlobalItem *right;
};

typedef GlobalItem *GlobalItemPtr; 

#endif
                                                                                                                                                                                                                                                                                globals.h                                                                                           0000640 0027600 0027600 00000002461 12417630271 013430  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              /* globals.h

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
                                                                                                                                                                                                               localItem.h                                                                                         0000644 0027600 0027600 00000001304 12417347354 013724  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              /* class definition for local item, which is to be used to represent the local item stock of a store in program 5
Author:Alexi Kessler */
#ifndef LOCALITEM_H
#define LOCALITEM_H

#include <string>
#include "globals.h"


class LocalItem{
	public:
		LocalItem();
		LocalItem(std::string newName);
		LocalItem(std::string newName, int count);
		
		int id_compare(LocalItem *newNode);

		std::string getName();
		void setName(std::string);
		int getCount();
		void setCount(int);
		LocalItem *getNext();
		void setNext(LocalItem *);
		void printLocalItem();
		
	private:
		std::string name;
		int localCount;
		LocalItem *nextItem;
};

typedef LocalItem *LocalItemPtr; 

#endif
                                                                                                                                                                                                                                                                                                                            mallHead.h                                                                                          0000640 0027600 0027600 00000001704 12417630550 013513  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              #ifndef MALLHEAD_H
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
                                                            process.h                                                                                           0000750 0027600 0027600 00000001565 12416345031 013465  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              #ifndef PROCESS_H_
#define PROCESS_H_

#include <stdio.h>

// A process is defined by the process ID, the arrival time (in 100 millisecond intervals), 
// and the cpu time (in 100 millisecond intervals). It keeps track of how much time it has
// waited, and how much time it has left in it's run
class process{
 public:
  process();
  process(int, int, int, int);
  int procLessThan(process *);
  float getDifference(float);
  process *cloneProc();
  ~process();

  int get_pid();
  int get_aTime();
  int get_cpuTime();
  int get_waitTime();
  int get_remainTime();
  int get_ioTime();

  void set_pid(int);
  void set_aTime(int);
  void set_cpuTime(int);
  void set_waitTime(int);
  void set_remainTime(int);
  void set_ioTime(int);

 private:
  int pid;
  int aTime;
  int cpuTime;
  int waitTime;
  int ioTime;
  int remainTime;
};

#endif
                                                                                                                                           queue.h                                                                                             0000750 0027600 0027600 00000002221 12416604430 013122  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              #ifndef QUEUE_H_
#define QUEUE_H_
#include "process.h"

class fcfs;
class rr;

// A generic member of the queue, which has a reference to
// the process in the queue and the next element of the queue


class queueNode{

  friend class queue;
 public:
  queueNode(process *);
  queueNode *get_next();
  queueNode *enqueue(process *);
  queueNode *sortedInsert(process *);
  queueNode *cloneQueue();
  void set_next(queueNode *);
  process *get_proc();
  void set_proc(process *);
  ~queueNode();
  
 private:
  queueNode *next;
  process *proc;
};

class queue{
 public:
  queue();
  queue( queueNode *);
  
  queue *cloneQueue(queue *);
  fcfs *cloneQueue(fcfs *);
  rr *cloneQueue(rr *, int);

  queue *pop( process **);
  void peak(process **);
  queue* enqueue(process *);
  queue* sortedInsert(process *);
  void processEX(float *, float *);
  int getQueueMin();
  int getQueueMax();
  float getQueueAverage();
  float getQueueVariance(float);
  ~queue();

  queueNode *get_front();
  void set_front(queueNode*);

 private:
  queueNode *front;
};//

queueNode *sortedInsert(queueNode *, process *);
#endif
                                                                                                                                                                                                                                                                                                                                                                               queueUtil.h                                                                                         0000750 0027600 0027600 00000000424 12416345031 013762  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              
#ifndef UTIL_H_
#define UTIL_H_
#include "queue.h"
#include <iostream>

#define DEBUG 0
#define DEBUG1 1

#define DEBUG_PRINT(...)

// Processes all of the stats for a given queue, and prints
// them to a given file
void processesStats(queue *stats);

#endif
                                                                                                                                                                                                                                            robot.h                                                                                             0000640 0027600 0027600 00000001577 12417553601 013142  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              /* A class header for the robots that deliver items in program 5
Author: Alexi Kessler */
#ifndef ROBOT_H
#define ROBOT_H
#include "tile.h"

class Robot
{
	public:
		Robot();
		Robot(int id);
		Robot(int id, int stores);
		Robot(int id, int stores, int row, int col, int floor);
		Robot(int id, int stores, int row, int col, int floor, tilePtr dest);
		
		int getID();
		void setID(int);
		int getR();
		void setR(int);
		int getC();
		void setC(int);
		int getF();
		void setF(int);
		int getNumStore();
		void setNumStore(int);
		Tile *getTile(int);
		
		tilePtr getDests();
		void addDest(tilePtr);
		void removeDest();
		bool checkDestsEmpty();
		
		int deliverItem();
		int deliverItems(int);
		
		void printRobot();
		void printDests();
	private:
		int ID;
		int r, c, f;
		int numStore;
		tilePtr Dests;
};

typedef Robot *robotPtr;

#endif
                                                                                                                                 rr.h                                                                                                0000750 0027600 0027600 00000001112 12416604430 012417  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              #ifndef RR_H_
#define RR_H_

#include "queue.h"
class rr:public queue
{
 public:
  rr( process *, int);
  void runRR();
  int get_curTime();
  int get_slice();
  queue *get_schedQueue();
  queue *get_finishedProcesses();
  queue *get_runningQueue();
  void processArrive();
  ~rr();

  rr *set_curTime(int);
  rr *set_slice(int);
  rr *set_runningQueue(queue *);
  rr *set_schedQueue(queue *);
  rr *set_finishedProcesses(queue *);

 private:
  int curTime;
  int slice;
  queue *schedQueue;
  queue *runningQueue;
  queue *finishedProcesses;
};

#endif
                                                                                                                                                                                                                                                                                                                                                                                                                                                      shopper.h                                                                                           0000640 0027600 0027600 00000001274 12417632202 013462  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              /* A class header for the shoppers that purchase items in program 5
Author: Alexi Kessler */
#ifndef SHOPPER_H
#define SHOPPER_H
#include "tile.h"

class Shopper
{
	public:
		Shopper();
		Shopper(int id);
		Shopper(int id, int stores);
		
		int getID();
		void setID(int);
		int getR();
		void setR(int);
		int getC();
		void setC(int);
		int getF();
		void setF(int);
		//Item list functions
		Tile *getDest(void);
		void addDest(tilePtr);

		//Takes simple list of items that were scanned in, adds store to dest.
		void shopperApp();
		void printDests();
	private:
		int ID;
		int r, c, f;
		int numStore;
		//Item list of some kind
		tilePtr Dests;
};

#endif
                                                                                                                                                                                                                                                                                                                                    tile.h                                                                                              0000640 0027600 0027600 00000001615 12417604440 012741  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              /* A tile class to hold individual nodes of the Mall, be they path or store
Author: Alexi Kessler */
#ifndef TILE_H
#define TILE_H
#include "localItem.h"

class Tile
{
	public:
		Tile();
		Tile(int t, int s, int row, int col, int floor);
		
		void setType(int);
		int getType();
		void setStep(int);
		int getStep();
		void setPosition(int, int, int);
		int getRow();
		int getCol();
		int getFloor();
		void setRow(int);
		void setCol(int);
		void setFloor(int);
		
		int sizeInventory();
		void addToInventory(LocalItemPtr);
		void removeInventoryItem();
		LocalItemPtr getInventory();
		void setInventory(LocalItemPtr);
		
		void setNextTile(Tile *newTilePtr);
		Tile *getNextTile();
		void printInventory();
		void printTile();
	private:
		int type;
		int step;
		int r, c, f;
		Tile *nextTile;
		LocalItemPtr inventory;
		
};

typedef Tile *tilePtr;

#endif
                                                                                                                   util.h                                                                                              0000750 0027600 0027600 00000000424 12417633053 012762  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              
#ifndef UTIL_H_
#define UTIL_H_
#include "queue.h"
#include <iostream>

#define DEBUG 0
#define DEBUG1 1

#define DEBUG_PRINT(...)

// Processes all of the stats for a given queue, and prints
// them to a given file
void processesStats(queue *stats);

#endif
                                                                                                                                                                                                                                            makefile                                                                                            0000640 0027600 0027600 00000003226 12417633264 013341  0                                                                                                    ustar   arkessler                       arkessler                                                                                                                                                                                                              #Makefile for Program 5

OBJS = prog5.o init_mall.o decide.o small.o eventList.o binTree.o tile.o shopper.o robot.o globalItem.o localItem.o movement.o rr.o fcfs.o queue.o process.o util.o 

CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall

Prog5: $(OBJS)
	$(CC) $(LFLAGS) -lm $(OBJS) -o Prog5

prog5.o : binTree.h globals.h externals.h prog5.cpp 
	$(CC) $(CFLAGS) prog5.cpp

init_mall.o : externals.h globals.h init_mall.cpp
	$(CC) $(CFLAGS) init_mall.cpp

decide.o : externals.h globals.h decide.cpp
	$(CC) $(CFLAGS) decide.cpp

small.o : externals.h small.cpp
	$(CC) $(CFLAGS) small.cpp

robot.o :robot.cpp robot.h tile.h binTree.h 
	$(CC) $(CFLAGS) robot.cpp

movement.o: movement.cpp 
	$(CC) $(CFLAGS) movement.cpp

globalItem.o: globalItem.cpp globalItem.h
	$(CC) $(CFLAGS) globalItem.cpp

binTree.o: binTree.cpp binTree.h
	$(CC) $(CFLAGS) binTree.cpp

eventList.o: eventList.cpp eventList.h externals.h globals.h
	$(CC) $(CFLAGS) eventList.cpp	

shopper.o: shopper.cpp shopper.h globals.h externals.h
	$(CC) $(CFLAGS) shopper.cpp

rr.o: rr.h process.h queue.h util.h rr.cpp
	$(CC) $(CFLAGS) rr.cpp

fcfs.o: fcfs.h queue.h process.h util.h fcfs.cpp  process.o util.o queue.o
	$(CC) $(CFLAGS) fcfs.cpp

queue.o: queue.h process.h queue.cpp process.o
	$(CC) $(CFLAGS) queue.cpp 

process.o: process.h process.cpp
	$(CC) $(CFLAGS) process.cpp

util.o: queue.h util.h util.cpp
	$(CC) $(CFLAGS) util.cpp

tile.o: tile.h tile.cpp
	$(CC) $(CFLAGS) tile.cpp	

localitem.o: localItem.h localItem.cpp
	$(CC) $(CFLAGS) loacalItem.cpp

store_functions.o: store_functions.cpp
	$(CC) $(CFLAGS) store_functions.cpp
clean:
	rm *.o Prog5
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          