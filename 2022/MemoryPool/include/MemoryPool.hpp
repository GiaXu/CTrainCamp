#ifndef __MEMORY_POOL_HPP__
#define __MEMORY_POOL_HPP__

#include "MemoryPool.h"

class MemoryPool
{
public:
    explicit MemoryPool(uint32 size);
    ~MemoryPool();

    void* alloc(uint32 size);
    void free(void* p);

    void output();
protected:

private:
    MemoryPool_t m_mp;
}; // class MemoryPool

#endif //__MEMORY_POOL_HPP__