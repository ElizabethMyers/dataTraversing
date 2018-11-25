  
#ifndef H_graph
#define H_graph

#include <iostream> 
#include <fstream>
#include <iomanip>
#include "linkedList.h"
#include "unorderedLinkedList.h"
#include "linkedQueue.h"
#include <unordered_map>

using namespace std;

class graphType
{
public:
    bool isEmpty() const;
      //Function to determine whether the graph is empty.
      //Postcondition: Returns true if the graph is empty;
      //               otherwise, returns false.

    void createGraph();
      //Function to create a graph.
      //Postcondition: The graph is created using the  
      //               adjacency list representation.

    void clearGraph();
      //Function to clear graph.
      //Postcondition: The memory occupied by each vertex 
      //               is deallocated.

    void printGraph() const;
      //Function to print graph.
      //Postcondition: The graph is printed.

    void depthFirstTraversal();
      //Function to perform the depth first traversal of
      //the entire graph.
      //Postcondition: The vertices of the graph are printed 
      //               using depth first traversal algorithm.


    void breadthFirstTraversal();
      //Function to perform the breadth first traversal of
      //the entire graph.
      //Postcondition: The vertices of the graph are printed 
      //               using breadth first traversal algorithm.

	void cycleFinder();
	  //Functionn that traverses the entire graph and determins nodes
	  // that start cycles in the graph 
	  //Postcondition: The nodes that start the cycles are printed

	void cycleFinderisVisited(int v, unordered_map<int, bool> visitedNode);
	  //Function that traverses through the graph and uses unordered_map and dft
	  //techniques to keep track of visited nodes
	  //Parameters: The imput node, unordered_map to determine if it is visited
	  //Postcondition: The nodes that start the cycles are printed

    graphType(int size = 0); 
      //Constructor
	  //Postcondition: gSize = 0; maxSize = size;
      //               graph is an array of pointers to linked
      //               lists.

    ~graphType();
      //Destructor
      //The storage occupied by the vertices is deallocated.

protected:
    int maxSize;    //maximum number of vertices
    int gSize;      //current number of vertices
    unorderedLinkedList<int> *graph; //array to create 
                                     //adjacency lists 

private:
    void dft(int v, bool visited[]);
      //Function to perform the depth first traversal of 
      //the graph at a node specified by the parameter vertex.
      //This function is used by the public member functions
      //depthFirstTraversal and dftAtVertex.
      //Postcondition: Starting at vertex, the vertices are 
      //               printed using depth first traversal 
      //               algorithm.
};

bool graphType::isEmpty() const
{
    return (gSize == 0);
}

void graphType::createGraph()
{
    ifstream infile;
    char fileName[50];

    int index;
    int vertex;
    int adjacentVertex;

    if (gSize != 0)	//if the graph is not empty, make it empty
        clearGraph();

    cout << "Enter input file name: ";
    cin >> fileName;
    cout << endl;

    infile.open(fileName);

    if (!infile)
    {
        cout << "Cannot open input file." << endl;
        return;
    }

    infile >> gSize;	//get the number of vertices

    for (index = 0; index < gSize; index++)
    {
        infile >> vertex;
        infile >> adjacentVertex;

        while (adjacentVertex != -999)
        {
            graph[vertex].insertLast(adjacentVertex);
            infile >> adjacentVertex;
        } //end while
    } // end for

    infile.close();
} //end createGraph

void graphType::clearGraph()
{
    int index;

    for (index = 0; index < gSize; index++)
        graph[index].destroyList();

    gSize = 0;
} //end clearGraph


void graphType::printGraph() const
{
    int index;

    for (index = 0; index < gSize; index++)
    {
        cout << index << " ";
        graph[index].print();
        cout << endl;
    }

    cout << endl;
} //end printGraph

void graphType::depthFirstTraversal()
{
	//Pointer to create the array to keep track of the visited vertices
	bool *visited;
	//Creating an array parallel to the visited array to keep track of 
	//if a vertices is visited with a size the same as the graph size
	visited = new bool[gSize];
	//Declare index
	int index;
	//Starting at 0, traverse through the array to the end or until 
	//finding a spot where the vertices has not been visited
	//This will set each index of the array initially to false
	for (index = 0; index < gSize; index++)
		visited[index] = false;

	//For each vertices not visited, do depth first travel
	for (index = 0; index < gSize; index++)
		//If the vertices has not been visited and is false
		//Recursively call the dft function which will run through the connected
		//vertices and count them as visited
		if (!visited[index])
			dft(index, visited);
	//Delete the array
	delete[] visited;
} //end depthFirstTraversal

void graphType::dft(int v, bool visited[])
{
	//Count the vertices passed into the function as true, or counted
	visited[v] = true;
	//print the visited vertex
	cout << " " << v << " ";
	//Implement an iterator from linkedListIterator
	linkedListIterator<int> graphIt;

	//for each vertex adjacent to v
	//Start at the vertices and traverse through until reaching the end of
	//the vertices' connections
	for (graphIt = graph[v].begin(); graphIt != graph[v].end(); ++graphIt)
	{
		//Create a variable that holds the information the iterator points to
		int w = *graphIt;
		//If the info the iterator points to has not been visited, 
		//recursively call the dft function to count it as visited
		if (!visited[w])
			dft(w, visited);
	}
} //end dft

void graphType::breadthFirstTraversal()
{
	//Create a queue from linkedQueueType
	linkedQueueType<int> queue;
	//Pointer to create the array to keep track of the visited vertices
	bool *visited;
	//Creating an array parallel to the visited array to keep track of 
	//if a vertices is visited with a size the same as the graph size
	visited = new bool[gSize];
	//Starting at 0, while less than the size of the graph, iterate through
	//while setting the whole array to false
	for (int ind = 0; ind < gSize; ind++)
		visited[ind] = false; //initialize array visitation to false
	//Implement an iterator using linkedListIterator
	linkedListIterator<int> graphIt;
	//Starting at 0, while less than the size of the graph, iterate through
	//to see if the vertices has been visited(is true or false)
	for(int index = 0; index < gSize; index++)
		//If the vertices at the index is false, count it as now visited,
		//print it, and add to queue
		if (!visited[index])
		{
			//Add the index which was not visited into the created queue
			queue.addQueue(index);
			//Change the vertices to be now true and visited
			visited[index] = true;
			//Print the visited index
			cout << " " << index << " ";
		
	//If the queue is empty and has not yet been implemented, fill it
			while (!queue.isEmptyQueue())
			{
				//Create a front of the queue
				int u = queue.front();
				//Delete the node in the queue
				queue.deleteQueue();
				//Start at the front of the queue and traverse through until 
				//reaching the end of the vertices' connections
				for (graphIt = graph[u].begin(); graphIt != graph[u].end(); ++graphIt)
				{
					//Crease a variable that holds the information the iterator points to
					int w = *graphIt;
					//If the info the iterator points to has not been visited
					if (!visited[w])
					{
						//Add the vertices into the queue
						queue.addQueue(w);
						//Count the vertices as now visited and true
						visited[w] = true;
						//Print the now visited verticies
						cout << " " << w << " ";
					}
				}
			}
	}
} //end breadthFirstTraversal

void graphType::cycleFinder()
{
	//Create an unordered map of int and bool
	unordered_map <int, bool> visitedNode;
	//Declare index
	int index;
	//Starting at 0, traverse through the map to the end or until 
	//finding a spot where the vertices has not been visited
	//This will set each index of the map initially to false
	for (index = 0; index < gSize; index++)
		visitedNode.insert({ index, false });
	//Call cycle finder recursively starting at the first node
	//to find if there is a cycle, but the first node will always
	//start off as visited
	visitedNode[0] = true;
	cycleFinderisVisited(0, visitedNode);

}

void graphType::cycleFinderisVisited(int v, unordered_map<int, bool> visitedNode)
{
	//Count the vertices passed into the function as true, or counted
	visitedNode[v] = true;
	//Implement an iterator from linkedListIterator
	linkedListIterator<int> graphIt;

	//for each vertex adjacent to v
	//Start at the vertices and traverse through until reaching the end of
	//the nodes' connections
	for (graphIt = graph[v].begin(); graphIt != graph[v].end(); ++graphIt)
	{
		//Crease a variable that holds the information the iterator points to
		int w = *graphIt;
		//If the info the iterator points to has not been visited, 
		//recursively call the cycle finder function to count it as visited
		if (visitedNode[w] == false)
			cycleFinderisVisited(w, visitedNode);
		//If the node has been visited before and is true, there is a cycle
		//that occurs which begins at the "true" node
		if (visitedNode[w])
			cout << "There is a cycle starting at: " << w << endl;
	}

}

    //Constructor
graphType::graphType(int size)
{
    maxSize = size;
    gSize = 0;
    graph = new unorderedLinkedList<int>[size];
}

    //Destructor
graphType::~graphType()
{
    clearGraph();
}

#endif