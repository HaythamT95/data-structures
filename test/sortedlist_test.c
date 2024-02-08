#include <stdio.h> /*printf*/

#include "sortedlist.h"

enum State{FAIL,SUCCESS};

static int TestRunner();

static int TestCreateList();

static int TestSortedListIsEmpty();
static int TestSortedListLength();

static int TestSortedListPopFront();
static int TestSortedListPopBack();

static int TestSortedListGet();
static int TestSortedListRemove();

static int TestSortedListFind();
static int TestSortedListFindIf();

static int TestSortedListIsEqual();

static int TestSortedListForEach();
static int TestSortedListMerge();


int CompareIntegers(const void *data1, const void *data2);
int ActionAddOne(void *data, void *param);
int EqualsAddOne(void *num1, void *num2);

sorted_list_ty *list = NULL;
sorted_list_ty *list2 = NULL;

int *p1 = NULL;

int main()
{
	int state = SUCCESS;
	state = TestRunner();
	return state;
}

int TestRunner()
{
	int state = SUCCESS;

	state = TestCreateList();

	if(SUCCESS == state)
	{
		printf("Test Create List Succeed :)\n");
	}
	else
	{
		printf("Test Create List Failed :(\n");
	}

	state = TestSortedListIsEmpty();

	if(SUCCESS == state)
	{
		printf("Test IsEmpty List Succeed :)\n");
	}
	else
	{
		printf("Test IsEmpty List Failed :(\n");
	}

	state = TestSortedListLength();

	if(SUCCESS == state)
	{
		printf("Test Length List Succeed :)\n");
	}
	else
	{
		printf("Test Length List Failed :(\n");
	}

	state = TestSortedListPopFront();

	if(SUCCESS == state)
	{
		printf("Test PopFront List Succeed :)\n");
	}
	else
	{
		printf("Test PopFront List Failed :(\n");
	}

	state = TestSortedListPopBack();

	if(SUCCESS == state)
	{
		printf("Test PopBack List Succeed :)\n");
	}
	else
	{
		printf("Test PopBack List Failed :(\n");
	}

	state = TestSortedListGet();

	if(SUCCESS == state)
	{
		printf("Test Get List Succeed :)\n");
	}
	else
	{
		printf("Test Get List Failed :(\n");
	}

	state = TestSortedListRemove();

	if(SUCCESS == state)
	{
		printf("Test Remove List Succeed :)\n");
	}
	else
	{
		printf("Test Remove List Failed :(\n");
	}

	state = TestSortedListFind();

	if(SUCCESS == state)
	{
		printf("Test Find List Succeed :)\n");
	}
	else
	{
		printf("Test Find List Failed :(\n");
	}

	state = TestSortedListFindIf();

	if(SUCCESS == state)
	{
		printf("Test FindIf List Succeed :)\n");
	}
	else
	{
		printf("Test FindIf List Failed :(\n");
	}

	state = TestSortedListIsEqual();

	if(SUCCESS == state)
	{
		printf("Test IsEqual List Succeed :)\n");
	}
	else
	{
		printf("Test IsEqual List Failed :(\n");
	}

	state = TestSortedListForEach();

	if(SUCCESS == state)
	{
		printf("Test ForEach List Succeed :)\n");
	}
	else
	{
		printf("Test ForEach List Failed :(\n");
	}

	state = TestSortedListMerge();

	if(SUCCESS == state)
	{
		printf("Test Merge List Succeed :)\n");
	}
	else
	{
		printf("Test Merge List Failed :(\n");
	}

	return state;
}

int TestCreateList()
{
	int test_result = SUCCESS;

	cmp_func_ty cmp_func = CompareIntegers;

	list = SortedListCreate(cmp_func);

	if(NULL == list)
	{
		test_result = FAIL;
	}

	SortedListDestroy(list);

	return test_result;
}

int TestSortedListIsEmpty()
{
	int test_result = SUCCESS;
	int is_empty_result = 0;
	int is_empty_expected = 1;
	cmp_func_ty cmp_func = CompareIntegers;

	list = SortedListCreate(cmp_func);

	is_empty_result = SortedListIsEmpty(list);

	if(is_empty_expected != is_empty_result)
	{
		test_result = FAIL;
	}

	SortedListDestroy(list);

	return test_result;
}

int TestSortedListLength()
{
	int test_result = SUCCESS;
	int length_result = 0;
	int length_expected = 1;
	int element = 1;
	sorted_list_iter_ty iter;

	cmp_func_ty cmp_func = CompareIntegers;

	list = SortedListCreate(cmp_func);

	p1 = &element;

	iter = SortedListInsert(list,p1);

	length_result = SortedListLength(list);

	if(length_result != length_expected)
	{
		test_result = FAIL;
	}

	SortedListDestroy(list);

	return test_result;
}

int TestSortedListPopBack()
{
	int test_result = SUCCESS;
	int length_result = 0;
	int length_expected = 0;
	int element = 1;
	int element2 = 2;

	sorted_list_iter_ty iter;

	cmp_func_ty cmp_func = CompareIntegers;

	list = SortedListCreate(cmp_func);

	p1 = &element2;
	iter = SortedListInsert(list,p1);

	p1 = &element;
	iter = SortedListInsert(list,p1);

	SortedListPopBack(list);
	SortedListPopBack(list);

	length_result = SortedListLength(list);

	if(length_result != length_expected)
	{
		test_result = FAIL;
	}

	SortedListDestroy(list);

	return test_result;
}


int TestSortedListPopFront()
{
	int test_result = SUCCESS;
	int length_result = 0;
	int length_expected = 2;
	int element = 1;
	int element2 = 0;
	int element3 = 3;
	sorted_list_iter_ty iter;
	cmp_func_ty cmp_func = CompareIntegers;

	list = SortedListCreate(cmp_func);

	p1 = &element;
	iter = SortedListInsert(list,p1);
	p1 = &element3;
	iter = SortedListInsert(list,p1);
	p1 = &element2;
	iter = SortedListInsert(list,p1);

	SortedListPopFront(list);

	length_result = SortedListLength(list);

	if(length_result != length_expected)
	{
		test_result = FAIL;
	}

	SortedListDestroy(list);

	return test_result;
}

int TestSortedListGet()
{
	int test_result = SUCCESS;
	sorted_list_iter_ty iter;
	int element = 1;
	int element2 = 2;
	cmp_func_ty cmp_func = CompareIntegers;

	int *result=NULL;

	list = SortedListCreate(cmp_func);

	p1 = &element2;
	iter = SortedListInsert(list,p1);
	
	p1 = &element;
	iter = SortedListInsert(list,p1);

	iter = SortedListBegin(list);
	iter = SortedListNext(iter);

	result = SortedListGetData(iter);

	if(*result != element2)
	{
		test_result = FAIL;
	}

	SortedListDestroy(list);

	return test_result;
}

int TestSortedListRemove()
{
	int test_result = SUCCESS;
	sorted_list_iter_ty head_node;
	int element1 = 1;
	int element2 = 2;
	int element3 = 3;
	cmp_func_ty cmp_func = CompareIntegers;

	size_t length_expected = 2;
	size_t length_result = 0;

	list = SortedListCreate(cmp_func);
	p1 = &element1;
	head_node = SortedListInsert(list,p1);
	p1 = &element2;
	head_node = SortedListInsert(list,p1);
	p1 = &element3;
	head_node = SortedListInsert(list,p1);

	head_node = SortedListBegin(list);
	head_node = SortedListRemove(list,head_node);

	length_result = SortedListLength(list);

	if(length_result != length_expected)
	{
		test_result = FAIL;
	}
	
	SortedListDestroy(list);

	return test_result;
}

int TestSortedListFind()
{
	int test_result = SUCCESS;
	cmp_func_ty cmp_func = CompareIntegers;
	int element1 = 1;
	int element2 = 2;
	int element3 = 3;
	sorted_list_iter_ty iter;
	sorted_list_iter_ty head;
	sorted_list_iter_ty end;
	int *result = NULL;

	list = SortedListCreate(cmp_func);
	p1 = &element1;
	iter = SortedListInsert(list,p1);
	p1 = &element2;
	iter = SortedListInsert(list,p1);
	p1 = &element3;
	iter = SortedListInsert(list,p1);

	head = SortedListBegin(list);
	end = SortedListEnd(list);

	iter = SortedListFind(list,head,end,&element2);

	result = SortedListGetData(iter);

	if(element2 != *result)
	{
		test_result = FAIL;
	}

	SortedListDestroy(list);

	return test_result;
}

int TestSortedListFindIf()
{
	int test_result = SUCCESS;
	cmp_func_ty cmp_func = CompareIntegers;
	int element1 = 1;
	int element2 = 2;
	int element3 = 3;
	sorted_list_iter_ty iter;
	sorted_list_iter_ty head;
	sorted_list_iter_ty end;
	int *result = NULL;

	list = SortedListCreate(cmp_func);
	p1 = &element1;
	iter = SortedListInsert(list,p1);
	p1 = &element2;
	iter = SortedListInsert(list,p1);
	p1 = &element3;
	iter = SortedListInsert(list,p1);

	head = SortedListBegin(list);
	end = SortedListEnd(list);

	iter = SortedListFindIf(head,end,cmp_func,&element2);

	result = SortedListGetData(iter);

	if(element2 != *result)
	{
		test_result = FAIL;
	}

	SortedListDestroy(list);

	return test_result;
}
int TestSortedListIsEqual()
{
	int test_result = SUCCESS;
	cmp_func_ty cmp_func = CompareIntegers;
	int element1 = 1;
	int element2 = 2;
	int element3 = 3;
	sorted_list_iter_ty first;
	sorted_list_iter_ty second;
	int result = 0;
	int expected = 1;

	list = SortedListCreate(cmp_func);
	p1 = &element1;
	first = SortedListInsert(list,p1);
	p1 = &element2;
	first = SortedListInsert(list,p1);
	p1 = &element3;
	first = SortedListInsert(list,p1);

	first = SortedListBegin(list);
	second = SortedListBegin(list);

	result = SortedListIterIsEqual(first,second);

	if(expected != result)
	{
		test_result = FAIL;
	}

	second = SortedListNext(second);
	result = SortedListIterIsEqual(first,second);

	expected = 0;

	if(expected != result)
	{
		test_result = FAIL;
	}

	SortedListDestroy(list);

	return test_result;
}

int TestSortedListForEach()
{
	int test_result = SUCCESS;
	cmp_func_ty cmp_func = CompareIntegers;
	int element1 = 1;
	int element2 = 2;
	int element3 = 3;
	int element = 1;

	sorted_list_iter_ty iter;
	sorted_list_iter_ty head;
	sorted_list_iter_ty tail;
	int result = 0;
	int expected_result = 0;

	list = SortedListCreate(cmp_func);
	p1 = &element1;
	iter = SortedListInsert(list,p1);
	p1 = &element2;
	iter = SortedListInsert(list,p1);
	p1 = &element3;
	iter = SortedListInsert(list,p1);

	head = SortedListBegin(list);
	tail = SortedListEnd(list);

	result = SortedListForEach(head,tail,ActionAddOne,&element);
	result = SortedListForEach(head,tail,EqualsAddOne,NULL);

	if(expected_result != result)
	{
		test_result = FAIL;
	}

	SortedListDestroy(list);

	return test_result;
}

int TestSortedListMerge()
{
	int test_result = SUCCESS;
	cmp_func_ty cmp_func = CompareIntegers;
	int element1 = 1;
	int element2 = 2;
	int element3 = 3;
	int element11 = 1;
	int element22 = 2;
	int element33 = 3;
	sorted_list_iter_ty iter;
	size_t dest_length_result = 0;
	size_t dest_length_expected = 6;
	size_t src_length_result = 0;
	size_t src_length_expected = 0;


	list = SortedListCreate(cmp_func);
	p1 = &element1;
	iter = SortedListInsert(list,p1);
	p1 = &element2;
	iter = SortedListInsert(list,p1);
	p1 = &element3;
	iter = SortedListInsert(list,p1);

	list2 = SortedListCreate(cmp_func);
	p1 = &element11;
	iter = SortedListInsert(list2,p1);
	p1 = &element22;
	iter = SortedListInsert(list2,p1);
	p1 = &element33;
	iter = SortedListInsert(list2,p1);

	SortedListMerge(list,list2);

	dest_length_result = SortedListLength(list);
	src_length_result = SortedListLength(list2);

	if(dest_length_result != dest_length_expected ||
									src_length_result != src_length_expected)
	{
		test_result = FAIL;
	}


	SortedListDestroy(list);
	SortedListDestroy(list2);

	return test_result;
}

int CompareIntegers(const void *data1, const void *data2)
{
	if(*(int*)data1 > *(int*)data2)
	{
		return 1;
	}
	else if(*(int*)data1 < *(int*)data2)
	{
		return -1;
	}
	return 0;
}

int ActionAddOne(void *data, void *param)
{
	if(NULL == data || NULL == param)
	{
		return 1;
	}
	*(int*)data+=*(int*)param;
	return 0;
}

int EqualsAddOne(void *num1, void *num2)
{
	int array[2]={2,3};
	static size_t i = 0;
	(void)num2;
	return array[i++] == *(int*)num1?0:1;
}