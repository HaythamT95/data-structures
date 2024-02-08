#include <stdio.h> /*printf*/

#include "vector.h"

enum State{FAIL,SUCCESS};

static int Runner();

static int TestCreateVector();

static int TestSetValue();
static int TestGetValue();

static int TestMaximumCapacity();
static int TestGetSize();

static int TestPushBack();
static int TestPopBack();

static int TestReserve();
static int TestShrinkToFit();

static int TestDestroyVector();

static int TestStruct();

vector_ty *vec = NULL;

struct vector_test
{
	char a;
	char b;
	char c;
	char d;
	int x;
};

int main()
{
	int state = SUCCESS;
	state = Runner();
	return state;
}

int Runner()
{
	int state = SUCCESS;

	state = TestCreateVector();

	if(SUCCESS == state)
	{
		printf("Test Create Vector Succeed :)\n");
	}
	else
	{
		printf("Test Create Vector Failed :(\n");
	}

	state = TestSetValue();

	if(SUCCESS == state)
	{
		printf("Test Vector Set Value Succeed :)\n");
	}
	else
	{
		printf("Test Vector Set Value Failed :(\n");
	}

	state = TestGetValue();

	if(SUCCESS == state)
	{
		printf("Test Vector Get Value Succeed :)\n");
	}
	else
	{
		printf("Test Vector Get Value Failed :(\n");
	}

	state = TestMaximumCapacity();

	if(SUCCESS == state)
	{
		printf("Test Vector Maximum Capacity Succeed :)\n");
	}
	else
	{
		printf("Test Vector Maximum Capacity Failed :(\n");
	}

	state = TestGetSize();

	if(SUCCESS == state)
	{
		printf("Test Vector Size Succeed :)\n");
	}
	else
	{
		printf("Test Vector Size Failed :(\n");
	}

	state = TestPushBack();

	if(SUCCESS == state)
	{
		printf("Test Vector Push Back Succeed :)\n");
	}
	else
	{
		printf("Test Vector Push Back Failed :(\n");
	}

	state = TestPopBack();

	if(SUCCESS == state)
	{
		printf("Test Vector Pop Back Succeed :)\n");
	}
	else
	{
		printf("Test Vector Pop Back Failed :(\n");
	}

	state = TestReserve();

	if(SUCCESS == state)
	{
		printf("Test Vector Reserve Succeed :)\n");
	}
	else
	{
		printf("Test Vector Reserve Failed :(\n");
	}

	state = TestShrinkToFit();

	if(SUCCESS == state)
	{
		printf("Test Vector Shrink To Fit Succeed :)\n");
	}
	else
	{
		printf("Test Vector Shrink To Fit Failed :(\n");
	}

	state = TestDestroyVector();

	if(SUCCESS == state)
	{
		printf("Test Vector Destory Succeed :)\n");
	}

	state = TestStruct();

	if(SUCCESS == state)
	{
		printf("Test Struct Succeed :)\n");
	}
	else
	{
		printf("Test Struct Failed :(\n");
	}

	return state;
}

int TestCreateVector()
{
	int test_result = SUCCESS;
	size_t capacity = 5;
	size_t size_of_element = sizeof(int);

	vec = VectorCreate(capacity,size_of_element);

	if(NULL == vec)
	{
		test_result = FAIL;
	}

	VectorDestroy(vec);

	return test_result;
}

int TestSetValue()
{
	int state = SUCCESS;
	int val = 100;
	int *expected = NULL;
	int *result;

	size_t capacity = 5;
	size_t size_of_element = sizeof(int);
	vec = VectorCreate(capacity,size_of_element);

	VectorSetValue(vec,0,&val);

	result = VectorGetValue(vec,0);

	if(NULL != expected || NULL != result)
	{
		state = FAIL;
	}
	
	VectorDestroy(vec);

	return state;
}

int TestGetValue()
{
	int state = SUCCESS;
	int *expected = NULL;
	int *result;
	size_t capacity = 5;
	size_t size_of_element = sizeof(int);
	vec = VectorCreate(capacity,size_of_element);

	result = VectorGetValue(vec,1);

	if(NULL != expected || NULL != result)
	{
		state = FAIL;
	}

	VectorDestroy(vec);

	return state;
}

int TestMaximumCapacity()
{
	int state = SUCCESS;
	size_t expected = 5;
	size_t result = 0;

	size_t capacity = 5;
	size_t size_of_element = sizeof(int);
	vec = VectorCreate(capacity,size_of_element);

	result = VectorGetMaxCapacity(vec);

	if(expected != result)
	{
		state = FAIL;
	}	

	VectorDestroy(vec);

	return state;
}

int TestGetSize()
{
	int state = SUCCESS;
	size_t expected = 0;
	size_t result = 0;

	size_t capacity = 5;
	size_t size_of_element = sizeof(int);
	vec = VectorCreate(capacity,size_of_element);

	result = VectorGetSize(vec);

	if(expected != result)
	{
		state = FAIL;
	}

	VectorDestroy(vec);

	return state;
}

int TestPushBack()
{
	int state = SUCCESS;
	int result = 0;
	int element = 555;
	size_t expected_size = 0;
	size_t size = 1;

	size_t capacity = 5;
	size_t size_of_element = sizeof(int);
	vec = VectorCreate(capacity,size_of_element);

	result = VectorPushBack(vec,&element);
	expected_size = VectorGetSize(vec);

	if(expected_size != size && 1 == result)
	{
		state = FAIL;
	}

	VectorDestroy(vec);

	return state;
}

int TestPopBack()
{
	int state = SUCCESS;
	int result = 0;
	int element = 123;
	size_t expected_size = 2;
	size_t size = 0;
	size_t i = 0;

	size_t capacity = 5;
	size_t size_of_element = sizeof(int);
	vec = VectorCreate(capacity,size_of_element);

	for(i = 0; i < 7; ++i)
	{
		result = VectorPushBack(vec,&element);

	}

	for(i = 0; i < 5; ++i)
	{
		result = VectorPopBack(vec);
	}

	size = VectorGetSize(vec);

	if(expected_size != size && 1 == result)
	{
		state = FAIL;
	}

	VectorDestroy(vec);

	return state;
}

int TestReserve()
{
	int state = SUCCESS;
	int result = 0;
	int element = 123;
	size_t expected_size = 10;
	size_t cap = 0;
	size_t i = 0;

	size_t capacity = 5;
	size_t size_of_element = sizeof(int);
	vec = VectorCreate(capacity,size_of_element);

	for(i = 0; i < 6; ++i)
	{
		result = VectorPushBack(vec,&element);
	}

	capacity = 10;
	result = VectorReserve(vec,capacity);

	cap = VectorGetMaxCapacity(vec);

	if(expected_size != cap)
	{
		state = FAIL;
	}

	(void)result;

	VectorDestroy(vec);

	return state;
}

int TestShrinkToFit()
{
	int state = SUCCESS;
	int result = 0;
	int element = 123;
	size_t expected_capacity = 2;
	size_t result_capacity = 0;
	size_t capacity = 5;
	size_t size_of_element = sizeof(int);
	vec = VectorCreate(capacity,size_of_element);

	result = VectorPushBack(vec,&element);
	result = VectorPushBack(vec,&element);

	result = VectorShrinkToFit(vec);

	result_capacity = VectorGetMaxCapacity(vec);

	if(expected_capacity != result_capacity)
	{
		state = FAIL;
	}

	(void)result;

	return state;
}

int TestDestroyVector()
{
	int state = SUCCESS;

	VectorDestroy(vec);
	vec = NULL;

	return state;
}

static void PrintStruct(struct vector_test st_vec)
{
	printf("%c %c %c %c %d\n",st_vec.a,st_vec.b,st_vec.c,st_vec.d,st_vec.x);
}

int TestStruct()
{
	int state = SUCCESS;
	size_t capacity = 1;
	struct vector_test st_vec;
	size_t size_of_element = sizeof(st_vec);
	struct vector_test *test = NULL;
	
	st_vec.a = 'a';
	st_vec.b = 'b';
	st_vec.c = 'c';
	st_vec.d = 'd';
	st_vec.x = 5;

	vec = VectorCreate(capacity,size_of_element);
	PrintStruct(st_vec);

	st_vec.a = 'x';
	st_vec.b = 'y';
	st_vec.c = 't';
	st_vec.d = 'z';
	st_vec.x = 10;

	VectorPushBack(vec,&st_vec);

	test = VectorGetValue(vec,0);
	
	PrintStruct(*test);

	VectorDestroy(vec);
	vec = NULL;

	return state;
}

