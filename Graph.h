/************************************************************************
*                                                                       *
*									*
*	Name:Patrick Leonard						*	
*	Assignment: Program 3						*
*	Class: CS 202							*
*	Date: 11/15/12							*
*	File: Graph.h							*
*									*
*	This header file declares the Graph class. This is the abstract *
*data type that manages the UML Class Diagram. It is an undirected	*
*adjacency graph that uses an array of Class objects where each Class   *
*has inherited an EdgeList to use as a list of edges in the graph. 	*
*It uses a depth-first traversal that uses the system stack by being	*
*called recursively. There are quite a few overloaded operators, with 	*
*many be used for adding Class objects to the graph. The relational 	*
*operators compare the number of Class objects in the compared graphs,	*
*and insertion and extraction operators are overloaded as well. 	*
*Everything is done as recursively as possible. Has IO for editing      *
*Class object member data and functions.                                *
************************************************************************/


#ifndef GRAPH_H
#define GRAPH_H

#include "Class.h"
#include <iostream>

class Graph

	{

		private:

			//Maximum amount of Classes allowed in the diagram
			static const int MAX_CLASSES = 20;

			//Pointer to array of pointers to Class objects
			Class** classArray;

			//Number of Class objects in the array
			int nClasses;

		public:

			//Default constructor
			Graph();

			//Copy constructor, accepts a reference to a Graph object
			Graph(const Graph &source);

			//Overloaded assignment operator, uses Graph object as right operand
			Graph& operator=(const Graph &source);

			//Class destructor
			~Graph();

			//Adds a Class object to the graph using the character array argument
			void addClass(const char input[]);

			//Overloaded insertion operator, inserts a string into creating a Class object
			//that is then added to the graph
			friend std::istream& operator>>(std::istream &input, Graph& graph);

			//Overloated += operator that adds and already created Class object 
			//into the Graph, deletes the EdgeList as it might not match the graph
			Graph& operator+=(const Class &addClass);

			//Handles IO for editing the class that matches the character array input
			void editClass(const char input[]);

			//Used by editClass() to edit the data member list of the Class object
			//Accepts integer for index argument
			void editClassData(int index);

			//Used by editClass() to edit the member function list of the CLass object
			//Accepts integer for index argument
			void editClassFunction(int index);

			//Removes Class object fromt the graph that matches the input character array\
			//Also remvoes it's connections from other class objects in the graph
			void removeClass(const char input[]);

			//Recursive helper function called by removeClass() that deletes the Edges
			//and the Class object itself, accpets integer and Edge pointer as arguments
			void recurseClassRemove(int index, Edge* temp);

			//Adds a connection between two Class objects that match the input character arrays
			void addEdge(const char input1[], const char input2[]);

			//Removes a connection between two Class objects that match the input character arrays
			void removeEdge(const char input1[], const char input2[]);

			//Returns the index integer for the Class object that matches the input character array
			int classArraySearch(const char input[]);

			//Function that calls the recurseDepthFirst(), will displays all Class objects in graph
			//Even if not connected, and resets the visited member boolean for each Class object
			void depthFirstTraverse();

			//Recursive function that marks as visited and displays all Class objects in the graph
			void recurseDepthFirst(int index);

			//Overloaded extraction operator, calls depthFirstTraverse() and announces the end of 
			//the Class Diagram
			friend std::ostream& operator<<(std::ostream &out, Graph &graph);

			//Overloaded function that displays the Class details that matches the input 
			//character array, calls other displayClass()
			void displayClass(const char input[]);

			//Displays the class details that match the index in the classArray
			void displayClass(int index);

			//Displays the connections to a given Class object, accepts a pointer to the first 
			//Edge in the EdgeList inherited in each Class object
			void displayConnections(Edge* first);

			//Overloaded relational operators that compare the amount of Class objects 
			//in two graphs
			friend bool operator==(const Graph &graph1, const Graph &graph2);

			friend bool operator!=(const Graph &graph1, const Graph &graph2);

			friend bool operator>(const Graph &graph1, const Graph &graph2);	

			friend bool operator<(const Graph &graph1, const Graph &graph2);

			friend bool operator<=(const Graph &graph1, const Graph &graph2);

			friend bool operator>=(const Graph &graph1, const Graph &graph2);

			//Overload + operator that creates a graph by adding an already made 
			//class object with an already made graph to make a new graph
			//with the new Class object 
			friend Graph& operator+(const Graph &graph, const Class &addClass);

			friend Graph& operator+(const Class &addClass, const Graph &graph);

	};	

#endif
			

			


