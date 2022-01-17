#include "MemoryPool.h"

void initMemoryPool(MemoryPool_t *mp,uint32 size)
{
    if (NULL == mp)
    {
        return;
    }
    mp->base = malloc(size);
    mp->size = size;
    return;
}

void destroyMemoryPool(MemoryPool_t *mp)
{
    if (NULL == mp)
    {
        return;
    }
    if (NULL != mp->base)
    {
        free(mp->base);
        mp->base = NULL;
    }
    mp->size = 0;
    return;
}
