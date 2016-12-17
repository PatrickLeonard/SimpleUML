/************************************************************************
*                                                                       *
*									*
*	Name:Patrick Leonard						*	
*	Assignment: Program 3						*
*	Class: CS 202							*
*	Date: 11/15/12							*
*	File: ClassMember.cpp						*
*									*
*	This .cpp file implements the ClassMember object. This is the   *
*function and data members of the Class object. This object is a link	*
*in the lists and peform as such. They hold one data member, a character*
*array that is the data member or function of the class object. This  	*
*class also has a pointer to the next ClassMember object.        	*
*									*
************************************************************************/



#include "Class.h"

//Overloaded constructor, accepts a pointer to a character array as input
ClassMember::ClassMember(char* input): next(NULL)

	{

		member = input;

	}

//Copy constructor, accepts a ClassMember object by reference
ClassMember::ClassMember(const ClassMember &source): next(NULL)

	{

		//Create a new character array assign the member pointer to the array
		int length = 0;

		length = strlen(source.member);

		char* newString = new char[length + 1];

		strcpy(newString, source.member);

		member = newString;

	}

//Overloaded assignment operator, accepts a ClassMember object as right operand
ClassMember& ClassMember::operator=(const ClassMember &source)

	{

		//Check for self-assignment
		if(this == &source)

			{

				return *this;

			}

		//Check for need to deallocate memory
		if(member != NULL)

			{

				delete [] member;

			}	

		next = NULL;

		//Perform same operation as copy constructor
		int length = 0;

		length = strlen(source.member);

		char* newString = new char[length + 1];

		strcpy(newString, source.member);

		member = newString;

		return *this;  //return a reference to this object

	}

//Class destructor
ClassMember::~ClassMember()

	{

		delete [] member;

		next = NULL;

	}

//Sets the next pointer to the input pointer to ClassMember object
void ClassMember::setNext(ClassMember* nextmember)

	{

		next = nextmember;

	}

//Returns a pointer by value of the next member 
ClassMember* ClassMember::getNext()

	{

		return next;

	}

//Deletes the member character array, and sets the member pointer to the input pointer
void ClassMember::editMember(char* input)

	{

		delete [] member;

		member = input;

	}

//Compares the member character array to the input character array and returns
//the result of the strcmp()
int ClassMember::memberCompare(const char  input[])

	{

		return strcmp(member, input);

	}

//Displays the member character array
void ClassMember::displayMember()

	{

		std::cout << member << std::endl;

	}
