#include <stdio.h> /*printf*/

#include "singlylinkedlist.h"

enum State{FAIL,SUCCESS};

static int Runner();

static int TestCreateList();

static int TestSListPushFront();
static int TestSListPushBack();

static int TestSListPopFront();
static int TestSListPopBack();

static int TestSListIsEmpty();
static int TestSListLength();

static int TestSListGetValue();
static int TestSListSetValue();

static int TestSListInsert();
static int TestSListInsertBefore();

static int TestSListRemove();
static int TestSListRemoveAfter();

static int TestSListForEach();

static int TestSListAppend();

int Equals(const void *num1, const void *num2);
int ActionAddOne(void *data, void *param);
int EqualsAddOne(void *data, void *param);

slist_ty *list = NULL;
slist_ty *list2 = NULL;

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
	
	state = TestSListIsEmpty();

	if(SUCCESS == state)
	{
		printf("Test IsEmpty List Succeed :)\n");
	}
	else
	{
		printf("Test IsEmpty List Failed :(\n");
	}

	state = TestSListLength();

	if(SUCCESS == state)
	{
		printf("Test Length List Succeed :)\n");
	}
	else
	{
		printf("Test Length List Failed :(\n");
	}

	state = TestSListPushFront();

	if(SUCCESS == state)
	{
		printf("Test PushFront List Succeed :)\n");
	}
	else
	{
		printf("Test PushFront List Failed :(\n");
	}

	state = TestSListPopFront();

	if(SUCCESS == state)
	{
		printf("Test PopFront List Succeed :)\n");
	}
	else
	{
		printf("Test PopFront List Failed :(\n");
	}

	state = TestSListPushBack();

	if(SUCCESS == state)
	{
		printf("Test PushBack List Succeed :)\n");
	}
	else
	{
		printf("Test PushBack List Failed :(\n");
	}

	state = TestSListPopBack();

	if(SUCCESS == state)
	{
		printf("Test PopBack List Succeed :)\n");
	}
	else
	{
		printf("Test PopBack List Failed :(\n");
	}

	state = TestSListGetValue();

	if(SUCCESS == state)
	{
		printf("Test GetData List Succeed :)\n");
	}
	else
	{
		printf("Test GetData List Failed :(\n");
	}

	state = TestSListSetValue();

	if(SUCCESS == state)
	{
		printf("Test GetData List Succeed :)\n");
	}
	else
	{
		printf("Test GetData List Failed :(\n");
	}

	state = TestSListInsert();

	if(SUCCESS == state)
	{
		printf("Test Insert List Succeed :)\n");
	}
	else
	{
		printf("Test Insert List Failed :(\n");
	}

	state = TestSListInsertBefore();

	if(SUCCESS == state)
	{
		printf("Test InsertBefore List Succeed :)\n");
	}
	else
	{
		printf("Test InsertBefore List Failed :(\n");
	}

	state = TestSListRemove();

	if(SUCCESS == state)
	{
		printf("Test Remove List Succeed :)\n");
	}
	else
	{
		printf("Test Remove List Failed :(\n");
	}

	state = TestSListRemoveAfter();

	if(SUCCESS == state)
	{
		printf("Test RemoveAfter List Succeed :)\n");
	}
	else
	{
		printf("Test RemoveAfter List Failed :(\n");
	}

	state = TestSListForEach();

	if(SUCCESS == state)
	{
		printf("Test ForEach List Succeed :)\n");
	}
	else
	{
		printf("Test ForEach List Failed :(\n");
	}

	state = TestSListAppend();

	if(SUCCESS == state)
	{
		printf("Test Append List Succeed :)\n");
	}
	else
	{
		printf("Test Append List Failed :(\n");
	}

	return state;
}

int TestCreateList()
{
	int test_result = SUCCESS;

	list = SListCreate();

	if(NULL == list)
	{
		test_result = FAIL;
	}

	SListDestroy(list);

	return test_result;
}

int TestSListPushFront()
{
	int test_result = SUCCESS;
	int push_result = 0;
	int element = 1;

	list = SListCreate();

	p1 = &element;

	push_result = SListPushFront(list,p1);
	push_result = SListPushFront(list,p1);

	if(0 == push_result)
	{
		test_result = FAIL;
	}

	SListDestroy(list);

	return test_result;
}

int TestSListPushBack()
{
	int test_result = SUCCESS;
	int push_result = 0;
	char *strings[] = {"Hello","World!"};
	size_t i = 0;

	list = SListCreate();

	for(i = 0; i < 2; ++i)
	{
		push_result = SListPushBack(list,strings[i]);
		if(0 == push_result)
		{
			test_result = FAIL;
		}
	}
	
	SListDestroy(list);

	return test_result;
}

int TestSListPopFront()
{
	int test_result = SUCCESS;
	int push_result = 0;
	int pop_result = 0;
	int length_result = 0;
	int length_expected = 0;
	int element = 1;

	list = SListCreate();

	p1 = &element;
	push_result = SListPushFront(list,p1);

	pop_result = SListPopFront(list);
	length_result = SListLength(list);

	if(length_result != length_expected)
	{
		test_result = FAIL;
	}

	(void)push_result;
	(void)pop_result;

	SListDestroy(list);

	return test_result;
}

int TestSListPopBack()
{
	int test_result = SUCCESS;
	int push_result = 0;
	int pop_result = 0;
	int length_result = 0;
	int length_expected = 0;
	int element = 1;
	int element2 = 2;

	list = SListCreate();

	p1 = &element;
	push_result = SListPushBack(list,p1);
	
	p1 = &element2;
	push_result = SListPushBack(list,p1);

	pop_result = SListPopBack(list);
	pop_result = SListPopBack(list);

	length_result = SListLength(list);

	if(length_result != length_expected)
	{
		test_result = FAIL;
	}

	(void)push_result;
	(void)pop_result;

	SListDestroy(list);

	return test_result;
}

int TestSListIsEmpty()
{
	int test_result = SUCCESS;
	int is_empty_result = 0;
	int is_empty_expected = 1;

	list = SListCreate();

	is_empty_result = SListIsEmpty(list);

	if(is_empty_expected != is_empty_result)
	{
		test_result = FAIL;
	}

	SListDestroy(list);

	return test_result;
}

int TestSListLength()
{
	int test_result = SUCCESS;
	int length_result = 0;
	int length_expected = 2;
	int element = 1;
	int push_result = 0;

	list = SListCreate();

	p1 = &element;

	push_result = SListPushFront(list,p1);
	push_result = SListPushFront(list,p1);

	length_result = SListLength(list);

	if(length_result != length_expected)
	{
		test_result = FAIL;
	}

	(void)push_result;

	SListDestroy(list);

	return test_result;
}

int TestSListForEach()
{
	int test_result = SUCCESS;
	int push_result = 0;
	int element1 = 1;
	int element2 = 2;
	int element3 = 1;

	list = SListCreate();
	p1 = &element1;
	push_result = SListPushBack(list,p1);
	p1 = &element2;
	push_result = SListPushBack(list,p1);

	p1 = &element3;
	test_result = SListForEach(list,SListBegin(list),SListEnd(list),ActionAddOne,p1);

	test_result = SListForEach(list,SListBegin(list),SListEnd(list),EqualsAddOne,NULL);
	
	(void)push_result;
	SListDestroy(list);

	return test_result;
}

int TestSListRemoveAfter()
{
	int test_result = SUCCESS;
	int push_result = 0;
	slist_node_ty *node = NULL;
	int element1 = 1;
	int element2 = 2;
	size_t length_expected = 1;
	size_t length_result = 0;

	list = SListCreate();
	p1 = &element1;
	push_result = SListPushBack(list,p1);
	p1 = &element2;
	push_result = SListPushBack(list,p1);

	node = SListFind(list,Equals,&element1);

	list = SListRemoveAfter(list,node);

	length_result = SListLength(list);

	if(length_result != length_expected)
	{
		test_result = FAIL;
	}

	(void)push_result;
	SListDestroy(list);

	return test_result;
}

int TestSListRemove()
{
	int test_result = SUCCESS;
	int push_result = 0;
	slist_node_ty *node = NULL;
	int element1 = 1;
	int element2 = 2;
	size_t length_expected = 1;
	size_t length_result = 0;

	list = SListCreate();
	p1 = &element1;
	push_result = SListPushBack(list,p1);
	p1 = &element2;
	push_result = SListPushBack(list,p1);

	node = SListFind(list,Equals,&element1);

	list = SListRemove(list,node);

	length_result = SListLength(list);

	if(length_result != length_expected)
	{
		test_result = FAIL;
	}
	
	(void)push_result;
	SListDestroy(list);

	return test_result;
}

int TestSListInsertBefore()
{
	int test_result = SUCCESS;
	int push_result = 0;
	slist_node_ty *node = NULL;
	slist_node_ty *inserted_node = NULL;

	int element1 = 1;
	int element2 = 2;
	int element3 = 0;

	list = SListCreate();
	p1 = &element1;
	push_result = SListPushBack(list,p1);
	p1 = &element2;
	push_result = SListPushBack(list,p1);

	node = SListFind(list,Equals,&element1);

	inserted_node = SListInsertBefore(list,node,&element3);

	p1 = SListGetData(inserted_node);

	if(*p1 != element3)
	{
		test_result = FAIL;
	}

	(void)push_result;
	SListDestroy(list);

	return test_result;
}

int TestSListInsert()
{
	int test_result = SUCCESS;
	int push_result = 0;
	slist_node_ty *node = NULL;
	slist_node_ty *inserted_node = NULL;

	int element1 = 1;
	int element2 = 2;
	int element3 = 3;

	list = SListCreate();
	p1 = &element1;
	push_result = SListPushBack(list,p1);
	p1 = &element2;
	push_result = SListPushBack(list,p1);

	node = SListFind(list,Equals,&element2);

	inserted_node = SListInsert(list,node,&element3);

	p1 = SListGetData(inserted_node);

	if(*p1 != element3)
	{
		test_result = FAIL;
	}
	
	(void)push_result;
	SListDestroy(list);

	return test_result;
}

int TestSListSetValue()
{
	int test_result = SUCCESS;
	int push_result = 0;
	slist_node_ty *node = NULL;
	int element1 = 1;
	int element2 = 2;
	int element3 = 3;
	int element4 = 4;

	list = SListCreate();
	p1 = &element1;
	push_result = SListPushBack(list,p1);
	p1 = &element2;
	push_result = SListPushBack(list,p1);
	p1 = &element3;
	push_result = SListPushBack(list,p1);
	p1 = &element4;
	push_result = SListPushBack(list,p1);

	node = SListFind(list,Equals,&element4);

	element4 = -999;
	p1 = &element4;
	SListSetData(node,p1);
	p1 = SListGetData(node);

	if(*p1 != element4)
	{
		test_result = FAIL;
	}
	 
	(void)push_result;
	SListDestroy(list);

	return test_result;
}

int TestSListGetValue()
{
	int test_result = SUCCESS;
	int push_result = 0;
	slist_node_ty *node = NULL;
	int element1 = 1;
	int element2 = 2;
	int element3 = 3;
	int element4 = 4;

	list = SListCreate();
	p1 = &element1;
	push_result = SListPushBack(list,p1);
	p1 = &element2;
	push_result = SListPushBack(list,p1);
	p1 = &element3;
	push_result = SListPushBack(list,p1);
	p1 = &element4;
	push_result = SListPushBack(list,p1);

	node = SListFind(list,Equals,&element4);

	p1 = SListGetData(node);

	if(*p1 != element4)
	{
		test_result = FAIL;
	}
	 
	(void)push_result;
	SListDestroy(list);

	return test_result;
}

int TestSListAppend()
{
	int test_result = SUCCESS;

	int element1 = 1;
	int element2 = 2;
	int element3 = 3;
	int element4 = 4;

	list = SListCreate();
	p1 = &element1;
	SListPushBack(list,p1);
	p1 = &element2;
	SListPushBack(list,p1);

	list2 = SListCreate();
	p1 = &element3;
	SListPushBack(list2,p1);
	p1 = &element4;
	SListPushBack(list2,p1);

	SListAppend(list,list2);

	/*PrintList(list);*/

	SListDestroy(list);
	SListDestroy(list2);

	return test_result;

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

int Equals(const void *num1, const void *num2)
{
	return *(int*)num1 == *(int*)num2?0:1;
}

int EqualsAddOne( void *num1, void *num2)
{
	int array[2]={2,3};
	static size_t i = 0;
	(void)num2;
	return array[i++] == *(int*)num1?0:1;
}

