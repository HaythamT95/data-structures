/*****************************************************************************/
/*
Project: AVL
Name: Haytham
Reviewer: ***
Date: 05.12.2023
Version: 1.0 - Initial        
*/
/*****************************************************************************/

#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h> /*size_t*/

typedef struct avl avl_ty;

typedef enum
{
	MALLOC_FAIL = -1,
	SUCCESS = 0,
	TRAVERSAL_ERR = 2
}avl_status_ty;

/*
	Description: Check if data1 is before data2
	Return value: 1 true, 0 false
	Note: params can be NULL value
*/
typedef int(*is_before_func_ty)(const void *data1_, const void *data2_,
														const void *params_);

/*
	Input: Function to compare data, and more params if needed
	Return: NULL if fails to allocate
	Note: is_before_params_ can be NULL
	Complexity: O(1)
*/
avl_ty* AVLCreate(is_before_func_ty is_before_, const void *is_before_params_);

/*
	Note: NULL is allowed
	Complexity: O(nlogn)
*/
void AVLDestroy(avl_ty *avl_);

/*
	Return: Pointer to data - Found, NULL - Not found
	Complexity: O(logn)
*/
void* AVLRemove(avl_ty *avl_, const void* key_);

/*
	Return: Non zero if fails
	Complexity: O(logn)
*/
avl_status_ty AVLInsert(avl_ty *avl_, void *data_);

/*
	Description: Count Max Height of AVL Tree
	Complexity: O(logn)
*/
size_t AVLHeight(const avl_ty *avl_);

/*
	Complexity: O(n)
*/
size_t AVLSize(const avl_ty *avl_);

/*
	Complexity: O(1)
*/
int AVLIsEmpty(const avl_ty *avl_);

/*
	Return: NULL if not found
	Complexity: O(logn)
	IMPROTANT: Don't change the fields that influence order,
				the object is still in the set
*/
void* AVLFind(avl_ty *avl_, const void* key_);

typedef enum 
{
	PRE_ORDER,
	IN_ORDER,
	POST_ORDER
}traversal_ty;

/*
	Description: Manipulate data using given function
	Return value: Non zero if fails
	IMPROTANT: Don't change the fields that influence order - undefined
*/
typedef int(*avl_op_func_ty)(void *data_, void *func_param_);

/*
	Description: Manipulate data using given function
	Return value: Will stop if op_func_ returns non zero and return it.
	Note: func_param_ can be NULL
	Complexity: O(n)
*/
int AVLForEach(avl_ty *avl_, traversal_ty mode_,
	                               avl_op_func_ty op_func_, void *func_param_);

#endif /*__AVL_H__*/