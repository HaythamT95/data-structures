#include <stdio.h> /*fprintf*/
#include <stdlib.h> /*malloc, free*/
#include <stddef.h> /*size_t*/
#include <assert.h> /*assert*/

#include "sortedlist.h"
#include "priority.h"

struct priority_queue
{
    sorted_list_ty *sorted_list;
};

priority_ty *PriorityCreate(queue_cmp_func_ty compare_func)
{
    priority_ty *p_queue = NULL;
    assert(NULL != compare_func);

    p_queue = (priority_ty*)malloc(sizeof(priority_ty));

    if(NULL == p_queue)
    {
        fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
        return NULL;
    }

    p_queue->sorted_list = SortedListCreate((cmp_func_ty)compare_func);

    if(NULL == p_queue->sorted_list)
    {
        free(p_queue);
        fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
        return NULL;
    }

    return p_queue;
}

void PriorityDestroy(priority_ty *p_queue)
{
    assert(NULL != p_queue);

    SortedListDestroy(p_queue->sorted_list);
    p_queue->sorted_list = NULL;

    free(p_queue);
    p_queue = NULL;
}

priority_queue_status_ty PriorityEnqueue(priority_ty *p_queue, void *data)
{
    assert(NULL != p_queue);

    if(NULL == SortedListGetData(SortedListInsert(p_queue->sorted_list,data)))
    {
        return PRIORITY_GENERAL_ERR;
    }

    return PRIORITY_NO_ERROR;
}

void *PriorityDequeue(priority_ty *p_queue)
{
    void *data = NULL;
    assert(NULL != p_queue);

    data = PriorityPeek(p_queue);
    SortedListPopBack(p_queue->sorted_list);
    return data;
}

void *PriorityPeek(priority_ty *p_queue)
{
    assert(NULL != p_queue);

    return SortedListGetData(SortedListEnd(p_queue->sorted_list));
}

int PriorityIsEmpty(const priority_ty *p_queue)
{
    assert(NULL != p_queue);

    return SortedListIsEmpty(p_queue->sorted_list);
}

size_t PrioritySize(const priority_ty *p_queue)
{
    assert(NULL != p_queue);

    return SortedListLength(p_queue->sorted_list);
}

void PriorityClear(priority_ty *p_queue)
{
    assert(NULL != p_queue);

    while(!PriorityIsEmpty(p_queue))
    {
        SortedListPopFront(p_queue->sorted_list);
    }
}

void *PriorityErase(priority_ty *p_queue, queue_cmp_func_ty is_match, void *data)
{
    void *returned_data = NULL;
    sorted_list_iter_ty iter;

    assert(NULL != p_queue);
    assert(NULL != is_match);

    iter = SortedListFindIf(SortedListBegin(p_queue->sorted_list),
                                            SortedListEnd(p_queue->sorted_list),
                                                            is_match, data);
 

    returned_data = SortedListGetData(iter);

    SortedListRemove(p_queue->sorted_list,iter);

    return returned_data;
}

void PrintPQueue(const priority_ty *p_queue)
{
    PrintList(p_queue->sorted_list);
}