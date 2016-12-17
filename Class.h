/************************************************************************
*                                                                       *
*									*
*	Name:Patrick Leonard						*	
*	Assignment: Program 3						*
*	Class: CS 202							*
*	Date: 11/15/12							*
*	File: Class.h							*
*									*
*	This header file declares the Class object. This is the vertex  *
*of this graph program. The Class object has a name, a linear linked	*
*list of data and function members, and a boolean to note if the vertex *
*has been visited by the graph traversal. This class is also derived	*
*from the EdgeList class and has access to the first node of the	*
*EdgeList as it is of protected visibility. This allows the class to	*
*manage the list of its connections in the graph and the lists of the	*
*classes data/function members without the class being too bulky.	*
*									*
************************************************************************/

#ifndef CLASS_H 
#define CLASS_H

#include "EdgeList.h"
#include "ClassMember.h"
#include <cstdlib>
#include <cstring>
#include <iostream>

class Class: public EdgeList

	{

		private: 

			//Name of the Class object
			char* className;
		
			//Pointer to the first in the data member list
			ClassMember* dataFirst;

			//Pointer to the first in the member function list
			ClassMember* functionFirst;

			//Keeps track of if this vertex has been visited by the graph traversal
			bool visited;

		public:

			//Overloaded Constructor, accepts a character array input
			Class(const char input[]);

			//Copy Constructor, accepts a reference to a Class object 
			Class(const Class &source);

			//Overloaded assignment operator, accepts a Class object as right side argument
			Class& operator=(const Class &source);

			//Recursive function to copy the member data linked list
			void copyData(ClassMember* dataCopy);

			//An insertion function to add already created data member links to the list
			//accepts a pointer to a ClassMember object
			void copyDataInsert(ClassMember* copyDataMember);

			//Recursive funciton to copy the member functions linked list
			void copyFunction(ClassMember* functionCopy);

			//An insertion function to add already cread member function links to the list
			//accepts a pointer to a ClassMember object
			void copyFunctionInsert(ClassMember* copyMemberFunction);	

			//Recursive function to travers to the end of a member function/data list
			//Accepts a pointer to a ClassMember object
			ClassMember* traverseEnd(ClassMember* start);

			//Class destructor
			~Class();

			//Helper funciton to the destructor that recursively deletes the ClassMember lists
			//accepts a pointer to a ClassMember object
			void classDestructHelper(ClassMember* destroy); 	

			//Creates a ClassMember object with the character array argument and adds it to the data list
			void addData(const char input[]);

			//Creates a ClassMember object with the character array argument and adds it to the function list
			void addFunction(const char input[]);

			//Removes a data member from the list that matches the character array argument
			void removeData(const char input[]);

			//Removes a member fucntion from the list that matches the character array argument
			void removeFunction(const char input[]);

			//Recursively searchs through either list and finds the link before the one to be removed and returns 
			//a pointer to that link, accepts a character array and a pointer to a ClassMember object
			ClassMember* removeHelper(const char input[], ClassMember* start);

			//Returns a pointer to the first Edge in the EdgeList for use by the graph's depthFirstTraversal()
			Edge* getFirst();

			//Sets the visited boolean data member to the boolean argument
			void setVisited(bool set);

			//Returns by value the boolean data member visited
			bool getVisited();

			//Copies the input character array to a newly created array and returns a pointer to a char
			char* arrayCopy(const char input[]);

			//Compares the character array argument to the name of the Class object and returns the result
			//of the strcpy(char*, char*) function
			int compareClassName(const char input[]);

			//Displays the name of the class 
			void displayClassName();

			//Displays the class name, data members, and member functions, nicely formatted
			void displayClass();

			//Used by displayClass() to display the data members
			void displayData();

			//Used by displayClass to display the member functions
			void displayFunction();

			//Recursive function to display all the data and function members
			//accepts a pointer to the first link in those lists, used by both displayFunction() and displayData()
			void recurseDisplay(ClassMember* start);

	};			

#endif
