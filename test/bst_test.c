#include <stdio.h> /*printf*/

#include "bst.h"

#define FAIL 1

static int TestRunner();

static int TestCreateBST();

static int TestBSTIsEmpty();

static int TestBSTInsert();
static int TestBSTInsertSameElement();

static int TestBSTRemoveNodeWithNoChildren();
static int TestBSTRemoveNodeWithOneChild();
static int TestBSTRemoveNodeWithTwoChildren();

static int TestBSTForEach();
static int TestBSTFind();

int IsBefore(const void *data1, const void *data2, const void *params);
int AddParam(void *data, void *func_param);

bst_ty *bst = NULL;

int main()
{
	int state = SUCCESS;

	state = TestRunner();

	return state;
}

int TestRunner()
{
	int state = SUCCESS;

	state = TestCreateBST();

	if(SUCCESS == state)
	{
		printf("Test Create BST Succeed :)\n");
	}
	else
	{
		printf("Test Create BST Failed :(\n");
	}

	state = TestBSTIsEmpty();

	if(SUCCESS == state)
	{
		printf("Test IsEmpty BST Succeed :)\n");
	}
	else
	{
		printf("Test IsEmpty BST Failed :(\n");
	}

	state = TestBSTInsert();

	if(SUCCESS == state)
	{
		printf("Test Insert BST Succeed :)\n");
	}
	else
	{
		printf("Test Insert BST Failed :(\n");
	}

	state = TestBSTInsertSameElement();

	if(SUCCESS == state)
	{
		printf("Test InsertSameElement BST Succeed :)\n");
	}
	else
	{
		printf("Test InsertSameElement BST Failed :(\n");
	}

	state = TestBSTRemoveNodeWithNoChildren();

	if(SUCCESS == state)
	{
		printf("Test RemoveNodeWithNoChildren Succeed :)\n");
	}
	else
	{
		printf("Test RemoveNodeWithNoChildren Failed :(\n");
	}

	state = TestBSTRemoveNodeWithOneChild();

	if(SUCCESS == state)
	{
		printf("Test RemoveNodeWithOneChild Succeed :)\n");
	}
	else
	{
		printf("Test RemoveNodeWithOneChild Failed :(\n");
	}

	state = TestBSTRemoveNodeWithTwoChildren();

	if(SUCCESS == state)
	{
		printf("Test RemoveNodeWithTwoChildren Succeed :)\n");
	}
	else
	{
		printf("Test RemoveNodeWithTwoChildren Failed :(\n");
	}

	state = TestBSTForEach();

	if(SUCCESS == state)
	{
		printf("Test ForEach Succeed :)\n");
	}
	else
	{
		printf("Test ForEach Failed :(\n");
	}

	state = TestBSTFind();

	if(SUCCESS == state)
	{
		printf("Test Find Succeed :)\n");
	}
	else
	{
		printf("Test Find Failed :(\n");
	}

	return state;
}

int TestCreateBST()
{
	int test_result = SUCCESS;

	is_before_func_ty is_before_func = IsBefore;

	bst = BSTCreate(is_before_func, NULL);

	if(NULL == bst)
	{
		test_result = FAIL;
	}

	BSTDestroy(bst);

	return test_result;
}

int TestBSTIsEmpty()
{
	int test_result = SUCCESS;
	int expected_is_empty = 1;
	int result_is_empty = 0;

	is_before_func_ty is_before_func = IsBefore;

	bst = BSTCreate(is_before_func, NULL);

	result_is_empty = BSTIsEmpty(bst);

	if(result_is_empty != expected_is_empty)
	{
		test_result = FAIL;
	}

	BSTDestroy(bst);

	return test_result;
}

int TestBSTInsert()
{
	/*		1		*/
	/*	   /  \		*/
	/*	  0	   2	*/
	/*	 /			*/
	/*	-1    		*/

	int test_result = SUCCESS;
	is_before_func_ty is_before_func = IsBefore;
	int element01 = -1;
	int element0 = 0;
	int element1 = 1;
	int element2 = 2;
	size_t result_size = 0;
	size_t expected_size = 4;

	int expected_is_empty = 0;
	int result_is_empty = 0;

	bst = BSTCreate(is_before_func, NULL);

	BSTInsert(bst, &element1);
	BSTInsert(bst, &element2);
	
	BSTInsert(bst, &element0);
	BSTInsert(bst, &element01);

	result_size = BSTSize(bst);

	result_is_empty = BSTIsEmpty(bst);

	if(result_is_empty != expected_is_empty || expected_size != result_size)
	{
		test_result = FAIL;
	}

	BSTDestroy(bst);

	return test_result;
}


int TestBSTInsertSameElement()
{
	/*		1		*/
	/*	   /  \		*/
	/*	  0	   2	*/

	int test_result = SUCCESS;
	is_before_func_ty is_before_func = IsBefore;
	int element0 = 0;
	int element1 = 1;
	int element2 = 2;
	size_t result_size = 0;
	size_t expected_size = 3;

	int expected_is_empty = 0;
	int result_is_empty = 0;

	bst = BSTCreate(is_before_func, NULL);

	BSTInsert(bst, &element1);
	BSTInsert(bst, &element2);
	
	BSTInsert(bst, &element0);
	BSTInsert(bst, &element0);

	result_size = BSTSize(bst);

	result_is_empty = BSTIsEmpty(bst);

	if(result_is_empty != expected_is_empty || expected_size != result_size)
	{
		test_result = FAIL;
	}

	BSTDestroy(bst);

	return test_result;
}

int TestBSTRemoveNodeWithNoChildren()
{
	/*		1		*/
	/*	   /  \		*/
	/*	  0	   2	*/
	/*	 /			*/
	/*	-1    		*/ /*Deleting -1*/

	int test_result = SUCCESS;
	is_before_func_ty is_before_func = IsBefore;
	int element01 = -1;
	int element0 = 0;
	int element1 = 1;
	int element2 = 2;
	size_t result_size = 0;
	size_t expected_size = 3;

	bst_iter_ty to_delete;
	bst_iter_ty begin_after_del;
	int *result_begin_after_del;

	bst = BSTCreate(is_before_func, NULL);

	BSTInsert(bst, &element1);
	BSTInsert(bst, &element2);
	
	BSTInsert(bst, &element0);
	BSTInsert(bst, &element01);

	to_delete = BSTBegin(bst);

	to_delete = BSTRemove(bst, to_delete);
	begin_after_del = BSTBegin(bst);
	result_begin_after_del = BSTGetData(begin_after_del);

	result_size = BSTSize(bst);

	if(expected_size != result_size || *result_begin_after_del != element0)
	{
		test_result = FAIL;
	}

	BSTDestroy(bst);

	return test_result;
}

int TestBSTRemoveNodeWithOneChild()
{
	/*		10		*/
	/*	   /  \		*/
	/*	  5	   15	*/ /*Deleting 5*/
	/*	   \		*/
	/*	    7		*/

	int test_result = SUCCESS;
	is_before_func_ty is_before_func = IsBefore;
	int element01 = 15;
	int element0 = 7;
	int element1 = 10;
	int element2 = 5;
	size_t result_size = 0;
	size_t expected_size = 3;

	bst_iter_ty to_delete;
	bst_iter_ty begin_after_del;
	int *result_begin_after_del;

	bst = BSTCreate(is_before_func, NULL);

	BSTInsert(bst, &element1);
	BSTInsert(bst, &element2);
	
	BSTInsert(bst, &element0);
	BSTInsert(bst, &element01);

	to_delete = BSTBegin(bst); /*5*/

	to_delete = BSTRemove(bst, to_delete); /*5*/

	begin_after_del = BSTBegin(bst); /*7*/

	result_begin_after_del = BSTGetData(begin_after_del); /*7*/

	result_size = BSTSize(bst);

	if(expected_size != result_size || *result_begin_after_del != element0)
	{
		test_result = FAIL;
	}

	BSTDestroy(bst);

	return test_result;
}

int TestBSTRemoveNodeWithTwoChildren()
{
	/*		10		*/ /*Deleting 10*/ 	/*		11		*/
	/*	   /  \		*/				  	/*	   /  \		*/	
	/*	  5	   11	*/ 		/*-->*/		/*	  5	   15	*/
	/*	   \	\	*/					/*	   \		*/
	/*	    7	15	*/					/*	    7		*/

	int test_result = SUCCESS;
	is_before_func_ty is_before_func = IsBefore;
	int element01 = 15;
	int element0 = 7;
	int element1 = 10;
	int element11 = 11;
	int element2 = 5;
	size_t result_size = 0;
	size_t expected_size = 4;

	bst_iter_ty to_delete;
	bst_iter_ty begin_after_del;
	int *result_begin_after_del;

	bst = BSTCreate(is_before_func, NULL);

	BSTInsert(bst, &element1);
	BSTInsert(bst, &element2);
	
	BSTInsert(bst, &element0);
	BSTInsert(bst, &element11);
	BSTInsert(bst, &element01);

	to_delete = BSTBegin(bst); /*5*/
	to_delete = BSTNext(to_delete); /*7*/
	to_delete = BSTNext(to_delete); /*10*/	

	to_delete = BSTRemove(bst, to_delete); /*10*/

	begin_after_del = BSTBegin(bst); /*5*/

	result_begin_after_del = BSTGetData(begin_after_del); /*5*/

	result_size = BSTSize(bst);

	if(expected_size != result_size || *result_begin_after_del != element2)
	{
		test_result = FAIL;
	}

	BSTDestroy(bst);

	return test_result;
}

int TestBSTForEach()
{
	/*		1		*/				 /*		2	   */
	/*	   /  \		*/	/*Adding 1*/ /*	   / \	   */
	/*	  0	   2	*/ 	  /*-->*/  	 /*	  1	  2	   */
	/*	 /			*/				 /*	 /		   */
	/*	-1    		*/				 /*	0    	   */

	int test_result = SUCCESS;
	is_before_func_ty is_before_func = IsBefore;
	int element01 = -1;
	int element0 = 0;
	int element1 = 1;
	int element2 = 2;

	int addone = 1;
	int status = 0;
	bst_iter_ty begin;
	bst_iter_ty last;

	bst = BSTCreate(is_before_func, NULL);

	BSTInsert(bst, &element1);
	BSTInsert(bst, &element2);
	
	BSTInsert(bst, &element0);
	BSTInsert(bst, &element01);
	begin = BSTBegin(bst);
	last = BSTEnd(bst);
	last = BSTPrev(last);

	printf("before for each\n");

	while(!BSTIsSameIter(begin,last))
	{
		printf("%d\n",*(int*)BSTGetData(begin));
		begin = BSTNext(begin);
	}
	begin = BSTBegin(bst);
	last = BSTEnd(bst);
	last = BSTPrev(last);

	status = BSTForEach(begin, last, AddParam, &addone);
	printf("\nafter for each\n");

	begin = BSTBegin(bst);
	last = BSTEnd(bst);
	last = BSTPrev(last);

	while(!BSTIsSameIter(begin,last))
	{
		printf("%d\n",*(int*)BSTGetData(begin));
		begin = BSTNext(begin);
	}

	if(SUCCESS != status)
	{
		test_result = FAIL;
	}

	BSTDestroy(bst);

	return test_result;
}

int TestBSTFind()
{
	/*		10		*/
	/*	   /  \		*/
	/*	  5	   15	*/ /*Find 7*/
	/*	   \		*/
	/*	    7		*/

	int test_result = SUCCESS;
	is_before_func_ty is_before_func = IsBefore;
	int element01 = 15;
	int element0 = 7;
	int element1 = 10;
	int element2 = 5;
	int element_non_existing = 0;
	int *result_iter = NULL;
	int *result_iter_next = NULL;

	bst_iter_ty iter;
	bst_iter_ty iter_next;
	bst_iter_ty iter_non_existing;

	bst = BSTCreate(is_before_func, NULL);

	BSTInsert(bst, &element1);
	BSTInsert(bst, &element2);
	
	BSTInsert(bst, &element0);
	BSTInsert(bst, &element01);

	iter = BSTFind(bst, &element2);

	iter_next = BSTNext(iter);

	result_iter = BSTGetData(iter);

	result_iter_next = BSTGetData(iter_next);

	if(*result_iter != element2 || *result_iter_next != element0)
	{
		test_result = FAIL;
	}

	iter_non_existing = BSTFind(bst, &element_non_existing);

	if(!BSTIsSameIter(iter_non_existing, BSTEnd(bst)))
	{
		test_result = FAIL;
	}

	BSTDestroy(bst);

	return test_result;
}

int IsBefore(const void *data1, const void *data2, const void *params)
{
	(void)params;
	if(*(int*)data1 < *(int*)data2)
	{
		return 1;
	}
	return 0;
}

int AddParam(void *data, void *func_param)
{
	*(int*)data+=*(int*)func_param;
	return 0;
}