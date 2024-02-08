#include <stdio.h> /*printf*/
#include <string.h> /*strcmp*/

#include "bitarray.h"

enum Boolean {EQUAL};
enum State {SUCCESS,FAIL};

static int Runner();

static int testSetAll();
static int testResetAll();
static int testSetOn();
static int testSetOff();
static int testSetBit();
static int testGetValue();
static int testFlip();
static int testByteMirror();
static int testMirrorLUT();
static int testRotateRight();
static int testRotateLeft();
static int testCountOnBits();
static int testCountOnBitsLUT();
static int testCountOffBits();
static int testToString();
static int testIsBitOff();

int main() 
{
	int state = SUCCESS;
	state = Runner();
    return state;
}

int Runner()
{
	int state = SUCCESS;

	state = testSetAll();

	if(SUCCESS == state)
	{
		printf("Test SetAll Passed\n");
	}
	else
	{
        printf("Test SetAll Failed\n");
	}

	state = testResetAll();

	if(SUCCESS == state)
	{
		printf("Test ResetAll Passed\n");
	}
	else
	{
        printf("Test ResetAll Failed\n");
	}

	state = testSetOn();

	if(SUCCESS == state)
	{
		printf("Test SetOn Passed\n");
	}
	else
	{
        printf("Test SetOn Failed\n");
	}

	state = testSetOff();

	if(SUCCESS == state)
	{
		printf("Test SetOff Passed\n");
	}
	else
	{
        printf("Test SetOff Failed\n");
	}

	state = testSetBit();

	if(SUCCESS == state)
	{
		printf("Test SetBit Passed\n");
	}
	else
	{
        printf("Test SetBit Failed\n");
	}

	state = testGetValue();

	if(SUCCESS == state)
	{
		printf("Test GetValue Passed\n");
	}
	else
	{
        printf("Test GetValue Failed\n");
	}

	state = testFlip();

	if(SUCCESS == state)
	{
		printf("Test Flip Passed\n");
	}
	else
	{
        printf("Test Flip Failed\n");
	}

	state = testByteMirror();

	if(SUCCESS == state)
	{
		printf("Test Mirror Passed\n");
	}
	else
	{
        printf("Test Mirror Failed\n");
	}

	state = testMirrorLUT();

	if(SUCCESS == state)
	{
		printf("Test Mirror LUT Passed\n");
	}
	else
	{
        printf("Test Mirror LUT Failed\n");
	}

	state = testRotateRight();

	if(SUCCESS == state)
	{
		printf("Test Rotate Right Passed\n");
	}
	else
	{
        printf("Test Rotate Right Failed\n");
	}

	state = testRotateLeft();

	if(SUCCESS == state)
	{
		printf("Test Rotate Left Passed\n");
	}
	else
	{
        printf("Test Rotate Left Failed\n");
	}

	state = testCountOnBits();

	if(SUCCESS == state)
	{
		printf("Test CountOn Passed\n");
	}
	else
	{
        printf("Test CountOn Failed\n");
	}

	state = testCountOnBitsLUT();

	if(SUCCESS == state)
	{
		printf("Test CountOnLUT Passed\n");
	}
	else
	{
        printf("Test CountOnLUT Failed\n");
	}

	state = testCountOffBits();

	if(SUCCESS == state)
	{
		printf("Test CountOff Passed\n");
	}
	else
	{
        printf("Test CountOff Failed\n");
	}

	state = testToString();

	if(SUCCESS == state)
	{
		printf("Test ToString Passed\n");
	}
	else
	{
        printf("Test ToString Failed\n");
	}

	state = testIsBitOff();

	if(SUCCESS == state)
	{
		printf("Test IsBitOff Passed\n");
	}
	else
	{
        printf("Test IsBitOff Failed\n");
	}

	return SUCCESS;
}

int testSetAll() 
{
    bitarr_ty bit_array = 0;
    int is_test_successful = SUCCESS; 
    bitarr_ty expected = 0xFFFFFFFFFFFFFFFF;
    bitarr_ty result = 0;

    result = SetAll(bit_array);

    if(result != expected)
    {
    	is_test_successful = FAIL;
    }

    return is_test_successful;
}

int testResetAll()
{
    bitarr_ty bit_array = 0x54874;
    int is_test_successful = SUCCESS; 
    bitarr_ty expected = 0;
    bitarr_ty result = 0;
    
    result = ResetAll(bit_array);

    if(result != expected)
    {
    	is_test_successful = FAIL;
    }

    return is_test_successful;
}

int testSetOn()
{
    bitarr_ty bit_array = 0x54874;
    int is_test_successful = SUCCESS; 
    bitarr_ty expected = 0x5487C; 
    bitarr_ty result = 0;

    result = SetOn(bit_array, 3); 

    if (result != expected)
    {
        is_test_successful = FAIL;
    }

    return is_test_successful;
}

int testSetOff()
{
    bitarr_ty bit_array = 0x5487C;
    int is_test_successful = SUCCESS;
    bitarr_ty expected = 0x54874; 
    bitarr_ty result = 0;

    result = SetOff(bit_array, 3); 

    if (result != expected)
    {
        is_test_successful = FAIL;
    }

    return is_test_successful;
}

int testSetBit()
{
    bitarr_ty bit_array = 0x5487C;
    int is_test_successful = SUCCESS;
    bitarr_ty expected = 0x54874; 
    bitarr_ty result = 0;

    result = SetBit(bit_array, 3, OFF); 

    if (result != expected)
    {
        is_test_successful = FAIL;
    }

    return is_test_successful;
}

int testGetValue()
{
    bitarr_ty bit_array = 0x54874;
    int is_test_successful = SUCCESS;
    int expected = ON; 
    int result = 0;

    result = GetVal(bit_array, 2);

    if (result != expected)
    {
        is_test_successful = FAIL;
    }

    return is_test_successful;
}

int testFlip()
{
    bitarr_ty bit_array = 0x54874;
    int is_test_successful = SUCCESS;
    bitarr_ty expected = 0x54870;
    bitarr_ty result = 0;

    result = bit_array; 
    result = FlipBit(bit_array,2); 

    if (result != expected)
    {
        is_test_successful = FAIL;
    }

    return is_test_successful;
}

int testByteMirror() 
{
    bitarr_ty originalValue = 0x3;
    int is_test_successful = SUCCESS;
    bitarr_ty expected = 0xC000000000000000; 
    bitarr_ty result = Mirror(originalValue);

    if (result != expected) 
    {
        is_test_successful = FAIL;
    }

    return is_test_successful;
}

int testMirrorLUT()
{
	bitarr_ty originalValue = 0x3;
    int is_test_successful = SUCCESS;
    bitarr_ty expected = 0xC000000000000000; 
    bitarr_ty result = MirrorLUT(originalValue);

    if (result != expected) 
    {
        is_test_successful = FAIL;
    }

    return is_test_successful;
}

int testRotateRight()
{
	bitarr_ty originalValue = 0xC000000000000000;
    int is_test_successful = SUCCESS;
    bitarr_ty expected = 0x3;
    bitarr_ty result = RotateRight(originalValue, 62); 

    if (result != expected)
    {
        is_test_successful = FAIL;
    }

    return is_test_successful;
}

int testRotateLeft()
{
	bitarr_ty originalValue = 0xC000000000000000;
    int is_test_successful = SUCCESS;
    bitarr_ty expected = 0x3;
    bitarr_ty result = RotateLeft(originalValue, 2); 

    if (result != expected)
    {
        is_test_successful = FAIL;
    }

    return is_test_successful;
}

int testCountOnBits()
{
	bitarr_ty input = 0x557A1; 
    size_t expected = 10; 
    int is_test_successful = SUCCESS;

    size_t result = CountOn(input);

    if (result != expected) 
    {
         is_test_successful = FAIL;
    }

    return is_test_successful;
}

int testCountOnBitsLUT()
{
	bitarr_ty input = 0x557A1; 
    size_t expected = 10; 
    int is_test_successful = SUCCESS;

    size_t result = CountOnLUT(input);

    if (result != expected) 
    {
         is_test_successful = FAIL;
    }

    return is_test_successful;
}

int testCountOffBits()
{
	bitarr_ty input = 0x557A1; 
    size_t expected = 54; 
    int is_test_successful = SUCCESS;

    size_t result = CountOff(input);

    if (result != expected) 
    {
         is_test_successful = FAIL;
    }

    return is_test_successful;
}

int testToString()
{
	char string[65];
	bitarr_ty input = 0xA1; 
    int is_test_successful = SUCCESS;
    char *expected = "0000000000000000000000000000000000000000000000000000000010100001";

    ToString(input,string);

    if(EQUAL != strcmp(string,expected))
    {
    	is_test_successful = FAIL;
    }

    return is_test_successful;
}

int testIsBitOff()
{
	bitarr_ty input = 0xA; 
    size_t expected = 1; 
    int is_test_successful = SUCCESS;

    size_t result = IsBitOff(input,3);

    if (result != expected) 
    {
         is_test_successful = FAIL;
    }

    return is_test_successful;
}