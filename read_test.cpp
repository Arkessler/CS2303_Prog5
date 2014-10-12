#include <iostream>
using namespace std;

#include "binTree.h"


int main(){
  int choice;
  

  printInstructions();
  cin >> choice;
  switch(choice){
  case 0:
    scanRobots();
    break;
  case 1:

    break;
  case 2:
    
    break;
}
}


void printInstructions(){
  cout<< "Pick a choice:"<<endl;
  cout<< "    0 is currently testing: Scan in Robots" << endl;
  cout<< "    1 is currently testing: Nothing" <<endl;
  cout<< "    2 is currently testing: Nothing" <<endl;
  cout<< "Choice: ";
}


void scanRobots(){
  int numBots = 0, i = 0, j = 0, numItems;
  cin >> numBots;
  int storeCounts[numBots];
 
  for (i = 0; i < numBots; i++){
    int tempStoreCnt;
    cin >> tempStoreCnt;
    RobotsNotInSim[i].set_numStores(tempStoreCnt);

    for (j = 0; j < storeCounts[i]; j++){
      int row, col, floor;
      cin >> row;
      cin >> col;
      cin >> floor;
      tilePtr insert = new Tile( type, step, row, col, floor);
      RobotsNotInSim[i].addDest(&(Mall[row][col][floor]));
    }

  }
  
  


}
