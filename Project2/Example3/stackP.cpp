////////////////////////////////////////////////////////
// ECE 2574, Homework 3, Bowei Zhao
//
// File name: stackP.cpp
// Description: cpp for the stack
// Date: 3/20/2014
//

// Include all the standard input/output streams 
// header files, and standard libraries for C++ to use

#include "stackP.h"

// constructor
stackP::stackP(void)
{
	top = NULL;
	count = 0;
}


// sets the top to be the last city in there
char stackP::gettop()
{
	return top->city;
}

// function to get the total price after being called from mapclass.cpp
int stackP::getprice()
{
	int total;
	total = 0;
	// looops through

	for (stackNode * cur = top; cur != NULL; cur = cur->prev)
	{
		// adds price up
		total = total + cur->price;
	}
	// returns total
	return total;
}
// pretty much just flips the stack so we can access it from the bottom up

void stackP::reverse()
{
	stackNode * CurrentTopStack;
	stackNode * p;
	stackNode * temp;
	bool first;

	first = true;
	CurrentTopStack = top;

	for (stackNode * cur = top; cur != NULL; cur = cur->prev)
	{
		if (first == true)
		{
			p = new stackNode;
			p->prev = NULL;
			p->next = NULL;
			p->city = cur->city;
			p->price = cur->price;
			first = false;
		}
		else
		{
			temp = p;
			p->next = new stackNode;
			p = p->next;
			p->prev = temp;
			p->next = NULL;
			p->city = cur->city;
			p->price = cur->price;
		}
	}

	top = p;
	
}

// just retuns us the count of the stack
int stackP::getCount()
{
	return count;
}

// deconstructor. Delete, all the things!
stackP::~stackP()
{
	if (top != NULL)
	{
		while (top->prev != NULL)
		{
			top = top->prev;
			delete top->next;
			top->next = NULL;
		}
		delete top;
		top = NULL;
	}
	count = 0;
}

// checks if the stack is empty
bool stackP::isEmpty() const
{
	return bool(count == 0);
}

// the default function for pushing
void stackP::push(const char &newItem, int price)
{
	try
	{

		if (isEmpty() )
		{
			throw 2;
		}

	}
	catch (int i)
	{
		if ( i ==1)
		{
			cout << "NOTICE: The Stack is FULL" << endl;
		}
		if (i == 2)
		{
			cout << "NOTICE: The Stack is Empty" << endl;
		}
	}

	if (top == NULL)
	{
		stackNode * x;
		x = new stackNode;
		x->next = NULL;
		x->prev = NULL;
		x->city = newItem;
		x->price = price;
		top = x;
		count ++;

	}
	else
	{
		stackNode * x;
		x = new stackNode;
		x->next = NULL;
		x->prev = top;
		x->city = newItem;
		x->price = price;
		top = x;
		count ++;
	}



}

// default function for popping

void stackP::pop()
{
	try
	{
		// if there is nothing to pop. You pop nothing
		if (isEmpty())
		{
			throw 1;

		}
	}
	catch (int i)
	{
		if(i ==1)
		{
			cout << "NOTICE,Cant pop. stack does not have anything in it. Fill it please" << endl;
		}

	}
	if (count > 1)
		// if there is stuff to actually pop
	{
		// move throughout the list from the top all the way to the bottom by continuously moving pointer
		// to the one before. Deleting the next pointer and setting it to NULL so that it is the end. 
		top = top->prev;
		delete top->next;
		top->next = NULL;
		count --;
	}
	else if(count ==  1)
	{
		delete top;
		top = NULL;
		count --;
	}

}


// peeks at the next variables
char stackP::peek()
{
	try
	{

		// if there is nothing to peek at. Obviously you dont peek it
		if(isEmpty())
		{
			throw 1;
		}
		else
		{
			// otherwise, just give it the last thing in the stock duh
			return top->city;
		}
	}
	catch(int i)
	{
		if(i == 1)
			cout << "NOTICE: Stack is empty. Nothing to peek at." << endl;
	}
	// return the top city as you need to return something as this is non-void
    return top ->city;
}