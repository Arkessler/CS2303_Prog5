CS 2303 Program 5
Team 2D: Max Li, Alexi Kessler

As is, our program 5 runs fine for the testData in Stage 1. Robots are read in with their destinations and items to deliver,
stored as the "inventories" of their destinations. When the robots reach a store, they stay there for the time it takes to move
all of the items from their destination inventory to the local Mall store inventory. That location is then removed from their 
destinations and they are sent on their way after waiting long enough to deliver all of their items. 

There is a minor issue in the output of Stage 1 in that arrivals are printed out after item deliveries when both occurs at 
the same time.

Stage 2 has yet to be implemented. We've laid the groundwork for the code, shoppers are very similar to robots, they just have 
item lists. Items in this case are globalItems, which form the basis of the tree and hold Store locations. The shoppers' 
destinations are generated through the use of the shopper app. When they arrive at a store they will be put in 
the store queue. The queues are coded, but not implemented in the simulation. 

The division of work was pretty much as close to 50/50 as possible. Alexi wrote most of the robot, tile, item, mall and movement
code, and Max wrote most of the shopper, shopperApp, tree, queue, and eventList code, with both adding in helper functions and 
small tweaks in various places. We both collaborated on the overall logic and structure of the program as we went, bouncing logic
and bugs off of one another. 