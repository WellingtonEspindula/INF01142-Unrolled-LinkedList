#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "linkedlist.h"

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
//    LinkedList vanillaLinkedList = initLinkedList(CLASSIC);
//
//    clock_t startTime = clock();
//    for (int i = 0; i <= n; i++) {
//        vanillaLinkedList.addFirst(&vanillaLinkedList, i);
////        printf("i=%d\n", i);
//    }
//    clock_t endTime = clock();
//
//    double elapsedTimeSeconds = ((double) endTime- (double) startTime)/(double) CLOCKS_PER_SEC;
//    printf("Insertion time = %f ms", elapsedTimeSeconds*1E3);

    LinkedList vanillaLinkedList = initLinkedList(CLASSIC);
    for (int i = 0; i <= 20; i++) {
        vanillaLinkedList.addLast(&vanillaLinkedList, i);
//        printf("i=%d\n", i);
    }
    vanillaLinkedList.print(vanillaLinkedList);
//    vanillaLinkedList.addAt(&vanillaLinkedList, 4123312, 1);
//    vanillaLinkedList.print(vanillaLinkedList);

    for (int i = -1; i <= 21; i++) {
        int pos = i;
        Node *element = vanillaLinkedList.get(vanillaLinkedList, pos);
        if (element != NULL) printf("\nat = %d, value = %.1f", pos, element->data);
        else printf("\nIsh num alcancou");
    }

    return 0;
}
