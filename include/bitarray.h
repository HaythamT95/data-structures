/*****************************************************************************/
/*
Project: Bitarray
Name: Haytham
Reviewer: Shahar
Date: 20.09.2023
Version: 1.0 - Initial
         
*/
/*****************************************************************************/
#ifndef __BITARRAY_H__
#define __BITARRAY_H__

#include <stddef.h> /*size_t*/

#define BYTE 8

enum ON_OFF{OFF, ON};

typedef size_t bitarr_ty;

/*
Explanation: Set all bits to 1
Input: bit array
Return: bit array with all one's
*/
bitarr_ty SetAll(bitarr_ty);

/*
Explanation: Set all bits to 0
Input: bit array
Return: bit array with all zero's
*/
bitarr_ty ResetAll(bitarr_ty);

/*
Explanation: Set bit at position to 1
Input: bit array, position
Return: bit array
*/
bitarr_ty SetOn(bitarr_ty, size_t);

/*
Explanation: Set bit at position to 0
Input: bit array, position
Return: bit array
*/
bitarr_ty SetOff(bitarr_ty, size_t);

/*
Explanation: Set bit at position to val
Input: bit array, position,val
Return: bit array
*/
bitarr_ty SetBit(bitarr_ty, size_t, int);

/*
Explanation: Get bit at position
Input: bit array, position
Return: unsigned char value [0-1]
*/
int GetVal(bitarr_ty, size_t);

/*
Explanation: Flip all bits
Input: bit array
Return: bit array
*/
bitarr_ty FlipBit(bitarr_ty, size_t);

/*
Explanation: Mirror all bits
Input: bit array
Return: bit array
*/
bitarr_ty Mirror(bitarr_ty);

/*
Explanation: Mirror all bits using lookup table
Input: bit array
Return: bit array
*/
bitarr_ty MirrorLUT(bitarr_ty);

/*
Explanation: Rotate bits right
Input: bit array, number of shifts
Return: bit array
*/
bitarr_ty RotateRight(bitarr_ty, size_t);

/*
Explanation: Rotate bits left
Input: bit array, number of shifts
Return: bit array
*/
bitarr_ty RotateLeft(bitarr_ty, size_t);

/*
Explanation: Count bits that are 1
Input: bit array
Return: Number of set bits
*/
size_t CountOn(bitarr_ty);

/*
Explanation: Count bits that are 1 using lookup table
Input: bit array
Return: Number of set bits
*/
size_t CountOnLUT(bitarr_ty bit_array);

/*
Explanation: Count bits that are 0
Input: bit array
Return: Number of off bits
*/
size_t CountOff(bitarr_ty);

/*
Explanation: Convert bit array to string
Input: bit array
Return: Converted bit array to string
*/
char *ToString(size_t, char*);

/*
Explanation: Check if bit is on or off
Input: bit array, position
Return: on or off
*/
int IsBitOff(bitarr_ty , size_t);

#endif /*__BITARRAY_H__*/