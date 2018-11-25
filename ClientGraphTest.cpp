/*
Name: Elizabeth Myers
Date: 6/3/17
Class: CSC 2431
Assignment: Homework 5
Description: Traversing a graph in different methods
*/

#include <iostream>
#include "linkedList.h"
#include "linkedQueue.h"
#include "unorderedLinkedList.h"
#include "queueADT.h"
#include "graphType.h"


using namespace std;

int main()
{
	//Implement the program  by creating a graph with set number of nodes
	graphType graph(8);
	//Create graph which will ask user to input the file holding the graph data
	graph.createGraph();

	//Test cycleFinder
	//Should be two cycles at 0 and 4
	graph.cycleFinder();
	cout << endl;
	cout << endl;

	//Test BreadthFirstTraversal
	//Output should be: 0 1 3 4 2 5 6 7
	cout << "Breadth first traversal:" << endl;
	graph.breadthFirstTraversal();
	cout << endl;
	cout << endl;

	//Test depthFirstTraversal
	//Output should be: 0 1 2 3 4 5 6 7
	cout << "Depth first traversal:" << endl;
	graph.depthFirstTraversal();
	cout << endl;


	return 0;
}