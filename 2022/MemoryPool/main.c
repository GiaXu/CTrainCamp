#include "MemoryPool.h"

int main()
{
    MemoryPool_t mp;
    initMemoryPool(&mp,1024);
    destroyMemoryPool(&mp);
    return 0;
}