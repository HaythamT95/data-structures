#include <stdio.h> /*fprintf*/
#include <stdlib.h> /*malloc, free*/
#include <time.h> /*time_t*/
#include <assert.h> /*assert*/

#include "task.h"

#define BAD_TIMESTAMP ((time_t)-1)
#define MATCH 0
#define NO_MATCH 1

struct task 
{
	uid_ty task_id;
	task_op_func_ty op_func;
	void *op_params;
	time_t interval_in_sec;
	time_t time_to_run;
};

/*
 *****************************PSEUDOCODE******************************
task_ty *TaskCreate(time_t interval_in_sec, task_op_func_ty op_func, void *op_params)
{
	0. Validate Input
	1. CreateTask
	2. GenerateUID
	3. init vars
	4. Return task
}

void TaskDestroy(task_ty *task)
{
	0. Validate Input
	1. Free
}

task_status_ty TaskUpdateTimeToRun(task_ty *task)
{
	0. Validate Input
	1. GetTimeStamp
		1.1 If time stamp = bad ? Return ERROR(1)
	2. Calculate new time
	3. Update
}

time_t TaskGetTimeToRun(task_ty *task)
{
	0. Validate Input
	1. Return TimeToRun
}

uid_ty TaskGetUID(task_ty *task)
{
	0. Validate Input
	1. Return UID
}

int TaskIsMatch(task_ty *task, uid_ty task_id)
{
	0. Validate Input
	1. Check if two tasks are equal Using UIDSame
	2. Return values from UIDSame
}

task_repeat_status_ty TaskRun(task_ty *task)
{
	0. Validate Input
	1. Call op_func of task with task params
}

int TaskIsBefore(task_ty *first_task, task_ty *second_task)
{
	0. Validate Input
	1. Return whos task should be first between first_task and second_task
}
*/


task_ty *TaskCreate(time_t interval_in_sec, task_op_func_ty op_func,
															void *op_params)
{
	task_ty *task = NULL;
	uid_ty uid;

	assert(NULL != op_func);
	assert(0 < interval_in_sec);

	task = (task_ty*)malloc(sizeof(task_ty));

	if(NULL == task)
	{
		fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
		return NULL;
	}

	uid = UIDGenerate();
	task->interval_in_sec = interval_in_sec;
	task->op_func = op_func;
	task->op_params = op_params;
	task->task_id = uid;
	task->time_to_run = uid.time_stamp + interval_in_sec;

	return task;
}

void TaskDestroy(task_ty *task)
{
	if(NULL != task)
	{
		free(task);
		task = NULL;
	}
}

task_status_ty TaskUpdateTimeToRun(task_ty *task)
{
	time_t updated_time;
	assert(NULL != task);

	updated_time = time(NULL);

	if(BAD_TIMESTAMP == updated_time)
	{
		return TASK_ERROR;
	}

	task->time_to_run = updated_time + task->interval_in_sec;

	return TASK_NO_ERROR;
}

time_t TaskGetTimeToRun(const task_ty *task)
{
	assert(NULL != task);

	return task->time_to_run;
}

uid_ty TaskGetUID(const task_ty *task)
{
	assert(NULL != task);

	return task->task_id;
}

int TaskIsMatch(const void *task, const void *task_id)
{

	assert(NULL != task);

	return UIDSame(((task_ty*)task)->task_id, *(uid_ty*)task_id)? 
															1 : 0;
}

task_repeat_status_ty TaskRun(task_ty *task)
{
	assert(NULL != task);

	return task->op_func(task->op_params);
}

int TaskIsBefore(void *first_task, void *second_task)
{
	assert(NULL != first_task);
	assert(NULL != second_task);

	return ((task_ty*)first_task)->time_to_run < 
										((task_ty*)second_task)->time_to_run;
}