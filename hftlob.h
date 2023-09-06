#ifndef HFTLOB_H
#define HFTLOB_H

typedef struct Order{
    char *tid;
    unsigned buyorsell;
    double shares;
    double limit;
    double entryTime;
    double eventTime;
    struct Order *nextOrder;
    struct Order *prevOrder;
    struct Limit *parentLimit;
    int exchangeid;
} Order;

typedef struct Limit{
    double limitPrice;
    double size;
    double totalVolume;
    int orderCount;
    struct Limit *parent;
    struct Limit *leftChild;
    struct Limit *rightChild;
    struct Order *headOrder;
    struct Order *tailOrder;
} Limit;

typedef struct QueueItem
{
    Limit *limit;
    struct QueueItem *previous;
} QueueItem;

typedef struct Queue
{
    int size;
    QueueItem *head;
    QueueItem *tail;
} Queue;



/* init or INITIALIZATION functions*/

void initOrder(Order *order);

void initLimit(Limit *limit);

void initQueueItem(QueueItem *item);

void initQueue(Queue *q);


/* Queue Functions*/

void pushToQueue(Queue *q, Limit *limit);

Limit *popFromQueue(Queue *q);

int queueIsEmpty(Queue *q);


/* Order Functions*/

int pushOrder(Limit *limit, Order *new_order);

Order *popOrder(Limit *limit);

int removeOrder(Order *order);


/* Binary Search Tree Balancing Functions */

void balanceBranch(Limit *limit);

void rotateLeftLeft(Limit *limit);

void rotateLeftRight(Limit *limit);

void rotateRightLeft(Limit *limit);

void rotateRightRight(Limit *limit);

/* Binary Search Tree Functions*/
Limit *createRoot(void);

int addNewLimit(Limit *root, Limit *limit);

void replaceLimitInParent(Limit *limit, Limit *newLimit);

int removeLimit(Limit *limit);

/* Functions for various BST Operations*/

int limitExists(Limit *root, Limit *limit);

int limitIsRoot(Limit *limit);

int hasGrandpa(Limit *limit);

Limit *getGrandpa(Limit *limit);

Limit *getMinimumLimit(Limit *limit);

Limit *getMaximumLimit(Limit *limit);

int getHeight(Limit *limit);

int getBalanceFactor(Limit *limit);

void copyLimit(Limit *source, Limit *tar);

/* CuTest Fuctions*/
void RunAllTests(void);

#endif