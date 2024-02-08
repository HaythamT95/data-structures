/*
Name: Haytham
Pseudocode Reviewer: Jonathan
Reviewer: Jonathan
*/
#include <stdio.h> /*fprintf*/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/

#include "bst.h"

#define NUMBER_OF_CHILDREN 2

typedef struct bst_metadata
{
	struct bst_metadata* children[NUMBER_OF_CHILDREN];
	struct bst_metadata* up;
	void *data;
}node_ty;

struct bst
{
	node_ty dummy;
	is_before_func_ty is_before;
	const void* is_before_params;
};

enum DIRECTION
{
	LEFT = 0,
	RIGHT = 1
};

static node_ty* DownUntil(node_ty *node, int left_or_right);
static node_ty* UpUntil(node_ty *node, int left_or_right);
static node_ty* PrevNext(node_ty *node, int is_next);
static node_ty** FindIMP(bst_ty* bst_, const void* data_, node_ty** parent_);
static bst_iter_ty ToIter(node_ty* node);
static int ValidIter(bst_iter_ty iter);
static void ConnectNodes(node_ty *parent_, node_ty *child_, int side);
static int WhichSide(node_ty *node);
static void Disconnect(node_ty *node);
static void SimpleRemove(node_ty *node);
static void AttachParentToChild(node_ty *parent_, node_ty *child_, node_ty **where_);

bst_ty *BSTCreate(is_before_func_ty is_before_, const void *params)
{
	/*assert*/
	bst_ty *bst = NULL;

	assert(NULL != is_before_);

	/*Malloc bst*/
		/*If malloc failed return NULL*/
	bst = (bst_ty*)malloc(sizeof(bst_ty));

	if(NULL == bst)
	{
		fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
        return NULL;
	}

	/*Initialize dummy*/
	bst->dummy.children[LEFT] = NULL;
	bst->dummy.children[RIGHT] = NULL;
	bst->dummy.up = NULL;
	bst->dummy.data = NULL;

	bst->is_before = is_before_;
	bst->is_before_params = params;

	/*return pointer to BST*/
	return bst;
}

void BSTDestroy(bst_ty *bst_)
{
	bst_iter_ty runner;
	node_ty *curr = NULL;
	bst_iter_ty end;
	bst_iter_ty prev;

	/*check if not NULL*/
	if(NULL != bst_)
	{
		/*curr = BSTBegin()*/
		runner = BSTBegin(bst_);
		/*end = dummy*/
		end = BSTEnd(bst_);

		if(!BSTIsSameIter(runner, end))
		{
			prev = BSTPrev(end);
		}

		/*For each node from curr to end*/
			/*next = Next(curr)*/
			/*free(curr)*/
			/*curr = next*/
		while(!BSTIsSameIter(runner, end))
		{
			curr = runner.where;
			runner = BSTNext(runner);
			free(curr);
			curr = NULL;
			
			if(BSTIsSameIter(runner,prev))
			{
				curr = runner.where;
				free(curr);
				curr = NULL;

				break;
			}
		}

		/*Delete BST*/
		free(bst_);
		bst_ = NULL;
	}
}

size_t BSTSize(const bst_ty *bst_)
{
	bst_iter_ty runner;
	bst_iter_ty end;
	size_t size = 0;
	/*assert*/
	assert(NULL != bst_);

	/*begin = BSTBegin()*/
	runner = BSTBegin((bst_ty *)bst_);

	/*end = dummy*/
	end = BSTEnd((bst_ty *)bst_);

	/*For each node from begin to end*/
	while(!BSTIsSameIter(runner, end))
	{
		runner = BSTNext(runner);

		/*count = count + 1*/
		++size;
	}

	/*Return count*/
	return size;
}

int BSTIsEmpty(const bst_ty *bst_)
{
	/*assert*/
	assert(NULL != bst_);

	/*Return Dummy-> children IS NULL*/
	return NULL == bst_->dummy.children[LEFT];
}

status_bst_ty BSTInsert(bst_ty *bst_, void *data_)
{
	node_ty *new_node = NULL;
	node_ty *parent = NULL;
	node_ty **where = NULL;

	/*assert*/
	assert(NULL != bst_);

	/*bst_iter_ty iter = FindIMP(bst_,data_,parent)*/
	where = FindIMP(bst_, data_, &parent);


	if(NULL == *where && parent->data != data_)
	{
		/*Allocate node*/
		new_node = (node_ty*)malloc(sizeof(node_ty));

		/*handle failure*/
		if(NULL == new_node)
		{
			fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
	        return MALLOC_FAIL;
		}

		new_node->data = data_;

		AttachParentToChild(parent, new_node, where);
	}
	
	return SUCCESS;
}

bst_iter_ty BSTRemove(bst_ty *bst_, bst_iter_ty to_delete_)
{
	bst_iter_ty ret;

	/*assert*/
	assert(NULL != bst_);
	assert(ValidIter(to_delete_));

	/*ret = next(to_rem)*/
	ret = BSTNext(to_delete_);

	/*if two children*/
	if(NULL != to_delete_.where->children[RIGHT] && NULL != to_delete_.where->children[LEFT])
	{
		/*swap data to_rem ret*/
		to_delete_.where->data = ret.where->data;

		if(ret.where->children[RIGHT] == NULL)
		{
			Disconnect(ret.where);
		}
		else
		{
			ConnectNodes(to_delete_.where, ret.where->children[RIGHT], RIGHT);
			ret.where->up = NULL;
		}

		free(ret.where);
		ret.where = NULL;

		return to_delete_;
	}
	else
	{
		/*SimpleRemove*/
			/*free(to_delete_)*/
		SimpleRemove(to_delete_.where);
		free(to_delete_.where);
		to_delete_.where = NULL;
	}

	/*Return Next(to_delete_)*/
	return ret;
}

bst_iter_ty BSTBegin(bst_ty *bst_)
{
	/*assert*/
	assert(NULL != bst_);

	/*return ToIterIMP(DownUntilIMP(&dummy, left = 0))*/
	return ToIter(DownUntil(&bst_->dummy,LEFT));
}

bst_iter_ty BSTEnd(bst_ty *bst_)
{
	/*return ToIterIMP(DownUntilIMP(bst_, right = 1))*/
	return ToIter(&bst_->dummy);
}

bst_iter_ty BSTPrev(bst_iter_ty iter_)
{
/*	assert(ValidIter(iter_));
*/	
	/*PrevNextIMP(iter, is_next = 0 )*/
	return ToIter(PrevNext(iter_.where,LEFT));
}

bst_iter_ty BSTNext(bst_iter_ty iter_)
{
	assert(ValidIter(iter_));
	/*PrevNextIMP(iter, is_next = 1 )*/
	return ToIter(PrevNext(iter_.where,RIGHT));
}

int BSTIsSameIter(bst_iter_ty first_, bst_iter_ty second_)
{
	/*assert*/
	assert(ValidIter(first_));
	assert(ValidIter(second_));

	/*Return first_->data == second_->data*/
	return BSTGetData(first_) == BSTGetData(second_);
}

void *BSTGetData(bst_iter_ty iter_)
{
	assert(ValidIter(iter_));

	/*Return iter_.where->data*/
	return iter_.where->data;
}

bst_iter_ty BSTFind(bst_ty *bst_, const void *element_)
{
	node_ty **node = NULL;
	node_ty *parent = NULL;
	/*assert*/
	assert(NULL != bst_);

	/*bst_iter_ty iter->where = FindIMP(bst_,element_,parent)*/
	node = FindIMP(bst_, element_, &parent);

	/*if not found*/
		/*return end*/
	if(NULL == *node)
	{
		return BSTEnd(bst_);
	}

	/*return iter*/
	return ToIter(*node);
}

status_bst_ty BSTForEach(bst_iter_ty from_, bst_iter_ty to_,
								bst_op_func_ty op_func_, void *func_param_)
{
	int stat = 0;
	assert(ValidIter(from_));
	assert(ValidIter(to_));
	assert(NULL != op_func_);

	/*For each node from from_ to to_*/
		/*stat = Call op_func_(func_param_)*/
			/*If stat != 0*/
				/*return stat*/
	while(!BSTIsSameIter(from_,to_))
	{
		stat = op_func_(from_.where->data,func_param_);
		if(SUCCESS != stat)
		{
			return (status_bst_ty)stat;
		}
		from_ = BSTNext(from_);
	}
	
	/*Return Success*/
	return SUCCESS;
}

node_ty* UpUntil(node_ty *node, int left_or_right)
{
	node_ty *parent = NULL;

	assert(NULL != node);

	/*parent = iter->where->up*/
	parent = node->up;
	/*while parent->children[left_or_right] != iter */
		/*iter = parent*/
		/*parent = up*/

	 while (NULL != parent && NULL != parent->data)
    {
        if ((LEFT == left_or_right && parent->children[LEFT] != node) || 
            (RIGHT == left_or_right && parent->children[RIGHT] != node))
        {
            node = parent;
            parent = parent->up;
        }
        else
        {
            break;
        }
    }

	/*return parent node*/
	return parent;
}

node_ty* DownUntil(node_ty *node, int left_or_right)
{
	assert(NULL != node);

	/*while there is iter.child[left_or_right]*/

	while(NULL != node->children[left_or_right])
	{
		node = node->children[left_or_right];
	}
	/*Return Node*/
	return node;
}

node_ty* PrevNext(node_ty *node, int is_next)
{
	/*assert*/
	assert(NULL != node);

	/*if iter->where.children[is_next] != NULL*/
		/*DownUntilIMP(iter->where.children[is_next], !is_next)*/
	/*else*/
		/*UpUntilIMP(iter,!is_next)*/

	if(NULL != node->children[is_next])
	{
		node = DownUntil(node->children[is_next], !is_next);
	}
	else
	{
		node = UpUntil(node, !is_next);
	}

	/*Return Node*/
	return node;
}

node_ty** FindIMP(bst_ty* bst_, const void* data_, node_ty** parent_)
{
	node_ty **curr = NULL;
	int is_before_res = 0;

	/*assert*/
	assert(NULL != bst_);

	*parent_ = &bst_->dummy;
	curr = &bst_->dummy.children[LEFT];

	while(NULL != *curr && (*curr)->data != data_)
	{
		is_before_res = bst_->is_before(BSTGetData(ToIter(*curr)), data_, bst_->is_before_params);
		*parent_ = (*curr);
		curr = &(*curr)->children[is_before_res];
	}

	return curr;
}

bst_iter_ty ToIter(node_ty* node)
{
	bst_iter_ty iter;

	iter.where = node;

	return iter;
}

int ValidIter(bst_iter_ty iter)
{
	return NULL != iter.where;
}

void ConnectNodes(node_ty *parent_,node_ty *child_, int side)
{
	assert(NULL != parent_);
	child_->up = parent_;
	parent_->children[side] = child_;
}

int WhichSide(node_ty *node_)
{
	if(node_->up->children[LEFT] == node_)
	{
		return LEFT;
	}
	return RIGHT;
}

void Disconnect(node_ty *node_)
{
	int left_or_right = 0;
	left_or_right = WhichSide(node_);
	node_->up->children[left_or_right] = NULL;
	node_->up = NULL;
	node_->data = NULL;
	node_->children[LEFT] = NULL;
	node_->children[RIGHT] = NULL;
}

void SimpleRemove(node_ty *to_remove_)
{
	/*if NO children*/
		/*disconnect*/
	if(NULL == to_remove_->children[LEFT] && NULL == to_remove_->children[RIGHT])
	{
		Disconnect(to_remove_);
	}
	/*if One child*/
		/*Find which side then and connect child to parent*/
	else if(NULL != to_remove_->children[LEFT] || NULL != to_remove_->children[RIGHT])
	{
		ConnectNodes(to_remove_->up, to_remove_->children[NULL != to_remove_->children[RIGHT]], WhichSide(to_remove_));
	}
}

void AttachParentToChild(node_ty *parent_, node_ty *child_, node_ty **where_)
{
	child_->up = parent_;
	child_->children[LEFT] = NULL;
	child_->children[RIGHT] = NULL;
	*where_ = child_;
}