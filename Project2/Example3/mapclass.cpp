////////////////////////////////////////////////////////
// ECE 2574, Homework 3, Bowei Zhao
//
// File name: mapclass.cpp
// Description: cpp for the map class
// Date: 3/20/2014
//

// Include all the standard input/output streams 
// header files, and standard libraries for C++ to use

#include "mapclass.h"

using namespace std;

// this will just be my default constructor. 
mapclass::mapclass(void)
{

	// ADT initialization
	cityCurrent = NULL;					
	fpCurrent = NULL;				
	cityhead = NULL;
	flighthead = NULL;
	currentPrice = 0;
	recursion = true;

}

//destructor
mapclass::~mapclass(void)
{
	fpNode * temp;	
	//counter pointers and temporary pointers are initiated
	fpNode * cur;
	cityNode * cur2;
	cityNode * temp2;

	cur2 = cityhead;
	temp2 = cityhead->next;
	cur = flighthead;
	temp = flighthead->next;

	while (cur != NULL)								
	//both the cityNode and the flightlist are deleted
	{
		delete cur;
		cur = temp;
		if (temp != NULL)
		{
			temp = temp->next;
		}
	}

	while (cur2 != NULL)
	{
		delete cur2;
		cur2 = temp2;
		if (temp2 != NULL)
		{
			temp2 = temp2->next;
		}
	}

}

// sets the current city in the mapclass to whatever is fed
void mapclass::setCurrentCity(char cityName)
{
	currentCity = cityName;
}
// sets the first city as a ADT
void mapclass::setfirstcity(char fcity)
{
	firstcity= fcity;

}


int mapclass::getRoutePrice()
{
	// initialize an external local variable of total cost
	int totalcost =0;

	// 

	//currentprice is a private variable of class mapclass in mapclass.h
	currentPrice = currentFlightPath.getprice();

	// stores currentPrice in another int becuase currentPrice is a private variable you dont want
	// to mess with
	totalcost = currentPrice;

	return totalcost;

}



void mapclass::addFlight( char start, char end, int price )
{
	// using a struct of flight node. We will dynamically allocate memory
	fpNode *x;

	x = new fpNode;
	// we use some error checking with the try and catch
	try
	{
		if (x == NULL)
		{
			throw 1;
		}
	}
	catch (int i)
	{
		if (i == 1)
		{
			cout << "NOTICE: The values are NULL which mean uninitialization or incorrect values" << endl;
		}
	}

// we are setting the values in the struct to those that we are getting inputted
	x->flightcitystart = start;
	x->flightcityend = end;
	x->flightprice = price;
	x->next = NULL;
	// if the flightlist is empty, then we set the head and cur to the x which is the start and go through the list
	if (flighthead == NULL)
	{
		flighthead = x;
		fpCurrent = x;
	}
	// if the list is not empty, just go through as normal but put the flights onto the node after.
	else
	{
		fpCurrent->next = x;
		fpCurrent = x;
	}


}

void mapclass::addCity( char cityName )
{
	// makes a bool based off visisted and checks to see if we have went to the city already. If not, we run the code
	bool hasvisited;
	hasvisited = false;

	// testing to see if there are no cities in the list then you add the city and assign the head to the next node to allow it to add more cities
	if (cityhead == NULL)
	{
		// dynamically allocate memory
		cityNode *x;
		x = new cityNode;

		// rurn through a try and catch

		try
		{
			if (x == NULL)
			{
				throw 1;
			}
		}
		catch (int i)
		{
			if ( i == 1)
			{
				cout << "NOTICE: the list returns NULL" << endl;
			}
		}
		// you name the city into x and then make the current city also x
		
		// elements in ADT set equal to
		x->cityName = cityName;
		x->visited = false;
		x->next = NULL;
		cityhead = x;
		cityCurrent = x; 


	}
	else
	{
		// you loop through
		for (cityNode * cur = cityhead; cur != NULL; cur= cur->next)
		{
			// if the names of the ciities match, you set it to true
			if (cur->cityName == cityName)
			{
				hasvisited = true;
			}
		}
// but if you haven't visited it
		if (!hasvisited)
		{
			// you iniitalize some things in the ADT where visited is false and move on
			cityNode * x;

			x = new cityNode;

			x->cityName = cityName;
			x->visited = false;
			x->next = NULL;
			cityCurrent->next = x;
			cityCurrent = x;

		}
	}


}




void mapclass::markVisited( char cityName)
{
	// make a temporary struct of cityNode. Copy over all the data of cityhead which contains
	// all the cities in the flightmap to temp so it has access to it.


	for (cityNode * cur = cityhead; cur != NULL; cur = cur->next)//this function finds the city in the list and changes marker to true
	{
		try
		{
			if (cur == NULL)
			{
				throw 1;

			}
		}
		catch (int i)
		{
			if (i ==1)
			{
				cout << "NOTICE: City does not exist" << endl;
			}
		}
		
		if (cur->cityName == cityName)
		{
			cur->visited = true;
		}
	}

	// but if the temp has nothing in it.....then you gotta make stuff happen. 

}
void mapclass::search(char origincity, char destination)
{
	fpNode * fsearch = flighthead;
	//markVisited(origincity, true);

	// fsearch is used as a sourt of counter
	// has visited is used with the marking to find if it is a valid place to go
	bool hasvisited;

	hasvisited = false;

	// if the boolean of recursion based off previous ADT is true
	if (recursion == true)
	{
		// then you push the city original and the price of 0
		currentFlightPath.push(origincity, 0);
		// you set it false so this wont run again. Only for first timsies
		recursion= false;
	}
	// if the current city does not equal to your destination, and fsearch == null. 
	// this will reach until end is same as starting city. 
	while (currentCity!= destination)
	{
		if (fsearch == NULL)
		{
			// you pop the stacks and take the count. If there are more citie,s it recrusively calls itself then
			currentFlightPath.pop();
			if (currentFlightPath.getCount() != 0)
			{
				currentCity = currentFlightPath.gettop();
				search(currentFlightPath.gettop(), destination);

			}
			else
			{
				// nothing else to do
				break;
			}

		}
		// if the start cities do not match, then it starts from another city and we skip that one. 
		else if (origincity != fsearch->flightcitystart)
		{
			fsearch = fsearch->next;
		}
		else
		{
			for (cityNode *fsearch2 = cityhead; fsearch2 != NULL; fsearch2 = fsearch2->next)
			{
				if(fsearch2->cityName == fsearch->flightcityend && fsearch2->visited == true)
				{
					hasvisited = true;
				}
			}	
			if (!hasvisited)
			{
					currentFlightPath.push(fsearch->flightcityend, fsearch->flightprice);
					markVisited(fsearch->flightcityend);
					currentCity = fsearch->flightcityend;
					search(fsearch->flightcityend, destination);
			}
				fsearch = fsearch -> next;
				hasvisited = false;
			
		}
	}
}




bool mapclass::visitedCity( char cityName )
{
	// make a struct cityNode called temp and fill it with a list of all the cities
	cityNode *temp;
	temp = cityhead;


		try
	{
		if(temp == NULL)
		{
			throw 1;
		}
	}
	catch (int i)
	{
		if (i == 1)
		{
			cout << "NOTICE: The map is empty dude. Fix it" << endl;
		}
	}
		// while stuff is actually in there...because we want it to have stuff ya know?s

	while (temp != NULL)
	{
		// if the two names match then
		if(temp->cityName == cityName)
		{
			return temp->visited;
		}
		temp = temp->next;
	}

    return temp->next;
}


void mapclass::clear()
{

	try
	{
		//make a temporary struct cityNode of temp. Why? Because that struct has all the thingies i need
		cityCurrent = cityhead;
		recursion = true;
		currentPrice = 0;
		// give temp all the goodie stuff in cityhead which is all the cities in the flightmap
				// while something is actually in there
		while(currentFlightPath.getCount() != 0)
		{
			//runs a loop basically pooping everything out
			currentFlightPath.pop();
		}
		for (cityNode *temp = cityhead; temp != NULL; temp = temp ->next)
		{
			//reset visitation status to false. Don't want it to think its true
			// this runs in a loop like a boss
			temp->visited = false;
			// move it onto the next node
			//temp = temp->next;
		}
		if (cityhead == NULL)
		{
			throw 1;
		}
		if ( currentFlightPath.getCount() == 0)
		{
			throw 2;
		}
	}
	catch (int i)
	{
		if (i == 1)
		{
			cout<< "NOTICE map is (now) empty. You sure you wanted to run this?" << endl;
		}
		if ( i == 2)
		{
			cout << "Flight map has nothing in it. It has been cleared/is empty" << endl;
		}
	}

}
