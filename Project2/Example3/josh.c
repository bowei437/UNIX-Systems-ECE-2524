#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef int dataType;
dataType postfix_math(char *arr);
static dataType peek();
static void push(dataType num);
static dataType pop();
struct stack
{
	dataType *number;
	bool two_pop;
	bool more_data;
	int count;
	int size;
}my_stack;

int main(int argc, char *argv[])
{
	my_stack.number = (dataType *)malloc(sizeof(dataType) * 50);
	my_stack.count = 0;
	my_stack.size = 0;
	my_stack.two_pop = true;
	my_stack.more_data = false;

	dataType answer;
	char *str;
	str = (char*)malloc(sizeof(char) * 50);
	scanf("%[^\n]s", str);
	answer = postfix_math(str);
	if (my_stack.two_pop && !my_stack.more_data)
		printf("answer is: %d\n\n", answer);
		
	
	return 0;
}

static dataType peek()
{
	return my_stack.number[my_stack.count - 1];
}
static void push(dataType num)
{
	
	my_stack.number[my_stack.count] = num;
	my_stack.count++;
	my_stack.size++;
}

static dataType pop()
{
	--my_stack.size;
	return my_stack.number[--my_stack.count];
}

dataType postfix_math(char *arr)
{
	int i;
	int j = 0;
	int size;
	for (size = 0; arr[size] != '\0'; size++); //for the array size

	int temp = 0;
	bool pushed = false;
	for (i = 0; i < size; i++)
	{
		if (arr[i] == ' ');
		else if (arr[i] == '+')
		{
			if (my_stack.size > 1)//this is my check to make sure I have two values in my
			{	//stack to pop...if not then there is an error
				dataType a = pop();
				dataType b = pop();
				push(b+a);
			}

			else //my error
			{
				my_stack.two_pop = false;
				printf("Error -- not enough input/numbers\n\n");
				return 0;
			}
				
		}
		else if (arr[i] == '*')
		{

			if (my_stack.size > 1)
			{
				dataType a = pop();
				dataType b = pop();
				push(b*a);
			}

			else
			{
				my_stack.two_pop = false;
				printf("Error -- not enough input/numbers\n\n");
				return 0;
			}
		}
		else if (arr[i] == '-')
		{

			if (my_stack.size > 1)
			{
				dataType a = pop();
				dataType b = pop();
				push(b-a);
			}

			else
			{
				my_stack.two_pop = false;
				printf("Error -- not enough input/numbers\n\n");
				return 0;
			}
		}
		else if (arr[i] == '/')
		{

			if (my_stack.size > 1)
			{
				dataType a = pop();
				dataType b = pop();
				push(b/a);
			}

			else
			{
				my_stack.two_pop = false;
				printf("Error -- not enough inputs/numbers\n");
				return 0;
			}
		}/*
		else if (arr[i] == '^') 
		{

			if (my_stack.size > 1)
			{
				dataType a = pop();
				dataType b = pop();
				push(pow(b,a));
			}

			else
			{
				my_stack.two_pop = false;
				printf("Error -- not enough input/operators\n");
				return 0;
			}
		}*/
		else
		{
			if (arr[i + 1] == ' ')
			{
				if (!pushed)
				{
					dataType num = arr[i] - '0';
					push(num);
				}
				else
				{
					temp = temp*(10) + (arr[i] - '0');
					push(temp);
					temp = 0;
					pushed = false;
				}
				
			}
			else
			{
				pushed = true;
				temp = temp*(10) + (arr[i]- '0');
			}
		}
	}
	//error condition where my stack has more than enough input
		if (my_stack.size > 1)
		{
			my_stack.more_data = true;
			printf("Error -- too much input/numbers!\n\n");
		}

	return my_stack.number[0];
}
