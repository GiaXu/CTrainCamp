#include "MemoryPool.h"

int main()
{
    MemoryPool_t mp = EMPTY_MEMORY_POOL;
    initMemoryPool(&mp,1024);
    destroyMemoryPool(&mp);
    return 0;
}