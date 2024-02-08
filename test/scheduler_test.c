#include <stdio.h> /*printf*/
#include <unistd.h> /*sleep*/

#include "scheduler.h"

enum State{FAIL,SUCCESS};

static int TestRunner();

static int TestSchedulerCreate();

static int TestSchedulerAddTask();
static int TestSchedulerRemoveTask();
static int TestSchedulerClearAll();

static int TestSchedulerSize();
static int TestSchedulerIsEmpty();
static int TestSchedulerFunctionToFunction();
static int TestSchedulerSelfDestruct();


int PrintHello(void *param);
int CallPrintHello(void *param);
int ClearAll(void *param);
int RemoveSelf(void *param);

sched_ty *scheduler = NULL;

int main()
{
	int state = SUCCESS;
	state = TestRunner();
	return state;
}

int TestRunner()
{
	int state = SUCCESS;

	state = TestSchedulerCreate();

	if(SUCCESS == state)
	{
		printf("Test Create Scheduler Succeed :)\n");
	}
	else
	{
		printf("Test Create Scheduler Failed :(\n");
	}

	state = TestSchedulerAddTask();

	if(SUCCESS == state)
	{
		printf("Test AddTask Scheduler Succeed :)\n");
	}
	else
	{
		printf("Test AddTask Scheduler Failed :(\n");
	}

	state = TestSchedulerRemoveTask();

	if(SUCCESS == state)
	{
		printf("Test RemoveTask Scheduler Succeed :)\n");
	}
	else
	{
		printf("Test RemoveTask Scheduler Failed :(\n");
	}

	state = TestSchedulerSize();

	if(SUCCESS == state)
	{
		printf("Test Size Scheduler Succeed :)\n");
	}
	else
	{
		printf("Test Size Scheduler Failed :(\n");
	}

	state = TestSchedulerIsEmpty();

	if(SUCCESS == state)
	{
		printf("Test IsEmpty Scheduler Succeed :)\n");
	}
	else
	{
		printf("Test IsEmpty Scheduler Failed :(\n");
	}

	state = TestSchedulerFunctionToFunction();

	if(SUCCESS == state)
	{
		printf("Test FunctionToFunction Scheduler Succeed :)\n");
	}
	else
	{
		printf("Test FunctionToFunction Scheduler Failed :(\n");
	}

	state = TestSchedulerClearAll();

	if(SUCCESS == state)
	{
		printf("Test ClearAll Scheduler Succeed :)\n");
	}
	else
	{
		printf("Test ClearAll Scheduler Failed :(\n");
	}

	state = TestSchedulerSelfDestruct();

	if(SUCCESS == state)
	{
		printf("Test SelfDestruct Scheduler Succeed :)\n");
	}
	else
	{
		printf("Test SelfDestruct Scheduler Failed :(\n");
	}

	return state;
}

int TestSchedulerCreate()
{
	int test_result = SUCCESS;

	scheduler = SchedCreate();

	if(NULL == scheduler)
	{
		test_result = FAIL;
	}

	SchedDestroy(scheduler);

	return test_result;
}

int TestSchedulerAddTask()
{
	int test_result = SUCCESS;
	sched_op_func_ty print = PrintHello;
	sched_op_func_ty stop = (sched_op_func_ty)SchedStop;
	char *str1 = "Hello";
	char *str2 = "World!";

	scheduler = SchedCreate();
	SchedAddTask(scheduler,print,str1,1);

	SchedAddTask(scheduler,print,str2,2);

	SchedAddTask(scheduler,stop,scheduler,3);


	SchedRun(scheduler);
	sleep(5);
	SchedAddTask(scheduler,stop,scheduler,3);
	SchedRun(scheduler);

	if(NULL == scheduler)
	{
		test_result = FAIL;
	}

	SchedDestroy(scheduler);

	return test_result;
}

int TestSchedulerRemoveTask()
{
	int test_result = SUCCESS;
	sched_op_func_ty print = PrintHello;
	sched_op_func_ty stop = (sched_op_func_ty)SchedStop;
	uid_ty uid_to_remove1;
	uid_ty uid_to_remove2;
	uid_ty uid_to_remove3;

	char *str1 = "Hello";
	char *str2 = "World!";
	char *str3 = "C Programming";

	scheduler = SchedCreate();
	uid_to_remove1 = SchedAddTask(scheduler,print,str1,1);
	uid_to_remove2 = SchedAddTask(scheduler,print,str2,1);
	uid_to_remove3 = SchedAddTask(scheduler,print,str3,1);

	SchedRemoveTask(scheduler, uid_to_remove3);

	SchedAddTask(scheduler,stop,scheduler,5);

	SchedRun(scheduler);

	if(NULL == scheduler)
	{
		test_result = FAIL;
	}
	(void)uid_to_remove2;
	(void)uid_to_remove1;

	SchedDestroy(scheduler);

	return test_result;
}

int TestSchedulerSize()
{
	int test_result = SUCCESS;
	sched_op_func_ty print = PrintHello;
	sched_op_func_ty stop = (sched_op_func_ty)SchedStop;
	uid_ty uid_to_remove1;
	size_t size_result = 0;

	size_t size_before_removing = 3;
	size_t size_after_removing = 2;

	char *str1 = "Hello";
	char *str2 = "World!";
	char *str3 = "C Programming";

	scheduler = SchedCreate();

	if(NULL == scheduler)
	{
		test_result = FAIL;
	}

	uid_to_remove1 = SchedAddTask(scheduler,print,str1,1);
	SchedAddTask(scheduler,print,str2,1);
	SchedAddTask(scheduler,print,str3,1);
	size_result = SchedSize(scheduler);

	if(size_before_removing != size_result)
	{
		test_result = FAIL;
	}

	SchedRemoveTask(scheduler, uid_to_remove1);
	size_result = SchedSize(scheduler);

	if(size_after_removing != size_result)
	{
		test_result = FAIL;
	}
	SchedAddTask(scheduler,stop,scheduler,5);

	SchedRun(scheduler);

	SchedDestroy(scheduler);

	return test_result;
}

int TestSchedulerIsEmpty()
{
	int test_result = SUCCESS;
	sched_op_func_ty print = PrintHello;
	uid_ty uid_to_remove1;
	size_t isempty_result = 0;

	size_t size_before_removing = 0;
	size_t size_after_removing = 1;

	char *str1 = "Hello";

	scheduler = SchedCreate();

	if(NULL == scheduler)
	{
		test_result = FAIL;
	}

	uid_to_remove1 = SchedAddTask(scheduler,print,str1,1);
	isempty_result = SchedIsEmpty(scheduler);

	if(size_before_removing != isempty_result)
	{
		test_result = FAIL;
	}

	SchedRemoveTask(scheduler, uid_to_remove1);
	isempty_result = SchedIsEmpty(scheduler);


	if(size_after_removing != isempty_result)
	{
		test_result = FAIL;
	}


	SchedDestroy(scheduler);

	return test_result;
}

int TestSchedulerFunctionToFunction()
{
	int test_result = SUCCESS;
	sched_op_func_ty stop = (sched_op_func_ty)SchedStop;

	scheduler = SchedCreate();

	if(NULL == scheduler)
	{
		test_result = FAIL;
	}

	SchedAddTask(scheduler,CallPrintHello,scheduler,1);

	SchedAddTask(scheduler,stop,scheduler,5);
	SchedRun(scheduler);

	SchedDestroy(scheduler);

	return test_result;
}

int TestSchedulerClearAll()
{
	int test_result = SUCCESS;
	sched_op_func_ty stop = (sched_op_func_ty)SchedStop;
	char *str1 = "Hello";

	scheduler = SchedCreate();

	if(NULL == scheduler)
	{
		test_result = FAIL;
	}

	SchedAddTask(scheduler,PrintHello,str1,1);
	SchedAddTask(scheduler,ClearAll,scheduler,3);
	SchedAddTask(scheduler,stop,scheduler,5);
	SchedRun(scheduler);

	SchedDestroy(scheduler);

	return test_result;
}

int TestSchedulerSelfDestruct()
{
	int test_result = SUCCESS;
	uid_ty uid_to_remove1;
	uid_ty *remove = &uid_to_remove1;

	scheduler = SchedCreate();

	if(NULL == scheduler)
	{
		test_result = FAIL;
	}

	uid_to_remove1 = SchedAddTask(scheduler,RemoveSelf,remove,1);
	SchedRun(scheduler);

	SchedDestroy(scheduler);

	(void)uid_to_remove1;

	return test_result;
}


int RemoveSelf(void *param)
{
	int status = 0;
	(void)param;
	status = SchedRemoveTask(scheduler,*(uid_ty*)param);
	return status;
}

int ClearAll(void *param)
{
	(void)param;
	SchedClear(scheduler);
	return 0;
}

int PrintHello(void *param)
{
	printf("%s\n",(char*)param);
	return 1;
}

int CallPrintHello(void *param)
{
	char *str1="Hello";
	(void)param;
	SchedAddTask(scheduler,PrintHello,str1,1);
	return 1;
}