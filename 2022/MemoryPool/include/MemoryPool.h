#ifndef __MEMORY_POOL_H__

#include <stdlib.h>
#include <stdio.h>

#define EMPTY_MEMORY_POOL {NULL, 0,NULL,NULL}

typedef unsigned int uint32;
typedef unsigned char u8;

typedef struct 
{
    uint32 size;
    uint32 next;
}MemoryRecord_t;

typedef struct 
{
    u8* base;
    uint32 size;
    MemoryRecord_t* allocated;
    MemoryRecord_t* freed;
}MemoryPool_t;


void initMemoryPool (MemoryPool_t* mp, uint32 size);
void destroyMemoryPool (MemoryPool_t* mp);
void* _alloc (MemoryPool_t* mp, uint32 size);
void _free (MemoryPool_t* mp, void* p);

#endif  //__MEMORY_POOL_H__
