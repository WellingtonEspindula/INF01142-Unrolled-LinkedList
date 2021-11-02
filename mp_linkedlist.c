//
// Created by wmespindula on 28/10/2021.
//

#include <stddef.h>
#include <malloc.h>
#include <memory.h>
#include "LinkedList.h"

LinkedList mb_initLinkedList() {
    MemoryBlock *memoryBlock = memoryBlock_create();

    LinkedList ll = {
            // variables
            .size = 0,
            .head = NULL,
            .tail = NULL,

            .headMemoryBlock = memoryBlock,
            .tailMemoryBlock = memoryBlock,

            // methods
            .add = mb_insertHead,
            .addFirst = mb_insertHead,
            .addLast = mb_insertTail,
            .addAt = mb_insertAt,
            .get = mb_get,
            .getFirst = mb_getFirst,
            .getLast = mb_getLast,
            .next = next,
            .previous = previous,
            .pop = mb_deleteTail,
            .push = mb_insertHead,
            .print = mb_print
    };
    return ll;
}

bool mb_insertHead(LinkedList *linkedList, double data) {
    Node *headNode = linkedList->head;
    Node newNode = {
            .next = headNode,
            .previous = NULL,
            .data = data
    };
    Node *newNodePtr = memoryBlock_insertHead(linkedList->headMemoryBlock, newNode);

    if (headNode != NULL) {
        headNode->previous = newNodePtr;
    }

    if (linkedList->tail == NULL) {
        linkedList->tail = newNodePtr;
    }

    linkedList->head = newNodePtr;
    linkedList->size++;
    return true;
}

bool mb_insertAt(LinkedList *linkedList, double data, u_int pos) {
    return false;
}

Node newNodeTail(double data, Node *tail) {
    Node newNode = {
            .next = NULL,
            .data = data,
            .previous = tail,
    };
    return newNode;
}

bool mb_insertTail(LinkedList *linkedList, double data) {
    Node *tailNode = linkedList->tail;
    Node newNode = {
            .next = NULL,
            .previous = tailNode,
            .data = data
    };
    Node *newNodePtr = memoryBlock_insertTail(linkedList->tailMemoryBlock, newNode);

    if (tailNode != NULL) {
        tailNode->next = newNodePtr;
    }

    if (linkedList->head == NULL) {
        linkedList->head = newNodePtr;
    }
    linkedList->tail = newNodePtr;
    linkedList->size++;
    return true;
}


bool mb_delete(LinkedList *linkedList, u_int pos) {
    return true;
}

bool mb_deleteHead(LinkedList *linkedList) {
    return true;
}

bool mb_deleteTail(LinkedList *linkedList) {
    return true;
}

Node *mb_get(LinkedList linkedList, u_int pos) {
    return NULL;
}

Node *mb_getFirst(LinkedList linkedList) {
    return linkedList.head;
}

Node *mb_getLast(LinkedList linkedList) {
    return linkedList.tail;
}

void mb_print(LinkedList linkedList) {
    Node *current = linkedList.head;
    printf("----------------- Classic DLL (Doubly Linked List) : Current Status -----------------\n");
    printf("Normal Order: \n");

    printf("NULL| <- ");
    while (current != NULL) {
        printf("|%.1f|", current->data);
        current = current->next;
        if (current == NULL) {
            printf(" -> |NULL\n");
        } else {
            printf(" <=> ");
        }
    }

    printf("\n");
    printf("Head: %.1f\n", linkedList.getFirst(linkedList)->data);
    printf("Tail: %.1f\n", linkedList.getLast(linkedList)->data);
    printf("Size: %zu\n", linkedList.size);
    printf("------------------------------------------------------------------------------------\n");
}
