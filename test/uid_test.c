#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "uid.h"
enum State{FAIL,SUCCESS};

static int TestRunner();
static int TestGenerateUID();
static int TestMultithreadedGenerateUID();
static void* GenerateUID(void* vargp);

uid_ty uids[10];

int main()
{
	int state = SUCCESS;
	state = TestRunner();
	return state;
}

int TestRunner()
{
	int state = SUCCESS;

	state = TestGenerateUID();

	if(SUCCESS == state)
	{
		printf("Test Generate UID Succeed :)\n");
	}
	else
	{
		printf("Test Generate UID Failed :(\n");
	}

	state = TestMultithreadedGenerateUID();

	if(SUCCESS == state)
	{
		printf("Test Multithreaded Generate UID Succeed :)\n");
	}
	else
	{
		printf("Test Multithreaded Generate UID Failed :(\n");
	}

	return state;
}

int TestGenerateUID()
{
	int state = SUCCESS;
	int is_equal = 1;

	uid_ty uid1 = UIDGenerate();
	uid_ty uid2 = UIDGenerate();

	if(is_equal == UIDSame(uid1,uid2))
	{
		state = FAIL;
	}

	return state;
}

int TestMultithreadedGenerateUID()
{
	int state = SUCCESS;
	int is_equal = 1;
	size_t i = 0;
	size_t j = 0;

	pthread_t thread[10];

	for(i = 0; i < 10; ++i)
	{
		int *threadIndex = malloc(sizeof(int));
        *threadIndex = i;
		pthread_create(&thread[i], NULL, GenerateUID, threadIndex);
	}

	for(i = 0; i < 10; ++i)
	{
		pthread_join(thread[i], NULL);
	}
	
	for(i = 0; i < 10; ++i)
	{
		for(j = i + 1; j < 10; ++j)
		{
			if(is_equal == UIDSame(uids[i],uids[j]))
			{
				state = FAIL;
			}
		}
	}

	return state;
}

void* GenerateUID(void* vargp)
{
	int i = *(int*)vargp;
	uids[i] = UIDGenerate();

	return 0;
}