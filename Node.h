//
// Created by wmespindula on 28/10/2021.
//

#ifndef LOCALITY_STUDY_NODE_H
#define LOCALITY_STUDY_NODE_H

#ifndef ITEMS_PER_BLOCK
#define ITEMS_PER_BLOCK 8
#endif

typedef struct ArrayNode {
    double array[ITEMS_PER_BLOCK];
    struct ArrayNode *next;
    struct ArrayNode *prev;
    u_int8_t usedSlots;
} ArrayNode;

typedef struct Node {
    double data;
    bool isValid;

    // Classic Specific Implementation Vars
    struct Node *pPrevNode;
    struct Node *pNextNode;

    // Unrolled Specific Implementation Vars
    ArrayNode *currArrayNode;
    u_int8_t pos;
} Node;

#endif //LOCALITY_STUDY_NODE_H
