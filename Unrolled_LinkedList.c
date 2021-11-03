//
// Created by wmespindula on 28/10/2021.
//

#include <malloc.h>
#include <string.h>
#include "LinkedList.h"

#define ITEMS_PER_BLOCK 8

Node unrolled_findElement(LinkedList list, u_int pos);

void unrolled_quickSort(double a[], int l, int u);

int unrolled_partition(double a[], int l, int u);

struct ArrayNode *unrolled_split(struct ArrayNode *head);

struct ArrayNode *unrolled_mergeSort(struct ArrayNode *head);

ArrayNode *arrayNode_create() {
    ArrayNode *arrayNode = malloc(sizeof(ArrayNode));
    arrayNode->usedSlots = 0;
    arrayNode->next = NULL;
    arrayNode->prev = NULL;
    return arrayNode;
}

LinkedList unrolled_initLinkedList() {
    ArrayNode *pArrayNode = arrayNode_create();

    LinkedList ll = {
            // variables
            .size = 0,

            .headArrayNode = pArrayNode,
            .tailArrayNode = pArrayNode,

            // methods
            .add = unrolled_insertTail,
            .addLast = unrolled_insertTail,
            .get = unrolled_get,
            .getFirst = unrolled_getFirst,
            .getLast = unrolled_getLast,
            .isDone = unrolled_isDone,
            .next = unrolled_next,
            .previous = unrolled_previous,
            .delete = unrolled_deleteTail,
            .verbosePrint = verbosePrint,
            .simplePrint = simplePrint,
            .forEach = unrolled_forEach,
            .sort = unrolled_sort
    };
    return ll;
}

bool unrolled_insertTail(LinkedList *linkedList, double data) {
    if (linkedList->tailArrayNode->usedSlots == ITEMS_PER_BLOCK) {
        ArrayNode *newArrayNode = arrayNode_create();
        newArrayNode->prev = linkedList->tailArrayNode;
        linkedList->tailArrayNode->next = newArrayNode;
        linkedList->tailArrayNode = newArrayNode;
    }
    ArrayNode *tail = linkedList->tailArrayNode;
    tail->array[tail->usedSlots] = data;
    tail->usedSlots++;
    linkedList->size++;

    return true;
}

bool unrolled_deleteTail(LinkedList *linkedList) {
    if (linkedList->tailArrayNode->usedSlots > 0) {
        linkedList->tailArrayNode->usedSlots--;
    } else {
        if (linkedList->tailArrayNode->prev != NULL) {
            ArrayNode *tailArrayNode = linkedList->tailArrayNode;
            linkedList->tailArrayNode->prev->next = NULL;
            linkedList->tailArrayNode = tailArrayNode->prev;
            free(tailArrayNode);
        } else {
            return false;
        }
    }
    linkedList->size--;
    return true;
}

Node unrolled_findHead(LinkedList linkedList) {
    ArrayNode *headArrayNode = linkedList.headArrayNode;
    Node headNode = {
            .data = headArrayNode->array[0],
            .isValid = true,
            .currArrayNode = headArrayNode,
            .pos = 0
    };
    return headNode;
}

Node unrolled_findTail(LinkedList linkedList) {
    ArrayNode *tailArrayNode = linkedList.tailArrayNode;
    Node tailNode = {
            .data = tailArrayNode->array[tailArrayNode->usedSlots - 1],
            .isValid = true,
            .currArrayNode = tailArrayNode,
            .pos = (int) tailArrayNode->usedSlots - 1
    };
    return tailNode;
}

Node unrolled_findElement(LinkedList linkedList, u_int pos) {
    Node current = unrolled_findHead(linkedList);
    for (int i = 0; i < pos; i++) {
        current = unrolled_next(current);
    }
    return current;
}

Node unrolled_get(LinkedList linkedList, u_int pos) {
    if (pos < linkedList.size) {
        return unrolled_findElement(linkedList, pos);
    } else {
        return unrolled_findTail(linkedList);
    }
}

Node unrolled_getFirst(LinkedList linkedList) {
    return unrolled_findHead(linkedList);
}

Node unrolled_getLast(LinkedList linkedList) {
    return unrolled_findTail(linkedList);
}

bool unrolled_isDone(Node node) {
    return node.isValid == false;
}

Node unrolled_next(Node node) {
    ArrayNode *current = node.currArrayNode;
    if (node.pos == current->usedSlots - 1) {
        if (current->next != NULL) {
            // If the node is the last of a block, gets the first of the next block
            Node nextNode = {
                    .data = current->next->array[0],
                    .isValid = true,
                    .pos = 0,
                    .currArrayNode = current->next
            };
            return nextNode;
        } else {
            Node nextNode = {
                    .isValid = false,
                    .pos = -1,
                    .currArrayNode = NULL
            };
            return nextNode;
        }
    } else {
        int currentPos = node.pos;
        Node nextNode = {
                .data = current->array[currentPos + 1],
                .isValid = true,
                .pos = currentPos + 1,
                .currArrayNode = current
        };
        return nextNode;
    }
}

Node unrolled_previous(Node node) {
    ArrayNode *current = node.currArrayNode;
    if (node.pos == 0) {
        if (current->prev != NULL) {
            size_t lastElementInBlock = current->prev->usedSlots;
            // If the node is the first of a block, gets the last of the previous block
            Node nextNode = {
                    .data = current->prev->array[lastElementInBlock - 1],
                    .isValid = true,
                    .pos = (int) lastElementInBlock - 1,
                    .currArrayNode = current->prev
            };
            return nextNode;
        } else {
            // If the node is the head, returns an invalid node
            Node nextNode = {
                    .isValid = false,
                    .pos = -1,
                    .currArrayNode = NULL
            };
            return nextNode;
        }
    } else {
        int currentPos = node.pos;
        Node nextNode = {
                .data = current->array[currentPos - 1],
                .isValid = true,
                .pos = currentPos - 1,
                .currArrayNode = current
        };
        return nextNode;
    }
}

void unrolled_forEach(LinkedList linkedList, void (*func)(double data)) {
    if (linkedList.headArrayNode != NULL) {
        ArrayNode *currArrayNode = linkedList.headArrayNode;
        while (currArrayNode != NULL) {
            for (int i = 0; i < currArrayNode->usedSlots; i++) {
                double data = currArrayNode->array[i];
                func(data);
            }
            currArrayNode = currArrayNode->next;
        }

    }
}

void unrolled_sort(LinkedList *linkedList) {
    ArrayNode *curr = linkedList->headArrayNode;
    unrolled_mergeSort(curr);
}

/* ------ QUICK AND MERGE SORT ALGORITHMS ------ */
void unrolled_quickSort(double a[], int l, int u) {
    int j;
    if (l < u) {
        j = unrolled_partition(a, l, u);
        unrolled_quickSort(a, l, j - 1);
        unrolled_quickSort(a, j + 1, u);
    }
}

int unrolled_partition(double a[], int l, int u) {
    int i, j;
    double v, temp;
    v = a[l];
    i = l;
    j = u + 1;
    do {
        do
            i++;
        while (a[i] < v && i <= u);
        do
            j--;
        while (v < a[j]);
        if (i < j) {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    } while (i < j);
    a[l] = a[j];
    a[j] = v;
    return (j);
}

void merge(ArrayNode *head, int size, int lo, int mid, int hi) {
    double aux[size];
    // copy to aux[]
    ArrayNode *curr = head;
    int k = 0;
    while (curr) {
        memcpy(&aux[k], curr->array, sizeof(double) * curr->usedSlots);
        k += curr->usedSlots;
        curr = curr->next;
    }

    // merge back to a[]
    int i = lo, j = mid;
    ArrayNode *currArrayNode = head;
    while (currArrayNode != NULL) {
        for (k = 0; k < currArrayNode->usedSlots; k++) {
            if (i >= mid) { // NOLINT(bugprone-branch-clone)
                currArrayNode->array[k] = aux[j++];
            } else if (j > hi) { // NOLINT(bugprone-branch-clone)
                currArrayNode->array[k] = aux[i++];
            } else if (aux[j] < aux[i]) {
                currArrayNode->array[k] = aux[j++];
            } else {
                currArrayNode->array[k] = aux[i++];
            }
        }
        currArrayNode = currArrayNode->next;
    }
}

struct ArrayNode *unrolled_merge(ArrayNode *head, ArrayNode *second) {
    ArrayNode *curr = head;
    int size = curr->usedSlots;
    while (curr->next != NULL) {
        size += curr->usedSlots;
        curr = curr->next;
    }
    int mid = size;
    curr->next = second;
    curr = curr->next;
    while (curr != NULL) {
        size += curr->usedSlots;
        curr = curr->next;
    }
    merge(head, size, 0, mid, size - 1);
    return head;

}

// Function to do unrolled_merge sort
struct ArrayNode *unrolled_mergeSort(struct ArrayNode *head) {
    if (!head || !head->next) {
        if (head && !head->next) {
            unrolled_quickSort(head->array, 0, head->usedSlots - 1);
        }
        return head;
    }
    struct ArrayNode *second = unrolled_split(head);

    // Recur for left and right halves
    head = unrolled_mergeSort(head);
    second = unrolled_mergeSort(second);

    // Merge the two sorted halves
    return unrolled_merge(head, second);
}

struct ArrayNode *unrolled_split(struct ArrayNode *head) {
    struct ArrayNode *fast = head, *slow = head;
    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
    }
    struct ArrayNode *temp = slow->next;
    slow->next = NULL;
    return temp;
}

