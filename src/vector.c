#include <stdio.h> /*fprintf*/
#include <string.h> /*memcpy*/
#include <stdlib.h> /*malloc, realloc, free*/
#include <stddef.h> /*size_t*/
#include <assert.h> /*assert*/

#include "vector.h"

#define GROWTH_FACTOR 1.5
#define SHRINK_FACTOR 1.5

#define MAX_SIZE 1000

enum STATUS{STATUS_FAIL,STATUS_SUCCESS};

struct vector
{
    void* start;         
    size_t size_of_element;
    size_t curr_size;         
    size_t capacity;           
};

vector_ty *VectorCreate(size_t capacity , size_t size_of_element)
{
    vector_ty *vector = NULL;

    assert(0 != size_of_element);
    assert(MAX_SIZE > capacity);

    vector = (vector_ty*)malloc(sizeof(vector_ty));

    if(NULL == vector)
    {
        fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
        return NULL;
    }

    vector->curr_size = 0;
    vector->size_of_element = size_of_element;
    vector->capacity = capacity * size_of_element;
    vector->start = (char*)malloc(sizeof(char)*(capacity*size_of_element));

    if(NULL == vector->start)
    {
        fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
        free(vector);
        vector = NULL;
        return NULL;
    }

    return vector;
}

void VectorDestroy( vector_ty *vector)
{
    assert(NULL != vector);

    free(vector->start);
    vector->start = NULL;
    free(vector);
    vector = NULL;
}

void VectorSetValue( vector_ty *vector, size_t index, const void* val)
{
    size_t offset = 0;

    assert(NULL != vector);

    if((index <= VectorGetSize(vector)) && (0 < VectorGetSize(vector)))
    {
        offset = index * vector->size_of_element;
        memcpy((char *)vector->start + offset,val,vector->size_of_element);
    }
}

void *VectorGetValue( vector_ty *vector, size_t index)
{
    size_t offset = 0;

    assert(NULL != vector);

    if((NULL == vector) || (index > VectorGetSize(vector)) || (0 == VectorGetSize(vector)))
    {
        return NULL;
    }
    offset = index * vector->size_of_element;

    return (void*)((char *)vector->start + offset);
}

size_t VectorGetMaxCapacity( vector_ty *vector)
{
    assert(NULL != vector);

    return vector->capacity/vector->size_of_element;
}

size_t VectorGetSize( vector_ty *vector)
{
    assert(NULL != vector);

    if(NULL == vector)
    {
        return 0;
    }

    return vector->curr_size/vector->size_of_element;
}

status_ty VectorIsEmpty(const vector_ty *vector)
{
    assert(NULL != vector);

    if(vector->curr_size > 0)
    {
        return 0;
    }

    return 1;
}

status_ty VectorPushBack(vector_ty *vector, void *element)
{
    size_t new_size = 0;

    assert(NULL != vector);

    if(VectorGetMaxCapacity(vector) > VectorGetSize(vector))
    {
        memcpy((char *)vector->start+vector->curr_size,element,vector->size_of_element);
        vector->curr_size+=vector->size_of_element;
        return STATUS_SUCCESS;
    }
    else
    {
        new_size = GROWTH_FACTOR*VectorGetMaxCapacity(vector);
        if(STATUS_SUCCESS == VectorReserve(vector,new_size))
        {
            memcpy((char *)vector->start+vector->curr_size,element,vector->size_of_element);
            vector->curr_size+=vector->size_of_element;
            return STATUS_SUCCESS;
        }
    }

    return STATUS_FAIL;
}

status_ty VectorReserve(vector_ty *vector, size_t new_capacity)
{
    void *tmp_alloc = NULL;

    assert(NULL != vector);
    assert(MAX_SIZE > new_capacity);

    if((NULL == vector) || (0 >= new_capacity))
    {
        return STATUS_FAIL;
    }

    tmp_alloc = vector->start;

    tmp_alloc = realloc(vector->start,(new_capacity*vector->size_of_element));

    if(NULL == tmp_alloc)
    {
        fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
        return STATUS_FAIL;
    }

    vector->start=tmp_alloc;

    vector->capacity = new_capacity * vector->size_of_element;

    return STATUS_SUCCESS;
}

status_ty VectorPopBack(vector_ty *vector)
{
    size_t new_size = 0;

    assert(NULL != vector);

    new_size = VectorGetMaxCapacity(vector)/SHRINK_FACTOR;

    if(VectorGetSize(vector) < new_size)
    {
        if(STATUS_FAIL == VectorReserve(vector,new_size))
        {
            return STATUS_FAIL;
        }
    }
    
    vector->curr_size -= vector->size_of_element;

    return STATUS_SUCCESS;
}

status_ty VectorShrinkToFit(vector_ty *vector)
{
    size_t new_capacity = 0;

    void *tmp_alloc = NULL;

    assert(NULL != vector);

    new_capacity = VectorGetSize(vector);
    tmp_alloc = vector->start;

    tmp_alloc = realloc(vector->start,(new_capacity*vector->size_of_element));

    if(NULL == vector->start)
    {
        fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
        return STATUS_FAIL;
    }

    vector->start=tmp_alloc;

    vector->capacity = new_capacity * vector->size_of_element;

    return STATUS_SUCCESS;
}