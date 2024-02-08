/*****************************************************************************/
/*
Project: Hash
Name: Haytham
Reviewer: Najeeb
Date: 10.12.2023
Version: 1.0 - Initial        
*/
/*****************************************************************************/

#ifndef __HASH_H__
#define __HASH_H__

#include <stddef.h> /*size_t*/

typedef struct hash hash_ty;

typedef struct pair
{
	const void* key;
	void* data;
}pair_ty;

typedef enum
{
	MALLOC_FAIL = -1,
	SUCCESS = 0,
}hash_status_ty;

/*
	Return: Index to access after computation
	Note: params can be NULL value
*/
typedef size_t(*hash_func_ty)(const void* data_, const void* hash_params_);

/*
	Description: In case of the hash function generates two same hash value,
				 Use this function to compare inner keys
	Note: params can be NULL value
*/
typedef int(*is_same_key_ty)(const void* key1_, const void* key2_, const void* is_same_params_);

/*
	Input: Function to index the datad, capacity - recommended to be prime number
	Return: NULL if fails to allocate
	Complexity: O(1)
*/
hash_ty* HashCreate(size_t capacity_, hash_func_ty hash_func_, const void* hash_params_,
					is_same_key_ty is_same_, const void* is_same_params_);

/*
	Note: NULL is allowed
	Complexity: O(n)
*/
void HashDestroy(hash_ty* hash_);

/*
	Return: Pointer to data - Found, NULL - Not found
	Complexity: O(n)
*/
pair_ty HashRemove(hash_ty* hash_, const void* key_);

/*
	Return: Non zero if fails
	Complexity: O(1)
*/
hash_status_ty HashInsert(hash_ty* hash_, const void* key_, void* data_);

/*
	Complexity: O(n)
*/
size_t HashSize(hash_ty* hash_);

/*
	Complexity: O(n)
*/
int HashIsEmpty(const hash_ty* hash_);

/*
	Return: Pointer to data - Found, NULL - Not found
	Complexity: O(1)
*/
pair_ty HashFind(hash_ty* hash_, const void* key_);

/*
	Description: Manipulate data using given function
	Return value: Non zero if fails
*/
typedef int(*hash_op_func_ty)(void *data_, void *func_param_);

/*
	Return value: Will stop if op_func_ returns non zero and return it.
	Note: func_param_ can be NULL
	Note: Try not to change key
	Complexity: O(n)
*/
int HashForeach(hash_ty* hash_, hash_op_func_ty op_func_, void *func_param_);

typedef struct
{
	size_t longest_list;
	size_t median_list;
	size_t size;
	size_t capacity;
}hash_stats_ty;

/*
	Description: Check if your hash function makes the hashing efficiently
					using the stats provided
*/
hash_stats_ty HashStats(const hash_ty* hash);

#endif /*__HASH_H__*/