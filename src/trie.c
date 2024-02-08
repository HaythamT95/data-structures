/*
	Name: Haytham
	Reviewer: Diana
*/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/

#include "trie.h"
#include "utils.h"

#define BITS_PER_BYTE 8

typedef struct t_node
{
	struct t_node* b_t[2];
	int is_full;
}t_node_ty;

typedef struct trie
{
	t_node_ty* trie;
	size_t depth;
}trie_ty;

enum states
{
	SUCCESS = 1,
	FAILURE = 0,
	MALLOC_FAIL = -1,
	SIDE_IS_FULL = -2
};

static void DestroyIMP(t_node_ty* node_, size_t depth_);
static int GetIMP(t_node_ty** node_, unsigned long* wanted_ip_, size_t depth_);
static void FreeIMP(t_node_ty** node_, unsigned long num_, size_t depth_);
static t_node_ty* CreateNodeIMP();
static size_t CountIMP(t_node_ty* node_, size_t depth_);

static unsigned char CalcLSB(unsigned long num_, size_t depth_);
static unsigned long CalcNextIP(unsigned long num_, size_t depth_);

trie_ty* TrieCreate(size_t depth_)
{
	trie_ty* ret = NULL;

	/*assert*/
	assert(0 != depth_);
	
	/*depth != sizeof(unsigned long)*/
	assert(depth_ != sizeof(unsigned long) * BITS_PER_BYTE);

	/*Alloc trie*/
	ret = (trie_ty*)malloc(sizeof(trie_ty));
	if(NULL == ret)
	{
		/*handle failure*/
		return NULL;
	}

	ret->trie = (t_node_ty*)malloc(sizeof(t_node_ty));
	if(NULL == ret->trie)
	{
		free(ret);
		/*handle failure*/
		return NULL;
	}

	/*Init*/
	ret->trie->b_t[0] = NULL;
	ret->trie->b_t[1] = NULL;
	ret->trie->is_full = 0;
	ret->depth = depth_;

	/*return ret*/
	return ret;
}

void TrieDestroy(trie_ty* trie_)
{
	/*If not NULL*/
	if(NULL != trie_)
	{
		/*DestroyIMP(trie.trie->b_t[0])*/
		DestroyIMP(trie_->trie, trie_->depth);

		free(trie_);
	}
}

unsigned long TrieGet(trie_ty* trie_, unsigned long num_)
{
	unsigned long ip = 0;
	int status = 0;

	assert(NULL != trie_);
	assert(num_ <= (1UL << trie_->depth));
    assert(0 == trie_->trie->is_full);

    ip = num_;

    /* if (trie->root.is_full is 1)  */
    if(trie_->trie->is_full)
    {
       /*  return 0*/
    	return 0;
    }

    /*status = GetIMP(&(trie->root), ip , trie->depth); */
    status = GetIMP(&trie_->trie, &ip, trie_->depth);

    /* if (status == MALLOC_FAIL) */
    if (MALLOC_FAIL == status)
    {
        /* return 0 */
        return 0;
    }

    /*if status is 0 */
    if(FAILURE == status)
    {
    	/*ip = 0*/
    	ip = 0;
        /* status = GetIMP(&(trie->root), ip, trie->depth); */
        status = GetIMP(&trie_->trie, &ip, trie_->depth);
    }

    if(SUCCESS != status)
    {
        /* return 0; */
        return 0;
    }
    	
   /* return ip*/
   return ip;
}

void TrieFree(trie_ty* trie_, unsigned long num_)
{
	/*assert*/
	assert(NULL != trie_);

	/*FreeImp(trie.trie, num_, depth)*/
	FreeIMP(&(trie_->trie), num_, trie_->depth);
}

size_t TrieCountAvailable(trie_ty* trie_)
{
    /*assert*/
    assert(NULL != trie_);

    return (1UL << trie_->depth) - CountIMP(trie_->trie, trie_->depth);
}

int TrieIsAllTaken(const trie_ty* trie_)
{
	/*assert*/
	assert(NULL != trie_);

	/*if first node is full*/
	if(trie_->trie->is_full)
	{
		/*return 1*/
		return 1;
	}

	/*return 0*/
	return 0;
}

void DestroyIMP(t_node_ty* node_, size_t depth_)
{
	if(node_ && depth_ > 0)
	{
		/*DestroyIMP(node_->b_t[0])*/
		DestroyIMP(node_->b_t[0], depth_ - 1);

		/*DestroyIMP(node_->b_t[1])*/
		DestroyIMP(node_->b_t[1], depth_ - 1);

		/*free(node_)*/
		free(node_);
	}
}

size_t CountIMP(t_node_ty* node_, size_t depth_)
{
	if(0 == depth_)
    {
        return NULL != node_;
    }

    if (NULL == node_)
    {
        return 0;
    }

    return CountIMP(node_->b_t[0], depth_ - 1) + CountIMP(node_->b_t[1], depth_ - 1);
}

int GetIMP(t_node_ty** node_, unsigned long *wanted_ip_, size_t depth_) 
{
	int bit = 0;
	int ret = 0;

	/*assert*/
	assert(NULL != node_);

	/*if depth == 0*/
	if (0 == depth_)
	{

		/*check if *node!=null  and it not full*/
		if (NULL == *node_)
		{
			*node_ = BAD_MEM(void*);
			return SUCCESS;
		}
		else
		{
			/*return SIDEFULL*/
			return SIDE_IS_FULL;
		}
	}

	/*if node == NUll*/
	if (NULL == *node_)
	{
		/*create node*/
		*node_ = CreateNodeIMP();

        /*if (*node == NULL)*/
		if (NULL == *node_)
		{
        	/*return MALLOC_FAIL*/
			return MALLOC_FAIL;
		}

		/*attach node to parent*/
		node_ = &(*node_);
	}

    /*if node->is_full*/
	if ((*node_)->is_full)
	{
    	/*return SIDE_IS_FULL*/
		return SIDE_IS_FULL;
	}

	/*calc next bit */
	bit = CalcLSB(*wanted_ip_, depth_);

	/*ret = GetIMP(&((*node)->children[bit]), wanted_ip, depth - 1)*/
	ret = GetIMP(&((*node_)->b_t[bit]), wanted_ip_, depth_ - 1);

    /*if ret == SIDE_IS_FULL & bit ==0*/
	if (SIDE_IS_FULL == ret && 0 == bit)
	{
    	/*update  ip current bit to 1 and all right to zeros*/
		*wanted_ip_ = CalcNextIP(*wanted_ip_, depth_);

		/*ret = GetIMP(&((*node)->children[1]), new_ip, depth - 1)*/
		ret = GetIMP(&((*node_)->b_t[1]), wanted_ip_, depth_ - 1);
	}
	else if (SIDE_IS_FULL == ret && 1 == bit)
	{
    	/*return Failure*/
		return FAILURE;
	}

	/*if ret == FAILURE || ret == MALLOCFAIL*/
	if (MALLOC_FAIL == ret || FAILURE == ret)
	{
		/*return status*/
		return ret;
	}

	/*if depth is 1 - one before end*/
	if(1 == depth_)
	{	
		/*if have two childs*/
		if (NULL != (*node_)->b_t[0] && NULL != (*node_)->b_t[1])
		{
    		/*(*node)->is_full=1;*/
			(*node_)->is_full = 1;
		}
	}
	else
	{
		if (NULL != (*node_)->b_t[0] && NULL != (*node_)->b_t[1] 
			&& ((*node_)->b_t[0]->is_full && (*node_)->b_t[1]->is_full ))
		{
			(*node_)->is_full = 1;
		}
	}

    /*return SUCCESS*/
	return SUCCESS;
}

void FreeIMP(t_node_ty** node_, unsigned long num_, size_t depth_)
{
	unsigned char bit = 0;

	/*if node is NULL*/
	if(NULL == *node_)
	{
		/*return;*/
		return;
	}

	if(0 == depth_)
	{
		*node_ = NULL;
		return;
	}

    /*bit = (number >> (sizeof(unsigned long) * 8 - bit_position - 1)) & 1;*/
    bit = CalcLSB(num_, depth_);

    /* Recursively free the appropriate child node */
    if ((*node_)->b_t[bit])
    {
         FreeIMP(&((*node_)->b_t[bit]), num_, depth_ - 1);
    }

    /*Return the is_used status of the current node */
    (*node_)->is_full = 0;
}

t_node_ty* CreateNodeIMP()
{
	/*Alloc node*/
	t_node_ty* new_node = (t_node_ty*)malloc(sizeof(t_node_ty));

	if(NULL == new_node)
	{
		/*handle failure*/
		return NULL;
	}

	/*Init*/
	new_node->b_t[0] = NULL;
	new_node->b_t[1] = NULL;
	new_node->is_full = 0;

	/*return node*/
	return new_node;
}

unsigned char CalcLSB(unsigned long num_, size_t depth_)
{
	return (num_ >> (depth_ - 1)) & 1;
}

unsigned long CalcNextIP(unsigned long num_, size_t depth_)
{
	return (num_ | 1 << (depth_ - 1)) & ~((1 << (depth_ - 1)) - 1);
}