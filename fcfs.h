#ifndef FCFS_H_
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
