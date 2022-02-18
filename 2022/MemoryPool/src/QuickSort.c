#include "QuickSort.h"
#include "MemoryPool.h"
#include <assert.h>

/**
 * @brief creat a node
 * 
 * @return TNode* 
 */
Node_t* creatNode (MemoryPool_t* mp)
{
    Node_t* p = (Node_t*)(_alloc(mp, sizeof(Node_t)));//TODO: Debug
    p->left = NULL;
    p->right = NULL;
    p->value = 0;

    return p;
}

//maybe no need...
void fillNode (Node_t* p, int value)
{
    if (NULL == p)
    {
        return;
    }
    p->value = value;
}

/**
 * @brief Add a node to the linked list
 * 
 * @param pHead 
 * @param p 
 * @return Node_t* 
 */
Node_t* addANode (Node_t* pHead, Node_t* p)
{
    if (NULL == pHead || NULL == p)
    {
        return NULL;
    }
    Node_t* ap0 = pHead;
    while (NULL != ap0->right)
    {
        ap0 = ap0->right;
    }
    append(ap0, p);
    
    return pHead;
}

/**
 * @brief remove p from the linked list headed by pHead
 * 
 * @param pHead 
 * @param p 
 * @return Node_t* 
 */
Node_t* _remove (Node_t* pHead, Node_t* p)
{
    if (NULL == pHead || NULL == p)
    {
        return NULL;
    }
    if (p == pHead)
    {
        pHead = pHead->right;
        pHead->left = NULL;
        p->right = NULL;
    }
    else
    {
        p->left->right = p->right;
        if (NULL != p->right)
        {
            p->right->left = p->left;
        }
        p->left = NULL;
        p->right = NULL;
    }
    return pHead;
}


/**
 * @brief connect two nodes
 * 
 * @param pPerv 
 * @param pLast 
 */
void append (Node_t* pPrev, Node_t* pLast)
{
    assert (NULL != pPrev);
    assert (NULL != pLast);
    
    pPrev->right = pLast;
    pLast->left = pPrev;

    return;

}

/**
 * @brief Destroy the linked list with pHead as the head pointer
 * 
 * @param pHead 
 */
void destroy (MemoryPool_t mp, Node_t* pHead)
{
    if (NULL == pHead)
    {
        return;
    }

    Node_t *ap = pHead;

    if (NULL != pHead->left)
    {
        pHead->left->right = NULL;
    }

    while (NULL != ap)
    {
        pHead = pHead->right;
        _free(&mp, ap);
        ap = pHead;
    }
    return;
}

/**
 * @brief swap the positions of two nodes
 * 
 * @param pPrev 
 * @param pLast 
 */
void swap (Node_t* pHead, Node_t* p1, Node_t* p2)
{
    if (NULL == pHead || NULL == p1 || NULL == p2)
    {
        return;
    }
    if (p1->right == p2)
    {
        pHead = _remove(pHead, p2);
        _insert(pHead, p1, p2);
        return;
    }
    if (p2->right == p1)
    {
        pHead = _remove(pHead, p1);
        _insert(pHead, p2, p1);
        return;
    }
    Node_t* ap0 = p1->right;
    pHead = _remove(pHead, p1);
    _insert(pHead, p2, p1);
    pHead = _remove(pHead, p2);
    _insert(pHead, ap0, p2);

    return;
}

/**
 * @brief swap two pointers
 * 
 * @param p1 
 * @param p2 
 */
void swappointers (Node_t* p1, Node_t* p2)
{
    if (NULL == p1 || NULL == p2)
    {
        return;
    }
    Node_t* p0 = p1;
    p1 = p2;
    p2 = p0;

    p0 = NULL;

    return;
}

/**
 * @brief Insert pNewNode before pBase, if pBase is NULL, insert pNewNode after pBase
 * 
 * @param pBase 
 * @param pNewNode 
 * @return Node_t* 
 */
Node_t* _insert (Node_t* root, Node_t* pBase, Node_t* pNewNode)
{
    if (NULL == pNewNode)
    {
        return NULL;
    }
    if (NULL == pBase)
    {
        pBase = root;
        while (pBase->right != NULL)
        {
            pBase = pBase->right;
        }//while
        
        pBase->right = pNewNode;
        pNewNode->left = pBase;
        pNewNode->right = NULL;

        return root;
    }
    if (NULL != pBase->left)
    {
        Node_t* aPrev = pBase->left;
        aPrev->right = pNewNode;
        pNewNode->left = aPrev;
    }
    pNewNode->right = pBase;
    pBase->left = pNewNode;

    return root;

}

/**
 * @brief In the linked list with root as the root node, find the node whose value is value
 * 
 * @param root 
 * @param value 
 * @return Node_t* 
 */
Node_t* find (Node_t* root, int value)
{
    assert (NULL != root);

    Node_t* p = root;
    while (p->value != value)
    {
        p = p->right;
        if (NULL == p)
        {
            printf("Did not find!\n");
            return NULL;
        }
    }
    return p;
}

/**
 * @brief In the linked list with root as the root node, seek the offset-th node
 * 
 * @param root 
 * @param offset 
 * @return Node_t* 
 */
Node_t* seek (Node_t* root, int offset)
{
    assert (NULL != root);

    Node_t* p = root;
    while (0 != offset)
    {
        p = p->right;
        --offset;
    }//while

    return p;
}

int length (Node_t* pHead)
{
    if (NULL == pHead)
    {
        return 0;
    }
    int num = 0;
    while (NULL != pHead->right)
    {
        pHead = pHead->right;
        ++num;
    }
    return num;
}

Node_t* getpHead (Node_t* p)
{
    if (NULL == p)
    {
        return NULL;
    }
    while (NULL != p->left)
    {
        p = p->left;
    }
    return p;
}

void listRecords(const Node_t *pHead)
{
    while (NULL != pHead)
    {
        printf("%d, ", pHead->value);
        if (NULL == pHead->right)
        {
            return;
        }
        pHead = pHead->right;
    }
}



Node_t* Partition (Node_t* pLow, Node_t* pHigh)
{
    if (NULL == pLow || NULL == pHigh)
    {
        return NULL;
    }
    Node_t* apKey = pLow;
    Node_t* apHead = pLow;
    while (pLow != pHigh)
    {
        while (pHigh->value >= apKey->value)
        {
            pHigh = pHigh->left;
            if (pLow == pHigh)
            {
                return apKey;
            }
        }
        /*
        if (NULL != pLow->left)
        {
            while (NULL != apHead->left)
            {
                apHead = apHead->left;
            }
        }
        */
        swap(apHead, pLow, pHigh);
        Node_t* a = pHigh;
        pHigh = pLow;
        pLow = a;

        apHead = pLow;

        while (pLow->value <= apKey->value)
        {
            pLow = pLow->right;
            if (pLow == pHigh)
            {
                return apKey;
            }
        }
        /*
        if (NULL != pLow->left)
        {
            while (NULL != apHead->left)
            {
                apHead = apHead->left;
            }
        }
        */
        swap(apHead, pLow, pHigh);
        Node_t* b = pHigh;
        pHigh = pLow;
        pLow = b;
    }//while

    return apKey;
}

void QuickSort (Node_t* pLow, Node_t* pHigh)
{
    if (NULL == pLow || NULL == pHigh)
    {
        return;
    }
    if (pLow != pHigh)
    {
        Node_t* apivotloc = Partition(pLow, pHigh);
        Node_t* pPart1_Sec = apivotloc->left;
        Node_t* pPart2_Fir = apivotloc->right;

        Node_t* pPart1_Fir = pPart1_Sec;
        while (NULL != pPart1_Fir->left)
        {
            pPart1_Fir = pPart1_Fir->left;
        }

        Node_t* pPart2_Sec = pPart2_Fir;
        while (NULL != pPart2_Sec->right)
        {
            pPart2_Sec = pPart2_Sec->right;
        }

        pPart1_Sec->right = NULL;
        apivotloc->left = NULL;
        pPart2_Fir->left = NULL;
        apivotloc->right = NULL;
        
        QuickSort(pPart1_Fir, pPart1_Sec);
        while (NULL != pPart1_Sec->right)
        {
            pPart1_Sec = pPart1_Sec->right;
        }
        append(pPart1_Sec, apivotloc);
        
        QuickSort(pPart2_Fir, pPart2_Sec);
        while (NULL != pPart2_Fir->left)
        {
            pPart2_Fir = pPart2_Fir->left;
        }
        append(apivotloc, pPart2_Fir);
       
    }
    return;
}