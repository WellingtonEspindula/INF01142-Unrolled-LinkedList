//
// Created by wmespindula on 28/10/2021.
//

#ifndef LOCALITY_STUDY_LINKEDLIST_H
#define LOCALITY_STUDY_LINKEDLIST_H


#include <sys/types.h>
#include <stdbool.h>
#include "Node.h"

enum LinkedListType {
    CLASSIC,
    UNROLLED
};

typedef struct LinkedList {
    // Variables
    size_t size;
    Node *head;
    Node *tail;

    // Unrolled Specific Implementation Vars
    ArrayNode *headArrayNode;
    ArrayNode *tailArrayNode;

    // Methods
    /**
    * Add data to the end (tail) of the Linked List
    * @param linkedList
    * @param data
    * @return True if it was successful; False otherwise
    */
    bool (*add)(struct LinkedList *, double);

    /**
    * Append data to the tail of the Linked List
    * @param linkedList
    * @param data
    * @return True if it was successful; False otherwise
    */
    bool (*addLast)(struct LinkedList *, double);

    /**
    * Get Element at Linked List position
    * @param *linkedList
    * @return
    */
    Node (*get)(struct LinkedList, u_int);

    /**
    * Get First Element (Head) at Linked List
    * @param *linkedList
    * @param pos
    * @return
    */
    struct Node (*getFirst)(struct LinkedList);

    /**
    * Get Last Element (Tail) at Linked List
    * @param *linkedList
    * @return
    */
    Node (*getLast)(struct LinkedList);

    /**
     * Given a Node iteration, verifies if it reached the end
     * @return True if iteration is done; False otherwise
     */
    bool (*isDone)(struct Node);

    /**
    * Given a Node, returns the next element in the linked list.
    * If it's done, returns an invalid node.
    * @return pNextNode element node
    */
    Node (*next)(struct Node);

    /**
     * Given a Node, returns the previous element in the linked list
     * If it's done, returns an invalid node.
     * @return pPrevious element node
     */
    Node (*previous)(struct Node);

    /**
    * Delete data from the end (tail)
    * @param linkedList
    */
    bool (*delete)(struct LinkedList *);

    /**
     * Structure pretty print
     */
    void (*verbosePrint)(struct LinkedList);

    /**
     * Smallest (non verbose) print
     */
    void (*simplePrint)(struct LinkedList);

    /**
     * High performance iteration.
     * @param linkedList the list itself
     * @param func Function to be executed in each item of the list
     */
    void (*forEach)(struct LinkedList linkedList, void (*func)(double data));

    /**
     * Ascending List sort.
     * It was implemented the classic merge sort into doubly linked list
     * @param linkedList the list itself
     */
    void (*sort)(struct LinkedList *linkedList);

} LinkedList;

/*
 * -----------------------------------------
 * CLASSIC (DOUBLY) LINKED LIST IMPL METHODS
 * -----------------------------------------
 * */

LinkedList classic_initLinkedList();

bool classic_insertTail(LinkedList *linkedList, double data);

bool classic_insertHead(LinkedList *linkedList, double data);

bool classic_deleteTail(LinkedList *linkedList);

Node classic_get(LinkedList linkedList, u_int pos);

Node classic_getFirst(LinkedList linkedList);

Node classic_getLast(LinkedList linkedList);

bool classic_isDone(Node node);

Node classic_next(Node node);

Node classic_previous(Node node);

void classic_forEach(LinkedList linkedList, void (*func)(double data));

void classic_sort(LinkedList *linkedList);


/*
 * -----------------------------------------
 * MEMORY BLOCK LINKED LIST IMPL METHODS
 * -----------------------------------------
 * */
//
//bool mb_insertAt(LinkedList *linkedList, double data, u_int pos);
//
//bool mb_insertHead(LinkedList *linkedList, double data);
//
//bool mb_insertTail(LinkedList *linkedList, double data);
//
//bool mb_delete(LinkedList *linkedList, u_int pos);
//
//bool mb_deleteHead(LinkedList *linkedList);
//
//bool mb_deleteTail(LinkedList *linkedList);
//
//Node *mb_get(LinkedList linkedList, u_int pos);
//
//Node *mb_getFirst(LinkedList linkedList);
//
//Node *mb_getLast(LinkedList linkedList);
//
//void mb_print(LinkedList linkedList);
//
//LinkedList mb_initLinkedList();

/*
 * -----------------------------------------
 * UNROLLED LINKED LIST IMPL METHODS
 * -----------------------------------------
 * */

LinkedList unrolled_initLinkedList();

bool unrolled_insertTail(LinkedList *linkedList, double data);

bool unrolled_deleteTail(LinkedList *linkedList);

Node unrolled_get(LinkedList linkedList, u_int pos);

Node unrolled_getFirst(LinkedList linkedList);

Node unrolled_getLast(LinkedList linkedList);

bool unrolled_isDone(Node node);

Node unrolled_next(Node node);

Node unrolled_previous(Node node);

void unrolled_forEach(LinkedList linkedList, void (*func)(double data));

void unrolled_sort(LinkedList *linkedList);

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
    return linkedList.get(linkedList, pos).data;
}

/**
 * Get Element Data at Linked List first Element (Head)
 * @param *linkedList
 * @param pos
 * @return
 */
inline double getFirstData(LinkedList linkedList) {
    return linkedList.getFirst(linkedList).data;
}

/**
 * Get Element Data at Linked List last Element (Tail)
 * @param *linkedLists
 * @param pos
 * @return
 */
inline double getLastData(LinkedList linkedList) {
    return linkedList.getLast(linkedList).data;
}

inline size_t getSize(LinkedList linkedList) {
    return linkedList.size;
}

static void simplePrint(LinkedList linkedList) {
    for (Node current = linkedList.getFirst(linkedList); !linkedList.isDone(current); current = linkedList.next(
            current)) {
        printf("%.1f ", current.data);
    }
    printf("\n");
}

static void verbosePrint(LinkedList linkedList) {
    printf("----------------- Classic DLL (Doubly Linked List) : Current Status -----------------\n");
    printf("Normal Order: \n");

    printf("NULL| <- ");
    for (Node current = linkedList.getFirst(linkedList); !linkedList.isDone(current); current = linkedList.next(
            current)) {
        printf("|%.1f|", current.data);
        // If is not the last one, prints the connection
        if (!linkedList.isDone(linkedList.next(current))) {
            printf(" <=> ");
        }
    }
    printf(" -> |NULL\n");


    printf("\n");
    printf("Reverse Order: \n");
    printf("NULL| <- ");
    for (Node current = linkedList.getLast(linkedList); !linkedList.isDone(current); current = linkedList.previous(
            current)) {
        printf("|%.1f|", current.data);
        if (!linkedList.isDone(linkedList.previous(current))) {
            printf(" <=> ");
        } else {
            printf(" -> |NULL");
        }
    }

    printf("\n\n");
    printf("Head: %.1f\n", linkedList.getFirst(linkedList).data);
    printf("Tail: %.1f\n", linkedList.getLast(linkedList).data);
    printf("Size: %zu\n", linkedList.size);
    printf("------------------------------------------------------------------------------------\n");
}


static LinkedList initLinkedList(enum LinkedListType type) {
    if (type == CLASSIC) {
        return classic_initLinkedList();
    } else if (type == UNROLLED) {
        return unrolled_initLinkedList();
    } else {
        LinkedList ll = {};
        return ll;
    }
}

#endif //LOCALITY_STUDY_LINKEDLIST_H
