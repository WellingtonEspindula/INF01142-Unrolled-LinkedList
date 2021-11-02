//
// Created by wmespindula on 28/10/2021.
//

#include <malloc.h>
#include "LinkedList.h"

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
            .isDone = classic_isDone,
            .next = classic_next,
            .previous = classic_previous,
            .verbosePrint = verbosePrint,
            .forEach = classic_forEach
    };
    return ll;
}

Node *findTail(LinkedList linkedList) {
    return linkedList.tail;
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
        Node *tailElement = findTail(*linkedList);
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
        return *(findTail(linkedList));
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
    if (linkedList.tail != NULL) { return *(findTail(linkedList)); }
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
    linkedList->tail = tail->pPrevNode;
    tail->pPrevNode->pNextNode = NULL;

    free(tail);

    return true;
}

void classic_forEach(LinkedList linkedList, void (*func)(double data)) {
    Node *curr = linkedList.head;
    while (curr != NULL) {
        double data = curr->data;
        func(data);
        curr = curr->pNextNode;
    }
}
