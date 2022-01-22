#include "MemoryPool.h"

int main()
{
    MemoryPool_t mp = EMPTY_MEMORY_POOL;
    initMemoryPool(&mp,1024);
    printMemoryPool(&mp);

    u8* p = _alloc(&mp, 10);
    u8* a = _alloc(&mp, 10);
    u8* b = _alloc(&mp, 50);
    u8* c = _alloc(&mp, 10);

    printMemoryPool(&mp);

    _free(&mp, b);
    printMemoryPool(&mp);

    u8* x = _alloc(&mp, 20);
    printMemoryPool(&mp);

    _free(&mp, x);
    printMemoryPool(&mp);

    _free(&mp, p);
    printMemoryPool(&mp);

    _free(&mp, a);
    printMemoryPool(&mp);
    
    _free(&mp, c);
    printMemoryPool(&mp);

    destroyMemoryPool(&mp);
    printMemoryPool(&mp);
    return 0;
}