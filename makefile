#Makefile for Program 5

OBJS = prog5.o init_mall.o decide.o small.o eventList.o tile.o shopper.o robot.o localItem.o movement.o 

CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall

Prog5: $(OBJS)
	$(CC) $(LFLAGS) -lm $(OBJS) -o Prog5
	
prog5.o : globals.h prog5.cpp 
	$(CC) $(CFLAGS) prog5.cpp

init_mall.o : externals.h globals.h init_mall.cpp
	$(CC) $(CFLAGS) init_mall.cpp
	
decide.o : externals.h globals.h decide.cpp
	$(CC) $(CFLAGS) decide.cpp
	
small.o : externals.h small.cpp
	$(CC) $(CFLAGS) small.cpp

robot.o :robot.cpp robot.h tile.h 
	$(CC) $(CFLAGS) robot.cpp
		
movement.o: movement.cpp 
	$(CC) $(CFLAGS) movement.cpp

eventList.o: eventList.cpp eventList.h 
	$(CC) $(CFLAGS) eventList.cpp	

shopper.o: shopper.cpp shopper.h globals.h
	$(CC) $(CFLAGS) shopper.cpp

tile.o: tile.h tile.cpp
	$(CC) $(CFLAGS) tile.cpp	
	
localitem.o: localItem.h localItem.cpp
	$(CC) $(CFLAGS) loaclItem.cpp
clean:
	rm *.o Prog5
