#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

unsigned int SetBit(unsigned int value, int position){
    if(position < 0 || position >= 32){
        return value;
    }
    return value | (1U << position);
}

unsigned int ClearBit(unsigned int value, int position){
    if(position < 0 || position >= 32){
        return value;
    }
    return value & ~(1U << position);
}

unsigned int ToggleBit(unsigned int value, int position){
    if(position < 0 || position >= 32){
        return value;
    }
    return value ^ (1U << position);
}
