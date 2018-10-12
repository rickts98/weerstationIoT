#ifndef ethernet_h
#define ethernet_h
#include <stdint.h>

typedef unsigned char (*availableFunc)();
typedef int32_t (*peekFunc)();
typedef long int (*readFunc)();

void ethernetSetup(availableFunc Func, peekFunc peekFunc, readFunc readFunc);

unsigned char available();
int32_t peek1();
long int read1();

#endif