#include <stdio.h> /*printf*/
#include <string.h> /*strcmp*/

#include "cbuffer.h"

enum State{FAIL,SUCCESS};

static int Runner();

static int TestCreateBuffer();

static int TestBufferIsEmpty();
static int TestBufferFreeSpace();
static int TestBufferSize();

static int TestBufferWrite();
static int TestBufferRead();

c_buff_ty *c_buff = NULL;

int main()
{
	int state = SUCCESS;
	state = Runner();
	return state;
}

int Runner()
{
	int state = SUCCESS;
	
	state = TestCreateBuffer();

	if(SUCCESS == state)
	{
		printf("Test Create Buffer Succeed :)\n");
	}
	else
	{
		printf("Test Create Buffer Failed :(\n");
	}

	state = TestBufferIsEmpty();

	if(SUCCESS == state)
	{
		printf("Test IsEmpty Buffer Succeed :)\n");
	}
	else
	{
		printf("Test IsEmpty Buffer Failed :(\n");
	}

	state = TestBufferFreeSpace();

	if(SUCCESS == state)
	{
		printf("Test FreeSpace Buffer Succeed :)\n");
	}
	else
	{
		printf("Test FreeSpace Buffer Failed :(\n");
	}

	state = TestBufferSize();

	if(SUCCESS == state)
	{
		printf("Test Size Buffer Succeed :)\n");
	}
	else
	{
		printf("Test Size Buffer Failed :(\n");
	}

	state = TestBufferWrite();

	if(SUCCESS == state)
	{
		printf("Test Write Buffer Succeed :)\n");
	}
	else
	{
		printf("Test Write Buffer Failed :(\n");
	}

	state = TestBufferRead();

	if(SUCCESS == state)
	{
		printf("Test Read Buffer Succeed :)\n");
	}
	else
	{
		printf("Test Read Buffer Failed :(\n");
	}

	return state;
}

int TestCreateBuffer()
{
	int test_result = SUCCESS;
	size_t capacity = 5;

	c_buff = CBuffCreate(capacity);

	if(NULL == c_buff)
	{
		test_result = FAIL;
	}

	CBuffDestory(c_buff);

	return test_result;
}

int TestBufferIsEmpty()
{
	int test_result = SUCCESS;
	int is_empty_result = 0;
	int is_empty_expected = 1;
	size_t capacity = 5;

	c_buff = CBuffCreate(capacity);

	is_empty_result = CBuffIsEmpty(c_buff);

	if(is_empty_expected != is_empty_result)
	{
		test_result = FAIL;
	}

	CBuffDestory(c_buff);

	return test_result;
}

int TestBufferFreeSpace()
{
	int test_result = SUCCESS;
	size_t expected = 1;
	size_t result = 0;
	size_t capacity = 5;
	char *string="Hell";

	c_buff = CBuffCreate(capacity);

	CBuffWrite(c_buff,string,4);
	result = CBuffFreeSpace(c_buff);

	if(result != expected)
	{
		test_result = FAIL;
	}

	CBuffDestory(c_buff);

	return test_result;
}

int TestBufferSize()
{
	int test_result = SUCCESS;
	size_t expected = 4;
	size_t result = 0;
	size_t capacity = 5;
	char *string="Hell";

	c_buff = CBuffCreate(capacity);

	CBuffWrite(c_buff,string,4);
	result = CBuffSize(c_buff);

	if(result != expected)
	{
		test_result = FAIL;
	}

	CBuffDestory(c_buff);

	return test_result;
}

int TestBufferWrite()
{
	int test_result = SUCCESS;
	int expected = 1;
	size_t capacity = 5;
	ssize_t write_len = 0;
	char *string="Hell";
	char *string2="owww";

	c_buff = CBuffCreate(capacity);

	write_len = CBuffWrite(c_buff,string,4);
	write_len = CBuffWrite(c_buff,string2,1);

	if(write_len != expected)
	{
		test_result = FAIL;
	}

	CBuffDestory(c_buff);

	return test_result;
}

int TestBufferRead()
{
	int test_result = SUCCESS;
	size_t capacity = 5;
	char *string="Hell";
	char *expected_dest="ell";
	char dest[5];

	c_buff = CBuffCreate(capacity);

	CBuffWrite(c_buff,string,4);
	CBuffRead(c_buff,dest,1);
	CBuffRead(c_buff,dest,3);

	if(0 != strcmp(expected_dest,dest))
	{
		test_result = FAIL;
	}

	CBuffDestory(c_buff);

	return test_result;
}