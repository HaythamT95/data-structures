/*****************************************************************************/
/*
Project: Stack
Name: Haytham
Reviewer: Netanel
Date: 03.10.2023
Version: 1.0 - Initial
         
*/
/*****************************************************************************/

#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h>/*size_t*/

typedef struct stack stack_ty;

/*
Explanation: Create a stack with given capacity and element type
Input: Capacity, element size
Return: Pointer to stack
*/
stack_ty *StackCreate(size_t capacity, size_t size_of_element);

/*
Explanation: Deletes pointer to stack
Input: Pointer to stack
Return: None
*/
void StackDestroy(stack_ty *stack);

/*
Explanation: Insert element to stack
Input: Pointer to stack, pointer to element
Return: None
*/
void StackPush(stack_ty *stack, const void *element);

/*
Explanation: Remove top element from stack
Input: Pointer to stack
Return: None
*/
void StackPop(stack_ty *stack);

/*
Explanation: Look at top element from stack
Input: Pointer to stack
Return: Pointer to top element
*/
void *StackPeek(const stack_ty *stack);

/*
Explanation: Get number of elements in stack
Input: Pointer to stack
Return: Num of elements
*/
size_t StackSize(const stack_ty *stack);

/*
Explanation: Is stack empty or not
Input: Pointer to stack
Return: true (1), false(0)
*/
int StackIsEmpty(const stack_ty *stack);

/*
Explanation: Get maximum capacity of stack
Input: Pointer to stack
Return: Max capacity
*/
size_t StackCapacity(const stack_ty *stack);

#endif /*__STACK_H__*/