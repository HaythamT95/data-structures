#include <stdio.h> /*printf*/

#include "avl.h"

#define FAIL 1

static int TestRunner();

static int TestCreateAVL();

static int TestAVLIsEmpty();

static int TestAVLInsert();

static int TestAVLForEachPreOrder();
static int TestAVLForEachPostOrder();
static int TestAVLForEachInOrder();

static int TestAVLFind();
static int TestAVLHeight();

static int TestAVLRemoveNodeWithNoChildren();
static int TestAVLRemoveNodeWithOneChildren();
static int TestAVLRemoveNodeWithTwoChildren();

static int TestAVLInsertBalancing();


int IsBefore(const void *data1, const void *data2, const void *params);
int PrintAVL(void *data_, void *func_param_);

avl_ty *avl = NULL;

int main()
{
	int state = SUCCESS;

	state = TestRunner();

	return state;
}

int TestRunner()
{
	int state = SUCCESS;

	state = TestCreateAVL();

	if(SUCCESS == state)
	{
		printf("Test Create AVL Succeed :)\n");
	}
	else
	{
		printf("Test Create AVL Failed :(\n");
	}

	state = TestAVLIsEmpty();

	if(SUCCESS == state)
	{
		printf("Test IsEmpty AVL Succeed :)\n");
	}
	else
	{
		printf("Test IsEmpty AVL Failed :(\n");
	}

	state = TestAVLInsert();

	if(SUCCESS == state)
	{
		printf("Test Insert AVL Succeed :)\n");
	}
	else
	{
		printf("Test Insert AVL Failed :(\n");
	}

	state = TestAVLForEachPostOrder();

	if(SUCCESS == state)
	{
		printf("Test ForEachPostOrder Succeed :)\n");
	}
	else
	{
		printf("Test ForEachPostOrder Failed :(\n");
	}

	state = TestAVLForEachPreOrder();

	if(SUCCESS == state)
	{
		printf("Test ForEachPreOrder Succeed :)\n");
	}
	else
	{
		printf("Test ForEachPreOrder Failed :(\n");
	}

	state = TestAVLForEachInOrder();

	if(SUCCESS == state)
	{
		printf("Test ForEachInOrder Succeed :)\n");
	}
	else
	{
		printf("Test ForEachInOrder Failed :(\n");
	}

	state = TestAVLFind();

	if(SUCCESS == state)
	{
		printf("Test Find Succeed :)\n");
	}
	else
	{
		printf("Test Find Failed :(\n");
	}

	state = TestAVLHeight();

	if(SUCCESS == state)
	{
		printf("Test Height Succeed :)\n");
	}
	else
	{
		printf("Test Height Failed :(\n");
	}

	state = TestAVLRemoveNodeWithNoChildren();

	if(SUCCESS == state)
	{
		printf("Test RemoveNodeWithNoChildren Succeed :)\n");
	}
	else
	{
		printf("Test RemoveNodeWithNoChildren Failed :(\n");
	}

	state = TestAVLRemoveNodeWithOneChildren();

	if(SUCCESS == state)
	{
		printf("Test RemoveNodeWithOneChildren Succeed :)\n");
	}
	else
	{
		printf("Test RemoveNodeWithOneChildren Failed :(\n");
	}

	state = TestAVLRemoveNodeWithTwoChildren();

	if(SUCCESS == state)
	{
		printf("Test RemoveNodeWithTwoChildren Succeed :)\n");
	}
	else
	{
		printf("Test RemoveNodeWithTwoChildren Failed :(\n");
	}

	state = TestAVLInsertBalancing();

	if(SUCCESS == state)
	{
		printf("Test InsertBalancing Succeed :)\n");
	}
	else
	{
		printf("Test InsertBalancing Failed :(\n");
	}

	return state;
}

int TestCreateAVL()
{
	int test_result = SUCCESS;

	is_before_func_ty is_before_func = IsBefore;

	avl = AVLCreate(is_before_func, NULL);

	if(NULL == avl)
	{
		test_result = FAIL;
	}

	AVLDestroy(avl);

	return test_result;
}

int TestAVLIsEmpty()
{
	int test_result = SUCCESS;
	int expected_is_empty = 1;
	int result_is_empty = 0;

	is_before_func_ty is_before_func = IsBefore;

	avl = AVLCreate(is_before_func, NULL);

	result_is_empty = AVLIsEmpty(avl);

	if(result_is_empty != expected_is_empty)
	{
		test_result = FAIL;
	}

	AVLDestroy(avl);

	return test_result;
}

int TestAVLInsert()
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

	avl = AVLCreate(is_before_func, NULL);

	AVLInsert(avl, &element1);
	AVLInsert(avl, &element2);
	
	AVLInsert(avl, &element0);
	AVLInsert(avl, &element01);

	result_size = AVLSize(avl);

	result_is_empty = AVLIsEmpty(avl);

	if(result_is_empty != expected_is_empty  || expected_size != result_size)
	{
		test_result = FAIL;
	}

	AVLDestroy(avl);

	return test_result;
}

int TestAVLForEachPreOrder()
{
	/*		1		*/
	/*	   /  \		*/
	/*	  0	   2	*/
	/*	 /			*/
	/*	-1    		*/

	int test_result = SUCCESS;
	is_before_func_ty is_before_func = IsBefore;
	avl_op_func_ty op_func = PrintAVL;
	int element01 = -1;
	int element0 = 0;
	int element1 = 1;
	int element2 = 2;
	traversal_ty t = PRE_ORDER;
	size_t result_size = 0;
	size_t expected_size = 4;

	avl = AVLCreate(is_before_func, NULL);

	AVLInsert(avl, &element1);
	AVLInsert(avl, &element2);
	
	AVLInsert(avl, &element0);
	AVLInsert(avl, &element01);

	AVLForEach(avl, t, op_func, NULL);

	result_size = AVLSize(avl);

	if(expected_size != result_size)
	{
		test_result = FAIL;
	}

	AVLDestroy(avl);

	return test_result;
}

int TestAVLForEachPostOrder()
{
	/*		1		*/
	/*	   /  \		*/
	/*	  0	   2	*/
	/*	 /			*/
	/*	-1    		*/

	int test_result = SUCCESS;
	is_before_func_ty is_before_func = IsBefore;
	avl_op_func_ty op_func = PrintAVL;
	int element01 = -1;
	int element0 = 0;
	int element1 = 1;
	int element2 = 2;
	traversal_ty t = POST_ORDER;
	size_t result_size = 0;
	size_t expected_size = 4;

	avl = AVLCreate(is_before_func, NULL);

	AVLInsert(avl, &element1);
	AVLInsert(avl, &element2);
	
	AVLInsert(avl, &element0);
	AVLInsert(avl, &element01);

	AVLForEach(avl, t, op_func, NULL);

	result_size = AVLSize(avl);

	if(expected_size != result_size)
	{
		test_result = FAIL;
	}

	AVLDestroy(avl);

	return test_result;
}

int TestAVLForEachInOrder()
{
	/*		1		*/
	/*	   /  \		*/
	/*	  0	   2	*/
	/*	 /			*/
	/*	-1    		*/

	int test_result = SUCCESS;
	is_before_func_ty is_before_func = IsBefore;
	avl_op_func_ty op_func = PrintAVL;
	int element01 = -1;
	int element0 = 0;
	int element1 = 1;
	int element2 = 2;
	traversal_ty t = IN_ORDER;
	size_t result_size = 0;
	size_t expected_size = 4;

	avl = AVLCreate(is_before_func, NULL);

	AVLInsert(avl, &element1);
	AVLInsert(avl, &element2);
	
	AVLInsert(avl, &element0);
	AVLInsert(avl, &element01);

	AVLForEach(avl, t, op_func, NULL);

	result_size = AVLSize(avl);

	if(expected_size != result_size)
	{
		test_result = FAIL;
	}

	AVLDestroy(avl);

	return test_result;
}

int TestAVLFind()
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
	int found_elem = 0;

	int *not_found = NULL;

	avl = AVLCreate(is_before_func, NULL);

	AVLInsert(avl, &element1);
	AVLInsert(avl, &element2);
	
	AVLInsert(avl, &element0);
	AVLInsert(avl, &element01);

	found_elem = *(int*)AVLFind(avl, &element2);

	if(found_elem != element2)
	{
		test_result = FAIL;
	}

	not_found = AVLFind(avl, &element_non_existing);

	if(not_found != NULL)
	{
		test_result = FAIL;
	}

	AVLDestroy(avl);

	return test_result;
}

int TestAVLHeight()
{
	int test_result = SUCCESS;
	is_before_func_ty is_before_func = IsBefore;

	int element15 = 15;
	int element10 = 10;
	int element11 = 11;
	int element20 = 20;
	int element17 = 17;
	int element16 = 16;
	int element18 = 18;
	int element35 = 35;

	size_t result_height = 0;
	size_t expected_height = 4;

	avl = AVLCreate(is_before_func, NULL);

	AVLInsert(avl, &element15);
	AVLInsert(avl, &element10);
	
	AVLInsert(avl, &element11);
	AVLInsert(avl, &element20);
	AVLInsert(avl, &element17);
	AVLInsert(avl, &element16);
	AVLInsert(avl, &element18);
	AVLInsert(avl, &element35);

	result_height = AVLHeight(avl);

	if(result_height != expected_height)
	{
		test_result = FAIL;
	}

	AVLDestroy(avl);

	return test_result;
}

int TestAVLRemoveNodeWithNoChildren()
{
	/*	     15
		    /  \
		   11   20
		  /     / \
		 10    17  35
		       / \
		      16 18		*/ /*Deleting 35*/

	int test_result = SUCCESS;
	is_before_func_ty is_before_func = IsBefore;

	int element15 = 15;
	int element10 = 10;
	int element11 = 11;
	int element20 = 20;
	int element17 = 17;
	int element16 = 16;
	int element18 = 18;
	int element35 = 35;

	size_t result_size = 0;
	size_t expected_size = 7;
	int removed_elem = 0;

	avl = AVLCreate(is_before_func, NULL);

	AVLInsert(avl, &element15);
	AVLInsert(avl, &element10);
	
	AVLInsert(avl, &element11);
	AVLInsert(avl, &element20);
	AVLInsert(avl, &element17);
	AVLInsert(avl, &element16);
	AVLInsert(avl, &element18);
	AVLInsert(avl, &element35);

	removed_elem = *(int*)AVLRemove(avl, &element35);

	result_size = AVLSize(avl);

/*	AVLForEach(avl, IN_ORDER, PrintAVL, NULL);
*/
	if(expected_size != result_size || removed_elem != element35)
	{
		test_result = FAIL;
	}

	AVLDestroy(avl);

	return test_result;
}

int TestAVLRemoveNodeWithOneChildren()
{
	/*	     15
		    /  \
		   11   20
		  /     / \
		 10    17  35
		       / \
		      16 18		*//*Deleting 11*/

	int test_result = SUCCESS;
	is_before_func_ty is_before_func = IsBefore;

	int element15 = 15;
	int element10 = 10;
	int element11 = 11;
	int element20 = 20;
	int element17 = 17;
	int element16 = 16;
	int element18 = 18;
	int element35 = 35;

	size_t result_size = 0;
	size_t expected_size = 7;
	int removed_elem = 0;

	avl = AVLCreate(is_before_func, NULL);

	AVLInsert(avl, &element15);
	AVLInsert(avl, &element10);
	
	AVLInsert(avl, &element11);
	AVLInsert(avl, &element20);
	AVLInsert(avl, &element17);
	AVLInsert(avl, &element16);
	AVLInsert(avl, &element18);
	AVLInsert(avl, &element35);

	removed_elem = *(int*)AVLRemove(avl, &element11);

	result_size = AVLSize(avl);
	printf("%d\n",result_size);

/*	AVLForEach(avl, IN_ORDER, PrintAVL, NULL);
*/
	if(expected_size != result_size || removed_elem != element11)
	{
		test_result = FAIL;
	}

	AVLDestroy(avl);

	return test_result;
}

int TestAVLRemoveNodeWithTwoChildren()
{
	/*	     15
		    /  \
		   11   20
		  /     / \
		 10    17  35
		       / \
		      16 18		*/ /*Deleting 15*/

	int test_result = SUCCESS;
	is_before_func_ty is_before_func = IsBefore;

	int element15 = 15;
	int element10 = 10;
	int element11 = 11;
	int element20 = 20;
	int element17 = 17;
	int element16 = 16;
	int element18 = 18;
	int element35 = 35;

	size_t result_size = 0;
	size_t expected_size = 7;
	int removed_elem = 0;

	avl = AVLCreate(is_before_func, NULL);

	AVLInsert(avl, &element15);
	AVLInsert(avl, &element10);
	
	AVLInsert(avl, &element11);
	AVLInsert(avl, &element17);
	AVLInsert(avl, &element20);
	AVLInsert(avl, &element16);
	AVLInsert(avl, &element18);
	AVLInsert(avl, &element35);

	removed_elem = *(int*)AVLRemove(avl, &element15);
/*	printf("%d\n",removed_elem);
*/	result_size = AVLSize(avl);

	AVLForEach(avl, IN_ORDER, PrintAVL, NULL);

	if(expected_size != result_size || removed_elem != element15)
	{
		test_result = FAIL;
	}

	AVLDestroy(avl);

	return test_result;
}

int TestAVLInsertBalancing()
{
	int test_result = SUCCESS;
	is_before_func_ty is_before_func = IsBefore;

	int element4 = 4;
	int element2 = 2;
	int element3 = 3;

	avl = AVLCreate(is_before_func, NULL);

	AVLInsert(avl, &element4);
	AVLInsert(avl, &element2);
	AVLInsert(avl, &element3);

	AVLDestroy(avl);

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

int PrintAVL(void *data_, void *func_param_)
{
	(void)func_param_;
	printf("%d\n",*(int*)data_);
	return 0;
}