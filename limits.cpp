/* 
  LIMIT Operations
*/

#include "iostream"
#include "math.h"
#include "assert.h"
#include "stdio.h"
#include "stdlib.h"
#include "hftlob.h"


// Create a Limit Structure as root and return a ptr to it.
Limit *createRoot()
{
    Limit *ptr_limit = new Limit();
    initLimit(ptr_limit);
    ptr_limit->limitPrice = -INFINITY;
    return ptr_limit;
}


/* 
 *Add a new limit structure to the given limit tree.
*/

int addNewLimit(Limit* root, Limit *limit)
{
    if(limitExists(root, limit) == 1)
    {
        return 0;
    }
    limit->leftChild = NULL;
    limit->rightChild = NULL;

    Limit *currentLimit = root;
    Limit *child;
    
    while(true)
    {
        if(currentLimit->limitPrice < limit->limitPrice)
        {
            if(currentLimit->rightChild == NULL)
            {
                currentLimit->rightChild = limit;
                limit->parent = currentLimit;
                return 1;
            }
            else
            {
                currentLimit = currentLimit->rightChild;
            }
        }
        else if(currentLimit->limitPrice > limit->limitPrice)
        {
            if(currentLimit->leftChild == NULL)
            {
                currentLimit->leftChild = limit; 
                limit->parent = currentLimit;
                return 1;
            }
            else
            {
                currentLimit = currentLimit->leftChild;
            }
        }
        else
        {
            // If its equal, hence the limit already exists.
            break;
        }
        continue;
    }

    return 0;
}

void replaceLimitinParent(Limit *limit, Limit *newLimit)
{
    if(!limitIsRoot(limit))
    {
        if(limit==limit->parent->leftChild && !limitIsRoot(limit->parent))
        {
            limit->parent->leftChild = newLimit;
        }
        else
        {
            limit->parent->rightChild = newLimit;
        }
    }

    if(newLimit!=NULL)
    {
        newLimit->parent = limit->parent;
    }
}



int removeList(Limit *limit)

{
    if(!hasGrandpa(limit) && limitIsRoot(limit))
    {
        return 0;
    }

    Limit *ptr_successor = limit;
    if(limit->leftChild != NULL && limit->rightChild != NULL)
    {
        ptr_successor = getMinimumLimit(limit->rightChild);
        Limit *parent = ptr_successor->parent;
        Limit *leftChild = ptr_successor->leftChild;
        Limit *rightChild = ptr_successor->rightChild;

        if(limit->leftChild != ptr_successor)
        {
            ptr_successor->leftChild = limit->leftChild;
        }
        else
        {
            ptr_successor->leftChild = NULL;
        }

        if(limit->rightChild != ptr_successor)
        {
            ptr_successor->rightChild = limit->rightChild;
        }
        else
        {
            ptr_successor->rightChild = NULL;
        }

        limit->leftChild = leftChild;
        limit->rightChild = rightChild;
        ptr_successor->parent = limit->parent;

        if(ptr_successor->parent->rightChild == limit)
        {
            ptr_successor->parent->rightChild = ptr_successor;
        }
        else if(ptr_successor->parent->leftChild == limit)
        {
            ptr_successor->parent->leftChild = ptr_successor;
        }

        limit->parent = parent;

        removeLimit(limit);
    }

    else if(limit->leftChild != NULL && limit->rightChild == NULL)
    {
        replaceLimitinParent(limit, limit->leftChild);
        //Limit has only left child
    }
    else if(limit->leftChild == NULL && limit->rightChild != NULL)
    {
        replaceLimitinParent(limit, limit->rightChild);
        //Limit has only right child
    }
    else
    {
        replaceLimitinParent(limit, NULL);
        //Limit has no children
    }

    return 1;
}