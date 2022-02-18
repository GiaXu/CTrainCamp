//#include "MemoryPool.h"
//#include "MemoryPool.hpp"
#include "QuickSort.h"

int main()
{
    /**
    MemoryPool aPool(1024);

    void* p0 = aPool.alloc(10);
    void* p1 = aPool.alloc(10);
    void* p2 = aPool.alloc(50);
    void* p3 = aPool.alloc(10);
    aPool.output();

    aPool.free(p1);
    aPool.output();

    aPool.free(p3);
    aPool.output();

    aPool.free(p0);
    aPool.output();

    aPool.free(p2);
    aPool.output();

    aPool.~MemoryPool();
*/
    
    /**
    MemoryPool_t mp = EMPTY_MEMORY_POOL;
    initMemoryPool(&mp,1024);
    printMemoryPool(&mp);

    u8* p = static_cast<u8*>(_alloc(&mp, 10));
    
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
    */
    MemoryPool_t mp = EMPTY_MEMORY_POOL;
    initMemoryPool(&mp, 1024);
    printMemoryPool(&mp);

    int a[7] = {49, 38, 65, 97, 76, 13, 27};
    int i = 0;
    for (i = 0; i < 7; ++i)
    {
        printf("%d, ",a[i]);
    }

    printf("\n------link-------\n");

    Node_t* pHead = creatNode(&mp);
    pHead->value = a[0];
    for (i = 1; i < 7; ++i)
    {
        Node_t* p = creatNode(&mp);
        p->value = a[i];
        pHead = addANode(pHead, p);
    }
    listRecords(pHead);

    int offset = length(pHead);
    Node_t* pHight = seek(pHead, offset);
    QuickSort(pHead, pHight);
    printf("\n-----Sorted:--------\n");
    /*
    while (NULL != pHead->left)
    {
        pHead = pHead->left;
    }
    */
    pHead = getpHead(pHead);
    
    listRecords(pHead);
    
    destroyMemoryPool(&mp);
    return 0;
}