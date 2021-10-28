//
// Created by wmespindula on 28/10/2021.
//

#include <stddef.h>
#include <malloc.h>
#include "linkedlist.h"


Node *findTail(LinkedList linkedList) {
    Node *current = linkedList.head;
    while (current->next != NULL) {
        current = current->next;
    }

    return current;
}

Node *findPreviousElement(LinkedList linkedList, u_int pos) {
    Node *current = linkedList.head;
    return current->previous;
}

Node *findElement(LinkedList linkedList, u_int pos) {
    if (pos == 0) {
        return linkedList.head;
    } else {
        return findPreviousElement(linkedList, pos)->next;
    }
}

Node *classic_newNode(double data) {
    Node *pElement = (Node *) malloc(sizeof(Node));
    pElement->data = data;

    return pElement;
}

bool classic_insertHead(LinkedList *linkedList, double data) {
    Node *newElement = classic_newNode(data);
    newElement->previous = NULL;

    Node *head = linkedList->head;

    if (head != NULL) {
        newElement->next = head;
        head->previous = newElement;
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
        tailElement->next = newNode;
        newNode->previous = tailElement;
    }
    linkedList->size++;

    return true;
}


bool classic_insertAt(LinkedList *linkedList, double data, u_int pos) {
    if (pos < linkedList->size) {
        if (pos == 0) {
            return classic_insertHead(linkedList, data);
        } else {
            Node *elementAt = findElement(*linkedList, pos);
            Node *preElementAt = elementAt->previous;

            Node *newElement = classic_newNode(data);
            preElementAt->next = newElement;
            newElement->previous = preElementAt;
            newElement->next = elementAt;
            elementAt->previous = newElement;

            linkedList->size++;

            return true;
        }
    } else {
        return false;
    }
}

Node *classic_get(LinkedList linkedList, u_int pos) {
    if (pos < linkedList.size) {
        return findElement(linkedList, pos);
    }
    return NULL;
}

Node *classic_getFirst(LinkedList linkedList) {
    return linkedList.head;
}

Node *classic_getLast(LinkedList linkedList) {
    return findTail(linkedList);
}

void classic_print(LinkedList linkedList) {
    Node *current = linkedList.head;
    printf("---------- Classic DLL: Current Status -------\n");
    printf("Normal Order: \n");
    while (current != NULL) {
        printf("|%f| <=> ", current->data);
        current = current->next;
        if (current == NULL) {
            printf("|NULL| \n");
        }
    }

    printf("Reverse Order: \n");
    current = findTail(linkedList);
    while (current != NULL) {
        printf("|%f| <=> ", current->data);
        current = current->previous;
        if (current == NULL) {
            printf("|NULL| \n");
        }
    }
    printf("Size: %zu\n", linkedList.size);
    printf("----------------------------------------------\n")
}

bool classic_delete(LinkedList *linkedList, u_int pos) {
    return true;
}

bool classic_deleteHead(LinkedList *linkedList) {
    return true;
}

bool classic_deleteTail(LinkedList *linkedList) {
    return true;
}

