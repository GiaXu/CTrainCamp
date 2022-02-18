#include "MemoryPool.hpp"


MemoryPool::MemoryPool(uint32 size)
{
    initMemoryPool(&m_mp,size);
}

MemoryPool::~MemoryPool()
{
    destroyMemoryPool(&m_mp);
}

void* MemoryPool::alloc(uint32 size)
{
   return _alloc(&m_mp,size);
}

void MemoryPool::free(void* p)
{
    _free(&m_mp, p);
}

void MemoryPool::output()
{
    printMemoryPool(&m_mp);
}

