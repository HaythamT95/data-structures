#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "heap.h"

#define FAIL -1

static int CmpNumbers(const void* data1, const void* data2, const void* params);
static int IsMatch(const void* data1, const void* data2);

static int TestRunner();
static int TestHeapCreate();
static int TestHeapEnqueue();
static int TestHeapSize();
static int TestHeapRemove();

heap_ty *heap = NULL;

int main()
{
	int state = SUCCESS;

	state = TestRunner();

	return state;
}

int TestRunner()
{
	int state = SUCCESS;

	state = TestHeapCreate();

	if(SUCCESS == state)
	{
		printf("Test Create Heap Succeed :)\n");
	}
	else
	{
		printf("Test Create Heap Failed :(\n");
	}

	state = TestHeapEnqueue();

	if(SUCCESS == state)
	{
		printf("Test Enqueue Heap Succeed :)\n");
	}
	else
	{
		printf("Test Enqueue Heap Failed :(\n");
	}

	state = TestHeapSize();

	if(SUCCESS == state)
	{
		printf("Test Size Heap Succeed :)\n");
	}
	else
	{
		printf("Test Size Heap Failed :(\n");
	}

	state = TestHeapRemove();

	if(SUCCESS == state)
	{
		printf("Test Remove Heap Succeed :)\n");
	}
	else
	{
		printf("Test Remove Heap Failed :(\n");
	}

	return state;
}

int TestHeapCreate()
{
	int test_result = SUCCESS;
	int is_empty_result = 0;
	int is_empty_expected = 1;

	heap = HeapCreate(0, CmpNumbers, NULL);

	is_empty_result = HeapIsEmpty(heap);

	if(NULL == heap || is_empty_expected != is_empty_result)
	{
		test_result = FAIL;
	}

	HeapDestroy(heap);

	return test_result;
}

int TestHeapEnqueue()
{
	int test_result = SUCCESS;
	int element1 = 1;
	int element2 = 2;
	int element3 = 3;
	int element4 = 4;
	int element10 = 10;
	int element5 = 5;
	int element15 = 15;
	int element0 = 0;
	int *result = NULL;

	heap = HeapCreate(0, CmpNumbers, NULL);

	if(NULL == heap)
	{
		test_result = FAIL;
	}

	HeapEnqueue(heap, &element4);
	HeapEnqueue(heap, &element2);
	HeapEnqueue(heap, &element3);
	HeapEnqueue(heap, &element10);
	HeapEnqueue(heap, &element5);
	HeapEnqueue(heap, &element15);
	HeapEnqueue(heap, &element0);

	result = HeapDequeue(heap);

	if(*result != element0)
	{
		test_result = FAIL;
	}

	result = HeapPeek(heap);

	if(*result != element2)
	{
		test_result = FAIL;
	}

	HeapDestroy(heap);

	return test_result;
}


int TestHeapSize()
{
	int test_result = SUCCESS;
	int element1 = 1;
	int element2 = 2;
	int element3 = 3;
	int element4 = 4;
	int element10 = 10;
	int element0 = 0;
	size_t result_size = 0;
	size_t expected_size = 6;
	int is_empty_result = 0;
	int is_empty_expected = 0;

	heap = HeapCreate(0, CmpNumbers, NULL);

	if(NULL == heap)
	{
		test_result = FAIL;
	}

	HeapEnqueue(heap, &element4);
	HeapEnqueue(heap, &element2);
	HeapEnqueue(heap, &element3);
	HeapEnqueue(heap, &element10);
	HeapEnqueue(heap, &element1);
	HeapEnqueue(heap, &element0);

	result_size = HeapSize(heap);
	is_empty_result = HeapIsEmpty(heap);

	if(result_size != expected_size || is_empty_expected != is_empty_result)
	{
		test_result = FAIL;
	}

	HeapDestroy(heap);

	return test_result;
}

int TestHeapRemove()
{
	int test_result = SUCCESS;
	int element1 = 1;
	int element2 = 2;
	int element3 = 3;
	int element4 = 4;
	int element10 = 10;
	int element5 = 5;
	int element15 = 15;
	int element0 = 0;
	int *result = NULL;
	size_t result_size = 0;
	size_t expected_size = 5;

	heap = HeapCreate(0, CmpNumbers, NULL);

	if(NULL == heap)
	{
		test_result = FAIL;
	}

	HeapEnqueue(heap, &element4);
	HeapEnqueue(heap, &element2);
	HeapEnqueue(heap, &element3);
	HeapEnqueue(heap, &element10);
	HeapEnqueue(heap, &element5);
	HeapEnqueue(heap, &element15);
	HeapEnqueue(heap, &element0);

	result = HeapRemove(heap, IsMatch, &element0);

	result = HeapRemove(heap, IsMatch, &element2);

	result_size = HeapSize(heap);

	if(*result != element2 || result_size != expected_size )
	{
		test_result = FAIL;
	}

	result = HeapPeek(heap);

	if(*result != element3)
	{
		test_result = FAIL;
	}

	HeapDestroy(heap);

	return test_result;
}

int CmpNumbers(const void* data1, const void* data2, const void* params)
{
	(void)params;

	if(*(int*)data1 > *(int*)data2)
	{
		return 1;
	}
	else if(*(int*)data1 < *(int*)data2)
	{
		return -1;
	}
	return 0;
}

int IsMatch(const void* data1, const void* data2)
{
	if(*(int*)data1 == *(int*)data2)
	{
		return 1;
	}
	return 0;
}