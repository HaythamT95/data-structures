#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

#define FAIL -1
#define CAPACITY 1000

static size_t HashFunction(const void* data_, const void* hash_params_);
static int IsSame(const void* key1_, const void* key2_, const void* is_same_params_);
static int PrintMap(void* data, void* param);

static int TestRunner();
static int TestHashCreate();
static int TestHashIsEmpty();
static int TestHashSize();
static int TestHashRemove();
static int TestHashFind();
static int TestHashForeach();
static int TestHashStats();

typedef struct student
{
	char name[50];
	char id[10];
}S;

hash_ty *hash = NULL;

int main()
{
	int state = SUCCESS;

	state = TestRunner();

	return state;
}

int TestRunner()
{
	int state = SUCCESS;

	state = TestHashCreate();

	if(SUCCESS == state)
	{
		printf("Test Create Hash Succeed :)\n");
	}
	else
	{
		printf("Test Create Hash Failed :(\n");
	}

	state = TestHashIsEmpty();

	if(SUCCESS == state)
	{
		printf("Test ISEmpty Hash Succeed :)\n");
	}
	else
	{
		printf("Test ISEmpty Hash Failed :(\n");
	}

	state = TestHashSize();

	if(SUCCESS == state)
	{
		printf("Test Size Hash Succeed :)\n");
	}
	else
	{
		printf("Test Size Hash Failed :(\n");
	}

	state = TestHashRemove();

	if(SUCCESS == state)
	{
		printf("Test Remove Hash Succeed :)\n");
	}
	else
	{
		printf("Test Remove Hash Failed :(\n");
	}

	state = TestHashFind();

	if(SUCCESS == state)
	{
		printf("Test Find Hash Succeed :)\n");
	}
	else
	{
		printf("Test Find Hash Failed :(\n");
	}

	state = TestHashForeach();

	if(SUCCESS == state)
	{
		printf("Test Foreach Hash Succeed :)\n");
	}
	else
	{
		printf("Test Foreach Hash Failed :(\n");
	}

	state = TestHashStats();

	if(SUCCESS == state)
	{
		printf("Test Stats Hash Succeed :)\n");
	}
	else
	{
		printf("Test Stats Hash Failed :(\n");
	}

	return state;
}

int TestHashCreate()
{
	int test_result = SUCCESS;
	
	hash = HashCreate(CAPACITY, HashFunction, NULL, IsSame, NULL);

	if(NULL == hash)
	{
		test_result = FAIL;
	}

	HashDestroy(hash);

	return test_result;
}

int TestHashIsEmpty()
{
	int test_result = SUCCESS;
	int cap = 1000;
	int is_empty_result = 0;
	int is_empty_expected = 1;

	S s1;
	strcpy(s1.id,"315822965");
	strcpy(s1.name,"Haytham");

	hash = HashCreate(CAPACITY, HashFunction, &cap, IsSame, NULL);

	is_empty_result = HashIsEmpty(hash);

	if(is_empty_result != is_empty_expected)
	{
		test_result = FAIL;
	}

	HashInsert(hash, &s1.id, &s1);

	is_empty_result = HashIsEmpty(hash);
	is_empty_expected = 0;

	if(is_empty_result != is_empty_expected)
	{
		test_result = FAIL;
	}

	HashDestroy(hash);

	return test_result;
}

int TestHashSize()
{
	int test_result = SUCCESS;
	int cap = 1000;
	int size_result = 0;
	int size_expected = 0;
	S s1;
	S s2;

	strcpy(s1.id,"315822965");
	strcpy(s1.name,"Haytham");

	strcpy(s2.id,"208808485");
	strcpy(s2.name,"Asem");

	hash = HashCreate(CAPACITY, HashFunction, &cap, IsSame, NULL);

	size_result = HashSize(hash);

	if(size_result != size_expected)
	{
		test_result = FAIL;
	}

	HashInsert(hash, &s1.id, &s1);
	HashInsert(hash, &s2.id, &s2);

	size_result = HashSize(hash);
	size_expected = 2;
	
	if(size_result != size_expected)
	{
		test_result = FAIL;
	}

	HashDestroy(hash);

	return test_result;
}

int TestHashRemove()
{
	int test_result = SUCCESS;
	int cap = 1000;
	int size_result = 0;
	int size_expected = 0;
	S s1;
	S s2;
	pair_ty pair;

	strcpy(s1.id,"315822965");
	strcpy(s1.name,"Haytham");

	strcpy(s2.id,"208808485");
	strcpy(s2.name,"Asem");

	hash = HashCreate(CAPACITY, HashFunction, &cap, IsSame, NULL);

	size_result = HashSize(hash);

	if(size_result != size_expected)
	{
		test_result = FAIL;
	}

	HashInsert(hash, &s1.id, &s1);
	HashInsert(hash, &s2.id, &s2);

	size_result = HashSize(hash);
	size_expected = 2;
	
	if(size_result != size_expected)
	{
		test_result = FAIL;
	}

	pair = HashRemove(hash, &s2.id);
	
	size_expected = 1;

	size_result = HashSize(hash);

	if(size_result != size_expected || 0 != strcmp(pair.data, s2.name) || 0 != strcmp(pair.key, s2.id))
	{
		test_result = FAIL;
	}

	HashDestroy(hash);

	return test_result;
}

int TestHashFind()
{
	int test_result = SUCCESS;
	int cap = 1000;
	S s1;
	S s2;
	S s3;
	pair_ty pair3;
	pair_ty pair2;

	strcpy(s1.id,"315822965");
	strcpy(s1.name,"Haytham");

	strcpy(s2.id,"208808485");
	strcpy(s2.name,"Asem");

	strcpy(s3.id,"318565918");
	strcpy(s3.name,"Najeeb");

	hash = HashCreate(CAPACITY, HashFunction, &cap, IsSame, NULL);

	HashInsert(hash, &s1.id, &s1);
	HashInsert(hash, &s2.id, &s2);
	HashInsert(hash, &s3.id, &s3);

	pair3 = HashFind(hash, &s3.id);
	
	if( 0 != strcmp(pair3.data, s3.name) || 0 != strcmp(pair3.key, s3.id))
	{
		test_result = FAIL;
	}

	pair2 = HashRemove(hash, &s2.id);

	pair2 = HashFind(hash, &s2.id);

	if(NULL != pair2.key || NULL != pair2.data)
	{
		test_result = FAIL;
	}

	HashDestroy(hash);

	return test_result;
}

int TestHashForeach()
{
	int test_result = SUCCESS;
	int cap = 1000;
	S s1;
	S s2;
	S s3;

	strcpy(s1.id,"315822965");
	strcpy(s1.name,"Haytham");

	strcpy(s2.id,"208808485");
	strcpy(s2.name,"Asem");

	strcpy(s3.id,"318565918");
	strcpy(s3.name,"Najeeb");

	hash = HashCreate(CAPACITY, HashFunction, &cap, IsSame, NULL);

	HashInsert(hash, &s1.id, &s1);
	HashInsert(hash, &s2.id, &s2);
	HashInsert(hash, &s3.id, &s3);

	HashForeach(hash, PrintMap, NULL);

	HashDestroy(hash);

	return test_result;
}

int TestHashStats()
{
	int test_result = SUCCESS;
	int cap = 5;
	S s1;
	S s2;
	S s3;
	hash_stats_ty stats;

	strcpy(s1.id,"315822965");
	strcpy(s1.name,"Haytham");

	strcpy(s2.id,"208808485");
	strcpy(s2.name,"Asem");

	strcpy(s3.id,"318565918");
	strcpy(s3.name,"Najeeb");

	hash = HashCreate(cap, HashFunction, &cap, IsSame, NULL);

	HashInsert(hash, &s1.id, &s1);
	HashInsert(hash, &s2.id, &s2);
	HashInsert(hash, &s3.id, &s3);

	stats = HashStats(hash);

	printf("longest list = %lu\n",stats.longest_list);
	printf("median list = %lu\n",stats.median_list);
	printf("size = %lu\n",stats.size);
	printf("capacity = %lu\n",stats.capacity);

	HashDestroy(hash);

	return test_result;
}

size_t HashFunction(const void* data_, const void* hash_params_)
{
	unsigned long hash = 5381;
	char* str = (char*)data_;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % *(int*)hash_params_ ;
}

int IsSame(const void* key1_, const void* key2_, const void* is_same_params_)
{	
	(void*)is_same_params_;
	if(*(int*)key1_ == *(int*)key2_)
	{
		return 1;
	}
	return 0;
}

int PrintMap(void* data, void* param)
{
	pair_ty* pair = (pair_ty*)data;
	printf("%s\n",(char*)pair->data);
	(void)param;
	return 0;
}