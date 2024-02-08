/*******************************************************************************
Project: Vector (WS14)
Name: Haytham
Reviewer: Jonathan
Date: 05.10.2023
Version: 1.0 Initial
*******************************************************************************/

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h> /*size_t*/

typedef struct vector vector_ty;
typedef int status_ty;

/*
Function Description:create a vector with a capacity that was stated by the user

Return value: pointer to the vector

Notes: if memory allocation for the vector fails, returns NULL. 
	Undefined behaviour if capacity or element_size is set to 0.

Time Complexity: O(1)
*/
vector_ty *VectorCreate(size_t capacity , size_t size_of_element);

/*
Function Description: Set the value at a specified index in the vector.

Return value: void

Notes: 
- If 'vector' is NULL or 'index' is out of bounds, the function behavior is 
  undefined.
- 'val' should point to a valid value of the appropriate data type.

Time Complexity: O(1)
*/
void VectorSetValue( vector_ty *vector, size_t index, const void* val);


/*
Function Description: Get the value at a specified index in the vector.

Return value: 
- Pointer to the value at the specified index, 
   or NULL if 'vector' is NULL or 'index' is out of bounds.

Notes: 
- The returned pointer points to the value within the vector.
- Any modifications made to the returned value will affect the vector.

Time Complexity: O(1)
*/
void *VectorGetValue( vector_ty *vector, size_t index);

/*
Function Description: Get the current size (number of elements) of the vector.

Return value: 
- The current size of the vector.

Notes: 
- If 'vector' is NULL, the function returns 0.

Time Complexity: O(1)
*/
size_t VectorGetSize( vector_ty *vector);

/*
Function Description: Destroy the vector and free its resources.

Return value: void

Notes: 
- If 'vector' is NULL, the function has no effect.
- After calling this function, the 'vector' pointer becomes invalid and 
  should not be used.

Time Complexity: O(1)
*/
void VectorDestroy( vector_ty *vector);

/*
Function Description: Check if the vector is empty (contains no elements).

Return value: 
- STATUS_SUCCESS (1) if the vector is empty.
- STATUS_FAILURE (0) if the vector is not empty or 'vector' is NULL.

Notes: 
- The function checks if the vector's size is zero to determine emptiness.

Time Complexity: O(1)
*/
status_ty VectorIsEmpty(const vector_ty *vector);

/*
Function Description: Get the maximum capacity (number of elements) the vector
		 can hold without resizing.

Return value: 
- The maximum capacity of the vector.

Notes: 
- If 'vector' is NULL, the function returns 0.

Time Complexity: O(1)
*/
size_t VectorGetMaxCapacity( vector_ty *vector);

/*
Function Description:Shrink vector according to shrink factor

Return value: status of operation

Notes: if memory allocation for the vector fails, returns False. 
	Undefined behaviour if pointer is NULL.
	
Time Complexity: O(1)
*/
status_ty VectorShrinkToFit(vector_ty *vector);

/*
Function Description:Add another value to the end of the vector

Return value: status of operation

Notes: if adding to the vector fails, returns False. 
	Undefined behaviour if pointer is NULL or element is of wrong type.
	
Time Complexity: O(1)
*/
status_ty VectorPushBack(vector_ty *vector, void *element);

/*
Function Description:Remove value from the end of the vector

Return value: status of operation

Notes: if removing from vector fails, returns False. 
	Undefined behaviour if pointer is NULL.
	
Time Complexity: O(1)
*/
status_ty VectorPopBack(vector_ty *vector);

/*
Function Description:Change capacity of vector

Return value: status of operation

Notes: if resizing the vector fails returns False. 
	Undefined behaviour if pointer is NULL or new_capicty <= 0.
	
Time Complexity: O(1)
*/
status_ty VectorReserve(vector_ty *vector, size_t new_capacity);

#endif /*__VECTOR_H__*/
