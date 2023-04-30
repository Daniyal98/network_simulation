# Network Simulation

A simple network simulation showing how machines are routers are connected to each other.

## Working

A simple network of machines and routers is created using three different data structures.
1. Linked List
2. BTree
3. Splay Tree
A csv file is read in which all the edges are defined. Machines are connected with routers. We can simulate a message by sending a message from one machine to another and the program will print the path the message took.

### Linked List

A node is created in which router and machine names are stored along with the next pointer. The linked list will contain collection of these nodes. Each node will either have a machine name or a router name and the next pointer will point to the next node. In this way, we can create the connections between machines and routers.

### BTree

In BTree, we store the machines and routers in a tree structure where the lesser edges would go to the left and the higher edges to the right.

### Splay Tree

In Splay Tree, we store the machines and routers in a tree structure where the lesser edges would go to the left and the higher edges to the right. The most frequently searched machine or router would come to the top of the tree (Splay) and the tree would balance itself accordingly.

## How to build

This is a cmake project so cmake should be installed on your system. Create a build directory and run `cmake ..` in it. This will generate the makefles and now run `make`. This will generate the executable which you can run by `./network_simulation`.