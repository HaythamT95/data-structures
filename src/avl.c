/*
Name: Haytham
Pseudocode Reviewer: Jonathan
Reviewer: ***
*/
#include <stdio.h> /*fprintf*/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/

#include "avl.h"
#include "utils.h"

#define NUMBER_OF_CHILDREN 2

typedef struct node
{
	struct node* children[NUMBER_OF_CHILDREN];
	void *data;
	int height;
}avl_node_ty;

struct avl
{
	avl_node_ty dummy;
	is_before_func_ty is_before;
	const void* is_before_params;
};

enum DIRECTION
{
	LEFT = 0,
	RIGHT = 1
};

static avl_node_ty* FindAndRemoveIMP(avl_ty *avl_, avl_node_ty **node_, const void* key_, void **data_);

static void AVLDestoryHelpIMP(avl_node_ty *node_);
static avl_node_ty* FindIMP(avl_ty *avl_, avl_node_ty *node_, const void* key_);

static int PostOrderForEachIMP(avl_node_ty *node_, avl_op_func_ty op_func_, void *func_param_);
static int PreOrderForEachIMP(avl_node_ty *node_, avl_op_func_ty op_func_, void *func_param_);
static int InOrderForEachIMP(avl_node_ty *node_, avl_op_func_ty op_func_, void *func_param_);

static avl_node_ty* CreateNodeIMP(void *data_);
static avl_node_ty* InsertIMP(avl_ty *avl_, avl_node_ty **where_, avl_node_ty *new_node_);
static size_t SizeIMP(avl_node_ty *node_);
static size_t HeightIMP(avl_node_ty *node_);
static size_t MaxBetween(size_t left_, size_t right_);

static avl_node_ty* RotateLeftMost(avl_node_ty* node_, void **data_);
static void UpdateHeight(avl_node_ty *node_);
static int BalanceFactor(avl_node_ty *node_);
static avl_node_ty *RightRotate(avl_node_ty *node_);
static avl_node_ty *LeftRotate(avl_node_ty *node_);
static avl_node_ty *Balance(avl_node_ty *node_);

avl_ty* AVLCreate(is_before_func_ty is_before_, const void *is_before_params_)
{
	avl_ty *avl = NULL;
	/*assert*/
	assert(NULL != is_before_);

	/*allocate*/
	avl = (avl_ty*)malloc(sizeof(avl_ty));

	/*handle failure*/
	if(NULL == avl)
	{
		fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
        return NULL;
	}

	/*init*/
	avl->dummy.children[LEFT] = NULL;
	avl->dummy.children[RIGHT] = NULL;
	avl->dummy.data = NULL;
	avl->is_before = is_before_;
	avl->is_before_params = is_before_params_;

	/*return avl*/
	return avl;
}

void AVLDestroy(avl_ty *avl_)
{
	/*if avl IS NOT NULL*/
	if(NULL != avl_)
	{
		/*AVLDestoryHelpIMP(avl_->dummy.left)*/
		AVLDestoryHelpIMP(avl_->dummy.children[LEFT]);

		avl_->is_before = BAD_MEM(is_before_func_ty);
		avl_->is_before_params = BAD_MEM(void*);

		/*free(avl)*/
		free(avl_);
	}
}

void* AVLRemove(avl_ty *avl_, const void* key_)
{
	avl_node_ty *ret = NULL;
	void *data = NULL;

	/*assert*/
	assert(NULL != avl_);

	ret = FindAndRemoveIMP(avl_, &avl_->dummy.children[LEFT], key_, &data);
	(void)ret;

	return data;
}

avl_status_ty AVLInsert(avl_ty *avl_, void *key_)
{
	avl_node_ty *new_node = NULL;
	/*assert*/
	assert(NULL != avl_);

	/*new_node = CreateNode(key_)*/
	new_node = CreateNodeIMP(key_);

	if(NULL == new_node)
	{
		RET_IF_BAD(NULL != new_node, MALLOC_FAIL);
       	return MALLOC_FAIL;
	}

	/*InsertIMP(avl_, avl_->dummy->left, new_node)*/
	avl_->dummy.children[LEFT] = InsertIMP(avl_, &avl_->dummy.children[LEFT], new_node);

	/*return success*/
	return SUCCESS;
}

size_t AVLHeight(const avl_ty *avl_)
{
	/*assert*/
	assert(NULL != avl_);

	/*return HeightIMP(avl_->dummy.left)*/
	return HeightIMP(avl_->dummy.children[LEFT]);
}

size_t AVLSize(const avl_ty *avl_)
{
	/*assert*/
	assert(NULL != avl_);

	/*return SizeIMP(avl_->dummy.left)*/
	return SizeIMP(avl_->dummy.children[LEFT]);
}

int AVLIsEmpty(const avl_ty *avl_)
{
	assert(NULL != avl_);

	/*return avl->dummy->child is NULL*/
	return NULL == avl_->dummy.children[LEFT];
}

void* AVLFind(avl_ty *avl_, const void* key_)
{
	avl_node_ty *node = NULL;
	/*assert*/
	assert(NULL != avl_);
	assert(NULL != key_);

	/*node = FindIMP(avl_, avl->dummy.left, key_)*/
	node = FindIMP(avl_, avl_->dummy.children[LEFT], key_);

	if(NULL == node)
	{
		return NULL;
	}

	/*return node*/
	return node->data;
}

int AVLForEach(avl_ty *avl_, traversal_ty mode_,
	                               avl_op_func_ty op_func_, void *func_param_)
{
	int ret = 0;
	/*assert*/
	assert(NULL != avl_);
	assert(NULL != op_func_);

	/*switch(mode_)*/
	switch(mode_)
	{
		/*POST:	ret = PostOrderForEachIMP(avl->dummy.left, op_func_, func_param_)*/
		case POST_ORDER:
			ret = PostOrderForEachIMP(avl_->dummy.children[LEFT], op_func_, func_param_);
		break;

		/*PRE:	ret = PreOrderForEachIMP(avl->dummy.left, op_func_, func_param_)*/
		case PRE_ORDER:
			ret = PreOrderForEachIMP(avl_->dummy.children[LEFT], op_func_, func_param_);
		break;

		/*IN:	ret = InOrderForEachIMP(avl->dummy.left, op_func_, func_param_)*/
		case IN_ORDER:
			ret = InOrderForEachIMP(avl_->dummy.children[LEFT], op_func_, func_param_);
		break;

		default:
			ret = TRAVERSAL_ERR;
		break;
	}
		
	/*return ret*/
	return ret;
}

avl_node_ty * InsertIMP(avl_ty *avl_, avl_node_ty **where_, avl_node_ty *new_node_)
{
	int side = 0;

	/*assert*/
	assert(NULL != avl_);
	assert(NULL != new_node_);	

	/*if *where is NULL*/
	if(NULL == *where_)
	{
		/*connect here*/
		*where_ = new_node_;
		return *where_;
	}

	/*side = the side we should go to is_before_func*/
	side = avl_->is_before((*where_)->data,new_node_->data, avl_->is_before_params);

	/*InsertIMP(avl, &(*where)->children[side],new_node)*/
	(*where_)->children[side] = InsertIMP(avl_,&(*where_)->children[side], new_node_);

	return Balance(*where_);
}

int PostOrderForEachIMP(avl_node_ty *node_, avl_op_func_ty op_func_, void *func_param_)
{
	/*ret = 0*/
	int ret = 0;

	/*if node->left != NULL*/
	if(NULL != node_->children[LEFT])
	{
		/*ret = PostOrderForEachIMP(node->left, op_func_, func_param_)*/
		ret = PostOrderForEachIMP(node_->children[LEFT], op_func_, func_param_);
	}
	/*if ret == 0 AND node->right != NULL*/
	if(0 == ret && NULL != node_->children[RIGHT])
	{
		/*ret = PostOrderForEachIMP(node->right, op_func_, func_param_)*/
		ret = PostOrderForEachIMP(node_->children[RIGHT], op_func_, func_param_);
	}

	/*if ret = 0*/
	if(0 == ret)
	{
		/*ret = op_func_(node->data, func_param_)*/
		ret = op_func_(node_->data, func_param_);
	}

	/*return ret*/
	return ret;
}

int PreOrderForEachIMP(avl_node_ty *node_, avl_op_func_ty op_func_, void *func_param_)
{
	/*ret = 0*/
	int ret = 0;

	/*if node != NULL*/
	if(NULL != node_)
	{
		/*ret = op_func_(node->data, func_param_)*/
		ret = op_func_(node_->data, func_param_);
	}

	/*if ret == 0 AND node != NULL AND node->left != NULL*/
	if(0 == ret && NULL != node_ && NULL != node_->children[LEFT])
	{
		/*ret = PreOrderForEachIMP(node->left, op_func_, func_param_)*/
		ret = PreOrderForEachIMP(node_->children[LEFT], op_func_, func_param_);
	}

	if(0 == ret && NULL != node_ && NULL != node_->children[RIGHT])
	{
		/*ret = PreOrderForEachIMP(node->left, op_func_, func_param_)*/
		ret = PreOrderForEachIMP(node_->children[RIGHT], op_func_, func_param_);
	}

	/*return ret*/
	return ret;
}

int InOrderForEachIMP(avl_node_ty *node_, avl_op_func_ty op_func_, void *func_param_)
{
	/*ret = 0*/
	int ret = 0;

	/*if node != NULL AND node->left != NULL*/
	if(NULL != node_ && NULL != node_->children[LEFT])
	{
		/*ret = InOrderForEachIMP(node->left, op_func_, func_param_)*/
		ret = InOrderForEachIMP(node_->children[LEFT], op_func_, func_param_);
	}

	/*if ret == 0 AND node != NULL*/
	if(0 == ret && NULL != node_)
	{
		/*ret = op_func_(node->data, func_param_)*/
		ret = op_func_(node_->data, func_param_);
	}

	/*if ret == 0 AND node != NULL AND node->right != NULL*/
	if(0 == ret && NULL != node_ && NULL != node_->children[RIGHT])
	{
		/*ret = InOrderForEachIMP(node->right, op_func_, func_param_)*/
		ret = InOrderForEachIMP(node_->children[RIGHT], op_func_, func_param_);
	}

	/*return ret*/
	return ret;
}

avl_node_ty* CreateNodeIMP(void *data_)
{
	avl_node_ty *new_node = NULL;
	/*assert*/
	assert(NULL != data_);

	/*init node*/
	new_node = (avl_node_ty*)malloc(sizeof(avl_node_ty));

	if(NULL == new_node)
	{
       	return NULL;
	}

	new_node->data = data_;
	new_node->children[RIGHT] = NULL;
	new_node->children[LEFT] = NULL;
    new_node->height = 1; 

	/*return node*/
	return new_node;
}

void AVLDestoryHelpIMP(avl_node_ty *node_)
{
	/*if node is NULL*/
	if(NULL == node_)
	{
		/*return*/
		return;
	}

	/*AVLDestoryHelpIMP(node->left)*/
	AVLDestoryHelpIMP(node_->children[LEFT]);

	/*AVLDestoryHelpIMP(node->right)*/
	AVLDestoryHelpIMP(node_->children[RIGHT]);

	node_->children[LEFT] = BAD_MEM(avl_node_ty*);
	node_->children[RIGHT] = BAD_MEM(avl_node_ty*);
	node_->data = BAD_MEM(void*);

	/*free(node)*/
	free(node_);
}

size_t SizeIMP(avl_node_ty *node_)
{
	/*if node IS NULL*/
	if(NULL == node_)
	{
		/*return 0*/
		return 0;
	}
	/*else*/
	else
	{
		/*return (SizeIMP(node->left) + 1 + SizeIMP(node->right))*/
		return(SizeIMP(node_->children[LEFT]) + 1 + SizeIMP(node_->children[RIGHT]));
	}
}

size_t HeightIMP(avl_node_ty *node_)
{
	if(NULL == node_)
	{
		/*return 0*/
		return 0;
	}
	/*else*/
	else
	{
		/*return MAX(HeightIMP(node->left), HeightIMP(node->right)) + 1*/
		return MaxBetween(HeightIMP(node_->children[LEFT]), HeightIMP(node_->children[RIGHT])) + 1;
	}
}

size_t MaxBetween(size_t left_, size_t right_)
{
	return (left_ > right_) ? left_ : right_;
}

avl_node_ty* FindIMP(avl_ty *avl_, avl_node_ty *node_, const void* key_)
{
	int side = 0;
    assert(NULL != avl_);

    if (NULL == node_)
    {
        return NULL;
    }

    side = avl_->is_before(key_, node_->data, avl_->is_before_params);

    if (1 == side)
    {
        /* key is less than current node's data, go left */
        return FindIMP(avl_, node_->children[LEFT], key_);
    }
    else if (0 == side)
    {
        /* key is equal to current node's data, return the current node */
        return node_;
    }
    else
    {
        /* key is greater than current node's data, go right */
        return FindIMP(avl_, node_->children[RIGHT], key_);
    }
}

avl_node_ty* FindAndRemoveIMP(avl_ty* avl_, avl_node_ty** node_, const void* key_, void **data_) 
{
	avl_node_ty* child = NULL;
	void *moved_data = NULL;

    assert(NULL != avl_);

    if (NULL == *node_) 
    {
        return NULL;
    }

    /*Key is in the left subtree*/
    if (avl_->is_before(key_, (*node_)->data,avl_->is_before_params)) 
    {
    	/*Go to left subtree*/
        (*node_)->children[LEFT] = FindAndRemoveIMP(avl_, &(*node_)->children[LEFT], key_, data_);
    }

    /*Key is in the right subtree*/
    else if (avl_->is_before((*node_)->data, key_, avl_->is_before_params)) 
    {
    	/*Go to right subtree*/
        (*node_)->children[RIGHT] = FindAndRemoveIMP(avl_, &(*node_)->children[RIGHT], key_, data_);
    } 
    /*Node with the key found, perform the deletion*/
    else
    {   
    	/*Save data*/
     	
     	*data_ = (*node_)->data;

     	/*If has right child*/
        if (NULL == (*node_)->children[LEFT]) 
        {
        	/*return right child*/
            child = (*node_)->children[RIGHT];

            /*delete node*/
            free(*node_);

            return child;
        } 
        /*If has left child*/
        else if (NULL == (*node_)->children[RIGHT]) 
        {
        	/*return left child*/
            child = (*node_)->children[LEFT];

            /*delete node*/
            free(*node_);

            return child;
        }

        /*Node with two children: Get the smallest in the right subtree*/
       	(*node_)->children[RIGHT] = RotateLeftMost((*node_)->children[RIGHT], &moved_data);
       	(*node_)->data = moved_data;
    }
    
    *node_ = Balance(*node_);
    return *node_;            
}

avl_node_ty* RotateLeftMost(avl_node_ty *node_, void **moved_data_)
{
	avl_node_ty* child = NULL;

	if(NULL == node_->children[LEFT])
	{
		*moved_data_ = node_->data;
		child = node_->children[RIGHT];
		free(node_);
        return child;
	}

	node_->children[LEFT] = RotateLeftMost(node_->children[LEFT],moved_data_);


    return node_;
}

avl_node_ty *Balance(avl_node_ty *node_)
{
    int balance = 0;
    /* Update height of the current node */
    UpdateHeight(node_);

    /* Get the balance factor to check if the node became unbalanced */
    balance = BalanceFactor(node_);

    /* Perform rotations if needed */
    /* Left Heavy */
    if (balance > 1)
    {
        if (BalanceFactor(node_->children[LEFT]) >= 0)
        {
            return RightRotate(node_);
        }
        else
        {
            node_->children[LEFT] = LeftRotate(node_->children[LEFT]);
            return RightRotate(node_);
        }
    }

    /* Right Heavy */
    if (balance < -1)
    {
        if (BalanceFactor(node_->children[RIGHT]) <= 0)
        {
            return LeftRotate(node_);
        }
        else
        {
            node_->children[RIGHT] = RightRotate(node_->children[RIGHT]);
            return LeftRotate(node_);
        }
    }

    return node_;
}

void UpdateHeight(avl_node_ty *node_)
{
	int left_height = 0; 
	int right_height = 0;

    if (NULL == node_)
    {
        return;
    }

    /*Update left_height with the height of the left child (if it exists).*/
    left_height = (node_->children[LEFT]) ? node_->children[LEFT]->height : 0;

    /*Update right_height with the height of the right child (if it exists).*/
    right_height = (node_->children[RIGHT]) ? node_->children[RIGHT]->height : 0;

    /*Set the height of the current node to 1 plus the maximum of left_height and right_height.*/
    node_->height = 1 + ((left_height > right_height) ? left_height : right_height);
}

int BalanceFactor(avl_node_ty *node_)
{
	int left_height = 0; 
	int right_height = 0;

    if (NULL == node_)
    {
        return 0;
    }

    /*Update left_height with the height of the left child (if it exists).*/
    left_height = (node_->children[LEFT]) ? node_->children[LEFT]->height : 0;

    /*Update right_height with the height of the right child (if it exists).*/
    right_height = (node_->children[RIGHT]) ? node_->children[RIGHT]->height : 0;

    /*Return the balance factor, which is the difference between left_height and right_height.*/
    return left_height - right_height;
}

avl_node_ty *RightRotate(avl_node_ty *node_)
{
    avl_node_ty *left_child = NULL;
    avl_node_ty *right_child = NULL;

    assert(NULL != node_);

    /*Retrieve the left child of the current node.*/
    left_child = node_->children[LEFT];

    /*Retrieve the right child of the left child.*/
	right_child = left_child->children[RIGHT];

	/* Perform the right rotation.*/
    left_child->children[RIGHT] = node_;
    node_->children[LEFT] = right_child;

    /*Update the heights of the rotated nodes.*/
    UpdateHeight(node_);
    UpdateHeight(left_child);

    return left_child;
}

avl_node_ty *LeftRotate(avl_node_ty *node_)
{
    avl_node_ty *right_child = NULL;
    avl_node_ty *left_child = NULL;

    assert(NULL != node_);

    /*Retrieve the right child of the current node.*/
    right_child = node_->children[RIGHT];

    /*Retrieve the left child of the right child.*/
	left_child = right_child->children[LEFT];

	/*Perform the left rotation.*/
    right_child->children[LEFT] = node_;
    node_->children[RIGHT] = left_child;

    /*Update the heights of the rotated nodes.*/
    UpdateHeight(node_);
    UpdateHeight(right_child);

    return right_child;
}