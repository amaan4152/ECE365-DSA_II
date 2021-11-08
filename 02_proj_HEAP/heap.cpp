
/*
AMAAN RAHMAN
DSA II 
Professor Sable
Project 2
*/

#include <iostream>
#include "heap.h"

heap::heap(int capacity) : capacity{capacity}, currentSize{0}
{
    this->bin_heap.resize(capacity + 1);
    this->heapMap = hashTable(capacity * 2);
}

int heap::insert(const std::string &id, int key, void *pv)
{
    if (this->currentSize >= this->capacity)
        return 1;

    else if (this->heapMap.contains(id))
        return 2;

    heapNode node;
    node.id = id;
    node.key = key;
    if (pv)
        node.pv = pv;

    this->heapMap.insert(id, &this->bin_heap[++this->currentSize]);
    this->bin_heap[0] = node;
    percolateUp(this->currentSize);

    return 0;
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData)
{
    if (this->currentSize == 0)
        return 1;

    heapNode minItem = this->bin_heap[1];
    if (pId)
        *pId = minItem.id;
    if (pKey)
        *pKey = minItem.key;
    if (ppData)
        *(static_cast<void **>(ppData)) = minItem.pv;

    this->heapMap.remove(minItem.id);
    this->bin_heap[1] = this->bin_heap[this->currentSize--];
    this->percolateDown(1);

    return 0;
}

int heap::setKey(const std::string &id, int key)
{
    bool found;
    heapNode *node = static_cast<heapNode *>(this->heapMap.getPointer(id, &found));
    if (!found)
        return 1;

    int pos = getPos(node);
    int prevKey = node->key;
    node->key = key;

    if (node->key < prevKey)
    {
        this->bin_heap[0] = *node;
        percolateUp(pos);
    }
    else if (node->key > prevKey)
        percolateDown(pos);

    return 0;
}

int heap::remove(const std::string &id, int *pKey, void *ppData)
{
    bool found;
    heapNode *node = static_cast<heapNode *>(this->heapMap.getPointer(id, &found));
    if (!found)
        return 1;

    if (pKey)
        *pKey = node->key;
    if (ppData)
        *(static_cast<void **>(ppData)) = node->pv;

    setKey(id, this->bin_heap[1].key - 1);

    return this->deleteMin();
}

void heap::percolateUp(int hole)
{
    for (; this->bin_heap[0].key < this->bin_heap[hole / 2].key; hole /= 2)
    {
        this->bin_heap[hole] = this->bin_heap[hole / 2];
        this->heapMap.setPointer(this->bin_heap[hole].id, &this->bin_heap[hole]);
    }
    this->bin_heap[hole] = this->bin_heap[0];
    this->heapMap.setPointer(this->bin_heap[hole].id, &this->bin_heap[hole]);
}

void heap::percolateDown(int hole)
{
    int child;
    heapNode tmp = this->bin_heap[hole];

    for (; hole * 2 <= this->currentSize; hole = child)
    {
        child = hole * 2;
        if (child != this->currentSize && this->bin_heap[child + 1].key < this->bin_heap[child].key)
            ++child;

        if (this->bin_heap[child].key < tmp.key)
        {
            this->bin_heap[hole] = this->bin_heap[child];
            this->heapMap.setPointer(this->bin_heap[hole].id, &this->bin_heap[hole]);
        }
        else
            break;
    }

    this->bin_heap[hole] = tmp;
    this->heapMap.setPointer(this->bin_heap[hole].id, &this->bin_heap[hole]);
}

int heap::getPos(heapNode *pn)
{
    return (pn - &this->bin_heap[0]);
}
