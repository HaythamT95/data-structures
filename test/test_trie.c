#include <stdio.h>

#include "trie.h"

enum STATE
{
	FAIL = -1,
	SUCCESS = 0
};

static int TestRunner();
static int TestTrieCreate();
static int TestTrieAlloc();
static int TestTrieFree();
static int TestTrieCountAvailable();
static int TestTrieIsAllTaken();

trie_ty *trie = NULL;

int main()
{
	int state = SUCCESS;

	state = TestRunner();

	return state;
}

int TestRunner()
{
	int state = SUCCESS;

	state = TestTrieCreate();

	if(SUCCESS == state)
	{
		printf("Test Create Trie Succeed :)\n");
	}
	else
	{
		printf("Test Create Trie Failed :(\n");
	}

	state = TestTrieAlloc();

	if(SUCCESS == state)
	{
		printf("Test Alloc Trie Succeed :)\n");
	}
	else
	{
		printf("Test Alloc Trie Failed :(\n");
	}

	state = TestTrieFree();

	if(SUCCESS == state)
	{
		printf("Test Free Trie Succeed :)\n");
	}
	else
	{
		printf("Test Free Trie Failed :(\n");
	}

	state = TestTrieCountAvailable();

	if(SUCCESS == state)
	{
		printf("Test CountAvailable Trie Succeed :)\n");
	}
	else
	{
		printf("Test CountAvailable Trie Failed :(\n");
	}

	state = TestTrieIsAllTaken();

	if(SUCCESS == state)
	{
		printf("Test IsAllTaken Trie Succeed :)\n");
	}
	else
	{
		printf("Test IsAllTaken Trie Failed :(\n");
	}

	return state;
}

int TestTrieCreate()
{
	int test_result = SUCCESS;
	
	trie = TrieCreate(4);

	if(NULL == trie)
	{
		test_result = FAIL;
	}

	TrieDestroy(trie);

	return test_result;
}

int TestTrieAlloc()
{
	int test_result = SUCCESS;
	unsigned long ip = 0;
	unsigned long ip2 = 0;
	unsigned long ip3 = 0;
	unsigned long ip4 = 0;

	trie = TrieCreate(2);

	ip = TrieGet(trie, 1);
	ip2 = TrieGet(trie, 1);
	ip3 = TrieGet(trie, 1);
	ip4 = TrieGet(trie, 1);

	if(ip != 1 || ip2 != 0 || ip3 != 2 || ip4 != 3)
	{
		test_result = FAIL;
	}

	TrieDestroy(trie);

	return test_result;
}

int TestTrieFree()
{
	int test_result = SUCCESS;
	unsigned long ip = 0;
	unsigned long ip2 = 0;
	unsigned long ip3 = 0;
	unsigned long ip4 = 0;

	trie = TrieCreate(2);

	ip = TrieGet(trie, 1);
	ip2 = TrieGet(trie, 1);
	ip3 = TrieGet(trie, 1);

	TrieFree(trie, ip3);
	ip4 = TrieGet(trie, 1);

	if(ip != 1 || ip2 != 0 || ip4 != ip3)
	{
		test_result = FAIL;
	}

	TrieDestroy(trie);

	return test_result;
}

int TestTrieCountAvailable()
{
	int test_result = SUCCESS;
	unsigned long ip = 0;
	unsigned long ip2 = 0;
	unsigned long ip3 = 0;
	unsigned long ip4 = 0;
	size_t expected_available = 4;
	size_t result_available = 0;

	trie = TrieCreate(2);

	result_available = TrieCountAvailable(trie);

	if(result_available != expected_available)
	{
		test_result = FAIL;
	}

	ip = TrieGet(trie, 1);

	expected_available = 3;

	result_available = TrieCountAvailable(trie);

	if(result_available != expected_available)
	{
		test_result = FAIL;
	}

	ip2 = TrieGet(trie, 1);

	expected_available = 2;

	result_available = TrieCountAvailable(trie);

	if(result_available != expected_available)
	{
		test_result = FAIL;
	}

	ip3 = TrieGet(trie, 1);

	expected_available = 1;

	result_available = TrieCountAvailable(trie);
	
	if(result_available != expected_available)
	{
		test_result = FAIL;
	}

	(void)ip;
	(void)ip4;
	(void)ip3;
	(void)ip2;

	TrieDestroy(trie);

	return test_result;
}

int TestTrieIsAllTaken()
{
	int test_result = SUCCESS;
	unsigned long ip = 0;
	unsigned long ip2 = 0;
	unsigned long ip3 = 0;
	unsigned long ip4 = 0;
	int result_is_all_taken = 0;
	int expected_is_all_taken = 0;

	trie = TrieCreate(2);
	result_is_all_taken = TrieIsAllTaken(trie);

	if(expected_is_all_taken != result_is_all_taken)
	{
		test_result = FAIL;
	}

	ip = TrieGet(trie, 1);
	ip2 = TrieGet(trie, 1);
	ip3 = TrieGet(trie, 1);
	
	result_is_all_taken = TrieIsAllTaken(trie);

	if(expected_is_all_taken != result_is_all_taken)
	{
		test_result = FAIL;
	}

	ip4 = TrieGet(trie, 1);

	expected_is_all_taken = 1;
	result_is_all_taken = TrieIsAllTaken(trie);

	if(expected_is_all_taken != result_is_all_taken)
	{
		test_result = FAIL;
	}

	(void)ip;
	(void)ip4;
	(void)ip3;
	(void)ip2;

	TrieDestroy(trie);

	return test_result;
}