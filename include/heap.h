/*******************************************************************************
Project: Heap Queue 
Name: Haytham
Reviewer: -
Date: 12.12.2023
Version: 1.0
*******************************************************************************/

#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h> /*size_t*/

typedef enum
{
	MALLOC_FAIL = -1,
	SUCCESS = 0
}status_heap_ty;

typedef struct heap heap_ty;

/*
	Description: Check if data1 is bigger than data2
	Return value: 1 is bigger, 0 equal, -1 less than
	Note: params can be NULL value
*/
typedef int(*heap_cmp_func_ty)(const void *data1_, const void *data2_, const void* cmp_params_);

/*
	Note: 1) params can be NULL value
		  2) initial_capacity_  - Can be 0,
		   		the capacity increases if it the element size exceeds the initial_capacity_ which may affect performance
	Complexity: O(1)
*/
heap_ty *HeapCreate(size_t initial_capacity_ , heap_cmp_func_ty compare_func_, const void* cmp_params_);

/*
	Note: NULL is allowed
	Complexity: O(1)
*/
void HeapDestroy(heap_ty* heap_);

/*
	Complexity: O(logn), If capacity is exceeded with this enqueue then its O(size)
				Amortized is still O(log(size))
*/
status_heap_ty HeapEnqueue(heap_ty* heap_, void* data_);

/*
	Return: Max/Min element and remove it
	Undefined behavior: heap is empty
	Complexity: O(logn)
*/
void *HeapDequeue(heap_ty* heap_);

/*
	Return: Max/Min element
	Undefined behavior: heap is empty
	Complexity: O(1)
*/
void *HeapPeek(heap_ty* heap_);

/*
	Complexity: O(1)
*/
int HeapIsEmpty(const heap_ty* heap_);

/*
	Complexity: O(1)
*/
size_t HeapSize(const heap_ty* heap_);

/*
	Return: first pointer that is match, if not found NULL
	Note: is_match_params_ can be NULL
	Complexity: O(n)
*/
void *HeapRemove(heap_ty* heap_, int(*is_match)(const void* data_, const void* params_), const void* is_match_params_);

void HeapPrint(heap_ty *heap);

#endif /*__HEAP_H__*/