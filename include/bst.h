/******************************************************************************
Project: Binary Search Tree
Name: Haytham
Reviewer: Jonathan
Date: 27.11.23
Version: 1.0
******************************************************************************/

#ifndef __BST_H__
#define __BST_H__

typedef struct bst bst_ty;
typedef struct bst_iter bst_iter_ty;

typedef enum
{
	MALLOC_FAIL = -1,
	SUCCESS = 0
}status_bst_ty;

/*
	Description: Check if data1 is before data2
	Return value: 1 true, 0 false
	Note: params can be NULL value
*/
typedef int(*is_before_func_ty)(const void *data1, const void *data2,
														const void *params);

/*
	Note: params can be NULL value
*/
bst_ty *BSTCreate(is_before_func_ty is_before_, const void *params_);

/*
	Note: Null is allowed
*/
void BSTDestroy(bst_ty *bst_);

size_t BSTSize(const bst_ty *bst_);

int BSTIsEmpty(const bst_ty *bst_);

/*
	Return value: 0 Success, otherwise failed
*/
status_bst_ty BSTInsert(bst_ty *bst_, void *data_);

/*
	Return value: Next iterator
	Note: Invalidates all existing iterators
*/
bst_iter_ty BSTRemove(bst_ty *bst_, bst_iter_ty to_delete_);

/*
	Return value: Root element
*/
bst_iter_ty BSTBegin(bst_ty *bst_);

bst_iter_ty BSTEnd(bst_ty *bst_);

bst_iter_ty BSTPrev(bst_iter_ty iter_);

bst_iter_ty BSTNext(bst_iter_ty iter_);

/*
	Return value: 1 True, 0 False
*/
int BSTIsSameIter(bst_iter_ty first_, bst_iter_ty second_);

void *BSTGetData(bst_iter_ty iter_);

/*
	Return value: Iterator for element
	Note: If not found returns iterator with NULL value
*/
bst_iter_ty BSTFind(bst_ty *bst_, const void *element_);

/*
	Description: Manipulate data using given function
	Return value: 0 Failed, otherwise success
*/
typedef int(*bst_op_func_ty)(void *data, void *func_param);

/*
	Description: Manipulate data between given iterators with given function, 
					doesn't include to_ [from - to_)
	Return value: value of op_func_ - 0 Success, otherwise failed
	Note: func_param can be NULL value
	Undefined behavior: Manipulation on data that BST relies on upon
						inserting element
*/
status_bst_ty BSTForEach(bst_iter_ty from_, bst_iter_ty to_,
								bst_op_func_ty op_func_, void *func_param_);


struct bst_metadata;

typedef struct bst_iter
{
    struct bst_metadata* where;
}bst_iter_ty;

#endif /*__BST_H__*/