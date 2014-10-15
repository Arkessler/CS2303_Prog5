// Fig. 20.3: Listnode.h 
// Template ListNode class definition. 
#ifndef LISTNODE_H 
#define LISTNODE_H 

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
   Shopper *shopperID();
   int get_eType();

   EventList *getNext(){return nextPtr}
   void setNext(EventList *newNext){ nextPtr = newNext;}

 private: 
   int time;
   Robot *robotID;
   Shopper *shopperID;
   int eType;
   EventList *nextPtr; // next node in list 
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
  void setFirstPtr(EventNode *first){firstPtr = first;}
  void setLastPtr(EventNode *last){lastPtr = last;}

  bool isEmpty() const; 
  void print() const; 
 private: 
  EventNode *firstPtr; // pointer to first node 
  EventNode *lastPtr; // pointer to last node 

  // utility function to allocate new node 
  //EventNode *getNewNode( const  & ); 
}; // end class List 

#endif
