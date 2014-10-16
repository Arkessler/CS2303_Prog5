#Makefile for Program 5

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
	$(CC) $(CFLAGS) queue.cpp -lm

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
