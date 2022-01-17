#ifndef __MEMORY_POOL_H__

#include <stdlib.h>

typedef unsigned int uint32;
typedef unsigned char u8;

struct MemoryPool_s
{
    u8* base;
    uint32 size;
};

typedef struct MemoryPool_s MemoryPool_t;

void initMemoryPool(MemoryPool_t *mp,uint32 size);
void destroyMemoryPool(MemoryPool_t *mp);

#endif  //__MEMORY_POOL_H__
