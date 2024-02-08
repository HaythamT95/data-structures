#include <stdio.h>

#include "dhcp.h"

enum STATE
{
	FAIL = -1,
	SUCCESS = 0
};

static int TestRunner();
static int TestDHCPCreate();
static int TestDHCPAlloc();
static int TestDHCPFree();
static int TestDHCPIsAllTaken();

dhcp_ty *dhcp = NULL;

int main()
{
	int state = SUCCESS;

	state = TestRunner();

	return state;
}

int TestRunner()
{
	int state = SUCCESS;

	state = TestDHCPCreate();

	if(SUCCESS == state)
	{
		printf("Test Create DHCP Succeed :)\n");
	}
	else
	{
		printf("Test Create DHCP Failed :(\n");
	}

	state = TestDHCPAlloc();

	if(SUCCESS == state)
	{
		printf("Test Alloc DHCP Succeed :)\n");
	}
	else
	{
		printf("Test Alloc DHCP Failed :(\n");
	}

	state = TestDHCPFree();

	if(SUCCESS == state)
	{
		printf("Test Free DHCP Succeed :)\n");
	}
	else
	{
		printf("Test Free DHCP Failed :(\n");
	}

	state = TestDHCPIsAllTaken();

	if(SUCCESS == state)
	{
		printf("Test IsAllTaken DHCP Succeed :)\n");
	}
	else
	{
		printf("Test IsAllTaken DHCP Failed :(\n");
	}


	return state;
}

int TestDHCPCreate()
{
	int test_result = SUCCESS;
	ip_ty net_mask = 0xFFFFFF00;
	ip_ty prefix = 0xC0A8A0;
	
	dhcp = DHCPCreate(net_mask, prefix);

	if(NULL == dhcp)
	{
		test_result = FAIL;
	}

	DHCPDestroy(dhcp);

	return test_result;
}

int TestDHCPAlloc()
{
	int test_result = SUCCESS;
	ip_ty net_mask = 0xFFFFFF00;/*255.255.255.0*/
	ip_ty prefix = 0xC0A80A0;/*192.168.10.0*/
	ip_ty ip = 0xC0A80A0;/*192.168.10.0*/
	ip_ty ip2 = 0xC0A80A1;/*192.168.10.0*/
	
	dhcp = DHCPCreate(net_mask, prefix);
	/*printf("%lu\n",DHCPCountFree(dhcp));*/

	ip = DHCPAlloc(dhcp, ip);
	ip2 = DHCPAlloc(dhcp, ip2);

	/*printf("%lu\n", ip);
	printf("%lu\n", ip2);*/

	if(251 != DHCPCountFree(dhcp))
	{
		test_result = FAIL;
	}

	DHCPDestroy(dhcp);

	return test_result;
}

int TestDHCPFree()
{
	int test_result = SUCCESS;
	ip_ty net_mask = 0xFFFFFF00;/*255.255.255.0*/
	ip_ty prefix = 0xC0A80A0;/*192.168.10.0*/
	ip_ty ip = 0xC0A80A0;/*192.168.10.0*/
	ip_ty ip2 = 0xC0A80A1;/*192.168.10.0*/
	
	dhcp = DHCPCreate(net_mask, prefix);

	ip = DHCPAlloc(dhcp, ip);
	ip2 = DHCPAlloc(dhcp, ip2);

	DHCPFreeIP(dhcp, ip);

	if(252 != DHCPCountFree(dhcp))
	{
		test_result = FAIL;
	}

	DHCPDestroy(dhcp);

	return test_result;
}

int TestDHCPIsAllTaken()
{
	int test_result = SUCCESS;
	ip_ty net_mask = 0xFFFFFF00;/*255.255.255.0*/
	ip_ty prefix = 0xC0A80A0;/*192.168.10.0*/
	ip_ty ips[256] = {0xC0A80A0, 0};
	size_t i = 0;

	dhcp = DHCPCreate(net_mask, prefix);

	if(0 != DHCPIsAllTaken(dhcp))
	{
		test_result = FAIL;
	}

	for ( i = 0; i < 253; ++i)
	{
		ips[i] = DHCPAlloc(dhcp, ips[0]);
	}

	if(1 != DHCPIsAllTaken(dhcp))
	{
		test_result = FAIL;
	}

	/*for ( i = 0; i < 256; ++i)
	{
		printf("%lu \n", ips[i]);
	}*/

	DHCPDestroy(dhcp);

	return test_result;
}