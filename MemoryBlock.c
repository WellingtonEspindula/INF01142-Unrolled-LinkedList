//
// Created by wmespindula on 28/10/2021.
//

#include <memory.h>
#include <malloc.h>
#include "MemoryBlock.h"


MemoryBlock *memoryBlock_create() {
    MemoryBlock *memoryBlock = malloc(sizeof(MemoryBlock));
    memoryBlock->usedSlots = 0;
    memoryBlock->nextBlock = NULL;
    memoryBlock->prevBlock = NULL;
    return memoryBlock;
}

void memoryBlock_shiftRightNodes(MemoryBlock *memoryBlock) {
    memmove(&(memoryBlock->nodes[1]), &(memoryBlock->nodes[0]), memoryBlock->usedSlots * NODE_SIZE);
    for (int i = 1; i < memoryBlock->usedSlots - 1; ++i) {
        memoryBlock->nodes[i].next = &(memoryBlock->nodes[i+1]);
    }
}

Node* memoryBlock_insertHead(MemoryBlock *memoryBlock, Node node) {
    if (memoryBlock->usedSlots == 0) {
        memoryBlock->nodes[0] = node;
        memoryBlock->usedSlots++;
        return &(memoryBlock->nodes[0]);
    } else if (memoryBlock->usedSlots < ITEMS_PER_BLOCK) {
        memoryBlock_shiftRightNodes(memoryBlock);
        memoryBlock->nodes[0] = node;
        memoryBlock->usedSlots++;
        Node* node = &(memoryBlock->nodes[0]);
        node->next = &(memoryBlock->nodes[1]);
        return node;
    } else {
        MemoryBlock *newBlock = memoryBlock_create();
        memoryBlock->prevBlock = newBlock;
        return memoryBlock_insertHead(newBlock, node);
    }
}

Node* memoryBlock_insertTail(MemoryBlock *memoryBlock, Node node) {
    if (memoryBlock->usedSlots < ITEMS_PER_BLOCK) {
        size_t pos = memoryBlock->usedSlots;
        memoryBlock->nodes[pos] = node;
        memoryBlock->usedSlots++;
        return &(memoryBlock->nodes[pos]);
    } else {
        MemoryBlock *newBlock = memoryBlock_create();
        memoryBlock->nextBlock = newBlock;
        return memoryBlock_insertTail(newBlock, node);
    }
}