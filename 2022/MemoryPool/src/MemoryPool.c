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
 * @brief Find Next MR_T
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

    return (MemoryRecord_t*)(mp->base + f0->next);
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
 * @brief Insert a_f at the end of mr
 * 
 * @param mp 
 * @param mr 
 * @param a_f 
 * @return MemoryRecord_t* a_f if successful, NULL if failure
 */
static MemoryRecord_t* _insert (MemoryPool_t* mp, MemoryRecord_t* root, MemoryRecord_t* a_f)
{
    assert( NULL != mp);
    assert( NULL != a_f);

    if (NULL == root)
    {
        return a_f;
    }

    MemoryRecord_t* _aLast = root;

    while(0 != _aLast->next)
    {
        _aLast = _getNext(mp, _aLast);
    }
    _aLast->next = _getMRoffset(mp, a_f);

    return root;
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
    mp->allocated = _insert(mp, mp->allocated, f0);

    return _getMemoryPtr(f0);
}

void _free(MemoryPool_t* mp,void* p)
{
    if (NULL == mp)
    {
        return;
    }

}
