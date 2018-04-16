#ifndef EXTRENDED_QUEUE
#define EXTRENDED_QUEUE value

#include "Queue.h"

class Extended_Queue: public Queue
{
public:
    bool full() const;
    int  size() const;
    void clear();
    Error_code serve_and_retrieve(Queue_entry &item);
};

int Extended_Queue::size() const
/*Post: Return the number of entriesin the Extended_queue.*/
{
    return count;
}

bool Extended_Queue::full()const
{
    return count==maxqueue;
}

void Extended_Queue::clear()
{
    count=0;
    front=0;
    rear=maxqueue-1;
}

Error_code Extended_Queue::serve_and_retrieve(Queue_entry &item)
{
    if(count==0)
        return underflow;
    count--;
    item=entry[front];
    front =((front +1)== maxqueue)?0:(front +1);
    return success;
}


#endif