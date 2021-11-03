#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <memory.h>
#include "LinkedList.h"

void insertLinkedList(LinkedList *list, int n) {
    for (int i = 0; i <= n; i++) {
        list->add(list, i);
    }
}

void iterLinkedList(LinkedList *list, int n) {
    for (Node node = list->getFirst(*list); !list->isDone(node); node = list->next(node)) {}
}

void emptyFunction(double data) {}

void fastIterLinkedList(LinkedList *list, int n) {
    list->forEach(*list, emptyFunction);
}

void benchmark(void (*f)(LinkedList *list, int n), LinkedList *list, int n, const char* text) {
    clock_t startTime = clock();
    f(list, n);
    clock_t endTime = clock();

    double elapsedTimeSeconds = ((double) endTime- (double) startTime)/(double) CLOCKS_PER_SEC;
    printf("%s = %f ms\n", text, elapsedTimeSeconds*1E3);
}

//float mean(const float array[], size_t size) {
//    float mean = 0;
//    for (int i = 0; i < size; i++) {
//        mean += array[i];
//    }
//    mean /= (float) size;
//    return mean;
//}
//
//float stdev(const float array[], size_t size) {
//    float mean_calc = mean(array, size);
//    float sigma = 0;
//
//    for (int i = 0; i < size; i++) {
//        sigma += powf((mean_calc - array[i]), 2);
//    }
//    return sqrtf(sigma / (float) size);
//}

int main(int argc, char *argv[]) {
//    if (argc != 4) {
//        printf("Usage: %s <elements-number> <nb-experiments> <#experimento> (see run.py)\n", argv[0]);
//        exit(-1);
//    }
//
//    srand(clock());
//
//    int n = atoi(argv[1]);
//    int nb_exp = atoi(argv[2]);
//    int exp_num = atoi(argv[3]);
//
//    LinkedList classicLl = initLinkedList(CLASSIC);
//    benchmark(insertLinkedList, &classicLl, n, "Classic Insertion time");
//
//    LinkedList unrolledLl = initLinkedList(UNROLLED);
//    benchmark(insertLinkedList, &unrolledLl, n, "Unrolled Insertion time");
//
//    benchmark(iterLinkedList, &classicLl, n, "Classic Iteration time (Begin-End) ");
//    benchmark(iterLinkedList, &unrolledLl, n, "Unrolled Iteration time (Begin-End) ");
//
//    benchmark(fastIterLinkedList, &classicLl, n, "Classic Foreach Iteration time (Begin-End) ");
//    benchmark(fastIterLinkedList, &unrolledLl, n, "Unrolled Foreach Iteration time (Begin-End) ");


    /*
     * MY TEST AREA
     */


    /*
     * TESTS VANILLA LINKED LIST
     */
//    LinkedList classicLl = initLinkedList(CLASSIC);
//    for (int i = 0; i <= 20; i++) {
//        classicLl.addLast(&classicLl, i);
////        printf("i=%d\n", i);
//    }
//    classicLl.print(classicLl);
////    classicLl.addAt(&classicLl, 4123312, 1);
////    classicLl.print(classicLl);
//
//    for (int i = -1; i <= 21; i++) {
//        int pos = i;
//        Node *element = classicLl.get(classicLl, pos);
//        if (element != NULL) printf("\nat = %d, value = %.1f", pos, element->data);
//        else printf("\nIsh num alcancou");
//    }

//    printf("Node size = %lu B", sizeof(Node));


    /*
     * TESTS VANILLA LINKED LIST
     */
    LinkedList mbLinkedList = initLinkedList(CLASSIC);
    for (int i = 20; i >= 0; i--) {
        mbLinkedList.addLast(&mbLinkedList, i);
    }
    mbLinkedList.verbosePrint(mbLinkedList);
    printf("\n");
    mbLinkedList.sort(&mbLinkedList);
    mbLinkedList.verbosePrint(mbLinkedList);
//    for (int i = 0; i <= 21; ++i) {
//        bool removed = mbLinkedList.delete(&mbLinkedList);
//    }



//// MEM MOVE TESTS
//    int array[5] = {0,1,2,3};
//    memmove(&(array[1]), (&array[0]), sizeof(int)*4);
//    array[0] = 312;
//    for (int i = 0; i < 5; ++i) {
//        printf("%d, ", array[i]);
//    }
//    printf("\n");


    return 0;
}
