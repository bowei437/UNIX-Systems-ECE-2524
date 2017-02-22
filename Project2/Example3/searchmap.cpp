////////////////////////////////////////////////////////
// ECE 2574, Homework 3, Bowei Zhao
//
// File name: searchmap.cpp
// Description: cpp for the search map
// Date: 3/20/2014
//


// Include all the standard input/output streams 
// header files, and standard libraries for C++ to use

#include "mapclass.h"
#include "stackP.h"     // header file
#include <stddef.h>    // for NULL
//#include <assert.h>    // for assert()
#include <iostream> // for input outputstream
#include <locale>

// include everything we need to use
using namespace std;


// inputs arguments
int main(int argc, char * argv[])

{
	// try catch block that tests and sees how many arguments are feed into it through the command line. If they are not enough or incorrect, it runs the exceptions
	// however if it is 3, which is what we want, it continues through the code. 

	try
	{
		if (argc == 0)
		{
			throw 1;
		}
		if (argc == 2)
		{
			throw 2;
		}
		if (argc == 1)
		{
			throw 3;
		}
		if (argc == 3)
		{

			// initialize variables for use
			char initialcity, firstcity, secondcity;

			int cost;
			int count;

			// make a variable called flightmap that has access to my mapclass
			mapclass flightmap;

			// input stream will take in whatever argument is given first. This is the input file in this case
			ifstream in(argv[1]);
			{
				// tests to see if the file can be opened or not. One final check to make sure it exists and is hopefully valid.
				
				if (!in.is_open())
				{
					cout << "NOTICE: The input file is either not able to be opened, or is not valid" << endl;
					//return 0;
				}
				
				
				{	
					// i make an output stream. I name it out because that is what we always name it. We open up and feed it the file we call output.txt. It will make it if it isn't already there to overwrite
					ofstream out;
					out.open(argv[2]);
					// we pass in the first city. which can be thought of as the origin city. 

					// We define a new input stream rin to input the input file to test the origin city and make sure it is 1 char. Further tests are done below. This is but the initial one. 
					
					string n;
					ifstream rin(argv[1]);
					
					rin >> n;
					try
					{
						// if the length of the string is greater than 1, . ...houston. we have a problem
						if (n.length() != 1)
						{
							cout << "string n is "<< n << " and the size is " << n.length() << endl;
							
							throw 1;
							return 0;
							
						}
					}
					catch (int i)
					{
						if ( i ==1)
						{
							cout << "NOTICE: Please input city of just one character. Anything more than 1 char is not allowed" << endl;
							cout << "The code will not be responsible for checking if the other inputs are also 1 char. As if even the main has an error. So to shall the rest of it" << endl;
						}
					}
					
						
					
					in >> initialcity;

					
					//cout << "NOTICE: Initial City is " << initialcity << endl;

					// using the mapclasses public functions of set first city and set current city, we initiaize data so we can use it later
					// it initializes the ADT fields. 
					flightmap.setfirstcity(initialcity);
					flightmap.setCurrentCity(initialcity);

					// inputs the rest of the first initials of the document

					// The following block of code uses a secondar input stream called rin to also read in the cities 
					// it will test both city 1 to City 2 destination and make sure they are of 1 character
					// if even one of them are not, it will spit out an ERROR
					// 
					string test1;
					string test2;
					double testcost;

					rin >> test1 >> test2>> testcost;
					try
					{
						if (test1.length() != 1)
						{
							cout << "string test1 is "<< test1 << " and the size is " << test1.length() << endl;
							
							throw 1;
							return 0;
							
						}
						if (test2.length() != 1)
						{
							cout << "string test2 is "<< test2 << " and the size is " << test2.length() << endl;
							throw 2;
							return 0;

						}
					
					}
					catch (int i)
					{
						if ( i ==1)
						{
							cout << "NOTICE: Please input city primary of just one character. Anything more than 1 char is not allowed" << endl;
							cout << "The code will not be responsible for checking if the other inputs are also 1 char. As if even the main has an error. So to shall the rest of it" << endl;
							cout << "The problem here is with city " << test1 << endl;
						}
						if (i == 2)
						{
							cout << "NOTICE: Please input city secondary of just one character. Anything more than 1 char is not allowed" << endl;
							cout << "The code will not be responsible for checking if the other inputs are also 1 char. As if even the main has an error. So to shall the rest of it" << endl;
							cout << "The problem here is with city " << test2 << endl;

						}
					}

					// from here, it reads the standard city data and uses it normally

					in >> firstcity >> secondcity >> cost;

					//cout << "NOTICE: reached BEFORE while for values" << endl;

					// while the input has not failed. We loop through the file adding pretty much everything into the functions and setting the ADT up correctly
					while (!in.fail())
					{
						flightmap.addFlight(firstcity, secondcity, cost);
						//cout << "NOTICE: reached after add flight while for values" << endl;			
						flightmap.addCity(firstcity);
						//cout << "NOTICE: reached after add city 1 while for values" << endl;						
						flightmap.addCity(secondcity);
						//cout << "NOTICE: reached after add city 2 while for values" << endl;
						in >> firstcity >> secondcity >> cost;
						//cout << "NOTICE: reached after re-input while for values" << endl;

					}
						//cout << "NOTICE: reached past while for values" << endl;

					// this here is the code block for the output
					// we use built in functions of setw and left and right as a way to format it to look pretty. And it will look pretty of course
						out << left << setw(15) << "Destination" << left << setw(19) << "Flight Route from " << initialcity << right << setw(14) << "Total Cost" << endl;
					// this is a for loop that runs until the end. It will perform a search on the city while here
						// it searches for a route from the beginning to the end
						// and then it checks how many cities it goes through to reach the end. 
						for (cityNode * cur = flightmap.cityhead; cur != NULL; cur = cur->next)				
						{
							flightmap.search(initialcity, cur->cityName);									
							count = flightmap.currentFlightPath.getCount();										
																											
							// it checks if the count is non zero. Because it can't be if i t is.
							// the stack will then backtrack or 'reverse' itself. 
							// it then prints out destination cities

							if (flightmap.currentFlightPath.getCount() > 0 && flightmap.currentFlightPath.gettop() != initialcity)		
							{																								 
								flightmap.currentFlightPath.reverse();															
								out << left << setw(16) << cur->cityName;													
								cost = flightmap.getRoutePrice();															
								// it will continuously pop stacks in a loop																					
								for(int i = 0; i = (flightmap.currentFlightPath.getCount() - 1); i++)					
								{																				
									out << flightmap.currentFlightPath.gettop() << ", ";								
									flightmap.currentFlightPath.pop();												
								}																				
								// prints the last city and formats it nice and cool
								// setw is used again to align the stuff
								out << setw(20 ) << left << setfill(' ') << flightmap.currentFlightPath.gettop();	
								flightmap.currentFlightPath.pop();																	
								out << "$" << right << cost << endl;															
							}
							// needs to clear itself so that it can run the same operation again later. 																									
							flightmap.clear();																		
						}																								
					
				}
			}
		}
		
	}
	// Very WOW try catch exception stuff goes here WOW 
	// prety much only runs this if there are problems with the amount of input variables.  It should then give specific instructions as to what is going on. 
	catch ( int i)
	{
		if (i ==1 )
		{
			cout << "NOTICE: You have given nothing if that is even possible" << endl;
			cout << "Utilize the syntax of '. file executible . input.txt . output.txt 'thanks" << endl;

		}
		else if ( i == 2)
		{
			cout << "NOTICE: You have only specified either or an input/output and not both. Please include both" << endl;
			cout << "Utilize the syntax of '. file executible . input.txt . output.txt 'thanks" << endl;
		}
		else if ( i == 3)
		{
			cout << "NOTICE: You have not specified an input or output file. Please do so" << endl;
			cout << "Utilize the syntax of '. file executible . input.txt . output.txt ' " << endl;
		}

	}
}
	





