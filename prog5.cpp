#ifndef PROG5_CPP
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

#define DEBUG 1

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
		case 0: //Test robot class
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
		case 2: //Test robot movement
			{
				tilePtr testDest1 = new Tile(7, 7, 4, 4, 1);
				tilePtr testDest2 = new Tile(7, 4, 6, 4, 0);
				robotPtr testRob = new Robot(32, 1, 8, 16, 0, testDest1);
				testRob->addDest(testDest2);
				
				int t1 = travel(testRob, SIZE);
				int t2 = travel(testRob, SIZE);
				break;
			}
		case 3: //Test deliverItem Alexi
			{
				tilePtr testDest1 = new Tile(7, 7, 4, 4, 1);
				tilePtr testDest2 = new Tile(7, 4, 6, 4, 0);
				
				LocalItemPtr testItem1 = new LocalItem("A5", 5);
				LocalItemPtr testItem2 = new LocalItem("L7", 1);
				LocalItemPtr testItem3 = new LocalItem("D8", 10);
				LocalItemPtr testItem4 = new LocalItem("Z2", 7);
				
				
				/*
				if(DEBUG) {
				  cout<< "for test 1"<<endl;
				  robotPtr newTest = new Robot(32, 1, 8, 16, 0, testDest1);
				  newTest->getDests()->printInventory();
				}
				
				if(DEBUG) {
				  cout<<"for test 2"<<endl;
							  robotPtr newTest = new Robot(32, 1, 8, 16, 0, testDest1);
							  newTest->getDests()->printInventory();
							}
				
				 
				
				if(DEBUG) {
				  cout<<"for test 3"<< endl;
							  robotPtr newTest = new Robot(32, 1, 8, 16, 0, testDest1);
							  newTest->getDests()->printInventory();
							}*/
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
		case 4: //Test of deliverItems() Alexi
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
		case 5: //Test of EventList and EventNode Max
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
		case 6: //Test checkState
			{
				scanRobots();
			break;
			}
		default:
			cout<<"Improper or no test input";
			break;
	}
}

void scanRobots(){
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
      cout<< RobotsNotInSim[i].getTile(1)->getRow() << "~" << RobotsNotInSim[i].getTile(1)->getCol()<<endl;
      if(DEBUG) cout << "scanned store " << j << " for robot " << i << endl;
    }
    //if(DEBUG) cout << RobotsNotInSim[i].getID()<<endl;
    //Robot *curRobot = new Robot();
    //*curRobot = RobotsNotInSim[i];
    mallEvents->addNewEvent(25*i, &RobotsNotInSim[i], 0);
  }
  if(DEBUG) {
    mallEvents->print();
  }
}


void readShoppers(){
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
    }
    return prev->getTime();
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
