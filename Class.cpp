/************************************************************************
*                                                                       *
*									*
*	Name:Patrick Leonard						*	
*	Assignment: Program 3						*
*	Class: CS 202							*
*	Date: 11/15/12							*
*	File: Class.cpp							*
*									*
*	This .cpp file implements the Class object. This is the vertex  *
*of this graph program. The Class object has a name, a linear linked	*
*list of data and function members, and a boolean to note if the vertex *
*has been visited by the graph traversal. This class is also derived	*
*from the EdgeList class and has access to the first node of the	*
*EdgeList as it is of protected visibility. This allows the class to	*
*manage the list of its connections in the graph and the lists of the	*
*classes data/function members without the class being too bulky.	*
*									*
************************************************************************/

#include "Class.h"

//Overloaded constructor that creates a Class object with the name of the character array argument
Class::Class(const char input[]): dataFirst(NULL), functionFirst(NULL), visited(false) 

	{

		className = arrayCopy(input);

	}

//Copy Constructr, accepts by reference a CLass object
Class::Class(const Class &source): EdgeList(source), dataFirst(NULL), functionFirst(NULL), visited(false)

	{

		className = arrayCopy(source.className);   //Deep copy of the Class name

		ClassMember* dataCopy = source.dataFirst;  //Get a copy of the pointer to the first 

		ClassMember* functionCopy = source.functionFirst; //data and function links		

		copyData(dataCopy);    //Call the recursive funcions to copy both lists with 

		copyFunction(functionCopy); //their respective first links

	}

//Overloaded assignment operator, accepts a Class object as the right side operand
Class& Class::operator=(const Class &source)

	{

		//Check for self assignment
		if(this == &source)

			{

				return *this;

			}

		//Check for need to deallocate memory
		if(className != NULL)

			{

				delete [] className;  //Deallocate if needed

			}	

		if(dataFirst != NULL)

			{
				classDestructHelper(dataFirst);

			}

		if(functionFirst != NULL)

			{

				classDestructHelper(functionFirst);

			}

		dataFirst = NULL;

		functionFirst = NULL;

		EdgeList::operator=(source);   //Call base class assignment operator

		className = arrayCopy(source.className); //Deep copy class name

		ClassMember* dataCopy = source.dataFirst;  //Perform copy constructor operations

		ClassMember* functionCopy = source.functionFirst;		

		copyData(dataCopy);

		copyFunction(functionCopy);

		return *this;  //return the dereferenced object

	}
//Recursive function to copy the member data linked list
void Class::copyData(ClassMember* dataCopy) 

	{
		if(dataCopy == NULL)  //If passed end of list return

			{

				return;

			}

		ClassMember* copyDataMember = new ClassMember(*dataCopy); //Create a new ClassMember object copied from input pointer dereferenced

		this->copyDataInsert(copyDataMember);   //Insert the ClassMember into the respective list

		copyData(dataCopy->getNext());	//Recursive call to the next link

	}

//An insertion function to add already created data member links to the list
//accepts a pointer to a ClassMember object
void Class::copyDataInsert(ClassMember* copyDataMember)

	{

		ClassMember* temp = NULL;  //Create a temp pointer to ClassMember 

		if(dataFirst == NULL)     //If the list is empty set first to input link

			{

				dataFirst = copyDataMember;

			}

		else

			{

				temp = traverseEnd(dataFirst); //go to end of list

				temp->setNext(copyDataMember); //set the end to point to the input link

			}

	}

//Recursive funciton to copy the member functions linked list
void Class::copyFunction(ClassMember* functionCopy) 

	{
		if(functionCopy == NULL)   //If passed the end of the list then stop

			{

				return;

			}

		ClassMember* copyMemberFunction = new ClassMember(*functionCopy); //Create a new ClassMember object from dereferenced input pointer

		this->copyFunctionInsert(copyMemberFunction);   //Insert the ClassMember object to the respective list

		copyFunction(functionCopy->getNext());	  //Recursive call to tnext link in list

	}

//An insertion function to add already cread member function links to the list
//accepts a pointer to a ClassMember object
void Class::copyFunctionInsert(ClassMember* copyMemberFunction)

	{

		ClassMember* temp = NULL;    //Create a temp pointer to ClassMember object

		if(functionFirst == NULL)   //If list is empty point first to input pointer

			{

				functionFirst = copyMemberFunction;

				return;

			}

		else

			{

				temp = traverseEnd(functionFirst);   //go to end of list

				temp->setNext(copyMemberFunction);   //set end next to input pointer

				return;

			}

	}

//Recursive function to travers to the end of a member function/data list
//Accepts a pointer to a ClassMember object
ClassMember* Class::traverseEnd(ClassMember* start)

	{

		if(start->getNext() == NULL)  //If the link is at the end of the list return a pointer to that link

			{

				return start;

			}

		traverseEnd(start->getNext());  //Go to next in list

	}

//Class destructor
Class::~Class()

	{

		delete [] className;  //Delete the className data member

		classDestructHelper(dataFirst);  //call to recursive ClassMember list destructor helper function

		classDestructHelper(functionFirst);

	}

//Helper funciton to the destructor that recursively deletes the ClassMember lists
//accepts a pointer to a ClassMember object
void Class::classDestructHelper(ClassMember* destroy)
	
	{

		ClassMember* temp = NULL; //temp pointer to ClassMember 

		if(destroy == NULL)  //If input pointer is NULL stop, passed end of list

			{

				return;

			}

		temp = destroy;   //Set temp to the input pointer

		classDestructHelper(destroy->getNext());  //recursive call to next pointer

		delete temp;   //delete the ClassMember link
	}

//Creates a ClassMember object with the character array argument and adds it to the data list
void Class::addData(const char input[])

	{

		ClassMember* newData = new ClassMember(arrayCopy(input)); //Create a ClassMember with input character array

		ClassMember* temp = NULL;  //Create a temp pointer to ClassMember

		if(dataFirst == NULL) //If list is empty pointer first to newly created ClassMember

			{

				dataFirst = newData;

			}

		else

			{

				temp = traverseEnd(dataFirst); //Got to end of the list

				temp->setNext(newData);  //Point end next to the newly created ClassMember object

			}

	}

//Creates a ClassMember object with the character array argument and adds it to the function list
void Class::addFunction(const char input[])

	{

		ClassMember* newFunction = new ClassMember(arrayCopy(input)); //Create a new ClassMember object with input character array

		ClassMember* temp = NULL;    //Temp pointer to ClassMember 

		if(functionFirst == NULL)   //If function list is empty put newly created ClassMember to the first

			{

				functionFirst = newFunction;

			}

		else

			{

				temp = traverseEnd(functionFirst);  //Go to end of list

				temp->setNext(newFunction);   //Point the end next to newly created ClassMember object

			}

	}

//Removes a data member from the list that matches the character array argument
void Class::removeData(const char input[])

	{

		ClassMember* temp = NULL;   //temp pointer to ClassMember object

		ClassMember* delData = NULL;  //pointer to the object to be deleted

		if(dataFirst == NULL)   //If the list is empty nothing to delete

			{

				std::cout << "Data list is empty!" << std::endl;

				return;

			}
	
		if(dataFirst->memberCompare(input) == 0)   //If the first in list is to be deleted

			{

				temp = dataFirst;   //first in data list assigned to temp

				dataFirst = temp->getNext();  //new first pointed to next in list

				delete temp;   //delete the link

				return;

			}

		else

			{
			
				temp = removeHelper(input, dataFirst); //Find the link before the link to be removed

				if(temp == NULL)    //If null then the link wasn't found in the list

					{

						std::cout << "Data not found!" << std::endl;

						return;

					}

				delData = temp->getNext(); //Assign the pointer to be deleted

				temp->setNext(delData->getNext());  //Connect the list properly

				delete delData;   //delete the appropriate link

				return;

			}	

	}

//Removes a function from the member function list that is found witht the input character array
void Class::removeFunction(const char input[])

	{

		ClassMember* temp = NULL;  //temp pointer to ClassMember 

		ClassMember* delFunction = NULL;  //pointer to the ClassMember to be deleted

		if(functionFirst == NULL)   //If list is empty nothing to delete

			{

				std::cout << "Function list is empty!" << std::endl;

				return;

			}
	
		if(functionFirst->memberCompare(input) == 0)   //If first in list to be deleted

			{

				temp = functionFirst;  //assign first to temp pointer

				functionFirst = temp->getNext();  //set first to point to the next link

				delete temp;   //delete the ClassMember object

				return;

			}

		else

			{
			
				temp = removeHelper(input, functionFirst);  //Find link before the one to be deleted

				if(temp == NULL)   //If null the link not found

					{

						std::cout << "Function not found!" << std::endl;

						return;

					}

				delFunction = temp->getNext();  //set pointer to be deleted 

				temp->setNext(delFunction->getNext()); //Connect list correclty

				delete delFunction;  //delete appropriate link

				return;

			}	

	}

//Recursive helper function to remove data and fucntion members, accepts character array and pointer to first in list
ClassMember* Class::removeHelper(const char input[], ClassMember* start)

	{

		if(start->getNext() == NULL) //If null list is empty
		
			{

				return NULL;

			}

		if(start->getNext()->memberCompare(input) == 0) //If next link matches return pointer to link

			{

				return start;

			}

		removeHelper(input, start->getNext());   //Recursive call to next link with input character array

	}

//Returns a pointer to the first Edge in the Class' Edgelist
Edge* Class::getFirst()

	{

		return first;

	}

//Set the visisted boolean data member to input boolean value
void Class::setVisited(bool set)

	{

		visited = set;

	}

//Returns by value the boolean data member visited
bool Class::getVisited()

	{

		return visited;

	}

//Creates a new character array and copies the input chararcter array to the new one and returns a char pointer
//to the created aaray
char* Class::arrayCopy(const char input[])

	{

		int length = strlen(input);

		char* newString = new char[length + 1];

		strcpy(newString, input);

		return newString;

	}

//Compares the className member to the input character array, and returns the result of the srtcmp()
int Class::compareClassName(const char input[])
	
	{

		return strcmp(className, input);
	}

//Displays the Class details properly formatted
void Class::displayClass()

	{

		displayClassName();

		std::cout << "-----------------------\n" << std::endl;

		std::cout << "Member Data: " << std::endl;

		displayData();   

		std::cout << "\nMember Function(s): " << std::endl;

		displayFunction();

		std::cout << "\n";

	}

//Displays the name of the Class only
void Class::displayClassName()

	{
	
		std::cout << "Class Name: " << className << std::endl;
	}

//Displays the data members of the Class 
void Class::displayData()

	{

		if(dataFirst == NULL)

			{

				std::cout << "Data List is empty!" << std::endl;

				return;

			}

		recurseDisplay(dataFirst);  //Calls recursive function with first link in data member list

		return;

	}

//Displays the member functions of the Class
void Class::displayFunction()

	{

		if(functionFirst == NULL)

			{

				std::cout << "Function List is empty!" << std::endl;

				return;

			}

		recurseDisplay(functionFirst); //Calls recursive function with the first link in the member function list

		return;

	}

//Recursive function that displays all of the links in the data and function member lists
void Class::recurseDisplay(ClassMember* start)

	{

		if(start == NULL)   //If passed the end of the list stop

			{

				return;

			}

		else

			{

				start->displayMember();  //Displays the ClassMember

				recurseDisplay(start->getNext());  //Recursive call to next link

			}

	}
