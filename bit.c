#include <stdio.h>
#include "bit.h"

unsigned int SetBit(unsigned int value, int position){
    if(position < 0 || position >= 32) return value;
    return value | (1U << position);
}

unsigned int ClearBit(unsigned int value, int position){
    if(position < 0 || position >= 32) return value;
    return value & ~(1U << position);
}

unsigned int ToggleBit(unsigned int value, int position){
    if(position < 0 || position >= 32) return value;
    return value ^ (1U << position);
}

int GetBit(unsigned int value, int position){
    if(position < 0 || position >= 32) return 0;
    return !!(value & (1U << position));
}

int CountBits(unsigned int value){
    return __builtin_popcount(value);
}

unsigned int ShiftLeft(unsigned int value, int positions){
    if(positions < 0) return ShiftRight(value, -positions);
    if(positions >= 32) return 0;
    return value << positions;
}

unsigned int ShiftRight(unsigned int value, int positions){
    if(positions < 0) return ShiftLeft(value, -positions);
    if(positions >= 32) return 0;
    return value >> positions;
}

void PrintBinary(unsigned int value){
    for(int i = 31; i >= 0; --i){
        putchar((value >> i) & 1U ? '1' : '0');
        if(i % 8 == 0) putchar(' ');
    }
    putchar('\n');
}

void PrintHex(unsigned int value){
    printf("0x%08X\n", value);
}
