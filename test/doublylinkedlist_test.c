#include <stdio.h> /*printf*/
#include <string.h> /*strchr*/

#include "doublylinkedlist.h"

enum State{FAIL,SUCCESS};

static int Runner();

static int TestCreateList();

static int TestDListPushFront();
static int TestDListPushBack();

static int TestDListPopFront();
static int TestDListPopBack();

static int TestDListIsEmpty();
static int TestDListLength();

static int TestDListGetSet();

static int TestDListInsert();
static int TestDListRemove();

static int TestDListMultiFind();
static int TestDListForEach();
static int TestDListSplice();

int is_match(const void *str, const void *c);
int ActionAddOne(void *data, void *param);
int EqualsAddOne(void *num1, void *num2);

dlist_ty *list = NULL;

int *p1 = NULL;

int main()
{
	int state = SUCCESS;
	state = Runner();
	return state;
}


int Runner()
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

	state = TestDListIsEmpty();

	if(SUCCESS == state)
	{
		printf("Test IsEmpty List Succeed :)\n");
	}
	else
	{
		printf("Test IsEmpty List Failed :(\n");
	}

	state = TestDListLength();

	if(SUCCESS == state)
	{
		printf("Test Length List Succeed :)\n");
	}
	else
	{
		printf("Test Length List Failed :(\n");
	}

	state = TestDListPushFront();

	if(SUCCESS == state)
	{
		printf("Test PushFront List Succeed :)\n");
	}
	else
	{
		printf("Test PushFront List Failed :(\n");
	}

	state = TestDListPushBack();

	if(SUCCESS == state)
	{
		printf("Test PushBack List Succeed :)\n");
	}
	else
	{
		printf("Test PushBack List Failed :(\n");
	}

	state = TestDListPopFront();

	if(SUCCESS == state)
	{
		printf("Test PopFront List Succeed :)\n");
	}
	else
	{
		printf("Test PopFront List Failed :(\n");
	}

	state = TestDListPopBack();

	if(SUCCESS == state)
	{
		printf("Test PopBack List Succeed :)\n");
	}
	else
	{
		printf("Test PopBack List Failed :(\n");
	}

	state = TestDListGetSet();

	if(SUCCESS == state)
	{
		printf("Test GetSet List Succeed :)\n");
	}
	else
	{
		printf("Test GetSet List Failed :(\n");
	}

	state = TestDListInsert();

	if(SUCCESS == state)
	{
		printf("Test Insert List Succeed :)\n");
	}
	else
	{
		printf("Test Insert List Failed :(\n");
	}

	state = TestDListRemove();

	if(SUCCESS == state)
	{
		printf("Test Remove List Succeed :)\n");
	}
	else
	{
		printf("Test Remove List Failed :(\n");
	}

	state = TestDListMultiFind();

	if(SUCCESS == state)
	{
		printf("Test MultiFind List Succeed :)\n");
	}
	else
	{
		printf("Test MultiFind List Failed :(\n");
	}

	state = TestDListForEach();

	if(SUCCESS == state)
	{
		printf("Test ForEach List Succeed :)\n");
	}
	else
	{
		printf("Test ForEach List Failed :(\n");
	}

	state = TestDListSplice();

	if(SUCCESS == state)
	{
		printf("Test Splice List Succeed :)\n");
	}
	else
	{
		printf("Test Splice List Failed :(\n");
	}

	return state;
}

int TestCreateList()
{
	int test_result = SUCCESS;

	list = DListCreate();

	if(NULL == list)
	{
		test_result = FAIL;
	}

	DListDestroy(list);

	return test_result;
}

int TestDListIsEmpty()
{
	int test_result = SUCCESS;
	int is_empty_result = 0;
	int is_empty_expected = 1;

	list = DListCreate();

	is_empty_result = DListIsEmpty(list);

	if(is_empty_expected != is_empty_result)
	{
		test_result = FAIL;
	}

	DListDestroy(list);

	return test_result;
}

int TestDListLength()
{
	int test_result = SUCCESS;
	int length_result = 0;
	int length_expected = 2;
	int element = 1;

	list = DListCreate();

	p1 = &element;

	DListPushFront(list,p1);
	DListPushFront(list,p1);

	length_result = DListLength(list);

	if(length_result != length_expected)
	{
		test_result = FAIL;
	}

	DListDestroy(list);

	return test_result;
}

int TestDListPushFront()
{
	int test_result = SUCCESS;
	int push_result = 0;
	int element = 1;
	int element2 = 2;

	list = DListCreate();

	p1 = &element;
	push_result = DListPushFront(list,p1);
	p1 = &element2;
	push_result = DListPushFront(list,p1);

	if(0 != push_result)
	{
		test_result = FAIL;
	}

	DListDestroy(list);

	return test_result;
}

int TestDListPushBack()
{
	int test_result = SUCCESS;
	int push_result = 0;
	char *strings[] = {"Hello","World!"};
	size_t i = 0;

	list = DListCreate();

	for(i = 0; i < 2; ++i)
	{
		push_result = DListPushBack(list,strings[i]);
		if(0 != push_result)
		{
			test_result = FAIL;
		}
	}

	/*PrintListFromHead(list);
	PrintListFromTail(list);*/

	DListDestroy(list);

	return test_result;
}

int TestDListPopFront()
{
	int test_result = SUCCESS;
	int length_result = 0;
	int length_expected = 2;
	int element = 1;
	int element2 = 2;
	int element3 = 3;

	list = DListCreate();

	p1 = &element;
	DListPushBack(list,p1);
	p1 = &element2;
	DListPushBack(list,p1);
	p1 = &element3;
	DListPushBack(list,p1);

	DListPopFront(list);
	length_result = DListLength(list);

	if(length_result != length_expected)
	{
		test_result = FAIL;
	}

	/*PrintListFromHead(list);
	PrintListFromTail(list);*/

	DListDestroy(list);

	return test_result;
}

int TestDListPopBack()
{
	int test_result = SUCCESS;
	int length_result = 0;
	int length_expected = 0;
	int element = 1;
	int element2 = 2;

	list = DListCreate();

	p1 = &element;
	DListPushBack(list,p1);
	
	p1 = &element2;
	DListPushBack(list,p1);

	DListPopBack(list);
	DListPopBack(list);

	length_result = DListLength(list);

	if(length_result != length_expected)
	{
		test_result = FAIL;
	}

	DListDestroy(list);

	return test_result;
}

int TestDListGetSet()
{
	int test_result = SUCCESS;
	dlist_iter_ty iter;
	int element = 1;
	int element2 = 2;
	int element9 = 999;
	int *result=NULL;

	list = DListCreate();

	p1 = &element;
	DListPushBack(list,p1);
	
	p1 = &element2;
	DListPushBack(list,p1);

	iter = DListBegin(list);
	iter = DListNext(iter);
	p1 = &element9;
	DListSetData(iter,p1);
	result = DListGetData(iter);

	if(*result != element9)
	{
		test_result = FAIL;
	}

	DListDestroy(list);

	return test_result;
}


int TestDListInsert()
{
	int test_result = SUCCESS;
	dlist_iter_ty head_node;
	dlist_iter_ty inserted_node;

	int element1 = 1;
	int element2 = 2;
	int element3 = 0;

	list = DListCreate();
	p1 = &element1;
	DListPushBack(list,p1);
	p1 = &element2;
	DListPushBack(list,p1);

	head_node = DListBegin(list);
	p1 = &element3;
	inserted_node = DListInsert(list,head_node,p1);

	p1 = DListGetData(inserted_node);

	/*printf("%d\n",*p1);
	PrintListFromHead(list);
	PrintListFromTail(list);*/

	if(*p1 != element3)
	{
		test_result = FAIL;
	}

	DListDestroy(list);

	return test_result;
}

int TestDListRemove()
{
	int test_result = SUCCESS;
	dlist_iter_ty head_node;
	int element1 = 1;
	int element2 = 2;
	int element3 = 3;

	size_t length_expected = 2;
	size_t length_result = 0;

	list = DListCreate();
	p1 = &element1;
	DListPushBack(list,p1);
	p1 = &element2;
	DListPushBack(list,p1);
	p1 = &element3;
	DListPushBack(list,p1);

	head_node = DListBegin(list);
	head_node = DListRemove(list,head_node);

	length_result = DListLength(list);

	/*PrintListFromHead(list);*/

	if(length_result != length_expected)
	{
		test_result = FAIL;
	}
	
	DListDestroy(list);

	return test_result;
}

int TestDListMultiFind()
{
	int test_result = SUCCESS;
	dlist_ty *res_list = NULL;
	char *strings[] = {"Hello","World!","aaa","bbb"};
	char c = 'o';
	size_t i = 0;
	size_t length_expected = 2;
	size_t length_result = 0;

	list = DListCreate();

	for(i = 0; i < 4; ++i)
	{
		DListPushBack(list,strings[i]);
	}

	res_list = DListCreate();
	res_list = DListMultiFind(list,is_match,&c,res_list);

	/*PrintListFromHead(res_list);*/

	length_result = DListLength(res_list);

	if(length_result != length_expected)
	{
		test_result = FAIL;
	}

	DListDestroy(list);
	DListDestroy(res_list);

	return test_result;
}

int TestDListForEach()
{
	int test_result = SUCCESS;
	int element1 = 1;
	int element2 = 2;
	int element3 = 1;

	list = DListCreate();
	p1 = &element1;
	DListPushBack(list,p1);
	p1 = &element2;
	DListPushBack(list,p1);

	p1 = &element3;
	test_result = DListForEach(list,DListBegin(list),DListEnd(list),ActionAddOne,p1);

	/*PrintListFromHead(list);*/
	test_result = DListForEach(list,DListBegin(list),DListEnd(list),EqualsAddOne,NULL);
	
	DListDestroy(list);

	return test_result;
}

int TestDListSplice()
{
	int test_result = SUCCESS;
	dlist_ty *list2 = NULL;
	dlist_iter_ty from;
	dlist_iter_ty to;
	dlist_iter_ty where;
	size_t length_result = 0;
	size_t length_expected = 4;

	int element1 = 1;
	int element2 = 2;
	int element3 = 3;
	int element4 = 4;
	int element7 = 7;
	int element8 = 8;

	list = DListCreate();

	p1 = &element1;
	DListPushBack(list,p1);
	p1 = &element2;
	DListPushBack(list,p1);
	p1 = &element3;
	DListPushBack(list,p1);
	p1 = &element4;
	DListPushBack(list,p1);

	from = DListBegin(list);
	from = DListNext(from);
	to = DListEnd(list);
	to = DListPrev(to);

	list2 = DListCreate();
	p1 = &element7;
	DListPushBack(list2,p1);
	p1 = &element8;
	DListPushBack(list2,p1);
	where = DListBegin(list2);

	DListSplice(from, to, where);

	/*PrintListFromHead(list);
	PrintListFromHead(list2);*/

	length_result = DListLength(list2);

	if(length_result != length_expected)
	{
		test_result = FAIL;
	}

	DListDestroy(list);
	DListDestroy(list2);

	return test_result;
}

int is_match(const void *str, const void *c)
{

	return NULL == strchr(str,*(int*)c) ? 0 : 1;
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