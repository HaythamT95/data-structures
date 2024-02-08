/*******************************************************************************
Project: Sorting Algorithms
Name: Haytham
Reviewer: ***
Date: 22.11.23
Version: 1.0
*******************************************************************************/

#ifndef __SORT_H__
#define __SORT_H__

#include <stddef.h> /*size_t*/

/*
	Best Case: O(n) (when the array is already sorted)
	Worst Case: O(n^2)
	Average Case: O(n^2)
*/
void BubbleSort(int *array, size_t len);

/*
	Best Case: O(n) (when the array is already sorted)
	Worst Case: O(n^2)
	Average Case: O(n^2)
*/
void OptimizedBubbleSort(int *array, size_t len);

/*
	Best Case: O(n^2)
	Worst Case: O(n^2)
	Average Case: O(n^2)
*/
void SelectionSort(int *array, size_t len);

/*
	Best Case: O(n) (when the array is nearly sorted)
	Worst Case: O(n^2)
	Average Case: O(n^2)
*/
void InsertionSort(int *array, size_t len);

/*
	Return: -1 if not found, else index
	Note: Array must be sorted
	Best Case: O(1)
	Worst Case: O(log n)
*/
int BinarySearchIterative(int* array, size_t len, int data_to_find);

/*
	Return: -1 if not found, else index
	Note: Array must be sorted
	Best Case: O(1)
	Worst Case: O(log n)
*/
int BinarySearchRecursive(int* array, int data_to_find, int left, int right);

/*
	Best Case: O(n log n)
	Worst Case: O(n log n)
	Average Case: O(n log n)
*/
int MergeSort(int* array, size_t len);

/*
	Best Case: O(n log n)
	Worst Case: O(n^2)
	Average Case: O(n log n)
*/
void QSort(void* base, size_t nmemb, size_t size, int(*cmp_func)(const void*, const void*));

#endif /*__SORT_H__*/
