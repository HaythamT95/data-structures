#include <stdio.h> /*printf*/

#include "queue.h"

enum State{FAIL,SUCCESS};

static int Runner();

static int TestCreateQueue();

static int TestQueueIsEmpty();
static int TestQueueLength();

static int TestQueueEnqueue();
static int TestQueueDequeue();
static int TestQueuePeek();

static int TestQueueAppend();

queue_ty *queue = NULL;
queue_ty *queue2 = NULL;

int *p1 = NULL;

int main()
{
	int state = SUCCESS;
	state = Runner();
	return state;
}

int Runner()
{
	int state = SUCCESS;
	
	state = TestCreateQueue();

	if(SUCCESS == state)
	{
		printf("Test Create Queue Succeed :)\n");
	}
	else
	{
		printf("Test Create Queue Failed :(\n");
	}

	state = TestQueueIsEmpty();

	if(SUCCESS == state)
	{
		printf("Test IsEmpty Queue Succeed :)\n");
	}
	else
	{
		printf("Test IsEmpty Queue Failed :(\n");
	}

	state = TestQueueLength();

	if(SUCCESS == state)
	{
		printf("Test Length Queue Succeed :)\n");
	}
	else
	{
		printf("Test Length Queue Failed :(\n");
	}

	state = TestQueueEnqueue();

	if(SUCCESS == state)
	{
		printf("Test Enqueue Queue Succeed :)\n");
	}
	else
	{
		printf("Test Enqueue Queue Failed :(\n");
	}

	state = TestQueueDequeue();

	if(SUCCESS == state)
	{
		printf("Test Dequeue Queue Succeed :)\n");
	}
	else
	{
		printf("Test Dequeue Queue Failed :(\n");
	}

	state = TestQueuePeek();

	if(SUCCESS == state)
	{
		printf("Test Peek Queue Succeed :)\n");
	}
	else
	{
		printf("Test Peek Queue Failed :(\n");
	}

	state = TestQueueAppend();

	if(SUCCESS == state)
	{
		printf("Test Append Queue Succeed :)\n");
	}
	else
	{
		printf("Test Append Queue Failed :(\n");
	}

	return state;
}

int TestCreateQueue()
{
	int test_result = SUCCESS;

	queue = QCreate();

	if(NULL == queue)
	{
		test_result = FAIL;
	}

	QDestroy(queue);

	return test_result;
}

int TestQueueIsEmpty()
{
	int test_result = SUCCESS;
	int is_empty_result = 0;
	int is_empty_expected = 1;

	queue = QCreate();

	is_empty_result = QIsEmpty(queue);

	if(is_empty_expected != is_empty_result)
	{
		test_result = FAIL;
	}

	QDestroy(queue);

	return test_result;
}

int TestQueueLength()
{
	int test_result = SUCCESS;
	int length_result = 0;
	int length_expected = 2;
	int element = 1;

	queue = QCreate();

	p1 = &element;

	QEnqueue(queue,p1);
	QEnqueue(queue,p1);

	length_result = QSize(queue);

	if(length_result != length_expected)
	{
		test_result = FAIL;
	}

	QDestroy(queue);

	return test_result;
}

int TestQueueEnqueue()
{
	int test_result = SUCCESS;
	int push_result = 0;
	char *strings[] = {"Hello","World!"};
	size_t i = 0;

	queue = QCreate();

	for(i = 0; i < 2; ++i)
	{
		push_result = QEnqueue(queue,strings[i]);
		if(0 == push_result)
		{
			test_result = FAIL;
		}
	}
	
	QDestroy(queue);

	return test_result;
}

int TestQueueDequeue()
{
	int test_result = SUCCESS;
	int length_result = 0;
	int length_expected = 0;
	int element = 1;

	queue = QCreate();

	p1 = &element;
	QEnqueue(queue,p1);

	QDequeue(queue);

	length_result = QSize(queue);

	if(length_result != length_expected)
	{
		test_result = FAIL;
	}

	QDestroy(queue);

	return test_result;
}

int TestQueuePeek()
{
	int test_result = SUCCESS;
	int *result;
	int expected = 1;
	int element = 1;
	int element2 = 2;

	queue = QCreate();

	p1 = &element;
	QEnqueue(queue,p1);
	p1 = &element2;
	QEnqueue(queue,p1);

	result = QPeek(queue);
	if(*result != expected)
	{
		test_result = FAIL;
	}

	QDestroy(queue);

	return test_result;
}

int TestQueueAppend()
{
	int test_result = SUCCESS;
	int element1 = 1;
	int element2 = 2;
	int element3 = 3;
	int element4 = 4;

	queue = QCreate();
	p1 = &element1;
	QEnqueue(queue,p1);
	p1 = &element2;
	QEnqueue(queue,p1);

	queue2 = QCreate();
	p1 = &element3;
	QEnqueue(queue2,p1);
	p1 = &element4;
	QEnqueue(queue2,p1);

	QAppend(queue,queue2);

	/*PrintQueue(queue);*/

	QDestroy(queue);

	QDestroy(queue2);

	return test_result;
}