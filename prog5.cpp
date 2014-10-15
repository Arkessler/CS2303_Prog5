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
			
			travel(testRob, SIZE);
			travel(testRob, SIZE);
			break;
			}
		case 3: //Test deliverItems
			{
			tilePtr testDest1 = new Tile(7, 7, 4, 4, 1);
			tilePtr testDest2 = new Tile(7, 4, 6, 4, 0);
			
			LocalItemPtr testItem1 = new LocalItem("A5", 5);
			LocalItemPtr testItem2 = new LocalItem("L7", 1);
			LocalItemPtr testItem3 = new LocalItem("D8", 10);
			LocalItemPtr testItem4 = new LocalItem("Z2", 7);
			
			testDest1->addToInventory(testItem1);
			if(DEBUG) {
			  cout<< "for test 1"<<endl;
			  robotPtr newTest = new Robot(32, 1, 8, 16, 0, testDest1);
			  newTest->getDests()->printInventory();
			}
			testDest1->addToInventory(testItem2);
			if(DEBUG) {
			  cout<<"for test 2"<<endl;
                          robotPtr newTest = new Robot(32, 1, 8, 16, 0, testDest1);
                          newTest->getDests()->printInventory();
                        }
			
			testDest1->addToInventory(testItem3); 
			
			if(DEBUG) {
			  cout<<"for test 3"<< endl;
                          robotPtr newTest = new Robot(32, 1, 8, 16, 0, testDest1);
                          newTest->getDests()->printInventory();
                        }

			testDest2->addToInventory(testItem4);
			
			robotPtr testRob = new Robot(32, 1, 8, 16, 0, testDest1);
			testRob->addDest(testDest2);
			
                        //(testRob->getDests())->printInventory();

			//Test that item inventory initialized correctly
			(testRob->getDests())->printInventory();
			//Travel to first destination
			travel(testRob, SIZE);
			
			//See how long it takes to deliver first item
			int deliveryTime;
			deliveryTime = testRob->deliverItem();
			cout<<"Time that the robot will finish delivering its first item: "<<deliveryTime<<endl;
			
			(testRob->getDests())->removeInventoryItem();
			//Remove first item from inventory list
			
			cout<<"\nRemoved delivered item from dest Inventory"<<endl;
			cout<<"Checking for successful removal. Current Item list: "<<endl;
			(testRob->getDests())->printInventory();
			
			//HERE
			deliveryTime = testRob->deliverItem();
			cout<<"Time that the robot will finish delivering its second item: "<<deliveryTime<<endl;
			testRob->removeDest();
			cout<<endl;
			travel(testRob, SIZE);
			break;
			}
	case 4:
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
	  }

	  break;
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

/*
void readShoppers(){
  int numShoppers, arrival, numItems, itemCnt;
  std::string itemName;

  cout<< "Input number of shoppers: "<<endl;
  cin >> numShoppers;
  for (int i = 0; i < numShoppers; i++){
    cout<< "Input arrival time: "<< endl;
    cin >> arrival;
    cout<<"Input number of items to buy" <<endl;
    cin >> numItems;

    Shopper tempShopper = new Shopper(arrival, itemCnt);
    for (int j = 0; j < itemCnt; j++){

      cout << "Input item name:" <<endl;
      cin >>  itemName;
      cout << "input item count:" <<endl;
      cin >> itemCnt;

      //I AM NOT SURE WHERE TO GO FROM HERE
    }

  }

}
*/
  
#endif
