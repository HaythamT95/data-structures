#include <stdio.h> /*printf*/
#include <string.h> /*strcmp*/

#include "stack.h"

enum State {SUCCESS,FAIL};

static int Runner();

static int TestStackCreateDOUBLE();
static int TestStackPushDOUBLE();
static int TestStackPopDOUBLE();
static int TestStackPeekDOUBLE();
static int TestStackSizeDOUBLE();
static int TestStackIsEmptyDOUBLE();
static int TestStackCapacityDOUBLE();
static int TestStackDestroyDOUBLE();

static int TestStackCreateSTRING();
static int TestStackPushSTRING();
static int TestStackPopSTRING();
static int TestStackPeekSTRING();
static int TestStackSizeSTRING();
static int TestStackIsEmptySTRING();
static int TestStackCapacitySTRING();
static int TestStackDestroySTRING();

stack_ty *stack = NULL;

int main()
{
	int state = SUCCESS;

	state = Runner();

	return state;
}

int Runner()
{
	int state = 0;

	printf("=============Test_DOUBLE============= :)\n");

	state = TestStackCreateDOUBLE();

	if(SUCCESS == state)
	{
		printf("Test Stack Create Successeed :)\n");
	}
	else
	{
		printf("Test Stack Create Failed :(\n");
	}

	state = TestStackPushDOUBLE();

	if(SUCCESS == state)
	{
		printf("Test Stack Push Successeed :)\n");
	}
	else
	{
		printf("Test Stack Push Failed :(\n");
	}

	state = TestStackPopDOUBLE();

	if(SUCCESS == state)
	{
		printf("Test Stack Pop Successeed :)\n");
	}
	else
	{
		printf("Test Stack Pop Failed :(\n");
	}

	state = TestStackPeekDOUBLE();

	if(SUCCESS == state)
	{
		printf("Test Stack Peek Successeed :)\n");
	}
	else
	{
		printf("Test Stack Peek Failed :(\n");
	}

	state = TestStackSizeDOUBLE();

	if(SUCCESS == state)
	{
		printf("Test Stack Size Successeed :)\n");
	}
	else
	{
		printf("Test Stack Size Failed :(\n");
	}

	state = TestStackIsEmptyDOUBLE();

	if(SUCCESS == state)
	{
		printf("Test Stack IsEmpty Successeed :)\n");
	}
	else
	{
		printf("Test Stack IsEmpty Failed :(\n");
	}

	state = TestStackCapacityDOUBLE();

	if(SUCCESS == state)
	{
		printf("Test Stack Capacity Successeed :)\n");
	}
	else
	{
		printf("Test Stack Capacity Failed :(\n");
	}

	state = TestStackDestroyDOUBLE();

	if(SUCCESS == state)
	{
		printf("Test Stack Destory Successeed :)\n");
	}

	printf("\n=============Test_STRING============= :)\n");

	state = TestStackCreateSTRING();

	if(SUCCESS == state)
	{
		printf("Test Stack Create Successeed :)\n");
	}
	else
	{
		printf("Test Stack Create Failed :(\n");
	}

	state = TestStackPushSTRING();

	if(SUCCESS == state)
	{
		printf("Test Stack Push Successeed :)\n");
	}
	else
	{
		printf("Test Stack Push Failed :(\n");
	}

	state = TestStackPopSTRING();

	if(SUCCESS == state)
	{
		printf("Test Stack Pop Successeed :)\n");
	}
	else
	{
		printf("Test Stack Pop Failed :(\n");
	}

	state = TestStackPeekSTRING();

	if(SUCCESS == state)
	{
		printf("Test Stack Peek Successeed :)\n");
	}
	else
	{
		printf("Test Stack Peek Failed :(\n");
	}

	state = TestStackSizeSTRING();

	if(SUCCESS == state)
	{
		printf("Test Stack Size Successeed :)\n");
	}
	else
	{
		printf("Test Stack Size Failed :(\n");
	}

	state = TestStackIsEmptySTRING();

	if(SUCCESS == state)
	{
		printf("Test Stack IsEmpty Successeed :)\n");
	}
	else
	{
		printf("Test Stack IsEmpty Failed :(\n");
	}

	state = TestStackCapacitySTRING();

	if(SUCCESS == state)
	{
		printf("Test Stack Capacity Successeed :)\n");
	}
	else
	{
		printf("Test Stack Capacity Failed :(\n");
	}

	state = TestStackDestroySTRING();

	if(SUCCESS == state)
	{
		printf("Test Stack Destory Successeed :)\n");
	}

	return SUCCESS;
}

/*===============================DOUBLE_TESTS================================*/

int TestStackCreateDOUBLE()
{
	int state = SUCCESS;
	size_t capacity = 5;

	stack=StackCreate(capacity,sizeof(double));

	if(NULL == stack)
	{
		state = FAIL;
	}

	return state;
}

int TestStackPushDOUBLE()
{
	int state = SUCCESS;
	double num = 3;
	size_t size = 0;
	size_t expected = 1;

	StackPush(stack,&num);
	size = StackSize(stack);

	if(expected != size)
	{
		state = FAIL;
	}

	return state;
}

int TestStackPopDOUBLE()
{
	int state = SUCCESS;
	size_t size = 0;
	size_t expected = 0;

	StackPop(stack);
	size = StackSize(stack);

	if(expected != size)
	{
		state = FAIL;
	}

	return state;
}

int TestStackPeekDOUBLE()
{
	int state = SUCCESS;
	double num = 3;
	double expected = 3;
	double *result;

	StackPush(stack,&num);
	result = StackPeek(stack);

	if(expected != *result)
	{
		state = FAIL;
	}
	StackPop(stack);

	return state;
}

int TestStackSizeDOUBLE()
{
	int state = SUCCESS;
	double num = 3;
	size_t expected = 4;
	size_t result = 0;

	StackPush(stack,&num);
	StackPush(stack,&num);
	StackPush(stack,&num);
	StackPush(stack,&num);

	result = StackSize(stack);

	if(expected != result)
	{
		state = FAIL;
	}

	StackPop(stack);
	StackPop(stack);
	StackPop(stack);
	StackPop(stack);

	return state;
}

int TestStackIsEmptyDOUBLE()
{
	int state = SUCCESS;
	double num = 3;
	int expected = 0;
	int result = 0;

	StackPush(stack,&num);
	StackPush(stack,&num);
	StackPush(stack,&num);
	StackPush(stack,&num);

	result = StackIsEmpty(stack);

	if(expected != result)
	{
		state = FAIL;
	}

	StackPop(stack);
	StackPop(stack);
	StackPop(stack);
	StackPop(stack);

	expected = 1;

	result = StackIsEmpty(stack);

	if(expected != result)
	{
		state = FAIL;
	}

	return state;
}

int TestStackCapacityDOUBLE()
{
	int state = SUCCESS;
	int expected = 5;
	int result = 0;

	result = StackCapacity(stack);

	if(expected != result)
	{
		state = FAIL;
	}

	return state;
}

int TestStackDestroyDOUBLE()
{
	int state = SUCCESS;

	StackDestroy(stack);

	stack = NULL;

	return state;
}

/*===============================STRING_TESTS================================*/

int TestStackCreateSTRING()
{
	int state = SUCCESS;
	size_t capacity = 5;

	stack=StackCreate(capacity,sizeof(char*));

	if(NULL == stack)
	{
		state = FAIL;
	}

	return state;
}

int TestStackPushSTRING()
{
	int state = SUCCESS;
	char* string = "hello";
	size_t size = 0;
	size_t expected = 1;

	StackPush(stack,&string);
	size = StackSize(stack);

	if(expected != size)
	{
		state = FAIL;
	}

	return state;
}

int TestStackPopSTRING()
{
	int state = SUCCESS;
	size_t size = 0;
	size_t expected = 0;

	StackPop(stack);
	size = StackSize(stack);

	if(expected != size)
	{
		state = FAIL;
	}

	return state;
}

int TestStackPeekSTRING()
{
	int state = SUCCESS;
	char* string = "hello";
	double expected = 0;
	char* result;

	StackPush(stack,string);
	result = StackPeek(stack);

	if(expected != strcmp(string,result))
	{
		state = FAIL;
	}
	StackPop(stack);

	return state;
}

int TestStackSizeSTRING()
{
	int state = SUCCESS;
	char* string = "hello";
	size_t expected = 5;
	size_t result = 0;

	StackPush(stack,string);
	StackPush(stack,string);
	StackPush(stack,string);
	StackPush(stack,string);
	StackPush(stack,string);
	StackPush(stack,string);

	result = StackSize(stack);

	if(expected != result)
	{
		state = FAIL;
	}

	StackPop(stack);
	StackPop(stack);
	StackPop(stack);
	StackPop(stack);
	StackPop(stack);

	return state;
}

int TestStackIsEmptySTRING()
{
	int state = SUCCESS;
	char* string = "hello";
	int expected = 0;
	int result = 0;

	StackPush(stack,string);
	StackPush(stack,string);
	StackPush(stack,string);
	StackPush(stack,string);

	result = StackIsEmpty(stack);

	if(expected != result)
	{
		state = FAIL;
	}

	StackPop(stack);
	StackPop(stack);
	StackPop(stack);
	StackPop(stack);

	expected = 1;

	result = StackIsEmpty(stack);

	if(expected != result)
	{
		state = FAIL;
	}

	return state;
}

int TestStackCapacitySTRING()
{
	int state = SUCCESS;
	int expected = 5;
	int result = 0;

	result = StackCapacity(stack);

	if(expected != result)
	{
		state = FAIL;
	}

	return state;
}

int TestStackDestroySTRING()
{
	int state = SUCCESS;
	
	StackDestroy(stack);

	stack = NULL;

	return state;
}