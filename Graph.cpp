/************************************************************************
*                                                                       *
*									*
*	Name:Patrick Leonard						*	
*	Assignment: Program 3						*
*	Class: CS 202							*
*	Date: 11/15/12							*
*	File: Graph.cpp							*
*									*
*	This .cpp  file implements the Graph class. This is the abstract*
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


#include "Graph.h"

//Default constructor
Graph::Graph()

	{

		classArray = new Class*[MAX_CLASSES]; //Create a new array of pointers to Class objects

		nClasses = 0;  //No classes added yet

		for(int i = 0; i < MAX_CLASSES; ++i)  //Assign all pointers to NULL to start

			{

				classArray[i] = NULL;

			}

	}

//Copy constructor, accepts a reference to a Graph object
Graph::Graph(const Graph &source)

	{

		nClasses = source.nClasses;  //Copy nClasses member

		classArray = new Class*[MAX_CLASSES];  //Create a new array of pointers

		for(int i = 0; i < MAX_CLASSES; ++i) //Assign to null

			{

				classArray[i] = NULL;

				if(source.classArray[i] != NULL)  //If graph being copied has an object

					{
						//create a new Class object and place into array
						classArray[i] = new Class(*(source.classArray[i]));

					}

			}

	}

//Overloaded assignment operator, uses Graph object as right operand
Graph& Graph::operator=(const Graph &source)

	{

		//Check for self assignment
		if(this == &source)

			{

				return *this;

			}

		//Check if deallocation of memory is needed
		for(int i = 0; i < MAX_CLASSES; ++i)

			{

				if(classArray[i] != NULL)

					{

						delete classArray[i];

						classArray[i] = NULL;

					}

			}

		delete [] classArray; //delete array of pointers

		//Perform same operations as copy constructor
		nClasses = source.nClasses;

		classArray = new Class*[MAX_CLASSES];

		for(int i = 0; i < MAX_CLASSES; ++i)

			{

				classArray[i] = NULL;

				if(source.classArray[i] != NULL)

					{

						classArray[i] = new Class(*(source.classArray[i]));

					}

			}

		return *this; //return a reference to this Graph object

	}

//Class destructor
Graph::~Graph()

	{

		//Cycle through array and delete Class object as needed
		for(int i = 0; i < MAX_CLASSES; ++i)

			{

				if(classArray[i] != NULL)

					{

						delete classArray[i];

						classArray[i] = NULL;

					}

			}

		delete [] classArray;  //Delete array of pointers

	}

//Adds a Class object to the graph with the name being te input character array
void Graph::addClass(const char input[])

	{

		if((nClasses + 1) <= MAX_CLASSES) //if he graph has room
	
			{

				int i = 0;

				while(classArray[i] != NULL)  //find the nearest free spot in the array
			
					{

						++i;

					}

				classArray[i] = new Class(input);  //Create a new class with input char array

				++nClasses;	//increment the number of Class objects

				editClass(input);  //Allow user to add data members and member functions

			}

		else       //If graph is full, say so and return

			{

				std::cout << "\n\n---/---/--Class limit has be reached for this diagram--/---/---\n" << std::endl;

				return;

			}

	}

//Overloaded insertion operator, creates a Class object with istream object
std::istream& operator>>(std::istream &input, Graph& graph)
	
	{

		//Create a new string to input istream object into
		const int BUFFER_SIZE = 255;

		char* newString = new char[BUFFER_SIZE];

		input.getline(newString, BUFFER_SIZE);

		//Perform same operations as addClass()
		if((graph.nClasses + 1) <= graph.MAX_CLASSES)

			{

				int i = 0;

				while(graph.classArray[i] != NULL)
			
					{

						++i;

					}

				graph.classArray[i] = new Class(newString);

				++(graph.nClasses);	

				graph.editClass(newString);

			}

		else

			{

				std::cout << "\n\n---/---/--Class limit has be reached for this diagram--/---/---\n" << std::endl;

			}

		delete [] newString;  //deallocate memory for character array

		return input;  //return istream object

	}

//Overloaded =+ operator, uses Class object as right operand
Graph& Graph::operator+=(const Class &addClass)

	{

		if((nClasses + 1) <= MAX_CLASSES)  //If graph can take a new Class object

			{

				int i = 0;

				while(classArray[i] != NULL)
			
					{

						++i;

					}

				classArray[i] = new Class(addClass); //Create a Class object using copy constructor

				classArray[i]->edgeDestructHelper(classArray[i]->getFirst()); //Delete all Edges to this class, they may not match

			}

		else       //If graph is full say so 

			{

				std::cout << "\n\n---/---/--Class limit has been reached!--/---/---" << std::endl;

				std::cout << "---/---/--Unable to add class!--/---/---\n" << std::endl;

			}

		return *this;  //return a reference to this graph object
						
	}	

//Allows user to edit the data and function members of a Class object
//Accepts character array as argument
void Graph::editClass(const char input[])

	{

		int index = classArraySearch(input);  //get index of Class matching input chararcter array

		editClassData(index);  //call to edit data members

		editClassFunction(index); //call to edit member functions

	}

//Handles IO for adding or removing data members to/from a Class object matching index argument
void Graph::editClassData(int index)

	{

		//Create a string to accept input 
		const int BUFFER_SIZE = 255;

		char* memberInput = new char[BUFFER_SIZE];

		//int variable for switch statement
		int choice = 0;

		//char for confirmation question
		char ok = 'x';

		do

			{

				//Displays the class and prompt user for choice
				displayClass(index);

				choice = 0;

				std::cout << "\nWould you like to add or remove a data member?" << std::endl;

				std::cout << "1. Add " << std::endl;

				std::cout << "2. Remove " << std::endl;

				std::cout << "3. Quit " << std::endl;

				std::cout << "Selection: ";

				std::cin >> choice;

				std::cin.get();

				//Input validation for choice
				while((choice < 1) || (choice > 3))
					
					{

						std::cout << "Invalid input! Please enter a choice from 1 to 3: ";

						std::cin >> choice;

						std::cin.get();

					}

				switch(choice)  //Begin switch statement

					{

					case 1: 

						{

						do

						{

							std::cout << "\nEnter in the data member you'd like to add(include visibility, type, and name)." << std::endl;

							std::cin.getline(memberInput, BUFFER_SIZE);

							std::cout << "\nInput member: " << memberInput << " OK? (Y/N):";

							std::cin >> ok;

							std::cin.get();
						
							//Input validation for confirmation
							while((ok != 'Y') && (ok != 'y') && (ok != 'N') && (ok != 'n'))

								{

									std::cout << "Invalid input! Please enter in Y or N." << std::endl;

									std::cin >> ok;

									std::cin.get();

								}					

							if((ok == 'Y') || (ok == 'y'))

								{

									//Add data member to Class object
									classArray[index]->addData(memberInput);

								}

						}while((ok == 'n') || (ok == 'N'));  //If finished then discontinue do-while loop and break from switch case

						break;

						}

					case 2:

						{

						do

						{

							std::cout << "\nEnter in the data member you'd like to remove(include visibility, type, and name)." << std::endl;

							std::cin.getline(memberInput, BUFFER_SIZE);

							std::cout << "\nInput member: " <<  memberInput << " OK? (Y/N):";

							std::cin >> ok;

							std::cin.get();

							//Input validation for confirmation
							while((ok != 'Y') && (ok != 'y') && (ok != 'N') && (ok != 'n'))

								{

									std::cout << "Invalid input! Please enter in Y or N." << std::endl;

									std::cin >> ok;

									std::cin.get();

								}					

							if((ok == 'Y') || (ok == 'y'))

								{

									//Add member function to Class object
									classArray[index]->removeData(memberInput);

								}

						}while((ok == 'n') || (ok == 'N'));  //If finished then discontinue do-while loop and break switch case

						break;

						}

					case 3:

						{

							std::cout << "\nQuit editing the Member Data? (Y/N):";

							std::cin >> ok;	

							std::cin.get();

							//input validation for confirmation
							while((ok != 'Y') && (ok != 'y') && (ok != 'N') && (ok != 'n'))

							{

								std::cout << "Invalid input! Please enter in Y or N." << std::endl;

								std::cin >> ok;

								std::cin.get();

							}					

							if((ok == 'Y') || (ok == 'y'))

								{

									break;
								
								}

							else

								{

									choice = 0;

									break;

								}

						}

					}

			}while(choice != 3);  //If choose and confirm quit adding data members end do-while

		delete [] memberInput;  //deallocate input string memory

	}

//Handls IO for user to add member functions to the Class object that matches the integer argument
void Graph::editClassFunction(int index)

	{

		//Create a new character array for input
		const int BUFFER_SIZE = 255;

		char* memberInput = new char[BUFFER_SIZE];

		//int for switch case
		int choice = 0;

		//char for use confirmation
		char ok = 'x';

		do

			{

				displayClass(index);

				choice = 0;

				std::cout << "\nWould you like to add or remove a member function?" << std::endl;

				std::cout << "1. Add " << std::endl;

				std::cout << "2. Remove " << std::endl;

				std::cout << "3. Quit " << std::endl;

				std::cout << "Selection: ";

				std::cin >> choice;

				std::cin.get();

				//Input validation for choice
				while((choice < 1) || (choice > 3))
					
					{

						std::cout << "Invalid input! Please enter a choice from 1 to 3: ";

						std::cin >> choice;

						std::cin.get();

					}

				switch(choice)

					{

					case 1: 

						{

						do

						{

							std::cout << "\nEnter in the member function you'd like to add(include visibility, return type, name, and argument list)." << std::endl;

							std::cin.getline(memberInput, BUFFER_SIZE);

							std::cout << "\nInput member: " <<  memberInput << " OK? (Y/N):";

							std::cin >> ok;

							std::cin.get();

							//input validation for confirmation
							while((ok != 'Y') && (ok != 'y') && (ok != 'N') && (ok != 'n'))

								{

									std::cout << "Invalid input! Please enter in Y or N." << std::endl;

									std::cin >> ok;

									std::cin.get();

								}					

							if((ok == 'Y') || (ok == 'y'))

								{

									//Add function to Class object
									classArray[index]->addFunction(memberInput);

								}

						}while((ok == 'n') || (ok == 'N'));

						break;

						}

					case 2:

						{

						do

						{

							std::cout << "\nEnter in the member function you'd like to remove(include visibility, return type, name, and argument list)." << std::endl;

							std::cin.getline(memberInput, BUFFER_SIZE);

							std::cout << "\nInput member: " <<  memberInput << " OK? (Y/N):";

							std::cin >> ok;

							std::cin.get();

							//input validation for confirmation
							while((ok != 'Y') && (ok != 'y') && (ok != 'N') && (ok != 'n'))

								{

									std::cout << "Invalid input! Please enter in Y or N." << std::endl;

									std::cin >> ok;

									std::cin.get();

								}					

							if((ok == 'Y') || (ok == 'y'))

								{

									//Remove function member from Class object
									classArray[index]->removeFunction(memberInput);

								}

						}while((ok == 'n') || (ok == 'N'));

						break;

						}

					case 3:

						{

							std::cout << "\nQuit editing the Member Functions? (Y/N):";

							std::cin >> ok;	

							std::cin.get();

							while((ok != 'Y') && (ok != 'y') && (ok != 'N') && (ok != 'n'))

							{

								std::cout << "Invalid input! Please enter in Y or N." << std::endl;

								std::cin >> ok;

								std::cin.get();

							}					

						if((ok == 'Y') || (ok == 'y'))

							{

								break;
							
							}

						else

							{

								choice = 0;

								break;

							}

						}

					}

			}while(choice != 3); //If finisehd edition member functions end do-while loop

		delete [] memberInput;   //deallocate member for input character array

	}

//Removes a Class object from the graph that matches the input character array
void Graph::removeClass(const char input[])

	{

		int index = classArraySearch(input);  //Get index of Class object in classArray

		if(index != -1)  //If object is in the array

			{
		
				Edge* temp = classArray[index]->getFirst(); //get the first Edge in the object's EdgeList 

				recurseClassRemove(index, temp);   //call to recursive function to remove Edges from other Class Objects

				delete classArray[index];    //delete the Class Object

				classArray[index] = NULL;   //Set pointer in array to NULL

			}

	}

//Recursive helper function to removeCclass(), accepts integer and pointer to Edge as arugments
void Graph::recurseClassRemove(int index, Edge* temp)

	{

		if(temp == NULL) //If passed end of EdgeList then stop

			{

				return;

			}

		classArray[temp->getConnection()]->removeEdge(index); //Find connected object and remove Edge from its EdgeList

		recurseClassRemove(index, temp->getNext());   //Recursive call to next Edge with the index of the object to be deleted

	}

//Adds and Edge to the EdgeLists of the Class objects that match the two input character array arguments
void Graph::addEdge(const char input1[], const char input2[])

	{

		//Create a character array to input the description of the connection between the Class Objects
		const int BUFFER_SIZE = 255;

		char* edgeDescription = new char[BUFFER_SIZE];

		char ok = 'x';

		int index1 = classArraySearch(input1);  //Get index of Class objects and confirm they exist in classArray

		int index2 = classArraySearch(input2);

		if((index1 == -1) || (index2 == -1))  //If either input doesn't match an object say so and return

			{

				std::cout << "\n\n---/---/--One or both classes are not in diagram! No edge created!--/---/---\n" << std::endl;

				delete [] edgeDescription;  //deallocate member for input characer array

				return;

			}

		do          //If objects match allow user to add description to their satisfaction

			{

			std::cout << "\nPlease enter a short description of the relationship between these two classes." << std::endl;

			std::cout << "This would include aggregation, composition, inheritance, realization, \ngeneralization, dependency, and/or multiplicity." << std::endl;

			std::cin.getline(edgeDescription, BUFFER_SIZE);

			std::cout << "Input description: " << edgeDescription << " OK? (Y/N):";
			
			std::cin >> ok;	

			std::cin.get();

			//Input validation for confirmation
			while((ok != 'Y') && (ok != 'y') && (ok != 'N') && (ok != 'n'))

				{

					std::cout << "Invalid input! Please enter in Y or N." << std::endl;

					std::cin >> ok;

					std::cin.get();

				}					

			if((ok == 'Y') || (ok == 'y'))

				{

					//Once confirmed add Edge to both EdgeLists
					classArray[index1]->addEdge(index2, edgeDescription);

					classArray[index2]->addEdge(index1, edgeDescription);

					delete [] edgeDescription; //Deallocate memory for character array 

					return;
				
				}

			}while((ok == 'N') || (ok == 'n')); 

	}

//Removes a connection between the two Class objects that match the input character arrays
void Graph::removeEdge(const char input1[], const char input2[])

	{

		char ok = 'x';

		//Get indexs of Class objects in classArray and confirmer they are in the array
		int index1 = classArraySearch(input1);

		int index2 = classArraySearch(input2);

		if((index1 == -1) || (index2 == -1)) //If not in the array say so and return

			{

				std::cout << "\n\n---/---/--One or both classes are not in diagram--/---/---\n" << std::endl;

				return;

			}

		//Confirm assoaction removal
		std::cout << "\nRemove association between: " << std::endl;

		classArray[index1]->displayClassName();

		classArray[index2]->displayClassName();

		std::cout << "\nContinue? (Y/N): ";
		
		std::cin >> ok;	

		std::cin.get();

		//Input validation for confirmation
		while((ok != 'Y') && (ok != 'y') && (ok != 'N') && (ok != 'n'))

			{

				std::cout << "Invalid input! Please enter in Y or N." << std::endl;

				std::cin >> ok;

				std::cin.get();

			}					

		if((ok == 'Y') || (ok == 'y'))

			{

				//If confirmed removed the Edge from each objects EdgeList
				classArray[index1]->removeEdge(index2);

				classArray[index2]->removeEdge(index1);

				return;
			
			}

		else       //If not confirmed, say so and return

			{

				std::cout << "\n\n---/---/--Edge NOT removed!--/---/---\n" << std::endl;

				return;

			}

	}

//Returns and int to the index of classArray that matches the input character array
int Graph::classArraySearch(const char input[])

	{


		//Find Class object in the array and return index
		for(int i = 0; i < MAX_CLASSES; ++i)

			{

				if((classArray[i] != NULL) && (classArray[i]->compareClassName(input) == 0))

					{

						return i;

					}

			}

		//If not in array , say so and return sentinel value of -1
		std::cout << "\n\n---/---/--Class not found!--/---/---\n" << std::endl;

		return -1;

	}

//Calls recurseDepthFirst(), and cycles through entire classArray to ensure all Class objects are displayed
void Graph::depthFirstTraverse()

	{

		for(int i = 0; i < MAX_CLASSES; ++i)

			{

				if(classArray[i] != NULL)

					{

						recurseDepthFirst(i); //call to recursive function

					}

			}

		//Reset all Class objects to visited = false so search can be done again
		for(int j = 0; j < MAX_CLASSES; ++j)

			{

				if(classArray[j] != NULL)

					{

						classArray[j]->setVisited(false);

					}

			}

	}

//Recursive function that displays each Class object in a depth-first algorithm using the system stack 
//by being called recursively
void Graph::recurseDepthFirst(int index)

	{

		if(classArray[index]->getVisited())  //if array has been visited return

			{

				return;

			}

		classArray[index]->setVisited(true);  //Set visited to true

		displayClass(index);    //Display the class

		std::cout << "\n------Press ENTER to continue------\n"; //Give user a pause to see the data

		std::cin.get();

		Edge* temp = NULL;  //Create a temp pointer to first Edge object in EdgeList

		temp = classArray[index]->getFirst();

		while(temp != NULL)  //While not passed the end of the EdgeList

			{

				recurseDepthFirst(temp->getConnection()); //recursive call to connected index

				temp = temp->getNext(); //Step to next Edge in EdgeList

			}

	}

//Overloaded extraction operator, calls depthFirstTravers of Graph used as right operand
//ends by declaring the end of the diagram, returns that string
std::ostream& operator<<(std::ostream &out, Graph &graph)

	{

		graph.depthFirstTraverse();

		out << "\n\n---/---/--End of Class Diagram--/---/---\n\n";

		return out;

	}

//Displays the Class that matches the input character array using classArraySearch()
void Graph::displayClass(const char input[])

	{

		int temp = classArraySearch(input);

		if(temp != -1)

			{

				displayClass(temp);

			}
		
	}

//Displays the Class that matches the given index, including the connections in the graph 
void Graph::displayClass(int index)

	{

		classArray[index]->displayClass();

		std::cout << "Connection(s):\n";

		Edge* temp = NULL;

		temp = classArray[index]->getFirst();

		if(temp == NULL) //If list is NULL says so

			{

				std::cout << "Connections list is empty!" << std::endl;

				return;

			}
		
		else       //Else call displayConnections with first Edge in Class object's EdgeList

			{

				displayConnections(classArray[index]->getFirst());

				return;

			}

	}

//Recursive function that diplays the class name and description of the Class object's connections
void Graph::displayConnections(Edge* first)

	{

		if(first == NULL)  //If passed the end of the EdgeList then stop
	
			{

				return;

			}

		classArray[first->getConnection()]->displayClassName(); //Display className of connected object

		first->displayDescription();   //Display description of Edge

		displayConnections(first->getNext());  //recursive call to next Edge

	}	
//Overloaded relational operators that compare two graph's number of classes (nClasses)
bool operator==(const Graph &graph1, const Graph &graph2)

	{

		return (graph1.nClasses == graph2.nClasses);

	}

bool operator!=(const Graph &graph1, const Graph &graph2)

	{

		return (graph1.nClasses != graph2.nClasses);

	} 

bool operator>(const Graph &graph1, const Graph &graph2)

	{

		return (graph1.nClasses > graph2.nClasses);

	}

bool operator<(const Graph &graph1, const Graph &graph2)

	{

		return (graph1.nClasses < graph2.nClasses);

	}

bool operator<=(const Graph &graph1, const Graph &graph2)

	{

		return (graph1.nClasses <= graph2.nClasses);

	}

bool operator>=(const Graph &graph1, const Graph &graph2)

	{

		return (graph1.nClasses >= graph2.nClasses);

	}

//Overlaoded + operator that adds a graph to an already made Class object
//and returns a Graph with the next object inserted
Graph& operator+(const Graph &graph, const Class &addClass)

	{

		//create new Graph with copy constructor
		Graph* newGraph = new Graph(graph);

		if((graph.nClasses + 1) <= graph.MAX_CLASSES) //Make sure graph can handle new object

			{

				int i = 0;

				while(newGraph->classArray[i] != NULL) //Find first open spot in classArray
			
					{

						++i;

					}

				newGraph->classArray[i] = new Class(addClass);  //Create a new Class object with copy constructor

				newGraph->classArray[i]->edgeDestructHelper(newGraph->classArray[i]->getFirst()); //Delete all the new classes Edges as they may not match

			}

		else      //If another Class object can't fit, say so 

			{

				std::cout << "\n\n---/---/--Class limit has been reached!--/---/---" << std::endl;

				std::cout << "---/---/--Unable to add class!--/---/---\n" << std::endl;


			}

		return *newGraph;   //return reference to newly created Graph object

	}

//Overloaded + operator with the operands switched, performed same operations as above
Graph& operator+(const Class &addClass, const Graph &graph)

	{

		Graph* newGraph = new Graph(graph);

		if((graph.nClasses + 1) <= graph.MAX_CLASSES)

			{

				int i = 0;

				while(newGraph->classArray[i] != NULL)
			
					{

						++i;

					}

				newGraph->classArray[i] = new Class(addClass);

				newGraph->classArray[i]->edgeDestructHelper(newGraph->classArray[i]->getFirst());


			}

		else

			{

				std::cout << "\n\n---/---/--Class limit has been reached!--/---/---" << std::endl;

				std::cout << "---/---/--Unable to add class!--/---/---\n" << std::endl;

			}

		return *newGraph;

	}

