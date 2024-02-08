/*******************************************************************************
Project: Queue
Name: Haytham
Reviewer: Najeeb
Date: 24.10.2023
Version: 1.0
*******************************************************************************/

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h> /*size_t*/

typedef struct queue queue_ty;
typedef int status_op_ty;

/*
	Function: QueueCreate
	return value: queue_ty
	on success: Creates new queue
	undefined behaviour: Capacity = 0
	on failure: returns null
	Time Complexity: O(1)
*/
queue_ty *QCreate();

/*
	Function:QueueDestroy
	return value:None
	on success:Deletes queue
	undefined behaviour:Queue null
	on failure: Shouldn't fail.
	Time Complexity: O(n)
*/
void QDestroy(queue_ty *queue);

/*
	Function: Enqueue
	return value: Error code (0 for sucess, something else for failure)
	on success:Adds element to start of queue
	undefined behaviour:NULL queue or element
	on failure: returns nonzero
	Time Complexity: O(1)
*/
status_op_ty QEnqueue(queue_ty *queue, void *data);

/*
	Function:Dequeue
	return value:Error code (0 for sucess, something else for failure)
	on success:Removes an element from the end of the queue
	undefined behaviour:queue null
	on failure: returns nonzero
	Time Complexity: O(1)
*/
void QDequeue(queue_ty *queue);

/*
	Function:QueueIsEmpty
	return value:boolean
	on success:Returns whether the queue is empty or not
	undefined behaviour:queue null
	on failure: returns zero
	Time Complexity: O(1)
*/
status_op_ty QIsEmpty(const queue_ty *queue);

/*
	Function: QueuePeekFront
	return value: void *
	on success: reads element at the front of the queue
	undefined behaviour:Queue null
	on failure: returns null
	Time Complexity: O(1)
*/
void *QPeek(const queue_ty *queue);

/*
	Function:QueueSize
	return value: size_t
	on success: Reads the size of the queue
	undefined behaviour:queue null
	on failure: returns zero
	Time Complexity: O(n)
*/
size_t QSize(const queue_ty *queue);

/*
	Function:QueueAppend
	return value:New concatenated list
	on success:Concatenates dest with src with dest as start,
	undefined behaviour:Queues null
	on failure: returns NULL.
	Time Complexity: O(n)
*/
void QAppend(queue_ty *dest, queue_ty *src);

void PrintQueue(const queue_ty *queue);

#endif /*__QUEUE_H__*/