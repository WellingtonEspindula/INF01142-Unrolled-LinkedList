//
// Created by wmespindula on 28/10/2021.
//

#ifndef LOCALITY_STUDY_MEMORYBLOCK_H
#define LOCALITY_STUDY_MEMORYBLOCK_H

#include "Node.h"

#define ITEMS_PER_BLOCK 8
#define NODE_SIZE sizeof(Node)
#define BLOCK_SIZE NODE_SIZE * ITEMS_PER_BLOCK


typedef struct MemoryBlock {
    size_t usedSlots;
    Node nodes[ITEMS_PER_BLOCK];
    struct MemoryBlock *nextBlock;
    struct MemoryBlock *prevBlock;
} MemoryBlock;

MemoryBlock *memoryBlock_create();

void memoryBlock_shiftRightNodes(MemoryBlock *memoryBlock);

Node *memoryBlock_insertHead(MemoryBlock *memoryBlock, Node node);

Node *memoryBlock_insertTail(MemoryBlock *memoryBlock, Node node);


#endif //LOCALITY_STUDY_MEMORYBLOCK_H
