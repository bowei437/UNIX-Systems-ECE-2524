// Created by Bowei Zhao
// ECE 2524 UNIX 
// Professor McPherson
// November 15 2015 

// Postfix Calculator Program

#include "stack.h" // include all the code from stack. 


int main()
{
    char input[80]; // statically define maximum number of input character spaces
    printf("\033[2J\033[1;1H"); // Moves console down so you only see current input

    initALLOC(); // runs initial allocation of memory code

    while (fgets(input, 80, stdin)) // gets input with fgets through stdin, places in input with max 80char size
    {

    	printf("\n"); // move cursor down
    	int i = 0;
	    int len = strlen(input); // get string length of input to know where to go up to.
	    // this is different from sizeof as strlen goes up to \0 null character so it will give me actually up to last
	    // thing I typed in position of the char whereas sizeof will give me entire size of the defined array which would be
	    // 80 in this case. 

	    for(i = 0; i<len-1; i++)
	    {
	    	if (!isspace(input[i])) // sees if white space or just space and no input
	    	{
		    	if (isdigit(input[i])) // if its a number. We push into the stack
		    	{	int convert, c1, c2; // used to convert char to int so math and other stuff can be done on it
		    		int digits = 1;
		    		

		    		if(isdigit(input[i-1])) // sees if previous input in here at position just before is a number
		    		{	 					// this will then add those digits together as originally they come in one piece
		    			c1 = input[i] - '0'; // converts the number
		    			c2 = s.size[s.top-1]; // takes in the previous of what was given in.
		    			while(digits <= c1)
		    			{
		    				digits *= 10; // multiplies it by 10 until it is greater than c1 to find out how many times to move digit
		    			}
		    			if (c1 == 0) // if it's a 0 place, then just mult by 10 
		    			{
		    				convert = c2*10;
		    			}
		    			else
		    			{	// finally do the conversion and adding of both together
		    				convert = c2*digits+c1;

		    			}
		    			// decrement top to fit value in due to this one being the same as the previous for all intents
		    			s.top--;
		    			// push it in
		    			push(convert);
		    		}
		    		else
		    		{ // otherwise if signle digit number, just convert and push it into convert
		    			convert = input[i] - '0';
		    			push(convert);

		    		}

		    	}
		    	else if (!isdigit(input[i])) // if it's an operand (or else) it will pop it if it can
		    	{
		    		pop(input[i]);
		    		if (bool == 1)
		    		{
		    			break; // if an error condition is met, break. 
		    		}

		    	}

	    	}
	
	    }
	    //print_final();

	    if(stack_check()==1)
	    {
	    	printf("\nERROR Too much input. Too many numbers entered without sufficent operators\n");
	    }
	    else
	    {
	    	if (bool == 0)
		    {
		    	if (s.top-1 == 0)
				{
					printf("%d \n",s.size[0]); // used to just print out final answer. 
				}
		    }

	    }
	    	
	    empty(); // reset all stuff
	    input[0] = '\0'; // resets input by setting it to null characters
	    printf("\n");

    }
    free_mem(); // de-allocates array when done. 

	return 0;
}

