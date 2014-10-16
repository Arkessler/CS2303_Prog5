// Fig. 20.3: Listnode.h 
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
  EventNode *getFirstPtr()
    {
      if(firstPtr != NULL)return firstPtr;
      else return NULL;
    }
  EventNode *getLastPtr(){return lastPtr;}
  void setFirstPtr(EventNode *first){firstPtr = first;}
  void setLastPtr(EventNode *last){lastPtr = last;}

  EventList *getShopperEvents();
  bool isEmpty() const; 
  void print(); 
 private: 
  EventNode *firstPtr; // pointer to first node 
  EventNode *lastPtr; // pointer to last node 

  // utility function to allocate new node 
   
}; // end class List 

#endif
