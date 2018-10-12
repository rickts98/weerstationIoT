#include <Ethernet.h>
extern "C"
{
#include "ethernet.h"
}
#include <stdint.h>

EthernetClient client;

unsigned char ethernetAvailable()
{
    client = server.available();
    if (client.available())
    {
        return 1;
    }
    else
        return 0;
}

long int ethernetRead() {
    return client.read();
}

int32_t ethernetPeek() {
    return client.Peek();
}


