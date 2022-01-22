#include "MemoryPool.h"
#include <assert.h>


/**
 * @brief get the offset of mr
 * 
 * @param mp 
 * @param mr 
 * @return uint32 
 */
static uint32 _getMRoffset (MemoryPool_t* mp, MemoryRecord_t* mr)
{
    assert( NULL != mp );
    assert( NULL != mr );

    return (u8*)mr - mp->base;
}

/**
 * @brief Find Next one of f0
 * 
 * @param mp 
 * @param f0 
 * @return MemoryRecord_t* 
 */
static MemoryRecord_t* _getNext (MemoryPool_t* mp, MemoryRecord_t* f0)
{
    assert( NULL != mp );
    assert( NULL != f0 );
    if (0 == f0->next)
    {
        return NULL;
    }
    MemoryRecord_t* Next = (MemoryRecord_t*)(mp->base + f0->next);

    return Next;
}

/**
 * @brief Find the previous one of f0
 * 
 * @param mp 
 * @param root 
 * @param f0 
 * @return MemoryRecord_t* 
 */
static MemoryRecord_t* _getPrev (MemoryPool_t* mp, MemoryRecord_t* root, MemoryRecord_t* f0)
{
    assert( NULL != mp);
    assert( NULL != f0);
    assert( NULL != root);

    MemoryRecord_t* fPrev = root;
    const uint32 offset = _getMRoffset(mp, f0);
    while(fPrev->next != offset)
    {
        fPrev = _getNext(mp,fPrev);
        if (NULL == fPrev)
        {
            return NULL;
        }
    }//while
    return fPrev;

}

/**
 * @brief Return the memory of f0
 * 
 * @param f0 
 * @return void* 
 */
static void* _getMemoryPtr(MemoryRecord_t* f0)
{
    assert( NULL != f0);
    assert( f0->size > 0);

    return (u8*)f0 + sizeof(MemoryRecord_t);
}

/**
 * @brief Split the f0 into two memory recorders. The first one's size is 'size'
 * 
 * @param mp 
 * @param f0 
 * @param size 
 * @return MemoryRecord_t* New memory recorder 
 */
static MemoryRecord_t* _split (MemoryPool_t* mp,MemoryRecord_t* f0,uint32 size)
{
    assert( NULL != mp );
    assert( NULL != f0 );
    assert( 0 != size);
    assert( f0->size > size + sizeof(MemoryRecord_t));

    MemoryRecord_t* f1 = (MemoryRecord_t*)((u8*)f0 + sizeof(MemoryRecord_t) + size);

    f1->next = f0->next;
    f0->next = _getMRoffset(mp, f1);
    f1->size = f0->size - size - sizeof(MemoryRecord_t);
    f0->size = size;

    return f1;
}

/**
 * @brief Remove f0 from the list named root
 * 
 * @param mp 
 * @param root 
 * @param f0 
 * @return MemoryRecord_t* root if successful, NULL if failed.
 */
static MemoryRecord_t* _remove(MemoryPool_t* mp, MemoryRecord_t* root, MemoryRecord_t* f0)
{
    assert( NULL != mp);
    assert( NULL != root);
    assert( NULL != f0);

    if(root == f0)
    {
        MemoryRecord_t* newRoot = _getNext(mp, root);
        f0->next = 0;
        return newRoot;
    }

    MemoryRecord_t* fPrev = root;
    const uint32 offset = _getMRoffset(mp, f0);
    while(fPrev->next != offset)
    {
        fPrev = _getNext(mp,fPrev);
        if (NULL == fPrev)
        {
            return NULL;
        }
    }//while

    fPrev->next = f0->next;
    f0->next = 0;

    return root;
}

/**
 * @brief Determine where p is to be inserted in root
 * 
 * @param mp 
 * @param root 
 * @param p 
 * @return MemoryRecord_t* f0 is p's prev memory at the location to be inserted
 */
static MemoryRecord_t* _findPrevMR (MemoryPool_t* mp, MemoryRecord_t* root, MemoryRecord_t* p)
{
    assert( NULL != mp);
    assert( NULL != root);
    assert( NULL != p);

    MemoryRecord_t* f0 = root;
    MemoryRecord_t* f1 = root;
    uint32 p0 = _getMRoffset(mp, p);
    if (p0 <= _getMRoffset(mp, f1))
    {
        return NULL;
    }
    while (p0 > _getMRoffset(mp, f1))
    {
        f0 = f1;
        f1 = _getNext(mp, f1);
        if (NULL == f1)
        {
            return f0;
        }
    }//while
    
    return f0;
}

/**
 * @brief Insert a_f into root in order
 * 
 * @param mp 
 * @param root 
 * @param a_f 
 * @return MemoryRecord_t* root is succeed,NULL is failed
 */
static MemoryRecord_t* _InsertMR (MemoryPool_t* mp, MemoryRecord_t* root, MemoryRecord_t* a_f)
{
    assert( NULL != mp);
    assert( NULL != a_f);

    if (NULL == root)
    {
        root = a_f;
        return root;
    }
    MemoryRecord_t* f0 = _findPrevMR(mp, root, a_f);
    
    if (NULL == f0)
    {
        a_f->next = _getMRoffset(mp, root);
        root = a_f;

        return root;
    }
    if (0 != f0->next)
    {
        a_f->next = f0->next;
    }
    f0->next = _getMRoffset(mp, a_f);

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
                    _getMRoffset(mp, mr), mr->size, mr->next, _getMemoryPtr(mr));
            mr = _getNext(mp, mr);
        }
    }
}

void printMemoryPool(const MemoryPool_t* mp)
{
    assert (NULL != mp);
    printf("Memory Pool [base = %lu], [size = %d]:\n", mp->base, mp->size);
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
        printf("Invalid mp or size!\n");
        return NULL;
    }
    if(NULL == mp->freed)
    {
        return NULL;
    }
    MemoryRecord_t* f0 = mp->freed; 

    while (f0->size < size)
    {
        f0 = _getNext(mp, f0);
        if (NULL == _getNext(mp, f0))
        {
            printf("Not enough memory!\n");
            return NULL;
        }
    } //while

    if (size + sizeof(MemoryRecord_t) < f0->size) 
    {   
        _split(mp, f0 ,size);
    }

    mp->freed = _remove(mp, mp->freed, f0);

    mp->allocated = _InsertMR(mp, mp->allocated, f0);

    return _getMemoryPtr(f0); 
}

void _free(MemoryPool_t* mp,void* p)
{
    if (NULL == mp || NULL == p || NULL == mp->allocated || NULL == mp->freed)
    {
        printf("Invalid mp or p!\n");
        return;
    }
    MemoryRecord_t* p0 = mp->allocated;
    while (p != _getMemoryPtr(p0))
    {
        p0 = _getNext(mp, p0);
        if (NULL == p0)
        {
            printf("The memory is not in the allocation!\n");
            return;
        }
    }//while
    mp->allocated = _remove(mp, mp->allocated, p0);
    MemoryRecord_t* f1 = _findPrevMR(mp, mp->freed, p0); 
    if (NULL == f1)
    {
        if (mp->freed == (MemoryRecord_t*)((u8*)p0 + sizeof(MemoryRecord_t) + p0->size))
        {
            p0->size = p0->size + sizeof(MemoryRecord_t) + mp->freed->size;
            p0->next = mp->freed->next;
        }
        else
        {
            p0->next = _getMRoffset(mp, mp->freed);
        }
        mp->freed = p0;

        return;
    }

    if (0 != f1->next)
    {
        MemoryRecord_t* f2 = _getNext(mp, f1);
        if (f2 == (MemoryRecord_t*)((u8*)p0 + sizeof(MemoryRecord_t) + p0->size))
        {
            mp->freed = _remove(mp, mp->freed, f2);
            p0->size = p0->size + sizeof(MemoryRecord_t) + f2->size;
        }
    }
    if (p0 == (MemoryRecord_t*)((u8*)f1 + sizeof(MemoryRecord_t) + f1->size))
    {
        mp->freed = _remove(mp, mp->freed, f1);
        f1->size = f1->size + sizeof(MemoryRecord_t) + p0->size;
        p0 = f1;
    }
    mp->freed = _InsertMR(mp, mp->freed, p0);

    return;

}
