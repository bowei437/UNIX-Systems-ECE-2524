#include <stdio.h> // standard io libraries for c
#include <stdlib.h> // standard library for c
#include <string.h> // lets me use the strlen and other string stuff
#include <ctype.h> // needs this
#include <math.h>  // i wanna do the math

// -----------------------------Typdef Struct Definition --------------------------------
typedef struct Stack_MAN
{	
	int top; // I want to know the position of my stack
	int *size; // variable dynamically allocated array of size given later. 
	

}stack;
// -----------------------------Global Variables Definition --------------------------------

stack s;
int bool = 0;
int largest = 0;
// -----------------------------Function Initial Definition --------------------------------

void initALLOC(void);
void push(int p_input);
void pop(char pop_input);
int peak(void);
void free_mem();
void empty();
int stack_check(void);
void print_final(void);

// ------------------------------------Function Code  ---------------------------------------------

void print_final(void)
{
	int i;
	printf("Largest is %d", largest);
	for(i=0;i<10;i++)
	{
		printf("\nPrint Final Stack: [%d] = %d\n",i, s.size[i] );

	}
}
// This function is not used in the code. Used as Debugging step to show me final
// stuff that is in my stack. 

int peak(void)
{	
	int peak_boo;
	peak_boo = getchar();
	//printf("\nwhat is C %c\n", peak_boo);
	if (isdigit(peak_boo))
	{
		ungetc(peak_boo, stdin);
		return 1;
	}
	else
	{
		ungetc(peak_boo, stdin);
		return 0;
	}
	
}

// peak is a function that is not used in the code. I have asked McPherson on if we are 
// required to use peak and he said that if we can get it working our way to know what
// comes next then we don't need to use it. So I didn't.  


int stack_check(void)
{
	int i;
	int localbool =0;
	for (i=1;i<s.top+1;i++)
	{
		if (s.size[i] != 0) // just makes sure that nothing is left in stack past position 1
		{
			localbool = 1; // sets local boolean to not print final result. 
		}
	}
	if (localbool == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
// Stack_check function checks to make sure that nothing is left in the stack.
// if there is, it retuns a value that will print an error on the screen. 
// One of the ERROR Code Implementations. 

void free_mem()
{
	free(s.size);
}
// Memory freeing to de-allocate what I initially wanted

void initALLOC(void)
{
	s.size = (int *) malloc( sizeof(int)*10);
	s.top = 0;
}
// initial function to initialize variable sized array and giving it dynamic memory
// allocated to it. Also sets the top to 0 as initial stuff. 

void empty()
{
	s.top = 0; // resets stack
	int i = 0; // initializes i
	largest = 0; // clears the max stack size

	for(i=0;i<50;i++) // clears stack array
	{
		s.size[i] = 0;
	}
	bool = 0; // bool used for another error condition
}
// function run at end of code to pretty much erase everything and resets variables so they
// can be resued in the next iteration of the continuous loop


void push(int p_input)
{	
	s.size[s.top] = p_input; // whatever is passed in is pushed into stack at array pos top
	s.top++; // increments top for next thing to be pushed in
	largest++; // used for printing out final stack in debugging. Not used in real code
}

void pop(char pop_input)
{	double num1; // numbers are made as doubles due to division
	double num2;
	double result; // division can result in non-integer values

	if(s.top-1 >= 1) // error condition to make sure it can pop at least twice
	{
		s.top--; // decrement top first as it was previously incremented and so is blank stack
		num2 = s.size[s.top]; // take whatever is in stack and place in num2
		s.size[s.top] = 0; // reset value in stack at that position
		s.top--; // decrement again to reach the second value we want
		num1 = s.size[s.top]; // takes that value
		s.size[s.top] = 0; // resets stack position value

		
		if (pop_input == '+')
		{
			result = num1 + num2;
		}
		else if (pop_input == '-')
		{
			result = num1 - num2;
		}
		else if (pop_input == '*')
		{
			result = num1 * num2;
		}
		else if (pop_input == '/')
		{
			result = num1 / num2;
		}
		// code above just checks keyboard input based on what is passed into pop
		// through the fgets function. It then computes it through math with this. 
		// the answer of the computation is pushed back. 

		// this isn't the final answer though as an input can be computed multiple times
		// before a final result is actually done.
		push(result);


	}
	else // run if it can't pop at least twice
	{
		bool = 1; // bool is set to 1 so main loop will avoid printing out final answer
		printf("\nError, You've given too many operators without sufficent input numbers.\nCan't pop stack twice during at least one point in operation\n");
	}


}