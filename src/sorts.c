#include <stddef.h> /*size_t*/
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc, free*/
#include <string.h> /*memcpy*/

#include "sorts.h"

static void swap(void *a, void *b, size_t size);
static int merge(int *array, int left, int right, int mid);
static size_t partition(void* base,  size_t nmemb, size_t size, int(*cmp_func)(const void*, const void *));

void swap(void *a, void *b, size_t size)
{
	void* temp = (void*)malloc(size);
    
    if (NULL == temp) 
    {
        return;
    }

    memcpy(temp, a, size);

    memcpy(a, b, size);

    memcpy(b, temp, size);

    free(temp);
}

void OptimizedBubbleSort(int *array, size_t len)
{
	size_t i = 0;
	size_t j = 0;
	int swapped = 0;

	assert(NULL != array);
	assert(0 != len);

	for (i = 1; i < len; ++i)
	{
		swapped = 0;
		for (j = 0; j < len - 1; ++j)
		{
			if(array[j] > array[j+1])
			{
				swap(&array[j],&array[j+1],sizeof(int));
				swapped = 1;
			}
		}
		if (swapped == 0)
        {
           	break;
        }
	}
}

void BubbleSort(int *array, size_t len)
{
	size_t i = 0;
	size_t j = 0;

	assert(NULL != array);
	assert(0 != len);

	for (i = 1; i < len; ++i)
	{
		for (j = 0; j < len - 1; ++j)
		{
			if(array[j] > array[j+1])
			{
				swap(&array[j],&array[j+1],sizeof(int));
			}
		}
	}
}

void SelectionSort(int *array, size_t len)
{
	size_t i = 0;
	size_t j = 0;
	size_t i_min = 0;

	assert(NULL != array);
	assert(0 != len);

	for(i = 0; i < len - 1; ++i)
	{
		i_min = i;

		for (j = i + 1; j < len; ++j)
		{
			if(array[j] < array[i_min])
			{
				i_min = j;
			}
		}

		if(i_min != i)
		{
			swap(&array[i],&array[i_min], sizeof(int));
		}
	}

}

void InsertionSort(int *array, size_t len)
{
	size_t i = 0;
	size_t j = 0;

	assert(NULL != array);
	assert(0 != len);

	for (i = 1; i < len - 1; ++i)
	{
		j = i;

		while(j > 0 && array[j-1] > array[j])
		{
			swap(&array[j],&array[j-1], sizeof(int));
			--j;
		}
	}
}

int BinarySearchIterative(int* array, size_t len, int data_to_find)
{
	size_t left = 0;
	size_t right = len - 1;
	int index = 0;

	/*assert*/
	assert(NULL != array);
	assert(0 != len);

	/*for i = left to right*/
	while(left != right)
	{
		/*index = (right + left) / 2*/
		index = (right + left) / 2;

		/*if array[index] LESS THAN data*/
		if(array[index] < data_to_find)
		{
			/*left = index + 1*/
			left = index + 1;
		}
		/*if array[index] BIGGER THAN data*/
		else if(array[index] > data_to_find)
		{
			/*right = index - 1*/
			right = index - 1;
		}
		/*else found*/
		else
		{	
			/*return index*/
			return index;
		}
	}

	/*not found return -1*/
	return -1;
}

int BinarySearchRecursive(int* array, int data_to_find, int left, int right)
{
	int index = 0;

	/*assert*/
	assert(NULL != array);

	/*if (left > right)*/
	if(left == right)
	{
		/*return -1*/
		return -1;
	}

	/*index = (right + left) / 2*/
	index = (right + left) / 2;


	/*if array[index] LESS THAN data*/
	if(array[index] < data_to_find)
	{
		/*return BinarySearchRecursive(array, data_to_find, index + 1, right)*/
		return BinarySearchRecursive(array, data_to_find, index + 1, right);
	}

	/*if array[index] BIGGER THAN data*/
	else if(array[index] > data_to_find)
	{
		/*return BinarySearchRecursive(array, data_to_find, left, index - 1)*/
		return BinarySearchRecursive(array, data_to_find, left, index - 1);
	}
	/*if array[index] EQUAL TO data*/
	else
	{
		/*return index*/
		return index;
	}
}

int MergeSort(int* array, size_t len)
{
	int ret = 0;
	size_t mid = 0;
	/*assert*/
	assert(NULL != array);

	/*if len <= 1*/
	if(len <= 1 || ret != 0)
	{
		/*return ret*/
		return ret;
	}

	/*mid = (len) / 2*/
	mid = len / 2;

	/*MergeSort(array, mid) */
	ret = MergeSort(array, mid);

	if(ret != 0)
	{
		/*return ret*/
		return ret;
	}

	/*MergeSort(array + mid, len)*/
	ret = MergeSort(array + mid, len - mid);

	if(ret != 0)
	{
		/*return ret*/
		return ret;
	}

	/*ret = merge(array, 0, mid - 1, len - 1)*/
	ret = merge(array, 0, mid - 1, len - 1);

	return ret;
}

int merge(int *array, int left, int mid, int right)
{
	int left_size = 0;
	int right_size = 0;
	int *left_array = NULL;
	int *right_array = NULL;
	int i = 0;
	int j = 0;
	int k = 0;

	/*assert*/
	assert(NULL != array);

	/*calculate the sizes of the two subarrays*/
	left_size = mid - left + 1;
	right_size = right - mid;

	/*create temporary arrays for the left and right subarrays*/
	left_array = (int*)malloc(sizeof(int) * left_size);

	if(NULL == left_array)
	{
		return 1;
	}

	right_array = (int*)malloc(sizeof(int) * right_size);

	if(NULL == right_array)
	{
		free(left_array);
		return 1;
	}

	/*copy data from the original array to the temporary arrays*/
	for (i = 0; i < left_size; ++i)
	{
		left_array[i] = array[i];
	}

	for (i = 0; i < right_size; ++i)
	{
		right_array[i] = array[i + mid + 1];
	}

	i = 0;
	j = 0;
	k = 0;

	/*merge the two subarrays back into the original array*/
	while(i < left_size && j < right_size)
	{
		if(left_array[i] < right_array[j])
		{
			array[k] = left_array[i];
			++i;
		}
		else
		{
			array[k] = right_array[j];
			++j;
		}
		++k;
	}

	/*copy the remaining elements from left_array[], if any*/
	while(i < left_size)
	{
		array[k] = left_array[i];
		++i;
		++k;
	}

	/*copy the remaining elements from right_array[], if any*/
	while(j < right_size)
	{
		array[k] = right_array[j];
		++j;
		++k;
	}
    
    /*free the temporary arrays*/
    free(right_array);
    free(left_array);

    return 0;
}

size_t partition(void* base,  size_t nmemb, size_t size, int(*cmp_func)(const void*, const void *)) 
{
	size_t i = 0;
	char* pivot = NULL;
	size_t leftwall = 0; /*index to keep track of elements less than the pivot*/
	char* element = NULL;

	assert(NULL != base);
	assert(NULL != cmp_func);

	/*choose a pivot from last index*/
	pivot = (char*)base + (nmemb - 1) * size;

	/*for each element in array to nmemb(size)*/
	for ( i = 0; i < nmemb - 1; ++i) 
    {
    	/*read element*/
        element = (char*)base + i * size;

        /*if element less than pivot*/
        if (cmp_func(element, pivot) < 0) 
        {
        	 /*swap pivot back to its final position*/
            swap((char *)base + leftwall * size, element, size);

            /*move element pointer*/
            ++leftwall;
        }
    }

	/*swap pivot back to its final position*/
    swap((char *)base + leftwall * size, pivot, size);

    /*return the final position of the pivot*/
	return leftwall;
}

void QSort(void* base_, size_t nmemb_, size_t size_, int(*cmp_func)(const void*, const void*))
{	
	size_t pivot_location = 0;

	assert(NULL != base_);
	assert(NULL != cmp_func);

	if (nmemb_ > 1) 
    {
    	/*partition the array and get the pivot index*/
        pivot_location = partition(base_, nmemb_, size_, cmp_func);

        /*recursively sort the left partition*/
        QSort(base_, pivot_location, size_, cmp_func);

        /*recursively sort the right partition*/
        QSort((char*)base_ + (pivot_location + 1) * size_, nmemb_ - pivot_location - 1, size_, cmp_func);
    }
}

void HeapSort()
{
	/*Build heap (rearrange array)*/

    /*One by one extract an element from the heap*/
        /*Move current root to end*/
        /*call max heapify on the reduced heap*/ 
}