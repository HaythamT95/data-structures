/*
	Name: Haytham
	Reviewer: Diana
*/
#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/

#include "trie.h"
#include "dhcp.h"
#include "utils.h"

struct dhcp
{
	trie_ty* ips;
	ip_ty net_mask;
	ip_ty prefix;
};

DEBUG_ONLY(
static int ValidateNetMask(ip_ty net_mask_);
)

static size_t CalcDepth(ip_ty net_mask_);
static ip_ty CalcIPIMP(ip_ty net_mask_, ip_ty ip_);
static int InitPreAllocationIPS(dhcp_ty* dhcp_, size_t num_of_ips_);
static int IsGoodIPIMP(dhcp_ty* dhcp_, ip_ty ip);

dhcp_ty* DHCPCreate(ip_ty net_mask_, ip_ty prefix_)
{
	dhcp_ty* ret = NULL;
	size_t depth = 0;

	/*net mask MUST BE 1s at first then 0s*/
	assert(0 != ValidateNetMask(net_mask_));

	/*prefix & net_mask = prefix*/
	assert(prefix_ != (net_mask_ & prefix_));

	/*Alloc dhcp*/
	ret = (dhcp_ty*)malloc(sizeof(dhcp_ty));
	if(NULL == ret)
	{
		/*handle failure*/
		return NULL;
	}

	depth = CalcDepth(net_mask_);

	/*Alloc trie = CalcDepth()*/
	ret->ips = TrieCreate(depth);
	if(NULL == ret->ips)
	{
		/*handle failure*/
		free(ret);
		return NULL;
	}


	/*Init*/
	ret->net_mask = net_mask_;
	ret->prefix = prefix_;

	/*for subnet ID: 192.168.111.0/24, preallocates: 192.168.111.0, 192.168.111.254, 192.168.111.255*/
	if(InitPreAllocationIPS(ret, 1 << depth))
	{
		free(ret);
		return NULL;
	}

	/*return ret*/
	return ret;
}

void DHCPDestroy(dhcp_ty* dhcp_)
{
	if(NULL != dhcp_)
	{
		/*TrieDestroy(dhcp_->trie)*/
		TrieDestroy(dhcp_->ips);
		
		/*free(dhcp_)*/
		free(dhcp_);
	}
}

ip_ty DHCPAlloc(dhcp_ty* dhcp_, ip_ty ip_)
{
	ip_ty ret = 0;
	/*assert*/
	/*ip & netmask = prefix*/
	assert(0 == IsGoodIPIMP(dhcp_, ip_));

	/*ip = CalcIPIMP(ip_)*/
	ret = CalcIPIMP(dhcp_->net_mask, ip_);

	/*ret = TrieGet(dhcp_->trie, ip)*/
	ret = TrieGet(dhcp_->ips, ret);

	/*return ret*/
	return ret;
}

void DHCPFreeIP(dhcp_ty* dhcp_, ip_ty ip_)
{
	ip_ty ip = 0;

	/*assert*/
	/*ip & netmask = prefix*/
	assert(0 == IsGoodIPIMP(dhcp_, ip_));

	/*ip = CalcIPIMP(ip_)*/
	ip = CalcIPIMP(dhcp_->net_mask, ip_);

	/*TrieFree(dhcp_->trie, ip)*/
	TrieFree(dhcp_->ips, ip);
}

size_t DHCPCountFree(dhcp_ty* dhcp_)
{
	/*assert*/
	assert(NULL != dhcp_);

	/*return TrieCountAvailable(dhcp_->trie)*/
	return TrieCountAvailable(dhcp_->ips);
}

int DHCPIsAllTaken(dhcp_ty* dhcp_)
{
	/*assert*/
	assert(NULL != dhcp_);

	/*return TrieIsAllTaken(dhcp_->trie)*/
	return TrieIsAllTaken(dhcp_->ips);
}

DEBUG_ONLY(
	int ValidateNetMask(ip_ty net_mask_)
	{
		/*msb must be 1*/
		if(0 == ((net_mask_ << (sizeof(ip_ty) * 8 - 1)) & 1UL))
		{
			/*if not return 1*/
			return 1;
		}

		/*find first 0 after 1s then check if the rest are 0s*/
		while(0 == (net_mask_ & 1UL))
		{
			net_mask_>>=1;
		}

		while(net_mask_)
		{
			if(0 == (net_mask_ & 1UL))
			{
				return 1;
			}
			net_mask_>>=1;
		}

		/*return 0*/
		return 0;
	})


size_t CalcDepth(ip_ty net_mask_)
{
	size_t ret = 0;

	/*while(net_mask & 1)*/
	while(0 == (net_mask_ & 1UL))
	{
		/*++ret*/
		++ret;

		/*mask <<=1;*/
		net_mask_>>=1;
	}
		
	/*return ret*/
	return ret;
}

ip_ty CalcIPIMP(ip_ty net_mask_, ip_ty ip_)
{
	ip_ty mask = 1UL;

	while(0 == (net_mask_ & 1))
	{
		mask<<=1;
		mask|=1;
		net_mask_>>=1;
	}

	return ip_ & mask;
}

int InitPreAllocationIPS(dhcp_ty* dhcp_, size_t num_of_ips_)
{
	assert(NULL != dhcp_);

	TrieGet(dhcp_->ips, 0);

	if(0 == TrieGet(dhcp_->ips, num_of_ips_ - 1) || 0 == TrieGet(dhcp_->ips, num_of_ips_ - 2))
	{
		return 1;
	}
	return 0;
}

int IsGoodIPIMP(dhcp_ty* dhcp_, ip_ty ip)
{
	return dhcp_->prefix == (dhcp_->net_mask & ip);
}