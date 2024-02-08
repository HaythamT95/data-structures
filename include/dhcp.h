/*******************************************************************************
Project: DHCP
Name: Haytham
Reviewer: Diana
Date: 15.12.2023
Version: 1.0
*******************************************************************************/

#ifndef __DHCP_H__
#define __DHCP_H__

#include <stddef.h> /*size_t*/

typedef unsigned long ip_ty;

typedef struct dhcp dhcp_ty;

/*
	Return: NULL on failure
	Complexity: O(log(size))
*/
dhcp_ty* DHCPCreate(ip_ty net_mask_, ip_ty prefix_);

/*
	Note: NULL is allowed
	Complexity: O(n)
*/
void DHCPDestroy(dhcp_ty* dhcp_);

/*
	Return: If not available return next available ip
	Complexity: O(logn)
*/
ip_ty DHCPAlloc(dhcp_ty* dhcp_, ip_ty ip_);

/*
	Complexity: O(logn)
*/
void DHCPFreeIP(dhcp_ty* dhcp_, ip_ty ip_);

/*
	Return: Number of available IP addresses
*/
size_t DHCPCountFree(dhcp_ty* dhcp_);

/*
	Return: 1 - If all ips are taken, 0 - there are still available ips
	Complexity: O(1)
*/
int DHCPIsAllTaken(dhcp_ty* dhcp_);

#endif /*__DHCP_H__*/