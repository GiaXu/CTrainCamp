#include "MemoryPool.h"
#include <assert.h>


/**
 * @brief get the offset of mr
 * 
 * @param mp 
 * @param mr 
 * @return uint32 
 */
static uint32 _getMRoffset (const MemoryPool_t* mp, const MemoryRecord_t* mr)
{
    assert( NULL != mp );
    assert( NULL != mr );

    return (u8*)mr - mp->base;
}

/**
 * @brief Find Next one of f0
 * 
 * @param mp 
 * @param mr
 * @return MemoryRecord_t* 
 */
static MemoryRecord_t* _getNext (const MemoryPool_t* mp, const MemoryRecord_t* mr)
{
    assert( NULL != mp );
    assert( NULL != mr );
    if (0 == mr->next)
    {
        return NULL;
    }
    MemoryRecord_t* aNext = (MemoryRecord_t*)(mp->base + mr->next);

    return aNext;
}

/**
 * @brief Find the previous one of f0
 * 
 * @param mp 
 * @param root 
 * @param mr
 * @return MemoryRecord_t* 
 */
static MemoryRecord_t* _getPrev (const MemoryPool_t* mp, 
                                 const MemoryRecord_t* root, 
                                 const MemoryRecord_t* mr)
{
    assert( NULL != mp);
    assert( NULL != mr);
    assert( NULL != root);

    const MemoryRecord_t* aPrev = root;
    const uint32 offset = _getMRoffset(mp, mr);
    while(NULL != aPrev && aPrev->next != offset)
    {
        aPrev = _getNext(mp,aPrev);
    }//while

    return (MemoryRecord_t*)aPrev;
}

/**
 * @brief Return the memory of f0
 * 
 * @param mr 
 * @return void* 
 */
static void* _getMemoryPtr(const MemoryRecord_t* mr)
{
    assert( NULL != mr);
    assert( mr->size > 0);

    return (u8*)mr + sizeof(MemoryRecord_t);
}

/**
 * @brief Split the f0 into two memory recorders. The first one's size is 'size'
 * 
 * @param mp 
 * @param mr 
 * @param size 
 * @return MemoryRecord_t* New memory recorder 
 */
static MemoryRecord_t* _split (MemoryPool_t* mp,MemoryRecord_t* mr,uint32 size)
{
    assert( NULL != mp );
    assert( NULL != mr );
    assert( 0 != size);
    assert( mr->size > size + sizeof(MemoryRecord_t));

    MemoryRecord_t* amr = (MemoryRecord_t*)((u8*)mr + sizeof(MemoryRecord_t) + size);

    amr->next = mr->next;
    mr->next = _getMRoffset(mp, amr);
    amr->size = mr->size - size - sizeof(MemoryRecord_t);
    mr->size = size;

    return amr;
}

/**
 * @brief Remove f0 from the list named root
 * 
 * @param mp 
 * @param root 
 * @param mr
 * @return MemoryRecord_t* root if successful, NULL if failed.
 */
static MemoryRecord_t* _remove(MemoryPool_t* mp, MemoryRecord_t* root, MemoryRecord_t* mr)
{
    assert( NULL != mp);
    assert( NULL != root);
    assert( NULL != mr);

    if(root == mr)
    {
        MemoryRecord_t* newRoot = _getNext(mp, root);
        mr->next = 0;
        return newRoot;
    }

    MemoryRecord_t* aPrev = _getPrev(mp, root, mr);
    aPrev->next = mr->next;
    mr->next = 0;

    return root;
}

/**
 * @brief Determine where p is to be inserted in root
 *  // FIXME: Determine where p can be inserted in root.
 * @param mp 
 * @param root 
 * @param p 
 * @return MemoryRecord_t* f0 is p's prev memory at the location to be inserted
 */
static MemoryRecord_t* _findPrevMR (const MemoryPool_t* mp, const MemoryRecord_t* root, const MemoryRecord_t* p)
{
    assert( NULL != mp);
    assert( NULL != root);
    assert( NULL != p);

    uint32 ap0 = _getMRoffset(mp, p);
    if (ap0 <= _getMRoffset(mp, root))
    {
        return NULL;
    }
    const MemoryRecord_t* aMr = root;
    const MemoryRecord_t* aMrLast = aMr;
    while (ap0 > _getMRoffset(mp, aMrLast))
    {
        aMr = aMrLast;
        aMrLast = _getNext(mp, aMrLast);
        if (NULL == aMrLast)
        {
            // p0 will append to the list.
            return (MemoryRecord_t*)aMr;
        }
    }//while
    
    return (MemoryRecord_t*)aMr;
}

/**
 * @brief Insert a_f into root in order
 * 
 * @param mp 
 * @param root 
 * @param mr
 * @return MemoryRecord_t* root is succeed,NULL is failed
 */
static MemoryRecord_t* _insert (MemoryPool_t* mp, MemoryRecord_t* root, MemoryRecord_t* mr)
{
    assert( NULL != mp);
    assert( NULL != mr);

    if (NULL == root)
    {
        root = mr;
        return root;
    }
    MemoryRecord_t* amr = _findPrevMR(mp, root, mr);
    
    if (NULL == amr)
    {
        mr->next = _getMRoffset(mp, root);
        return mr;
    }
    if (0 != amr->next)
    {
        mr->next = amr->next;
    }
    amr->next = _getMRoffset(mp, mr);

    return root;
}

static void _printList(const MemoryPool_t* mp, const MemoryRecord_t* mr)
{
    assert( NULL != mp);
    if (NULL == mr)
    {
        printf("NULL\n");
    }
    else
    {
        while (NULL != mr)
        {
            printf("[offset = %d],[size = %d], [next = %d], [pointer = %lu]\n",
                    _getMRoffset(mp, mr), mr->size, mr->next, (unsigned long)_getMemoryPtr(mr));
            mr = _getNext(mp, mr);
        }
    }
}

void printMemoryPool(const MemoryPool_t* mp)
{
    assert (NULL != mp);
    printf("Memory Pool [base = %lu], [size = %d]:\n", (unsigned long)mp->base, (unsigned int)mp->size);
    printf("Allocated List : \n");
    _printList(mp, mp->allocated);
    printf("Freed List : \n");
    _printList(mp, mp->freed);
    printf("---- end ---- \n");
}


void initMemoryPool (MemoryPool_t *mp,uint32 size)
{
    if (NULL == mp)
    {
        return;
    }
    mp->base = malloc(size);
    mp->size = size;

    mp->allocated = NULL;

    mp->freed = (MemoryRecord_t*)(mp->base); 
    mp->freed->next = 0;
    mp->freed->size = size -  sizeof(MemoryRecord_t);

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
    mp->allocated = NULL;
    mp->freed = NULL;

    return;
}

void* _alloc (MemoryPool_t* mp, uint32 size)
{
    if (NULL == mp || 0 == size)
    {
        printf("Invalid memory pool or size!\n");
        return NULL;
    }
    if(NULL == mp->freed)
    {
        printf("The memory pool is full!\n");
        return NULL;
    }
    MemoryRecord_t* amr = mp->freed; 

    while (amr->size < size)
    {
        amr = _getNext(mp, amr);
        if (NULL == _getNext(mp, amr))
        {
            printf("Not enough memory!\n");
            return NULL;
        }
    } //while

    if (size + sizeof(MemoryRecord_t) < amr->size) 
    {   
        _split(mp, amr ,size);
    }

    mp->freed = _remove(mp, mp->freed, amr);

    mp->allocated = _insert(mp, mp->allocated, amr);

    return _getMemoryPtr(amr); 
}

void _free(MemoryPool_t* mp,void* p)
{
    if (NULL == mp || NULL == p || NULL == mp->allocated || NULL == mp->freed)
    {
        printf("Invalid memory pool or pointer!\n");
        return;
    }
    
    MemoryRecord_t* amr = mp->allocated;
    while (NULL != amr && p != _getMemoryPtr(amr))
    {
        amr = _getNext(mp, amr);
        
    }//while

    if (NULL == amr)
    {
        printf("The memory is not in the allocation!\n");
        return;
    }
    mp->allocated = _remove(mp, mp->allocated, amr);

    MemoryRecord_t* amrPrev = _findPrevMR(mp, mp->freed, amr); 
    if (NULL == amrPrev)
    {
        if (mp->freed == (MemoryRecord_t*)((u8*)amr + sizeof(MemoryRecord_t) + amr->size))
        {
            // merge the freed mr with the first node in the free list.
            amr->size = amr->size + sizeof(MemoryRecord_t) + mp->freed->size;
            amr->next = mp->freed->next;
        }
        else
        {
            amr->next = _getMRoffset(mp, mp->freed);
        }
        mp->freed = amr;

        return;
    }

    if (0 != amrPrev->next) // if amrPrev is NOT the last node of the free list
    {
        MemoryRecord_t* amrLast = _getNext(mp, amrPrev);
        if (amrLast == (MemoryRecord_t*)((u8*)amr + sizeof(MemoryRecord_t) + amr->size))
        {
            mp->freed = _remove(mp, mp->freed, amrLast);
            amr->size = amr->size + sizeof(MemoryRecord_t) + amrLast->size;
        }
    }

    if (amr == (MemoryRecord_t*)((u8*)amrPrev + sizeof(MemoryRecord_t) + amrPrev->size))
    {
        mp->freed = _remove(mp, mp->freed, amrPrev);
        amrPrev->size = amrPrev->size + sizeof(MemoryRecord_t) + amr->size;
        amr = amrPrev;
    }

    mp->freed = _insert(mp, mp->freed, amr);

    return;

}
