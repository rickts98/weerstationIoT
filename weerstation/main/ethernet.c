#include "ethernet.h"
#include <stdint.h>

availableFunc func;
peekFunc peek;
readFunc read;


void ethernetSetup(availableFunc Func, peekFunc peekFunc, readFunc readFunc) {
    func = Func;
    peek = peekFunc;
    read = readFunc;
}

unsigned char available(){
    if(func){
        return func();
    }
}

int32_t peek1() {
    if(peek){
        return peek();
    }
}

long int read1() {
    if(read){
        return read();
    }
}

