/*
	Name: Haytham
	Pseudocode Reviewer: Diana
	Reviewer: Diana
*/
#include <stdlib.h> /*malloc, free*/
#include <stddef.h> /*size_t*/
#include <string.h> /*memcpy*/
#include <assert.h> /*assert*/

#include "heap.h"
#include "vector.h"
#include "utils.h"

#define DEFAULT_CAPACITY 100

static int GetParentIndex(size_t child_index_);
static int GetLeftChildIndex(size_t parent_index_);
static int GetRightChildIndex(size_t parent_index_);
static void HeapifyUp(heap_ty *heap_, size_t index_);
static void HeapifyDown(heap_ty *heap_, size_t index_);
static void SwapElementsInVector(heap_ty* heap_, size_t index1, size_t index2);
static size_t SmallestBetweenTrio(heap_ty* heap_, size_t curr_index, size_t left_index, size_t right_index);

struct heap
{
	vector_ty* vector;
	heap_cmp_func_ty compare_func;
	const void* cmp_params;
};

heap_ty *HeapCreate(size_t initial_capacity_ , heap_cmp_func_ty compare_func_, const void* cmp_params_)
{
	heap_ty *heap = NULL;

	/*assert*/
	assert(NULL != compare_func_);

	/*Alloc heap*/
	heap = (heap_ty*)malloc(sizeof(heap_ty));

	if(NULL == heap)
	{
		/*handle failure*/
        return NULL;
	}

	/*Alloc vector = VectorCreate(initial_capacity_, sizeof(void*))*/
	heap->vector = VectorCreate(initial_capacity_ == 0 ? DEFAULT_CAPACITY : initial_capacity_, sizeof(void*));

	if(NULL == heap->vector)
	{
		/*handle failure*/
		free(heap);
        return NULL;
	}

	/*init params*/
	heap->compare_func = compare_func_;
	heap->cmp_params = cmp_params_;

	/*return heap*/
	return heap;
}

void HeapDestroy(heap_ty* heap_)
{
	if(NULL != heap_)
	{
		/*Call Vector destroy*/
		VectorDestroy(heap_->vector);

		/*curropt params of heap*/
		heap_->vector = DEBUG_ONLY(BAD_MEM(vector_ty*));
		heap_->compare_func = DEBUG_ONLY(BAD_MEM(heap_cmp_func_ty));
		heap_->cmp_params = DEBUG_ONLY(BAD_MEM(void*));

		/*free heap*/
		free(heap_);
	}
}

status_heap_ty HeapEnqueue(heap_ty* heap_, void* data_)
{
	int status = 0;

	/*assert*/
	assert(NULL != heap_);

	/*status = VectorPushBack(data_)*/
	status = VectorPushBack(heap_->vector, &data_);

	if(0 == status)
	{
		/*handle failure*/
		return MALLOC_FAIL;
	}

	/*HeapifyUp(heap_)*/
	HeapifyUp(heap_, HeapSize(heap_) - 1);

	/*return success*/
	return SUCCESS;
}

void *HeapDequeue(heap_ty* heap_)
{
	void *ret = NULL;
	void *last_element = NULL;
	/*assert*/
	assert(NULL != heap_);

	/*ret = VectorGetValue(heap_->vector, 0)*/
	ret = *(char**)VectorGetValue(heap_->vector, 0);

	/*last_element = VectorGetValue(heap_->vector, last element)*/
	last_element = *(char**)VectorGetValue(heap_->vector, HeapSize(heap_) - 1);

	/*VectorSetValue(heap_->vector, 0, last_element)*/
	VectorSetValue(heap_->vector, 0, &last_element);

	/*VectorPopBack(heap_->vector)*/
	VectorPopBack(heap_->vector);

	/*HeapifyDown(heap_)*/
	HeapifyDown(heap_, 0);

	/*return ret*/
	return ret;
}

void *HeapPeek(heap_ty* heap_)
{
	void *ret = NULL;
	/*assert*/
	assert(NULL != heap_);

	/*ret = VectorGetValue(heap_->vector, 0)*/
	ret = *(char**)VectorGetValue(heap_->vector, 0);

	/*return ret*/
	return ret;
}

int HeapIsEmpty(const heap_ty* heap_)
{
	/*assert*/
	assert(NULL != heap_);

	/*return VectorIsEmpty(heap_->vector)*/
	return VectorIsEmpty(heap_->vector);
}

size_t HeapSize(const heap_ty* heap_)
{
	/*assert*/
	assert(NULL != heap_);

	/*return VectorGetSize(heap_->vector)*/
	return VectorGetSize(heap_->vector);
}

void *HeapRemove(heap_ty* heap_, int(*is_match)(const void* data_, const void* params_), const void* is_match_params_)
{
	size_t i = 0;
	void *ret = NULL;

	/*assert*/
	assert(NULL != heap_);
	assert(NULL != is_match);

	/*for i = 0 to vec.size()*/
	for (i = 0; i < HeapSize(heap_); ++i)
	{
		/*if(is_match(VectorGetValue(i),data)*/
		if(is_match(*(char**)VectorGetValue(heap_->vector, i), is_match_params_))
		{
			/*ret = VectorGetValue(i)*/
			ret = *(char**)VectorGetValue(heap_->vector, i);

			/*swap with last elem*/
			SwapElementsInVector(heap_, i, HeapSize(heap_) - 1);

			/*popback*/
			VectorPopBack(heap_->vector);

			/*HeapDown(i)*/
			HeapifyDown(heap_, i);

			/*HeapUp(i)*/
			HeapifyUp(heap_, i);
			
			return ret;
		}
	}

	/*return ret*/
	return NULL;
}

int GetParentIndex(size_t child_index_)
{
	/*return (child_index_) / 2; */
	return (child_index_ - 1) / 2;
}

int GetLeftChildIndex(size_t parent_index_)
{
    /*return (2 * parent_index_); */
    return 2 * parent_index_ + 1;
}

int GetRightChildIndex(size_t parent_index_)
{
    /*return (2 * parent_index_ + 1); */
    return 2 * parent_index_ + 2;
}

void SwapElementsInVector(heap_ty* heap_, size_t index1, size_t index2)
{
	void *data1 = NULL;
	void *data2 = NULL;

	data1 = *(char**)VectorGetValue(heap_->vector, index1);
	data2 = *(char**)VectorGetValue(heap_->vector, index2);

	VectorSetValue(heap_->vector, index2, &data1);
	VectorSetValue(heap_->vector, index1, &data2);
}

void HeapifyUp(heap_ty *heap_, size_t index)
{
	int curr_index = 0;
	int parent_index = 0;

	/*assert*/
	assert(NULL != heap_);

	curr_index = index;
	parent_index = GetParentIndex(index);

	/*while not top AND curr > parent*/
	while(curr_index != 0 && 
		0 > heap_->compare_func(*(char**)VectorGetValue(heap_->vector, curr_index), *(char**)VectorGetValue(heap_->vector, parent_index), heap_->cmp_params))
	{
		/*swap data with parent*/
		SwapElementsInVector(heap_, curr_index, parent_index);

		/*advance curr to parent*/
		curr_index = parent_index;
		parent_index = GetParentIndex(parent_index);
	}
}

void HeapifyDown(heap_ty *heap_, size_t index)
{
	size_t curr_index = 0;
	size_t left_index = 0;
	size_t right_index = 0;
	size_t smallest_index = 0;

	/*assert*/
	assert(NULL != heap_);

	curr_index = index;
	left_index = GetLeftChildIndex(curr_index);
	right_index = GetRightChildIndex(curr_index);

	/*while not bottom AND not smallest in trio*/
	while(curr_index != SmallestBetweenTrio(heap_, curr_index, left_index, right_index))
	{
		/*swap elem with smallest son*/
		smallest_index = SmallestBetweenTrio(heap_, curr_index, left_index, right_index);
		SwapElementsInVector(heap_, curr_index, smallest_index);

		/*advance curr to smallest son*/
		curr_index = smallest_index;

		left_index = GetLeftChildIndex(curr_index);
		right_index = GetRightChildIndex(curr_index);
	}
}

size_t SmallestBetweenTrio(heap_ty* heap_, size_t curr_index, size_t left_index, size_t right_index)
{

	if(left_index >= HeapSize(heap_))
	{
		return curr_index;
	}

	if(right_index >= HeapSize(heap_))
	{
		if(-1 == heap_->compare_func(*(char**)VectorGetValue(heap_->vector,left_index), *(char**)VectorGetValue(heap_->vector,curr_index), heap_->cmp_params))
		{
			return left_index;
		}
		return curr_index;
	}

	if(-1 == heap_->compare_func(*(char**)VectorGetValue(heap_->vector,curr_index), *(char**)VectorGetValue(heap_->vector,left_index), heap_->cmp_params)
	 	&& -1 == heap_->compare_func(*(char**)VectorGetValue(heap_->vector,curr_index), *(char**)VectorGetValue(heap_->vector,right_index), heap_->cmp_params))
	{
		return curr_index;
	}

	else if(-1 == heap_->compare_func(*(char**)VectorGetValue(heap_->vector,left_index), *(char**)VectorGetValue(heap_->vector,curr_index), heap_->cmp_params)
	 	&& -1 == heap_->compare_func(*(char**)VectorGetValue(heap_->vector,left_index), *(char**)VectorGetValue(heap_->vector,right_index), heap_->cmp_params))
	{
		return left_index;
	}

	return right_index;
}

void HeapPrint(heap_ty *heap) 
{
    size_t i = 0;
    size_t heapsize = HeapSize(heap);


    printf("Heap Contents:\n");

    for (i = 0; i < heapsize; ++i) 
    {
        void *data =*(void**)VectorGetValue(heap->vector, i);

        printf("%d ", (*(int*)data));
    }

    printf("\n");
}