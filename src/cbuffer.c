/*
Name: Haytham
Reviewer: Diana
*/
#include <stdio.h> /*fprintf*/
#include <stdlib.h> /*free, malloc*/
#include <stddef.h> /*size_t*/
#include <sys/types.h> /*ssize_t*/
#include <assert.h> /*assert*/

#include "cbuffer.h"

struct c_buff
{
	size_t read_offset;
	size_t size;
	size_t capacity;
	char buffer[1];
};

c_buff_ty *CBuffCreate(size_t capacity)
{
	c_buff_ty *c_buff = (c_buff_ty*)malloc(sizeof(c_buff_ty) +
												sizeof(char) * (capacity - 1));

	if(NULL == c_buff)
    {
        fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
        return NULL;
    }

    c_buff->read_offset = 0;
    c_buff->size = 0;
    c_buff->capacity = capacity;

    return c_buff;
}

void CBuffDestory(c_buff_ty *c_buff)
{
	assert(NULL != c_buff);

	free(c_buff);
	c_buff = NULL;
}

int CBuffIsEmpty(const c_buff_ty *c_buff)
{
	assert(NULL != c_buff);

	return 0 == c_buff->size;
}

size_t CBuffFreeSpace(const c_buff_ty *c_buff)
{
	assert(NULL != c_buff);

	return c_buff->capacity - c_buff->size;
}

size_t CBuffSize(const c_buff_ty *c_buff)
{
	assert(NULL != c_buff);

	return c_buff->size;
}

ssize_t CBuffWrite(c_buff_ty *c_buff, const void *src, size_t count)
{
	char byte = 0;
	size_t i = 0;

	assert(NULL != c_buff);
	assert(NULL != src);
	assert(count <= CBuffFreeSpace(c_buff));

	for (i = 0; i < count; ++i)
	{
		byte = *((char*)src + i);
		c_buff->buffer[(c_buff->read_offset + c_buff->size)
													% c_buff->capacity] = byte;
        ++c_buff->size;
	}

	return count;
}

ssize_t CBuffRead(c_buff_ty *c_buff, void *dest, size_t count)
{
	size_t i = 0;

	assert(NULL != c_buff);
	assert(NULL != dest);
	assert(count <= CBuffSize(c_buff));

	for (i = 0; i < count; ++i)
	{
		*((char*)dest+i) = c_buff->buffer[c_buff->read_offset];
		c_buff->read_offset = (c_buff->read_offset + 1) % c_buff->capacity;
		--c_buff->size;
	}

	*((char*)dest+i) = '\0';

	return count;
}