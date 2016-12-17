/************************************************************************
*                                                                       *
*									*
*	Name:Patrick Leonard						*	
*	Assignment: Program 3						*
*	Class: CS 202							*
*	Date: 11/15/12							*
*	File: Edge.h							*
*									*
*	This header file declares the Edge object. This is the link in  *
*in the EdgeList and is to keep track of the connections between Class	*
*objects in the graph abstract data type. This class consists of an int *
*that is the index in the classArray, a description character array 	*
*describing the type of connection, and a pointer to the next Edge	*
*in the EdgeList. 							*
*									*
************************************************************************/


#ifndef EDGE_H
#define EDGE_H

#include <iostream>
#include <cstdlib>
#include <cstring>

class Edge

	{

		private:

			//Pointer to next Edge
			Edge* next;

			//Index of Class in classArray
			int connection;

			//Description of the connection between the Class objects
			char* description;

		public:

			//Default constructor
			Edge();

			//Overloaded constructor, accepts an int and a character array
			Edge(int con, const char desc[]);

			//Copy constructor, accepts an Edge object by reference
			Edge(const Edge &source);

			//Overloaded assignment operator that uses an Edge object as right operand 
			Edge& operator=(const Edge &source);

			//Class destructor
			~Edge();

			//Sets the next pointer to the input pointer 
			void setNext(Edge* newEdge);

			//Returns the value of the next pointer by value
			Edge* getNext();

			//Returns the connection integer for the Graph class
			int getConnection();

			//Displays the description of the connect between Class objects
			void displayDescription();

			//Creates a new character array and assigns it to the description pointer
			char* arrayCopy(const char input[]);

	};

#endif
