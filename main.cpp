/************************************************************************
*                                                                       *
*									*
*	Name:Patrick Leonard						*	
*	Assignment: Program 3						*
*	Class: CS 202							*
*	Date: 11/15/12							*
*	File: main.cpp							*
*									*
*	This .cpp file implements the UML Class Diagram (UCD) v.5.      *
*This is the main application of the graph abstrat data type. It uses	*
*a switch statement nested inside a do-while loop to execute all the    *
*capabilities of the graph abstract data type for a Class Diagram. 	*
*A few of the overloaded operators are used, but not all. No data is 	*
*saved, once again, but it is nicely formatted and pretty simple to use.*
*									*
************************************************************************/



#include "Graph.h"

int main()

	{

		//Basic overview of the program
		std::cout << "\n\nWelcome to the UML Class Diagram (UCD) v.5!" << std::endl;

		std::cout << "-------------------------------------------\n\n" << std::endl;

		std::cout << "This program is a test beta program for a Unified Modeling Language\n";

		std::cout << "Class Diagram. No data will be saved after the program is exited\n";

		std::cout << "and will only handle a maximum of 20 classes. Enjoy testing this program!\n\n\n";

		//Create the graph object and some input character arrays, and switch statement char
		Graph* graph = new Graph();

		const int BUFFER_SIZE = 255;

		char* input1 = new char[BUFFER_SIZE];

		char* input2 = new char[BUFFER_SIZE];

		char choice = 'x';

		do

			{

				choice = 'x';

				std::cout << "\n\nMain Menu\n";

				std::cout << "-------------------------\n\n";

				std::cout << "Please make you selection on how you would like to proceed." << std::endl;

				std::cout << "\n\n1. Display the details of a class" << std::endl;

				std::cout << "2. Add a class to the diagram" << std::endl;

				std::cout << "3. Remove a class from the diagram" << std::endl;

				std::cout << "4. Edit the member data and functions of a class" << std::endl;

				std::cout << "5. Add a connection between classes in the diagram" << std::endl;

				std::cout << "6. Removed a connection between classes in the diagram" << std::endl;

				std::cout << "7. Display the class diagram including the connections between the classes" << std::endl; 

				std::cout << "8. Exit the Program" << std::endl;
				
				std::cout << "Selection: ";

				std::cin >> choice;

				std::cin.get();

				//Input validation of choice for switch statement
				while((choice != '1') && (choice != '2') && (choice != '3') && (choice != '4') && (choice != '5') &&
					(choice != '6') && (choice !=  '7') && (choice != '8'))
				
					{

						std::cout << "Invalid Input! Please enter a choice from 1 to 7: ";

						std::cin >> choice;

						std::cin.get();

					}

				switch(choice)

					{

						case '1': //Enter in the name of a class and it will display Class details

						{

							std::cout << "\n\nDisplay Class Details\n";

							std::cout << "-------------------------\n\n";	

							std::cout << "Please enter the name of the class: ";

							std::cin.getline(input1, BUFFER_SIZE);

							graph->displayClass(input1);

							std::cout << "\n\n------Press enter to return to the previous menu------\n\n";

							std::cin.get();

							break;

						}

						case '2':  //Add a Class object using overloaded insertion operator

						{

							std::cout << "\n\nAdd a Class to Diagram\n";

							std::cout << "-------------------------\n\n";	

							std::cout << "This will begin the process of adding a class to the diagram.\n";

							std::cout << "It will also ask for the member data and functions for the class.\n";

							std::cout << "\n\nPlease enter in the name of the class you'd like to add: ";

							std::cin >> *graph; 

							break;

						}

						case '3':  //Remove a Class object by entering the Class name

						{

							std::cout << "\n\nRemove a Class from Diagram\n";

							std::cout << "-------------------------\n\n";	

							std::cout << "Please enter in the name of the class you'd like to remove: ";

							std::cin.getline(input1, BUFFER_SIZE);

							graph->removeClass(input1);

							break;

						}

						case '4':  //Edit a Class object by entering in the Class name

						{

							std::cout << "Edit Member Data and Functions" << std::endl;

							std::cout << "------------------------------\n\n";

							std::cout << "Please enter the name of the class you would like to edit: ";

							std::cin.getline(input1, BUFFER_SIZE);

							graph->editClass(input1);

							break;

						}

						case '5':  //Create an Edge by entering in the names of the Classes to connect

						{

							std::cout << "\n\nConnection Creation\n";

							std::cout << "----------------------------\n\n";

							std::cout << "Please enter the class name at one side of the connection: ";

							std::cin.getline(input1, BUFFER_SIZE);

							std::cout << "\n\nPlease enter the class name at the other side of the connection: ";

							std::cin.getline(input2, BUFFER_SIZE);

							graph->addEdge(input1, input2);	

							break;

						}

						case '6':  //Remove an Edge by entering in the names of the Classes to connect

						{

							std::cout << "\n\nConnection Removal\n";

							std::cout << "----------------------------\n\n";

							std::cout << "Please enter the class name at one side of the connection: ";

							std::cin.getline(input1, BUFFER_SIZE);

							std::cout << "\n\nPlease enter the class name at the other side of the connection: ";

							std::cin.getline(input2, BUFFER_SIZE);

							graph->removeEdge(input1, input2);	

							break;

						}

						case '7':  //Display the Class Diagram by using the overloaded extraction operator

						{

							std::cout << "\n" << *graph;

							break;
							
						}

						case '8':  //Choose to exit the program

						{

							char sure = 'x';

							std::cout << "Are you sure you would like to exit? (Y/N): ";

							std::cin >> sure;

							std::cin.get();

							//Input validation for confirmation
							while((sure != 'y') && (sure != 'Y') && (sure != 'n') && (sure != 'N'))

								{

									std::cout << "Invalid input! Please enter Y or N: ";

									std::cin >> sure;

									std::cin.get();

								}

							if((sure == 'Y') || (sure == 'y'))

								{

									break;

								}

							else

								{

									choice = 'x';

									break;

								} 

						}

					}

			}while(choice != '8');  //If chosen and confirmed to exit program end do-while after breaking out of switch statement

		//Deallocate memory
		delete [] input1;

		delete [] input2;

		delete graph;

		return 0;

	}
