/*******************************************************************************
Project: Singly Linked List 
Name: Haytham
Reviewer: Shahar
Date: 15.10.2023
Version: 1.0 Initial
*******************************************************************************/

#ifndef __SINGLY_LINKED_LIST_H__
#define __SINGLY_LINKED_LIST_H__

#include <stddef.h> /*size_t*/

typedef struct slist_node slist_node_ty;
typedef struct linkedlist slist_ty;
typedef int status_ty;

/*
Function Description: Create a list.

Return value: Pointer to the list

Notes:	1) If memory allocation for the list fails, returns NULL. 

Time Complexity: O(1)
*/
slist_ty *SListCreate(void);

/*
Function Description: Destroy the list and free its resources.

Return value: void

Notes:	1) If 'list' is NULL, the function has no effect.
		2) After calling this function, the 'list' pointer becomes invalid and 
  			should not be used.

Time Complexity: O(n)
*/
void SListDestroy(slist_ty *list);

/*
Function Description: Inserts element to the start of the list

Return value: Status - 1 SUCCESS, 0 - FAIL

Notes:	1) If adding to the vector fails, returns False. 
		2) Undefined behaviour if pointer is NULL or element is of wrong type.

Time Complexity: O(1)
*/
status_ty SListPushFront(slist_ty *list, void *element);

/*
Function Description: Inserts element to the end of the list

Return value: Status - 1 SUCCESS, 0 - FAIL

Notes:	1) If adding to the vector fails, returns False. 
		2) Undefined behaviour if pointer is NULL or element is of wrong type.

Time Complexity: O(1)
*/
status_ty SListPushBack(slist_ty *list, void *element);

/*
Function Description: Removes the first element of the list

Return value: Status - 1 SUCCESS, 0 - FAIL

Notes:	1) Undefined behaviour if pointer is NULL

Time Complexity: O(1)
*/
status_ty SListPopFront(slist_ty *list);

/*
Function Description: Removes the last element of the list

Return value: Status - 1 SUCCESS, 0 - FAIL

Notes:	1) Undefined behaviour if pointer is NULL

Time Complexity: O(1)
*/
status_ty SListPopBack(slist_ty *list);

/*
Function Description: Count the number of elements in the list

Return value: Number of elements

Notes:	1) If 'list' is NULL, return 0;

Time Complexity: O(n)
*/
size_t SListLength(const slist_ty *list);

/*
Function Description: Check if list is empty

Return value: 1 - empty, 0 - not empty

Time Complexity: O(1)
*/
int SListIsEmpty(const slist_ty *list);

/*
Function Description: Find first element that is user given function (Equals) return true

Return value: Pointer to node

Notes:	1) If 'list' is NULL, return NULL;
		2) If element not found return NULL;
		3) Equals function should return 0 if condition met, else any number

Time Complexity: O(n)
*/
slist_node_ty *SListFind(const slist_ty *list, int (*Equals)(const void *left, const void *right), const void *element);

/*
Function Description: Return node of head in given list

Return value: Pointer to head

Notes:	1) If 'list' is NULL, return NULL;

Time Complexity: O(1)
*/
slist_node_ty *SListBegin(const slist_ty *list);

/*
Function Description: Return last node in given list

Return value: Pointer to last node

Notes:	1) If 'list' is NULL, return NULL;

Time Complexity: O(1)
*/
slist_node_ty *SListEnd(const slist_ty *list);

/*
Function Description: Return next node to a given node 

Return value: Pointer to next node

Notes:	1) If 'list' is NULL, return NULL;

Time Complexity: O(1)
*/
slist_node_ty *SListNext(const slist_node_ty *current_node);

/*
Function Description: Get data from a specific node in the list

Return value: Pointer to the data stored in the node

Notes:	1) If 'slist_node_ty' is NULL, returns NULL.

Time Complexity: O(1)
*/
void *SListGetData(const slist_node_ty *node);

/*
Function Description: Set data in a specific node in the list

Return value: void

Notes:	1) If 'slist_node_ty' is NULL, the function has no effect.

Time Complexity: O(1)
*/
void SListSetData(slist_node_ty *node, void *data);

/*
Function Description: Insert a new node with the specified data after a given node in the list

Return value: Pointer to the updated list

Notes:	1) If 'list' or 'where' is NULL, the function has no effect.

Time Complexity: O(n)
*/
slist_node_ty *SListInsert(slist_ty *list, slist_node_ty *where, void *data);

/*
Function Description: Insert a new node with the specified data before a given node in the list

Return value: Pointer to the updated list

Notes:	1) If 'list' or 'where' is NULL, the function has no effect.

Time Complexity: O(n)
*/
slist_node_ty *SListInsertBefore(slist_ty *list, slist_node_ty *where, void *data);

/*
Function Description: Remove a specific node from the list

Return value: Pointer to the updated list

Notes:	1) If 'list' or 'to_remove' is NULL, the function has no effect.

Time Complexity: O(n)
*/
slist_ty *SListRemove(slist_ty *list, slist_node_ty *to_remove);

/*
Function Description: Remove the node after a specified node in the list

Return value: Pointer to the updated list

Notes:	1) If 'list' or 'to_remove' is NULL, the function has no effect.

Time Complexity: O(n)
*/
slist_ty *SListRemoveAfter(slist_ty *list, slist_node_ty *to_remove);

/*
Function Description: Apply a given action to a range of nodes in the list

Return value: 1 if all actions are successful, 0 if any action fails

Notes:	1) If 'list', 'from', 'to', or 'Action' is NULL, the function returns 0.
		2) Action function should return 0 if action succeed, else any value

Time Complexity: O(n)
*/
int SListForEach(slist_ty *list, slist_node_ty *from, slist_node_ty *to, int (*Action)(void *data, void *param), void *param);

/*
Function Description: merge two list src and dest into one -> dest 

Return value: void

Time Complexity: O(n)
*/
void SListAppend(slist_ty *dest,slist_ty *src);

void PrintSList(const slist_ty *list);

#endif /*__SINGLY_LINKED_LIST_H__*/