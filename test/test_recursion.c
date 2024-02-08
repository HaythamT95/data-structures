#include <stdio.h>

#include "stack.h"
#include "recursion.h"

int main()
{
	int res = 0;
	size_t result = 0;
	char* string = "HelloWorld";
	char* string2 = "Hello";
	char cpy_dest[6];
	char cat_dest[20] = "Hello, ";
    char *src1 = "World!";
    char *str = "Asem HelloWorld";
	stack_ty *stack = NULL;
	int elem1 = 1;
	int elem2 = 2;
	int elem3 = 3;
	int elem4 = 4;
	int elem5 = 5;
	res = Fibonacci(50);

	printf("Fib result = %d\n", res);

	result = StrlenRecursion(string);

	printf("Strlen = %lu\n",result);

	res = StrcmpRecursion(string,string2);

	printf("Strcmp = %d\n", res);

	StrcpyRecursion(cpy_dest, string2);

	printf("Strcpy = %s\n",cpy_dest);

	StrcatRecursion(cat_dest, src1);

	printf("Strcat = %s\n",cat_dest);

	str = StrstrRecursion(str, string2);

	printf("Strstr = %s\n",str);

	stack = StackCreate(5,sizeof(int));

	StackPush(stack,&elem1);
	StackPush(stack,&elem2);
	StackPush(stack,&elem3);
	StackPush(stack,&elem4);
	StackPush(stack,&elem5);

	SortStack(&stack);

	while(!StackIsEmpty(stack))
	{
		printf("%d\n",*(int*)StackPeek(stack));
		StackPop(stack);
	}

	StackDestroy(stack);
	return 0;
}