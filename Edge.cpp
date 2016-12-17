/************************************************************************
*                                                                       *
*									*
*	Name:Patrick Leonard						*	
*	Assignment: Program 3						*
*	Class: CS 202							*
*	Date: 11/15/12							*
*	File: Edge.cpp							*
*									*
*	This .cpp file implements the Edge object. This is the link in  *
*in the EdgeList and is to keep track of the connections between Class	*
*objects in the graph abstract data type. This class consists of an int *
*that is the index in the classArray, a description character array 	*
*describing the type of connection, and a pointer to the next Edge	*
*in the EdgeList. 							*
*									*
************************************************************************/


#include "Edge.h"

//Default constructor
Edge::Edge(): next(NULL), connection(-1), description(NULL)

	{

	}

//Overloaded constructor, accepts an integer and a character array
Edge::Edge(int con, const char desc[]): next(NULL)

	{

		connection = con;

		description = arrayCopy(desc); //call to arrayCopy 

	}

//Copy constructor, accepts a Edge object by reference
Edge::Edge(const Edge &source): next(NULL)

	{

		connection = source.connection;

		description = arrayCopy(source.description); //call to arrayCopy

	}

//Overloaded assignment operator, uses an Edge object as right operand
Edge& Edge::operator=(const Edge &source)

	{

		//Check for self assignment
		if(this == &source)

			{

				return *this;

			}

		//Check if deallocation of memory is needed
		if(description != NULL)

			{

				delete [] description;

			}

		//Perform same operations os copy constructor
		connection = source.connection;

		description = arrayCopy(source.description);

		next = NULL;

		return *this;  //return a reference to this object

	}

//Class destructor
Edge::~Edge()

	{

		delete [] description;

	}

//Sets next member to the input pointer
void Edge::setNext(Edge* newEdge)

	{

		next = newEdge;

	}

//Returns next pointer by value
Edge* Edge::getNext()

	{

		return next;

	}

//Returns the int connection member by value
int Edge::getConnection()

	{

		return connection;

	}

//Displays the description character array
void Edge::displayDescription()

	{

		std::cout << "Connection description: " << description << std::endl;

	}	

//Creates a new character array, copies the input into the new char array, and returns pointer to new array
char* Edge::arrayCopy(const char input[])

	{

		int length = strlen(input);

		char* newString = new char[length + 1];

		strcpy(newString, input);

		return newString;

	}
