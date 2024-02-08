#include <stdio.h> /*printf*/

#include "priority.h"

enum State{FAIL,SUCCESS};

static int TestRunner();

static int TestCreatePQueue();

static int TestPQueueInsert();
static int TestPQueueIsEmpty();
static int TestPQueueClear();
static int TestPQueueSize();

static int TestPQueuePeek();
static int TestPQueueDequeue();

static int TestPQueueErase();


int CompareIntegers(const void *data1, const void *data2);
int IsMatch(const void *data1,const void *data2);

priority_ty *p_queue = NULL;

int main()
{
	int state = SUCCESS;
	state = TestRunner();
	return state;
}

int TestRunner()
{
	int state = SUCCESS;

	state = TestCreatePQueue();

	if(SUCCESS == state)
	{
		printf("Test Create PQueue Succeed :)\n");
	}
	else
	{
		printf("Test Create PQueue Failed :(\n");
	}

	state = TestPQueueInsert();

	if(SUCCESS == state)
	{
		printf("Test Insert PQueue Succeed :)\n");
	}
	else
	{
		printf("Test Insert PQueue Failed :(\n");
	}

	state = TestPQueueIsEmpty();

	if(SUCCESS == state)
	{
		printf("Test IsEmpty PQueue Succeed :)\n");
	}
	else
	{
		printf("Test IsEmpty PQueue Failed :(\n");
	}

	state = TestPQueueClear();

	if(SUCCESS == state)
	{
		printf("Test Clear PQueue Succeed :)\n");
	}
	else
	{
		printf("Test Clear PQueue Failed :(\n");
	}

	state = TestPQueueSize();

	if(SUCCESS == state)
	{
		printf("Test Size PQueue Succeed :)\n");
	}
	else
	{
		printf("Test Size PQueue Failed :(\n");
	}

	state = TestPQueuePeek();

	if(SUCCESS == state)
	{
		printf("Test Peek PQueue Succeed :)\n");
	}
	else
	{
		printf("Test Peek PQueue Failed :(\n");
	}

	state = TestPQueueDequeue();

	if(SUCCESS == state)
	{
		printf("Test Dequeue PQueue Succeed :)\n");
	}
	else
	{
		printf("Test Dequeue PQueue Failed :(\n");
	}

	state = TestPQueueErase();

	if(SUCCESS == state)
	{
		printf("Test Erase PQueue Succeed :)\n");
	}
	else
	{
		printf("Test Erase PQueue Failed :(\n");
	}

	return state;
}

int TestCreatePQueue()
{
	int test_result = SUCCESS;

	queue_cmp_func_ty cmp_func = CompareIntegers;

	p_queue = PriorityCreate(cmp_func);

	if(NULL == p_queue)
	{
		test_result = FAIL;
	}

	PriorityDestroy(p_queue);

	return test_result;
}

int TestPQueueInsert()
{
	int test_result = SUCCESS;

	queue_cmp_func_ty cmp_func = CompareIntegers;

	int element = 1;
	int element2 = 0;
	int element3 = 3;
	int length_result = 0;
	int length_expected = 3;

	p_queue = PriorityCreate(cmp_func);

	PriorityEnqueue(p_queue, &element);
	PriorityEnqueue(p_queue, &element2);
	PriorityEnqueue(p_queue, &element3);
	length_result = PrioritySize(p_queue);

	if(length_result != length_expected)
	{
		test_result = FAIL;
	}

	PriorityDestroy(p_queue);

	return test_result;
}

int TestPQueueIsEmpty()
{
	int test_result = SUCCESS;
	int is_empty_result = 0;
	int is_empty_expected = 1;
	queue_cmp_func_ty cmp_func = CompareIntegers;

	p_queue = PriorityCreate(cmp_func);

	is_empty_result = PriorityIsEmpty(p_queue);

	if(is_empty_expected != is_empty_result)
	{
		test_result = FAIL;
	}

	PriorityDestroy(p_queue);

	return test_result;
}

int TestPQueueClear()
{
	int test_result = SUCCESS;
	int is_empty_result = 0;
	int is_empty_expected = 1;
	queue_cmp_func_ty cmp_func = CompareIntegers;
	int element = 1;
	int element2 = 0;
	int element3 = 3;

	p_queue = PriorityCreate(cmp_func);
	PriorityEnqueue(p_queue, &element);
	PriorityEnqueue(p_queue, &element2);
	PriorityEnqueue(p_queue, &element3);

	PriorityClear(p_queue);
	is_empty_result = PriorityIsEmpty(p_queue);

	if(is_empty_expected != is_empty_result)
	{
		test_result = FAIL;
	}

	PriorityDestroy(p_queue);

	return test_result;
}

int TestPQueueSize()
{
	int test_result = SUCCESS;
	int length_result = 0;
	int length_expected = 3;
	queue_cmp_func_ty cmp_func = CompareIntegers;
	int element = 1;
	int element2 = 0;
	int element3 = 3;

	p_queue = PriorityCreate(cmp_func);
	PriorityEnqueue(p_queue, &element);
	PriorityEnqueue(p_queue, &element2);
	PriorityEnqueue(p_queue, &element3);

	length_result = PrioritySize(p_queue);

	if(length_result != length_expected)
	{
		test_result = FAIL;
	}

	PriorityDestroy(p_queue);

	return test_result;
}

int TestPQueuePeek()
{
	int test_result = SUCCESS;
	int *result = NULL;
	queue_cmp_func_ty cmp_func = CompareIntegers;
	int element = 1;
	int element2 = 0;
	int element3 = 3;

	p_queue = PriorityCreate(cmp_func);
	PriorityEnqueue(p_queue, &element3);
	PriorityEnqueue(p_queue, &element);
	PriorityEnqueue(p_queue, &element2);

	result = PriorityPeek(p_queue);

	if(*result != element2)
	{
		test_result = FAIL;
	}

	PriorityDestroy(p_queue);

	return test_result;
}

int TestPQueueDequeue()
{
	int test_result = SUCCESS;
	queue_cmp_func_ty cmp_func = CompareIntegers;
	int element = 1;
	int element2 = 0;
	int element3 = 3;
	int length_result = 0;
	int length_expected = 2;

	p_queue = PriorityCreate(cmp_func);
	PriorityEnqueue(p_queue, &element3);
	PriorityEnqueue(p_queue, &element);
	PriorityEnqueue(p_queue, &element2);

	PriorityDequeue(p_queue);

	length_result = PrioritySize(p_queue);

	if(length_expected != length_result)
	{
		test_result = FAIL;
	}

	PriorityDestroy(p_queue);

	return test_result;
}

int TestPQueueErase()
{
	int test_result = SUCCESS;
	queue_cmp_func_ty cmp_func = CompareIntegers;
	int element = 1;
	int element2 = 0;
	int element3 = 3;
	int is_even = 2;
	int length_result = 0;
	int length_expected = 2;

	p_queue = PriorityCreate(cmp_func);
	PriorityEnqueue(p_queue, &element3);
	PriorityEnqueue(p_queue, &element);
	PriorityEnqueue(p_queue, &element2);

	PriorityErase(p_queue,IsMatch,&is_even);
	length_result = PrioritySize(p_queue);

	if(length_expected != length_result)
	{
		test_result = FAIL;
	}

	PriorityDestroy(p_queue);

	return test_result;
}

int CompareIntegers(const void *data1, const void *data2)
{
	if(*(int*)data1 > *(int*)data2)
	{
		return -1;
	}
	else if(*(int*)data1 < *(int*)data2)
	{
		return 1;
	}
	return 0;
}

int IsMatch(const void *data1, const void *data2)
{
	return *(int*)data1 % *(int*)data2 == 1;
}