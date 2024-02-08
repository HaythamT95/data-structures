/*
Name: Haytham
Reviewer: Amram
*/
#include <stdio.h> /*fprintf*/
#include <stdlib.h> /*free, malloc*/
#include <stddef.h> /*size_t*/
#include <assert.h> /*assert*/

#include "sortedlist.h"

#define EMPTY 1

struct sorted_list
{
	dlist_ty *dlist;
	cmp_func_ty compare_func;
};

sorted_list_ty *SortedListCreate(cmp_func_ty cmp_func)
{
	sorted_list_ty *sorted_list = NULL;
	assert(NULL != cmp_func);

	sorted_list = (sorted_list_ty*)malloc(sizeof(sorted_list_ty));

	if(NULL == sorted_list)
	{
		fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
        return NULL;
	}

	sorted_list->dlist = DListCreate();

	if(NULL == sorted_list->dlist)
	{
		free(sorted_list);
		fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
        return NULL;
	}

	sorted_list->compare_func = cmp_func;

	return sorted_list;
}

void SortedListDestroy(sorted_list_ty *sorted_list)
{
	assert(NULL != sorted_list);

	DListDestroy(sorted_list->dlist);
	sorted_list->dlist = NULL;

	free(sorted_list);
	sorted_list = NULL;
}

sorted_list_status_ty SortedListPopFront(sorted_list_ty *sorted_list)
{
	assert(NULL != sorted_list);

	if(EMPTY == SortedListIsEmpty(sorted_list))
	{
		return SORTED_GENERAL_ERR;
	}

	DListPopFront(sorted_list->dlist);

	return SORTED_NO_ERROR;
}

sorted_list_status_ty SortedListPopBack(sorted_list_ty *sorted_list)
{
	assert(NULL != sorted_list);

	if(EMPTY == SortedListIsEmpty(sorted_list))
	{
		return SORTED_GENERAL_ERR;
	}

	DListPopBack(sorted_list->dlist);

	return SORTED_NO_ERROR;
}

size_t SortedListLength(const sorted_list_ty *sorted_list)
{
	assert(NULL != sorted_list);

	return DListLength(sorted_list->dlist);
}

int SortedListIsEmpty(const sorted_list_ty *sorted_list)
{
	assert(NULL != sorted_list);

	return DListIsEmpty(sorted_list->dlist);
}

sorted_list_iter_ty SortedListBegin(const sorted_list_ty *sorted_list)
{
	sorted_list_iter_ty head;

	assert(NULL != sorted_list);

	head.internal_itr = DListBegin(sorted_list->dlist);
	return head;
}

sorted_list_iter_ty SortedListEnd(const sorted_list_ty *sorted_list)
{
	sorted_list_iter_ty tail;

	assert(NULL != sorted_list);

	tail.internal_itr = DListEnd(sorted_list->dlist);
	return tail;
}

sorted_list_iter_ty SortedListNext(sorted_list_iter_ty iter)
{
	sorted_list_iter_ty next;
	assert(NULL != DListGetNode(iter.internal_itr));

	next.internal_itr = DListNext(iter.internal_itr);
	return next;
}

sorted_list_iter_ty SortedListPrev(sorted_list_iter_ty iter)
{
	sorted_list_iter_ty prev;
	assert(NULL != DListGetNode(iter.internal_itr));

	prev.internal_itr = DListPrev(iter.internal_itr);
	return prev;
}

void *SortedListGetData(sorted_list_iter_ty iter)
{
	assert(NULL != DListGetNode(iter.internal_itr));

	return DListGetData(iter.internal_itr);
}

sorted_list_iter_ty SortedListInsert(sorted_list_ty *sorted_list, void *data)
{
	sorted_list_iter_ty inserted_iter;

	assert(NULL != sorted_list);

	inserted_iter = SortedListBegin(sorted_list);

	if(NULL != DListGetNode(inserted_iter.internal_itr))
	{
		while(NULL != SortedListGetData(inserted_iter) && 
			0 >= sorted_list->compare_func(
				SortedListGetData(inserted_iter),data))
		{
			inserted_iter = SortedListNext(inserted_iter);
		}
		DListInsert(sorted_list->dlist,inserted_iter.internal_itr,data);
	}
	else
	{
		DListPushFront(sorted_list->dlist,data);
		inserted_iter = SortedListBegin(sorted_list);
	}

	return inserted_iter;
}

sorted_list_iter_ty SortedListRemove(sorted_list_ty *sorted_list, 
                                                sorted_list_iter_ty to_remove)
{
	sorted_list_iter_ty next_to_remove;
	assert(NULL != sorted_list);
	assert(NULL != DListGetNode(to_remove.internal_itr));

	next_to_remove = SortedListNext(to_remove);

	DListRemove(sorted_list->dlist,to_remove.internal_itr);

	return next_to_remove;
}

sorted_list_iter_ty SortedListFind(const sorted_list_ty *sorted_list, 
           										sorted_list_iter_ty from,
           											sorted_list_iter_ty to,
           												const void *element)
{
	sorted_list_iter_ty runner;

	assert(NULL != sorted_list);
	assert(NULL != DListGetNode(from.internal_itr));
	assert(NULL != DListGetNode(to.internal_itr));

	runner = from;

	while(DListGetNode(runner.internal_itr) != DListGetNode(to.internal_itr) &&
		SORTED_NO_ERROR != sorted_list->compare_func(
											SortedListGetData(runner),element))
	{
		runner = SortedListNext(runner);
	}

	return runner;
}

sorted_list_iter_ty SortedListFindIf(sorted_list_iter_ty from,
                                   					sorted_list_iter_ty to,
                                   						cmp_func_ty cmp_func,
                                   							const void *param)
{
	sorted_list_iter_ty runner;

	assert(NULL != cmp_func);
	assert(NULL != DListGetNode(from.internal_itr));
	assert(NULL != DListGetNode(to.internal_itr));

	runner = from;

	while(DListGetNode(runner.internal_itr) != DListGetNode(to.internal_itr) &&
				SORTED_NO_ERROR != cmp_func(SortedListGetData(runner),param))
	{
		runner = SortedListNext(runner);
	}

	return runner;
}

int SortedListIterIsEqual(sorted_list_iter_ty first_iter,
                                              sorted_list_iter_ty second_iter)
{
	return DListIterIsEqual(first_iter.internal_itr,second_iter.internal_itr);
}

int SortedListForEach(sorted_list_iter_ty from, sorted_list_iter_ty to,
        								op_func_ty op_func, void *func_param)
{
	int action_result = 0;
	sorted_list_iter_ty runner;

	assert(NULL != op_func);
	assert(NULL != DListGetNode(from.internal_itr));
	assert(NULL != DListGetNode(to.internal_itr));

	runner = from;

	while(DListGetNode(runner.internal_itr) != DListGetNode(to.internal_itr) &&
		SORTED_NO_ERROR == 
				(action_result = op_func(SortedListGetData(runner),func_param)))
	{
		runner = SortedListNext(runner);
	}

	return action_result;
}

void SortedListMerge(sorted_list_ty *dest,sorted_list_ty *src)
{
	sorted_list_iter_ty src_head;
	sorted_list_iter_ty src_tail;

	assert(NULL != dest);
	assert(NULL != src);

	src_head = SortedListBegin(src);
	src_tail = SortedListEnd(src);

	while(src_head.internal_itr.node != src_tail.internal_itr.node)
	{
		src_head = SortedListInsert(dest,SortedListGetData(src_head));
		SortedListPopFront(src);
		src_head = SortedListBegin(src);
	}
	src_head = SortedListInsert(dest,SortedListGetData(src_head));
	SortedListPopFront(src);
}

void PrintList(const sorted_list_ty *list)
{
	PrintListFromHead(list->dlist);
}