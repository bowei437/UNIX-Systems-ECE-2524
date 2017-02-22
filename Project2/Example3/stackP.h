////////////////////////////////////////////////////////
// ECE 2574, Homework 3, Bowei Zhao
//
// File name: stackP.h
// Description: the header for the stack
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
using namespace std;

struct stackNode 
		{
			char city;
			stackNode *next;
			stackNode *prev;
			int price;
		};
class stackP
{
	public:
		stackP(void);
		//stackP( const stackP &toCopy );
		~stackP(void);
		bool isEmpty() const;
		void push(const char &newItem, int price);
		void pop();
		char gettop();
		// peek() returns the contents of the top-most element
		char peek();
		// records how much is in there
		int getCount();
			//flips the stack around. used when printing output
		void reverse();
		

		int getprice();
		//void clearstack();

	private:

		stackNode *top;
		int count;

};

