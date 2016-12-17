/************************************************************************
*                                                                       *
*									*
*	Name:Patrick Leonard						*	
*	Assignment: Program 3						*
*	Class: CS 202							*
*	Date: 11/15/12							*
*	File: EdgeList.h						*
*									*
*	This header file declares the EdgeList class. This is the list  *
*of Edge objects that represents the connections between Class objects	*
*in the graph abstract data type. It is a linear linked list with a     *
*pointer to the first Edge object in the list as a member variable.	*
uAll traversals in the list are recursive. This is also the base class	*
*for the Class class. The pointer to the first Edge is protected in 	*
*terms of visibility so the Class class has direct access to the first	*
*Edge object.                                                         	*
*									*
************************************************************************/


#ifndef EDGELIST_H
#define EDGELIST_H

#include <iostream>
#include <cstdlib>
#include "Edge.h"

class EdgeList

	{

		protected:

			//Poiner to the first Edge in the list
			Edge* first;

		public:

			//Default constructor
			EdgeList();

			//Copy constructor, accepts a EdgeList object by reference
			EdgeList(const EdgeList &source);

			//Overloaded assignment operator, uses EdgeList object as right operand
			EdgeList& operator=(const EdgeList &source);

			//Class destructor
			~EdgeList();

			//Helper function for copy constructor, inserts input pointer to the list
			void copyInsert(Edge* copyEdge);
	
			//Helper function to the Class destructor, recursive
			void edgeDestructHelper(Edge* destroy);

			//Helper fucntion to the copy constructor, recursive
			void copyHelper(Edge* copyLink);

			//Add an Edge to the list, acceps and integer and a character array
			void addEdge(int index, const char descInput[]);

			//Recursive traversal to the end of the list
			Edge* traverseEnd(Edge* start);

			//Removes an edge from the list by connection integer
			void removeEdge(int index);

			//Recursive helper to remove that returns a pointer to the link 
			//before the ones that is to be removed, accepts integer and pointer to start of list
			Edge* removeHelper(int index, Edge* start);

			//Displays the entire list by calling recurseDisplay()
			void displayList();

			//Recursively displays all the links the list
			void recurseDisplay(Edge* start);

	};

#endif
