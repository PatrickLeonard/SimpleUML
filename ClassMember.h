/************************************************************************
*                                                                       *
*									*
*	Name:Patrick Leonard						*	
*	Assignment: Program 3						*
*	Class: CS 202							*
*	Date: 11/15/12							*
*	File: ClassMember.h						*
*									*
*	This header file declares the ClassMember object. This is the   *
*function and data members of the Class object. This object is a link	*
*in the lists and peform as such. They hold one data member, a character*
*array that is the data member or function of the class object. This  	*
*class also has a pointer to the next ClassMember object.        	*
*									*
************************************************************************/



#ifndef CLASSMEMBER_H
#define CLASSMEMBER_H

#include <cstdlib>
#include <cstring>
#include <iostream>

class ClassMember

	{

		private:

			//Pointer to next ClassMember object
			ClassMember* next;

			//Pointer to a character array that is the data member or function of the Class object
			char* member;

		public:

			//Overloaded constructor that sets the member pointer to the input pointer to a char array
			ClassMember(char* input);

			//Copy constructor that accepts a ClassMember object as the argument
			ClassMember(const ClassMember &source);

			//Overloaded assignment operator, uses ClassMember object as the right operand
			ClassMember& operator=(const ClassMember &source);

			//Class destructor
			~ClassMember();

			//Sets the next pointer to the input pointer
			void setNext(ClassMember* nextData);

			//Returns the values of the next pointer by value
			ClassMember* getNext();

			//Deletes current member and sets it to newly input pointer to char array
			void editMember(char* input);

			//Compares the member character array to the input character array and 
			//returns the result of the strcmp()
			int memberCompare(const char input[]);

			//Display the member character array
			void displayMember();

	};


#endif
