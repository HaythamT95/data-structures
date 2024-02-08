/*******************************************************************************
Project: Trie
Name: Haytham
Reviewer: Diana
Date: 15.12.2023
Version: 1.0
*******************************************************************************/

#ifndef __TRIE_H__
#define __TRIE_H__

#include <stddef.h> /*size_t*/

typedef struct trie trie_ty;

/*
	Complexity: O(1)
*/
trie_ty* TrieCreate(size_t depth_);

/*
	Complexity: O(n)
*/
void TrieDestroy(trie_ty* trie_);

/*
	Return: 0 - On failure OR no available numbers, 
			If number is already taken returns next available number 
	Complexity: O(log(size))
*/
unsigned long TrieGet(trie_ty* trie_, unsigned long num_);

/*
	Complexity: O(log(size))
*/
void TrieFree(trie_ty* trie_, unsigned long num_);

size_t TrieCountAvailable(trie_ty* trie_);

/*
	Return: 1 - If trie is full, 0 - there is more space
	Complexity: O(1)
*/
int TrieIsAllTaken(const trie_ty* trie_);

#endif /*__TRIE_H__*/