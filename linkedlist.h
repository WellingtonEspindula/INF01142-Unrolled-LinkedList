//
// Created by wmespindula on 28/10/2021.
//

#ifndef LOCALITY_STUDY_LINKEDLIST_H
#define LOCALITY_STUDY_LINKEDLIST_H

#include <sys/types.h>
#include <stdbool.h>

enum LinkedListType {
    CLASSIC,
    MEMORY_POOL
};

typedef struct Node {
    double data;
    struct Node *previous;
    struct Node *next;
} Node;

typedef struct LinkedList {
    size_t size;
    Node *head;

    /**
    * Add data to the end (tail) of the Linked List
    * @param linkedList
    * @param data
    */
    bool (*add)(struct LinkedList *, double);

    /**
    * Append data to the tail of the Linked List
    * @param linkedList
    * @param data
    */
    bool (*addLast)(struct LinkedList *, double);

    /**
    * Inserts data into the given position of the Linked List
    * @param linkedList
    * @param data
    * @param pos
    */
    bool (*addAt)(struct LinkedList *, double, u_int);

    /**
    * Inserts data into the Linked List's Head
    * @param linkedList
    * @param data
    */
    bool (*addFirst)(struct LinkedList *, double);

    /**
    * Get Element at Linked List position
    * @param *linkedList
    * @return
    */
    Node *(*get)(struct LinkedList, u_int);

    /**
    * Get First Element (Head) at Linked List
    * @param *linkedList
    * @param pos
    * @return
    */
    Node *(*getFirst)(struct LinkedList);

    /**
    * Get Last Element (Tail) at Linked List
    * @param *linkedList
    * @return
    */
    Node *(*getLast)(struct LinkedList);

    /**
     * Given a Node, returns the next element in the linked list
     * @return next element node
     */
    Node *(*next)(Node);

    /**
     * Given a Node, returns the next element in the linked list
     * @return next element node
     */
    Node *(*previous)(Node);

    bool (*pop)(struct LinkedList *);

    bool (*push)(struct LinkedList *, double );

    /**
    * Delete data from given a position
    * @param linkedList
    * @param pos
    */
    bool (*delete)(struct LinkedList *, u_int);

    void (*print)(struct LinkedList);

} LinkedList;

/*
 * -----------------------------------------
 * CLASSIC (DOUBLY) LINKED LIST IMPL METHODS
 * -----------------------------------------
 * */

bool classic_insertTail(LinkedList *linkedList, double data);

bool classic_insertAt(LinkedList *linkedList, double data, u_int pos);

bool classic_insertHead(LinkedList *linkedList, double data);

bool classic_delete(LinkedList *linkedList, u_int pos);

bool classic_deleteHead(LinkedList *linkedList);

bool classic_deleteTail(LinkedList *linkedList);

Node *classic_get(LinkedList linkedList, u_int pos);

Node *classic_getFirst(LinkedList linkedList);

Node *classic_getLast(LinkedList linkedList);

void classic_print(LinkedList linkedList);

static LinkedList classic_initLinkedList();

/*
 * -----------------------------------------
 * MEMORY POOL LINKED LIST IMPL METHODS
 * -----------------------------------------
 * */

bool mp_insertAt(LinkedList *linkedList, double data, u_int pos);

bool mp_insertHead(LinkedList *linkedList, double data);

bool mp_insertTail(LinkedList *linkedList, double data);

bool mp_delete(LinkedList *linkedList, u_int pos);

bool mp_deleteHead(LinkedList *linkedList);

bool mp_deleteTail(LinkedList *linkedList);

Node *mp_get(LinkedList linkedList, u_int pos);

Node *mp_getFirst(LinkedList linkedList);

Node *mp_getLast(LinkedList linkedList);

void mp_print(LinkedList linkedList);

static LinkedList mp_initLinkedList();

/*
 * --------------------------
 * COMMON LINKED LIST METHODS
 * ---------------------------
 * */


/**
 * Get Element Data at Linked List position
 * @param *linkedList
 * @param pos
 * @return
 */
inline double getData(LinkedList linkedList, u_int pos) {
    return linkedList.get(linkedList, pos)->data;
}

/**
 * Get Element Data at Linked List first Element (Head)
 * @param *linkedList
 * @param pos
 * @return
 */
inline double getFirstData(LinkedList linkedList) {
    return linkedList.getFirst(linkedList)->data;
}

/**
 * Get Element Data at Linked List last Element (Tail)
 * @param *linkedLists
 * @param pos
 * @return
 */
inline double getLastData(LinkedList linkedList) {
    return linkedList.getLast(linkedList)->data;
}

inline size_t getSize(LinkedList linkedList) {
    return linkedList.size;
}

static Node *next(Node node) {
    return node.next;
}

static Node *previous(Node node) {
    return node.previous;
}


static LinkedList initLinkedList(enum LinkedListType type) {
    if (type == CLASSIC) {
        return classic_initLinkedList();
    } else if (type == MEMORY_POOL) {
        return mp_initLinkedList();
    } else {
        LinkedList ll = {};
        return ll;
    }
}

static LinkedList classic_initLinkedList() {
    LinkedList ll = {
            .size = 0,
            .head = NULL,
            .add = classic_insertHead,
            .addFirst = classic_insertHead,
            .addLast = classic_insertTail,
            .addAt = classic_insertAt,
            .get = classic_get,
            .getFirst = classic_getFirst,
            .getLast = classic_getLast,
            .next = next,
            .previous = previous,
            .pop = classic_deleteTail,
            .push = classic_insertHead,
            .print = classic_print
    };
    return ll;
}

static LinkedList mp_initLinkedList() {
    LinkedList ll = {
            .size = 0,
            .head = NULL,
            .add = mp_insertHead,
            .addFirst = mp_insertHead,
            .addLast = mp_insertTail,
            .addAt = mp_insertAt,
            .get = mp_get,
            .getFirst = mp_getFirst,
            .getLast = mp_getLast,
            .next = next,
            .previous = previous,
            .print = mp_print
    };
    return ll;
}


#endif //LOCALITY_STUDY_LINKEDLIST_H
