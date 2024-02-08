#include <stdio.h> /*fprintf*/
#include <stdlib.h> /*free, malloc*/
#include <stddef.h> /*size_t*/
#include <assert.h> /*assert*/

#include "singlylinkedlist.h"

enum STATUS{STATUS_FAIL,STATUS_SUCCESS};
enum OPERATION{PASS,EMPTY};

struct slist_node 
{
    void *data;
    struct slist_node* next;
};

struct linkedlist 
{
    struct slist_node* head;
    struct slist_node* tail;
};

slist_ty *SListCreate()
{
	slist_ty *list = (slist_ty*)malloc(sizeof(slist_ty));
	slist_node_ty *head = (slist_node_ty*)malloc(sizeof(slist_node_ty));
	slist_node_ty *tail = (slist_node_ty*)malloc(sizeof(slist_node_ty));

	if(NULL == list || NULL == head || NULL == tail)
    {
        fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
        return NULL;
    }

	head->data = NULL;
    tail->data = NULL;
    head->next = NULL;
    tail->next = NULL;

    list->head = head;
    list->tail = tail;

    return list;
}

status_ty SListPushFront(slist_ty *list, void *element)
{
	slist_node_ty *new_node = NULL;

	assert(NULL != list);

	if(NULL == list)
	{
		return STATUS_FAIL;
	}

	new_node = (slist_node_ty*)malloc(sizeof(slist_node_ty));

	if(NULL == new_node)
    {
        fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
        return STATUS_FAIL;
    }

    if(EMPTY == SListIsEmpty(list))
    {
    	new_node->next = list->tail;
    }
    else
    {
	    new_node->next = SListBegin(list);
	}

    list->head->next = new_node;
	new_node->data = element;

    return STATUS_SUCCESS;
}

status_ty SListPushBack(slist_ty *list, void *element)
{
	slist_node_ty *new_node = NULL;

	assert(NULL != list);

	if(NULL == list)
	{
		return STATUS_FAIL;
	}

	new_node = (slist_node_ty*)malloc(sizeof(slist_node_ty));

	if(NULL == new_node)
    {
        fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
        return STATUS_FAIL;
    }

    if(EMPTY == SListIsEmpty(list))
    {
    	list->head->next = new_node;
    	new_node->data = element;
    	new_node->next = list->tail;
    }
    else
    {
    	new_node->next = NULL;
    	new_node->data = NULL;
    	list->tail->data = element;
    	list->tail->next = new_node;
    	list->tail = new_node;
    }

    return STATUS_SUCCESS;
}

status_ty SListPopFront(slist_ty *list)
{
	slist_node_ty *tmp_node = NULL;

	assert(NULL != list);

	tmp_node = SListBegin(list);

	if(list->tail != tmp_node->next)
	{
		list->head->next=list->head->next->next;
	}
	else
	{
		list->head->next = NULL;
	}

	free(tmp_node);
	tmp_node = NULL;

	return STATUS_SUCCESS;
}

status_ty SListPopBack(slist_ty *list)
{
	slist_node_ty *tmp_node = NULL;
	slist_node_ty *del_node = NULL;

	assert(NULL != list);

	tmp_node = list->head;

	while(tmp_node->next->next != list->tail)
	{
		tmp_node = SListNext(tmp_node);
		del_node = tmp_node;
	}

	del_node=SListNext(tmp_node);

	if(list->head != tmp_node)
	{
		tmp_node->next = list->tail;
	}
	else
	{
		tmp_node->next=NULL;
	}

	free(del_node);
	del_node = NULL;

	return STATUS_SUCCESS;
}

int SListIsEmpty(const slist_ty *list)
{
	assert(NULL != list);

	return NULL == list->head->next ? 1:0;
}

size_t SListLength(const slist_ty *list)
{
	size_t count_nodes = 1;
	slist_node_ty *tmp_node = NULL;

	assert(NULL != list);

	if(EMPTY == SListIsEmpty(list))
	{
		return 0;
	}

	tmp_node = SListBegin(list);

	while(tmp_node->next != list->tail)
	{
		tmp_node = SListNext(tmp_node);
		++count_nodes;
	}

	return count_nodes;
}

void SListDestroy(slist_ty *list)
{
	slist_node_ty *current_node = NULL;
    slist_node_ty *tmp_node = NULL;

	assert(NULL != list);
	
	current_node = SListBegin(list);

	while(current_node != list->tail->next)
	{
		tmp_node = current_node;		
		current_node = SListNext(current_node);

		if(tmp_node!=list->tail)
		{
			free(tmp_node);
		}
	}

	free(list->head);
	list->head = NULL;

	free(list->tail);
	list->tail = NULL;

	free(list);
	list = NULL;
}

slist_node_ty *SListBegin(const slist_ty *list)
{
	assert(NULL != list);

	return list->head->next;
}

slist_node_ty *SListEnd(const slist_ty *list)
{
    slist_node_ty *tmp_node = NULL;

	assert(NULL != list);

	tmp_node = SListBegin(list);

	while(tmp_node->next != list->tail)
	{
		tmp_node = SListNext(tmp_node);
	}

	return tmp_node;
}

slist_node_ty *SListNext(const slist_node_ty *current_node)
{
	assert(NULL != current_node);

	return current_node->next;
}

void *SListGetData(const slist_node_ty *node)
{
	assert(NULL != node);

	return node->data;
}

void SListSetData(slist_node_ty *node, void *data)
{
	assert(NULL != node);

	node->data=data;
}

slist_node_ty *SListInsert(slist_ty *list, slist_node_ty *where, void *data)
{
	slist_node_ty *new_node = NULL;
	slist_node_ty *runner_node = NULL;

	assert(NULL != list);
	assert(NULL != where);
	assert(NULL != data);

	new_node = (slist_node_ty*)malloc(sizeof(slist_node_ty));

	if(NULL == new_node)
    {
        fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
        return NULL;
    }

    new_node->data = data;

	runner_node = SListBegin(list);

	while(runner_node->next != where->next || runner_node->data != where->data)
	{
		runner_node = SListNext(runner_node);
	}

	new_node->next = SListNext(runner_node);
	runner_node->next = new_node;

	return new_node;
}

slist_node_ty *SListInsertBefore(slist_ty *list, slist_node_ty *where, void *data)
{
	slist_node_ty *new_node = NULL;
	slist_node_ty *runner_node = NULL;

	assert(NULL != list);
	assert(NULL != where);
	assert(NULL != data);

	new_node = (slist_node_ty*)malloc(sizeof(slist_node_ty));

	if(NULL == new_node)
    {
        fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
        return NULL;
    }

    new_node->data = data;

	runner_node = list->head;

	while(runner_node->next->next != where->next ||
										runner_node->next->data != where->data)
	{
		runner_node = SListNext(runner_node);
	}

	new_node->next = SListNext(runner_node);
	runner_node->next = new_node;

	return new_node;
}

slist_ty *SListRemove(slist_ty *list, slist_node_ty *to_remove)
{
	slist_node_ty *runner_node = NULL;
	slist_node_ty *del_node = NULL;

	assert(NULL != list);
	assert(NULL != to_remove);

	runner_node = list->head;

	while(runner_node->next->next != to_remove->next ||
									runner_node->next->data != to_remove->data)
	{
		runner_node = SListNext(runner_node);
	}

	del_node = SListNext(runner_node);
	runner_node->next = runner_node->next->next;
	free(del_node);

	return list;
}

slist_ty *SListRemoveAfter(slist_ty *list, slist_node_ty *to_remove)
{
	assert(NULL != list);
	assert(NULL != to_remove);

	to_remove = SListNext(to_remove);
	
	return SListRemove(list,to_remove);
}

slist_node_ty *SListFind(const slist_ty *list,
							int (*Equals)(const void *left, const void *right),
							const void *element)
{
	slist_node_ty *runner_node = NULL;

	assert(NULL != list);
	assert(NULL != Equals);
	assert(NULL != element);

	runner_node = SListBegin(list);

	while(runner_node != list->tail)
	{
		if(PASS == Equals(runner_node->data,element))
		{
			return runner_node;
		}
		runner_node = SListNext(runner_node);
	}

	return NULL;
}

int SListForEach(slist_ty *list, slist_node_ty *from, slist_node_ty *to,
						int (*Action)(void *data, void *param), void *param)
{
	assert(NULL != list);
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != Action);

	while(from != to->next)
	{
		if(PASS != Action(from->data,param))
		{
			return STATUS_FAIL;
		}
		from = SListNext(from);
	}

	return STATUS_SUCCESS;
}

void SListAppend(slist_ty *dest,slist_ty *src)
{
	slist_node_ty *current = NULL;
    slist_node_ty *src_head = NULL;

    assert(NULL != dest);
    assert(NULL != src);

    src_head = SListBegin(src);

    current = dest->tail;

    current->data = src_head->data;
    current->next = src_head->next;

    src_head->data = NULL;
    src_head->next = NULL;

    dest->tail = src->tail;

    src->tail = src_head;
}

void PrintSList(const slist_ty *list)
{
	slist_node_ty *tmp_node = NULL;

    assert(NULL != list);

    tmp_node = SListBegin(list);

	while(tmp_node->next != list->tail)
	{
		printf("%d\n",*(int*)tmp_node->data);
		tmp_node = tmp_node->next;
	}
	printf("%d\n",*(int*)tmp_node->data);
}