/*****************************************************************************/
/*
Project: RECURSION
Name: Haytham
Reviewer: Najeeb
Date: 04.12.2023
Version: 1.0 - Initial        
*/
/*****************************************************************************/

#ifndef __RECURSION_H__
#define __RECURSION_H__

#include <stddef.h> /*size_t*/

#include "stack.h"

int Fibonacci(int element_index);

size_t StrlenRecursion(const char* str);

int StrcmpRecursion(char *s1, char *s2);

char* StrcpyRecursion(char *dest, char *src);

char *StrcatRecursion(char *dest, char *src);

char *StrstrRecursion(char *str, char* substr);

void SortStack(stack_ty **stack);

#endif /*__RECURSION_H__*/