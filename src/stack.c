#include <stdlib.h> /*malloc,free*/
#include <string.h> /*memcpy*/
#include <assert.h> /*assert*/

#include "stack.h"

struct stack
{
	size_t capacity;
	size_t curr_size;
	size_t size_of_element;
	char *buffer;
};

stack_ty *StackCreate(size_t capacity, size_t size_of_element)
{
	size_t total_size = sizeof(stack_ty) + capacity * size_of_element;

	stack_ty *stack=(stack_ty*)malloc(total_size);

	if (NULL == stack) 
	{
		return NULL;
	}

	stack->capacity = capacity * size_of_element;
	stack->size_of_element = size_of_element;
	stack->curr_size = 0;
	stack->buffer = ((char *)stack) + sizeof(stack_ty);

	return stack;
}

void StackDestroy(stack_ty *stack)
{
	assert(NULL != stack);

	free(stack);
	stack = NULL;
}

void StackPush(stack_ty *stack, const void *element)
{
	assert(NULL != stack);
	assert(NULL != element);

	if(stack->curr_size + stack->size_of_element <= stack->capacity)
	{
		memcpy(&stack->buffer[stack->curr_size], element, stack->size_of_element);
        stack->curr_size += stack->size_of_element;
	}
}

void StackPop(stack_ty *stack)
{
	assert(NULL != stack);

	if(stack->curr_size >= stack->size_of_element)
	{
		stack->curr_size -= stack->size_of_element;
	}
}

void *StackPeek(const stack_ty *stack)
{
	assert(NULL != stack);

	if(stack->curr_size > 0)
	{
		return (void*)&stack->buffer[stack->curr_size - stack->size_of_element];
	}
	return NULL;
}

size_t StackSize(const stack_ty *stack)
{
	assert(NULL != stack);

	return stack->curr_size/stack->size_of_element;
}

int StackIsEmpty(const stack_ty *stack)
{
	assert(NULL != stack);

	return  0 == stack->curr_size;
}

size_t StackCapacity(const stack_ty *stack)
{
	assert(NULL != stack);

	return stack->capacity/stack->size_of_element;
}