#include <stdlib.h>
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
fcfs::fcfs(queue *newSchedQueue){
  set_curTime(0);
  set_schedQueue(newSchedQueue);
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
    if (!get_schedQueue()->get_front()) {
      running = 0;
      if(DEBUG1) cout<<"no longer running" <<endl;
      break;
    }
    if(DEBUG1)cout<<"still running" <<endl;
  
    // Pop the next process off of the scheduling queue 
    process *nextProc;
    set_schedQueue(get_schedQueue()->pop(&nextProc));
  
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
  delete schedQueue;
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

queue *fcfs::get_schedQueue(){
  return schedQueue;
}

void fcfs::set_schedQueue(queue *newQueue){
  schedQueue = newQueue;
}

queue *fcfs::get_finishedProcesses(){
  return finishedProcesses;
}

void fcfs::set_finishedProcesses(queue *newQueue){
  finishedProcesses = newQueue;
}
