#include <stdio.h> /*fprintf*/
#include <stdlib.h> /*free, malloc*/
#include <stddef.h> /*size_t*/
#include <assert.h> /*assert*/

#include "singlylinkedlist.h"
#include "queue.h"

struct queue
{
	struct linkedlist* list;
};

queue_ty *QCreate()
{
	queue_ty *queue = (queue_ty*)malloc(sizeof(queue_ty));

	if(NULL == queue)
    {
        fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
        return NULL;
    }

	queue->list = SListCreate();

    return queue;
}

void QDestroy(queue_ty *queue)
{
	assert(NULL != queue);

	SListDestroy(queue->list);
	queue->list = NULL;

	free(queue);
	queue = NULL;
}

status_op_ty QEnqueue(queue_ty *queue, void *data)
{
	int result = 0;
	assert(NULL != queue);

	result = SListPushBack(queue->list,data);

	return result;
}

void QDequeue(queue_ty *queue)
{
	assert(NULL != queue);

	SListPopFront(queue->list);
}

void *QPeek(const queue_ty *queue)
{
	assert(NULL != queue);

	return SListGetData(SListBegin(queue->list));
}

status_op_ty QIsEmpty(const queue_ty *queue)
{
	assert(NULL != queue);

	return SListIsEmpty(queue->list);
}

size_t QSize(const queue_ty *queue)
{
	assert(NULL != queue);

	return SListLength(queue->list);
}

void QAppend(queue_ty *dest, queue_ty *src)
{
	assert(NULL != dest);
	assert(NULL != src);

	SListAppend(dest->list,src->list);
}

void PrintQueue(const queue_ty *queue)
{
	PrintSList(queue->list);
}