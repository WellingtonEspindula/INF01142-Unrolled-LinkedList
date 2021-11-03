//
// Created by wmespindula on 28/10/2021.
//

#include <malloc.h>
#include "LinkedList.h"

struct Node *mergeSort_split(struct Node *head);
struct Node *mergeSort(struct Node *head);
struct Node *mergeSort_split(struct Node *head);

LinkedList classic_initLinkedList() {
    LinkedList ll = {
            // variables
            .size = 0,
            .head = NULL,
            // methods
            .add = classic_insertTail,
            .addLast = classic_insertTail,
            .get = classic_get,
            .getFirst = classic_getFirst,
            .getLast = classic_getLast,
            .delete = classic_deleteTail,
            .isDone = classic_isDone,
            .next = classic_next,
            .previous = classic_previous,
            .verbosePrint = verbosePrint,
            .forEach = classic_forEach,
            .sort = classic_sort
    };
    return ll;
}

/**
 * Find tail iteration from head
 * @param linkedList
 * @return pointer to tail element
 */
Node *findTail(LinkedList linkedList) {
    Node *curr;
    for (curr = linkedList.head; curr->pNextNode != NULL; curr = curr->pNextNode) {}
    return curr;
}

Node *findElement(LinkedList linkedList, u_int pos) {
    if (pos == 0) {
        return linkedList.head;
    } else {
        Node *current = linkedList.head;
        for (int i = 0; i < pos; i++) {
            current = current->pNextNode;
        }
        return current;
    }
}

Node *classic_newNode(double data) {
    Node *pElement = (Node *) malloc(sizeof(Node));
    pElement->data = data;
    pElement->isValid = true;

    return pElement;
}

bool classic_insertHead(LinkedList *linkedList, double data) {
    Node *newElement = classic_newNode(data);
    newElement->pPrevNode = NULL;

    Node *head = linkedList->head;

    if (head != NULL) {
        newElement->pNextNode = head;
        head->pPrevNode = newElement;
    } else {
        linkedList->tail = newElement;
    }

    linkedList->head = newElement;
    linkedList->size++;

    return true;
}

bool classic_insertTail(LinkedList *linkedList, double data) {
    if (linkedList->head == NULL) {
        return classic_insertHead(linkedList, data);
    } else {
        Node *newNode = classic_newNode(data);
        Node *tailElement = linkedList->tail;
        tailElement->pNextNode = newNode;
        newNode->pPrevNode = tailElement;
        linkedList->tail = newNode;
    }
    linkedList->size++;

    return true;
}


bool classic_insertAt(LinkedList *linkedList, double data, u_int pos) {
    if (pos <= linkedList->size) {
        if (pos == 0) {
            return classic_insertHead(linkedList, data);
        } else if (pos == linkedList->size) {
            return classic_insertTail(linkedList, data);
        } else {
            Node *elementAt = findElement(*linkedList, pos);
            Node *preElementAt = elementAt->pPrevNode;

            Node *newElement = classic_newNode(data);
            preElementAt->pNextNode = newElement;
            newElement->pPrevNode = preElementAt;
            newElement->pNextNode = elementAt;
            elementAt->pPrevNode = newElement;

            linkedList->size++;

            return true;
        }
    }
    return false;
}

Node classic_get(LinkedList linkedList, u_int pos) {
    if (pos < linkedList.size) {
        return *(findElement(linkedList, pos));
    } else {
        return *(linkedList.tail);
    }
}

Node classic_getFirst(LinkedList linkedList) {
    if (linkedList.head != NULL) { return *(linkedList.head); }
    else {
        Node invalidNode = {
                .isValid = false
        };
        return invalidNode;
    }
}

Node classic_getLast(LinkedList linkedList) {
    if (linkedList.tail != NULL) {
        return *(linkedList.tail);
    }
    else {
        Node invalidNode = {
                .isValid = false
        };
        return invalidNode;
    }
}

bool classic_isDone(Node node) {
    return node.isValid == false;
}

Node classic_next(Node node) {
    if (node.pNextNode != NULL) {
        return *node.pNextNode;
    } else {
        Node invalidNode = {
                .isValid = false
        };
        return invalidNode;
    }
}

Node classic_previous(Node node) {
    if (node.pPrevNode != NULL) {
        return *node.pPrevNode;
    } else {
        Node invalidNode = {
                .isValid = false
        };
        return invalidNode;
    }
}


bool classic_deleteHead(LinkedList *linkedList) {
    Node *head = linkedList->head;
    linkedList->head = head->pNextNode;
    head->pNextNode->pPrevNode = NULL;

    free(head);

    return true;
}

bool classic_deleteTail(LinkedList *linkedList) {
    Node *tail = linkedList->tail;
    if (tail != NULL) {
        if (tail->pPrevNode != NULL) {
            linkedList->tail = tail->pPrevNode;
            tail->pPrevNode->pNextNode = NULL;
            free(tail);
        } else {
            linkedList->tail = NULL;
            linkedList->head = NULL;
            free(tail);
        }
        linkedList->size--;
        return true;
    } else {
        return false;
    }
}

void classic_forEach(LinkedList linkedList, void (*func)(double data)) {
    Node *curr = linkedList.head;
    while (curr != NULL) {
        double data = curr->data;
        func(data);
        curr = curr->pNextNode;
    }
}

void classic_sort(LinkedList *linkedList) {
    Node *newHead = mergeSort(linkedList->head);
    linkedList->head = newHead;
    linkedList->tail = findTail(*linkedList);
}


/* ------ MERGE SORT ALGORITHM (Code from GeeksForGeeks) ------ */
// Function to mergeSort_merge two linked lists
struct Node *mergeSort_merge(struct Node *first, struct Node *second) {
    // If first linked list is empty
    if (!first)
        return second;

    // If second linked list is empty
    if (!second)
        return first;

    // Pick the smaller value
    if (first->data < second->data) {
        first->pNextNode = mergeSort_merge(first->pNextNode, second);
        first->pNextNode->pPrevNode = first;
        first->pPrevNode = NULL;
        return first;
    } else {
        second->pNextNode = mergeSort_merge(first, second->pNextNode);
        second->pNextNode->pPrevNode = second;
        second->pPrevNode = NULL;
        return second;
    }
}

// Function to do mergeSort_merge sort
struct Node *mergeSort(struct Node *head) {
    if (!head || !head->pNextNode)
        return head;
    struct Node *second = mergeSort_split(head);

    // Recur for left and right halves
    head = mergeSort(head);
    second = mergeSort(second);

    // Merge the two sorted halves
    return mergeSort_merge(head, second);
}

struct Node *mergeSort_split(struct Node *head) {
    struct Node *fast = head, *slow = head;
    while (fast->pNextNode && fast->pNextNode->pNextNode) {
        fast = fast->pNextNode->pNextNode;
        slow = slow->pNextNode;
    }
    struct Node *temp = slow->pNextNode;
    slow->pNextNode = NULL;
    return temp;
}
