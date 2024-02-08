/*
	Name: Haytham
	Reviewer: Najeeb
*/
#include <stdio.h> /*fprintf*/
#include <stdlib.h> /*calloc, malloc, free*/
#include <assert.h> /*assert*/

#include "doublylinkedlist.h"
#include "hash.h"
#include "utils.h"

struct hash
{
	dlist_ty** lists;
	hash_func_ty hash_func;
	is_same_key_ty is_same;
	const void* hash_params;
	const void* is_same_params;
	size_t max_capacity;
};

enum MODE
{
	FIND,
	DELETE
};

static int CmpNumbers(const void * num1, const void * num2);
static pair_ty FindPair(hash_ty *hash_, const void* key_, int mode_);
static size_t HashFunctionToIndex(hash_ty *hash_, const void* key_);
static int FreePair(void* to_free_, void* ignore_);

hash_ty* HashCreate(size_t capacity_, hash_func_ty hash_func_, const void* hash_params_,
					is_same_key_ty is_same_, const void* is_same_params_)
{
	hash_ty* hash = NULL;
	size_t i = 0;

	/*assert*/
	assert(NULL != hash_func_);
	assert(NULL != is_same_);
	assert(0 != capacity_);

	/*Allocate*/
	hash = (hash_ty*)malloc(sizeof(hash_ty));
	
	if(NULL == hash)
	{
		/*handle failure*/
		fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
      return NULL;
	}

	/*init*/
	hash->lists = (dlist_ty**)calloc(capacity_, sizeof(dlist_ty*));

	if(NULL == hash->lists)	
	{
		/*handle failure*/
		fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
		free(hash);
      return NULL;
	}
	
	/*for i = 0 to capacity*/
	for(i = 0; i < capacity_; ++i)
	{
		/*create list*/
		hash->lists[i] = DListCreate();

		if(NULL == hash->lists[i])
		{
			/*handle failure*/
			fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
			HashDestroy(hash);
       	return NULL;
		}
	}

	/*init hash fields*/
	hash->max_capacity = capacity_;
	hash->hash_func = hash_func_;
	hash->hash_params = hash_params_;
	hash->is_same = is_same_;
	hash->is_same_params = is_same_params_;

	/*return*/
	return hash;
}

void HashDestroy(hash_ty* hash_)
{
	size_t i = 0;

	if(NULL != hash_)
	{
		/*For i = 0 to capacity*/
		for(i = 0; i < hash_->max_capacity; ++i)
		{			
			/*Remove each element from list*/
			DListForEach(hash_->lists[i], DListBegin(hash_->lists[i]), DListEnd(hash_->lists[i]), FreePair, NULL);
			DListDestroy(hash_->lists[i]);
			hash_->lists[i] = BAD_MEM(dlist_ty*);
		}

		/*curropt data*/
		hash_->max_capacity = BAD_MEM(size_t);
		hash_->hash_func = BAD_MEM(hash_func_ty);
		hash_->hash_params = BAD_MEM(void*);
		hash_->is_same = BAD_MEM(is_same_key_ty);
		hash_->is_same_params = BAD_MEM(void*);

		free(hash_->lists);
		hash_->lists = BAD_MEM(dlist_ty**);

		free(hash_);
	}
}

pair_ty HashRemove(hash_ty* hash_, const void* key_)
{
	pair_ty ret;

	/*assert*/
	assert(NULL != hash_);
	assert(NULL != key_);

	/*Remove & Return*/
	ret = FindPair(hash_, key_, DELETE);

	/*return ret*/
	return ret;
}

hash_status_ty HashInsert(hash_ty* hash_, const void* key_, void* data_)
{
	size_t index = 0;
	int status = 0;
	pair_ty* pairs = NULL;

	/*assert*/
	assert(NULL != hash_);
	assert(NULL != key_);
	assert(NULL != data_);

	/*init pairs*/
	pairs = (pair_ty*)malloc(sizeof(pair_ty));

	if(NULL == pairs)
	{
		/*handle failure*/
		fprintf(stderr, "ERROR ALLOCATING MEMORY\n");
      return MALLOC_FAIL;
	}

	/*index = HashFunctionValue(key)*/
	index = HashFunctionToIndex(hash_, key_);

	/*init pairs*/
	pairs->key = key_;
	pairs->data = data_;

	/*status = hash[index].push(key,data)*/
	status = DListPushFront(hash_->lists[index], pairs);

	/*If failed to push*/
	if(SUCCESS != status)
	{
		/*curropt data and free*/
		pairs->key = BAD_MEM(void*);
		pairs->data = BAD_MEM(void*);
		free(pairs);
		return MALLOC_FAIL;
	}

	/*ret status*/
	return status;
}

size_t HashSize(hash_ty* hash_)
{
	size_t i = 0;
	size_t size = 0;

	/*assert*/
	assert(NULL != hash_);

	/*for i = 0 to capacity*/
	for (i = 0; i < hash_->max_capacity; ++i)
	{
		/*size+=dlist.size()*/
		size += DListLength(hash_->lists[i]);
	}
		
	/*return size*/
	return size;
}

int HashIsEmpty(const hash_ty* hash_)
{
	size_t i = 0;
	int empty_list = 0;

	/*assert*/
	assert(NULL != hash_);

	/*size = HashSize()*/
	for (i = 0; i < hash_->max_capacity; ++i)
	{
		/*size+=dlist.size()*/
		empty_list = DListIsEmpty(hash_->lists[i]);

		/*if size is not zero*/
		/*return 0*/
		if(0 == empty_list)
		{
			return 0;
		}
	}

	/*return 1*/
	return 1;
}

pair_ty HashFind(hash_ty* hash_, const void* key_)
{
	pair_ty ret;

	/*assert*/
	assert(NULL != hash_);
	assert(NULL != key_);

	/*Find & Return*/
	ret = FindPair(hash_, key_, FIND);

	/*return ret*/
	return ret;
}

int HashForeach(hash_ty* hash_, hash_op_func_ty op_func_, void *func_param_)
{
	size_t i = 0;
	int status = 0;

	/*assert*/
	assert(NULL != hash_);
	assert(NULL != op_func_);

	/*for i = 0 to capacity*/
	for(i = 0; i < hash_->max_capacity; ++i)
	{
		/*Foreach element in list perform op_func*/
		status = DListForEach(hash_->lists[i], DListBegin(hash_->lists[i]), DListEnd(hash_->lists[i]), op_func_ ,func_param_);

		/*if status is NOT SUCCESS*/
		if(SUCCESS != status)
		{
			/*return status from Foreach*/
			return status;
		}
	}
		
	/*return stat*/
	return SUCCESS;
}

hash_stats_ty HashStats(const hash_ty* hash_)
{
	hash_stats_ty stat;
	size_t *size_counter = NULL;
	size_t i = 0;
	size_t curr_list_size = 0;

	/*assert*/
	assert(NULL != hash_);

	/*init stats*/
	stat.longest_list = 0;
	stat.median_list = 0;
	stat.size = 0;
	stat.capacity = 0;

	/*init lists of size cap*/
	size_counter = (size_t*)calloc(hash_->max_capacity, sizeof(size_t));

	/*for i = 0 to cap*/
	for (i = 0; i < hash_->max_capacity; ++i)
	{
		/*size = dlist.size()*/
		curr_list_size = DListLength(hash_->lists[i]);

		/*lists[i] = size*/
		size_counter[i] = curr_list_size;

		stat.size += curr_list_size;
	}
		
	stat.capacity = hash_->max_capacity;

	/*sort lists*/
	qsort(size_counter, hash_->max_capacity, sizeof(size_t), CmpNumbers);

	/*calc median - if odd*/
	if(1 == (stat.capacity & 1))
	{
		stat.median_list = size_counter[(stat.capacity + 1) / 2];
	}
	else
	{
		stat.median_list = (size_counter[(stat.capacity + 1) / 2] + size_counter[(stat.capacity / 2)]) / 2;
	}

	/*longest = lists[cap-1]*/
	stat.longest_list = size_counter[stat.capacity - 1];

	free(size_counter);

	/*return stats*/
	return stat;
}

int CmpNumbers(const void * num1_, const void * num2_)
{
   return *(size_t*)num1_ - *(size_t*)num2_;
}

pair_ty FindPair(hash_ty *hash_, const void* key_, int mode_)
{
	size_t index = 0;
	size_t list_size = 0;
	size_t curr_elem = 0;
	dlist_ty *list = NULL;
	dlist_iter_ty runner;
	pair_ty *element = NULL;
	pair_ty ret = {NULL, NULL};

	/*assert*/
	assert(NULL != hash_);
	assert(NULL != key_);

	/*index = HashFunctionValue(key)*/
	index = HashFunctionToIndex(hash_, key_);

	/*dlist = hash[index]*/
	list = hash_->lists[index];

	runner = DListBegin(list);
	list_size = DListLength(list);

	/*foreach elem in dlist*/
	while(curr_elem < list_size)
	{
		element = DListGetData(runner);

		/*if IsSame(key, elem->key)*/
		if(hash_->is_same(element->key, key_, hash_->is_same_params))
		{
			/*ret = elem*/
			ret.data = element->data;
			ret.key = element->key;

			/*if mode is DELETE*/
			if(DELETE == mode_)
			{
				/*remove from list*/
				runner = DListRemove(list, runner);

				element->data = BAD_MEM(void*);
				element->key = BAD_MEM(void*);

				free(element);
			}

			return ret;
		}

		++curr_elem;
		runner = DListNext(runner);
	}

	/*return ret*/
	return ret;
}

size_t HashFunctionToIndex(hash_ty *hash_, const void* key_)
{
	return hash_->hash_func(key_, hash_->hash_params) % hash_->max_capacity;
}

int FreePair(void* to_free_, void* ignore_)
{
	free(to_free_);
	(void)ignore_;

	return SUCCESS;
}