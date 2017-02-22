#ifndef __STACK_H__
#define __STACK_H__

typedef int stackType;

struct stack
{
	stackType *theStack;
	int size;
	int count;
};
 
#endif
#include <stdlib.h>

void initStack (struct stack*);