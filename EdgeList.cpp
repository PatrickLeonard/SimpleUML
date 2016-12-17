/************************************************************************
*                                                                       *
*									*
*	Name:Patrick Leonard						*	
*	Assignment: Program 3						*
*	Class: CS 202							*
*	Date: 11/15/12							*
*	File: EdgeList.cpp						*
*									*
*	This .cpp file implements the EdgeList class. This is the list  *
*of Edge objects that represents the connections between Class objects	*
*in the graph abstract data type. It is a linear linked list with a     *
*pointer to the first Edge object in the list as a member variable.	*
uAll traversals in the list are recursive. This is also the base class	*
*for the Class class. The pointer to the first Edge is protected in 	*
*terms of visibility so the Class class has direct access to the first	*
*Edge object.                                                         	*
*									*
************************************************************************/



#include "EdgeList.h"

//Default constructor
EdgeList::EdgeList(): first(NULL)

	{

	}

//Copy consructor, accepts an EdgeList object by referece
EdgeList::EdgeList(const EdgeList &source): first(NULL) 

	{

		Edge* copyLink = source.first;

		copyHelper(copyLink); //Call to recursive copy helper with first link in input EdgeList

	}

//Overloaded assignment operator, uses EdgeList object as right operand
EdgeList& EdgeList::operator=(const EdgeList &source)

	{

		//Check for self assignment
		if(this == &source)

			{

				return *this;

			}

		//Check is deallocation of member is needed
		if(first != NULL)

			{

				edgeDestructHelper(first); //call recursive destructor helper

			}

		//Perform same operations as copy constructor
		Edge* copyLink = source.first;

		copyHelper(copyLink);

		return *this;  //return a reference to this object

	}

//Helper function to copy the link list recursively, accepts pointer to first Edge in list
void EdgeList::copyHelper(Edge* copyLink) 

	{
		if(copyLink == NULL)   //If passed end of list stop

			{

				return;

			}

		Edge* copyEdge = new Edge(*copyLink);  //Create a new Edge using copy constructor

		this->copyInsert(copyEdge);   //Use copyInsert to add to the lsit

		copyHelper(copyLink->getNext()); //Recursive call to next link

	}

//Helper insert function for copy constructor, accepts pointer to Edge object
void EdgeList::copyInsert(Edge* copyEdge)

	{

		Edge* temp = NULL;  //temp pointer to Edge 

		if(first == NULL)  //If list is empty pointer first to input pointer

			{

				first = copyEdge;

			}

		else

			{

				temp = traverseEnd(first);  //Go to the end of the list

				temp->setNext(copyEdge);    //Point the end's next to the input pointer

			}

	}

//Class destructor
EdgeList::~EdgeList()

	{

		edgeDestructHelper(first); //Call to recursive helper function with start of list

	}

//Recusive helper function for the destructor, accepts pointer to the start of the EdgeList
void EdgeList::edgeDestructHelper(Edge* destroy)
	
	{

		Edge* temp = NULL;   //temp pointer to Edge

		if(destroy == NULL)  //If passed the end of list stop

			{

				return;

			}

		temp = destroy;   //Assign input pointer to temp

		edgeDestructHelper(destroy->getNext());  //recusive call to next Edge

		delete temp;  //delete the Edge object
	}		

//Adds and Edge to the list, accepts and integer and a character array as arguments
void EdgeList::addEdge(int index, const char descInput[])

	{

		Edge* newEdge = new Edge(index, descInput); //Create new Edge with inputs as arguments

		Edge* temp = NULL;  //temp pointer to Edge

		if(first == NULL)  //If list is empty point first to new Edge

			{

				first = newEdge;

			}

		else

			{

				temp = traverseEnd(first);  //Go to end of list

				temp->setNext(newEdge);  //Set end's next to new Edge

			}

	}

//Recursive function to get to the end of the list, accepts pointer to the start of list
Edge* EdgeList::traverseEnd(Edge* start)

	{

		if(start->getNext() == NULL) //If at the end of the list return pointer 

			{

				return start;

			}

		traverseEnd(start->getNext());  //Recursive call to next Edge

	}			

//Removes Edge from the list matching the integer argument 
void EdgeList::removeEdge(int index)

	{

		Edge* temp = NULL; //temp pointer to Edge

		Edge* delEdge = NULL;   //pointer to Edge to be deleted

		if(first == NULL)   //If EdgeList is empty says to and return

			{

				std::cout << "\n\n---/---/--Edge list is empty!--/---/---\n" << std::endl;

				return;

			}
	
		if(first->getConnection() == index)  //If Edge to be deleted is first Edge

			{

				temp = first;  //Assign first to temp

				first = temp->getNext(); //Set new first

				delete temp;  //Delete the Edge object

				return;

			}

		else

			{
			
				temp = removeHelper(index, first);  //Find Edge before one to be deleted

				if(temp == NULL)   //If passed the end of list, not found and return

					{

						std::cout << "\n\n---/---/--Edge not found!--/---/---\n" << std::endl;

						return;

					}

				delEdge = temp->getNext();  //Assign pointer to Edge to be deleted

				temp->setNext(delEdge->getNext());  //Connect list properly

				delete delEdge;   //Delete Edge object

				return;

			}	

	}

//Recursive helper function to find the Edge before the one to be removed
//Accepts an integer and a pointer to an Edge as arguments
Edge* EdgeList::removeHelper(int index, Edge* start)

	{

		if(start == NULL) //If passed end of list return NULL
		
			{

				return NULL;

			}

		if(start->getNext()->getConnection() == index) //If index matches to next Edge

			{

				return start;  //Return edge before one to be deleted

			}

		removeHelper(index, start->getNext()); //Recursive call to next Edge

	}

//Displays the list by calling recurseDisplay() 
void EdgeList::displayList()

	{

		if(first == NULL) //If list is empty says so

			{

				std::cout << "\n\n---/---/--Edge List is empty!--/---/---\n" << std::endl;

				return;

			}

		recurseDisplay(first);  //call recursiveDiaplsy() with first in list as argument

		return;

	}

//Recursive display function that properly displays the connection and description
//Accepts a pointer to an Edge object as argument 
void EdgeList::recurseDisplay(Edge* start)

	{

		if(start == NULL) //if passed end of list then stop

			{

				return;

			}

		else

			{

				//Display Edge properly
				std::cout << "\nEdge connection number: " << start->getConnection() << std::endl;

				start->displayDescription();

				recurseDisplay(start->getNext()); //recursive call to next Edge in list

			}

	}
