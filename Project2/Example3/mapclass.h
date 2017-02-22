////////////////////////////////////////////////////////
// ECE 2574, Homework 3, Bowei Zhao
//
// File name: mapclass.cpp
// Description: cpp for the mapclass
// Date: 3/20/2014
//

// Include all the standard input/output streams 
// header files, and standard libraries for C++ to use
#pragma once
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>
#include <cctype>
#include <cmath>
#include <fstream>
#include "stackP.h"
using namespace std;

// All the names below are nearly as given by the Professor 
// as they were self explanatory and easier to work with at times. 


struct cityNode 
{
char cityName;
bool visited;
cityNode *next;
};

struct fpNode 
{
fpNode *next;

char flightcitystart;
char flightcityend;
int flightprice;
};

class mapclass
{

public:
//linked list of all cities in flightmap
cityNode *cityhead;
//linked list of all flights in flightmap
fpNode *flighthead;
//stack which holds flights during flightmap search
stackP currentFlightPath;
mapclass(void);
~mapclass(void);
int getRoutePrice();
// Add a Flight to the list of all flights
void addFlight( char start, char end, int price );
// Add a City to the list of all cities
void addCity( char cityName);
// Determine whether a city has been already visited
bool visitedCity( char cityName );
// Marks city as visited
void markVisited( char cityName);
void backTrack();
void setCurrentCity( char cityName );
	//sets the very first city that is travelled from
void setfirstcity(char fcity);
// Prepares the class to be used for another search.
void clear();
// Find a flight path to a destination from currentCity
void search( char origincity, char destination );
private:
char firstcity;
char currentCity;
int currentPrice;
fpNode *fpCurrent;
cityNode *cityCurrent;
bool recursion;
};



