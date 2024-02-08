/*
Name: Haytham
Reviewer: Yan
*/
#include <stdio.h> /*fprintf*/
#include <stdlib.h> /*free, malloc*/
#include <stddef.h> /*size_t*/
#include <assert.h> /*assert*/

#include "doublylinkedlist.h"

enum STATUS{STATUS_FAIL, STATUS_SUCCESS};
enum OPERATION{NOT_EMPTY = 0, PASS = 1, EMPTY = 1};

struct dlist_node
{
    void *data;
    struct dlist_node *next;
    struct dlist_node *prev;
};

struct dlinkedlist 
{
    struct dlist_node* head;
    struct dlist_node* tail;
};

dlist_ty *DListCreate(void)
{
	dlist_ty *list = NULL;
	dlist_node_ty *head = NULL;
	dlist_node_ty *tail = NULL;

	list = (dlist_ty*)malloc(sizeof(dlist_ty));

	if(NULL == list)
    {
        fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
        return NULL;
    }

	head = (dlist_node_ty*)malloc(sizeof(dlist_node_ty));

	if(NULL == head)
    {
    	free(list);
        fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
        return NULL;
    }

	tail = (dlist_node_ty*)malloc(sizeof(dlist_node_ty));

	if(NULL == tail)
    {
    	free(head);
    	free(list);
        fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
        return NULL;
    }

	head->data = NULL;
    tail->data = NULL;
    head->next = NULL;
    tail->next = NULL;
    head->prev = NULL;
    tail->prev = NULL;

    list->head = head;
    list->tail = tail;

    return list;
}

void DListDestroy(dlist_ty *dlist)
{
	dlist_node_ty *current_node = NULL;

	assert(NULL != dlist);

	current_node = dlist->head;

	while(NULL != current_node->next)
	{
		DListPopFront(dlist);
		current_node = dlist->head;
	}

	free(dlist->head);
	dlist->head = NULL;

	free(dlist->tail);
	dlist->tail = NULL;

	free(dlist);
	dlist = NULL;
}

int DListIsEmpty(const dlist_ty *dlist)
{
	assert(NULL != dlist);

	return NULL == dlist->head->next ? EMPTY : NOT_EMPTY;
}

size_t DListLength(const dlist_ty *dlist)
{
	size_t count_nodes = 1;
	dlist_node_ty *tmp_node = NULL;

	assert(NULL != dlist);

	if(EMPTY == DListIsEmpty(dlist))
	{
		return 0;
	}

	tmp_node = dlist->head->next;

	while(tmp_node->next != dlist->tail)
	{
		tmp_node = tmp_node->next;
		++count_nodes;
	}

	return count_nodes;
}

dlist_status_ty DListPushFront(dlist_ty *dlist, void *element)
{
	dlist_node_ty *new_node = NULL;

	assert(NULL != dlist);

	new_node = (dlist_node_ty*)malloc(sizeof(dlist_node_ty));

	if(NULL == new_node)
    {
        fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
        return MALLOC_ERROR;
    }

    if(EMPTY == DListIsEmpty(dlist))
    {
    	new_node->next = dlist->tail;
    	dlist->tail->prev = new_node;
    }
    else
    {
	    new_node->next = dlist->head->next;
	}

	new_node->prev = dlist->head;
    dlist->head->next = new_node;
	new_node->data = element;

    return NO_ERROR;
}

dlist_status_ty DListPushBack(dlist_ty *dlist, void *element)
{
	dlist_node_ty *new_node = NULL;

	assert(NULL != dlist);

	new_node = (dlist_node_ty*)malloc(sizeof(dlist_node_ty));

	if(NULL == new_node)
    {
        fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
        return MALLOC_ERROR;
    }

    if(EMPTY == DListIsEmpty(dlist))
    {
    	dlist->head->next = new_node;
    	new_node->data = element;
    	new_node->next = dlist->tail;
    	new_node->prev = dlist->head;
    	dlist->tail->prev = new_node;
    }
    else
    {
    	new_node->next = NULL;
    	new_node->data = NULL;
    	new_node->prev = dlist->tail;
    	dlist->tail->data = element;
    	dlist->tail->next = new_node;
    	dlist->tail = new_node;
    }

    return NO_ERROR;
}

dlist_status_ty DListPopFront(dlist_ty *dlist)
{
	dlist_iter_ty head;

	assert(NULL != dlist);

	head = DListBegin(dlist);

	DListRemove(dlist,head);

	return NO_ERROR;
}

dlist_status_ty DListPopBack(dlist_ty *dlist)
{
	dlist_iter_ty tail;

	assert(NULL != dlist);

	tail = DListEnd(dlist);

	DListRemove(dlist,tail);

	return NO_ERROR;
}

dlist_iter_ty DListBegin(const dlist_ty *dlist)
{
	dlist_iter_ty head;
	assert(NULL != dlist);

	head.node = dlist->head->next;
	return head;
}

dlist_iter_ty DListEnd(const dlist_ty *dlist)
{
	dlist_iter_ty tail;

	assert(NULL != dlist);

	tail.node = dlist->tail->prev;
	return tail;
}

dlist_iter_ty DListNext(dlist_iter_ty iter)
{
	dlist_iter_ty next;
	assert(NULL != iter.node);

	next.node = iter.node->next;
	return next;
}

dlist_iter_ty DListPrev(dlist_iter_ty iter)
{
	dlist_iter_ty prev;
	assert(NULL != iter.node);

	prev.node = iter.node->prev;
	return prev;
}

void *DListGetData(dlist_iter_ty iter)
{
	void *data = NULL;
	assert(NULL != iter.node);

	data = iter.node->data;

	return data;
}

void DListSetData(dlist_iter_ty iter, void *data)
{
	assert(NULL != iter.node);

	iter.node->data = data;
}

int DListIterIsEqual(dlist_iter_ty first_iter, dlist_iter_ty second_iter)
{
	return first_iter.node == second_iter.node;
}

dlist_node_ty *DListGetNode(dlist_iter_ty iter)
{
	return iter.node;
}

dlist_iter_ty DListInsert(dlist_ty *dlist, dlist_iter_ty where, void *data)
{
	dlist_iter_ty new_node;

	assert(NULL != dlist);

	new_node.node = (dlist_node_ty*)malloc(sizeof(dlist_node_ty));

	if(NULL == new_node.node)
    {
        fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
        return new_node;
    }

	new_node.node->data = data;

	new_node.node->next = where.node;

	where.node->prev->next = new_node.node;

	new_node.node->prev = where.node->prev;

	where.node->prev = new_node.node;

	return new_node;
}

dlist_iter_ty DListRemove(dlist_ty *dlist, dlist_iter_ty to_remove)
{
	size_t list_len_is_one = 1;

	assert(NULL != dlist);

	if(list_len_is_one == DListLength(dlist))
	{
		dlist->head->next = NULL;
		dlist->tail->prev = NULL;
	}
	else
	{
		to_remove.node->prev->next = to_remove.node->next;
		to_remove.node->next->prev = to_remove.node->prev;
	}

	free(to_remove.node);

	return to_remove;
}

dlist_ty *DListMultiFind(const dlist_ty *dlist, int (*is_match)(const void *left,
					const void *right) ,const void *element, dlist_ty *output)
{
	dlist_iter_ty runner_node;

	assert(NULL != dlist);
	assert(NULL != is_match);
	assert(NULL != output);

	runner_node = DListBegin(dlist);

	while(runner_node.node != dlist->tail)
	{
		if(PASS == is_match(runner_node.node->data,element))
		{
			DListPushBack(output,runner_node.node->data);
		}
		runner_node = DListNext(runner_node);
	}

	return output;
}

int DListForEach(dlist_ty *dlist, dlist_iter_ty from, dlist_iter_ty to,
				int (*action)(void *data, void *param), void *param)
{
	assert(NULL != dlist);
	assert(NULL != action);

	if(DListIsEmpty(dlist))
	{
		return 0;
	}

	while(from.node != to.node->next)
	{
		if(STATUS_FAIL != action(from.node->data,param))
		{
			return STATUS_FAIL;
		}
		from = DListNext(from);
	}

	return STATUS_SUCCESS;
}

void DListSplice(dlist_iter_ty from, dlist_iter_ty to, dlist_iter_ty where)
{
	dlist_iter_ty prev_from = DListPrev(from);
	dlist_iter_ty next_to = DListNext(to);
	dlist_iter_ty next_where = DListNext(where);

	where.node->next = from.node;
	from.node->prev = where.node;

	to.node->next = next_where.node;
	next_where.node->prev = to.node;

	if(NULL == prev_from.node->prev)
	{
		prev_from.node->next = NULL;
	}
	else
	{
		prev_from.node->next = next_to.node;
	}

	if(NULL == next_to.node->next)
	{
		next_to.node->prev = NULL;
	}
	else
	{
		next_to.node->prev = prev_from.node;
	}
}

void PrintListFromHead(const dlist_ty *list)
{
	dlist_iter_ty tmp_node;
	dlist_iter_ty end_node;
	int *data = NULL;
    assert(NULL != list);

    tmp_node = DListBegin(list);
    end_node = DListEnd(list);
    if(NULL != tmp_node.node)
    {
    	while(tmp_node.node != end_node.node)
		{
			data = DListGetData(tmp_node);
			printf("%d->",*(int*)data);
			tmp_node = DListNext(tmp_node);
		}
		data = DListGetData(tmp_node);
		printf("%d\n",*(int*)data);
    }
	
}

void PrintListFromTail(const dlist_ty *list)
{
	dlist_iter_ty tmp_node;
	dlist_iter_ty start_node;
	int *data = NULL;

    assert(NULL != list);

    tmp_node = DListEnd(list);
    start_node = DListBegin(list);

	while(tmp_node.node != start_node.node)
	{
		data = DListGetData(tmp_node);
		printf("%d->",*(int*)data);
		tmp_node = DListPrev(tmp_node);
	}
	data = DListGetData(tmp_node);
	printf("%d\n",*(int*)data);
}