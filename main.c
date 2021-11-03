#include <stdio.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>
#include "LinkedList.h"

void insertLinkedList(LinkedList *list, double arr[], int n) {
    for (int i = 0; i <= n; i++) {
        list->add(list, arr[i]);
    }
}

void wcsInsertLinkedList(LinkedList *list, double arr[], int n) {
    for (int i = 0; i <= n; i++) {
        if (i % 2 == 0)
            list->add(list, i);
    }
    for (int i = 0; i <= n; i++) {
        if (i % 2 == 1)
            list->add(list, i);
    }
}

void destroyLinkedList(LinkedList *list, double arr[], int n) {
    while (list->delete(list));
}

void iterLinkedList(LinkedList *list, double arr[], int n) {
    for (Node node = list->getFirst(*list); !list->isDone(node); node = list->next(node)) {}
}

void sortLinkedList(LinkedList *list, double arr[], int n) {
    list->sort(list);
}

void emptyFunction(double data) {}

void fastIterLinkedList(LinkedList *list, double arr[], int n) {
    list->forEach(*list, emptyFunction);
}

double
benchmark(void (*f)(LinkedList *list, double arr[], int n), LinkedList *list, double arr[], int n, const char *text) {
    clock_t startTime = clock();
    f(list, arr, n);
    clock_t endTime = clock();

    double elapsedTimeSeconds = ((double) endTime - (double) startTime) / (double) CLOCKS_PER_SEC;
    printf("%s = %f ms\n", text, elapsedTimeSeconds * 1E3);
    return elapsedTimeSeconds;
}

float mean(const float array[], size_t size) {
    float mean = 0;
    for (int i = 0; i < size; i++) {
        mean += array[i];
    }
    mean /= (float) size;
    return mean;
}

float stdev(const float array[], size_t size) {
    float mean_calc = mean(array, size);
    float sigma = 0;

    for (int i = 0; i < size; i++) {
        sigma += powf((mean_calc - array[i]), 2);
    }
    return sqrtf(sigma / (float) size);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <elements-number> <nb-experiments> <#experimento> (see run.py)\n", argv[0]);
        exit(-1);
    }

    srand(clock());

    int n = atoi(argv[1]);
    int nb_exp = atoi(argv[2]);
    int exp_num = atoi(argv[3]);

    const char *header = "#num,type,size,mean,stdev";
    FILE *insertion_file = fopen("insertion.csv", "a");
    FILE *iteration_file = fopen("iteration.csv", "a");
    FILE *foreach_iteration_file = fopen("foreach_iteration.csv", "a");
    FILE *destroy_file = fopen("destroy.csv", "a");
    FILE *sort_file = fopen("sort.csv", "a");
    FILE *sort_wcs_file = fopen("sort_wcc.csv", "a");

    double classic_insertion_times[nb_exp];
    double unrolled_insertion_times[nb_exp];

    double classic_iteration_times[nb_exp];
    double unrolled_iteration_times[nb_exp];

    double classic_forEach_iteration_times[nb_exp];
    double unrolled_forEach_iteration_times[nb_exp];

    double classic_sort_times[nb_exp];
    double unrolled_sort_times[nb_exp];

    double classic_destroy_times[nb_exp];
    double unrolled_destroy_times[nb_exp];

//    double classic_wcs_times[nb_exp];
//    double unrolled_wcs_times[nb_exp];

    for (int i = 0; i < nb_exp; ++i) {

        // Create an array of random double elements
        double array[n];
        for (int j = 0; j < n; ++j) {
            array[j] = 1000 * ((double) rand() / RAND_MAX);
        }

        LinkedList classicLl = initLinkedList(CLASSIC);
        classic_insertion_times[i] = benchmark(insertLinkedList, &classicLl, array, n, "Classic Insertion time");

        LinkedList unrolledLl = initLinkedList(UNROLLED);
        unrolled_insertion_times[i] = benchmark(insertLinkedList, &unrolledLl, array, n, "Unrolled Insertion time");

        classic_iteration_times[i] = benchmark(iterLinkedList, &classicLl, NULL, n, "Classic Iteration time (Begin-End) ");
        unrolled_iteration_times[i] = benchmark(iterLinkedList, &unrolledLl, NULL, n, "Unrolled Iteration time (Begin-End) ");

        classic_forEach_iteration_times[i] = benchmark(fastIterLinkedList, &classicLl, NULL, n,
                                                       "Classic Foreach Iteration time (Begin-End) ");
        unrolled_forEach_iteration_times[i] = benchmark(fastIterLinkedList, &unrolledLl, NULL, n,
                                                        "Unrolled Foreach Iteration time (Begin-End) ");

        classicLl.simplePrint(classicLl);
        unrolledLl.simplePrint(unrolledLl);

        classic_sort_times[i] = benchmark(sortLinkedList, &classicLl, NULL, n, "Classic Sort time (random) ");
        unrolled_sort_times[i] = benchmark(sortLinkedList, &unrolledLl, NULL, n, "Unrolled Sort time (random) ");

        classicLl.simplePrint(classicLl);
        unrolledLl.simplePrint(unrolledLl);

        classic_destroy_times[i] = benchmark(destroyLinkedList, &classicLl, NULL, n, "Classic Destroy time ");
        unrolled_destroy_times[i] = benchmark(destroyLinkedList, &unrolledLl, NULL, n, "Unrolled Destroy time ");

        classicLl.simplePrint(classicLl);
        unrolledLl.simplePrint(unrolledLl);
//
//        classicLl = initLinkedList(CLASSIC);
//        wcsInsertLinkedList(&classicLl, n);
//        unrolledLl = initLinkedList(UNROLLED);
//        wcsInsertLinkedList(&unrolledLl, n);
//
//        classic_wcs_times[i] = benchmark(sortLinkedList, &classicLl, n, "Classic Sort time (WCC) ");
//        unrolled_wcs_times[i] = benchmark(sortLinkedList, &unrolledLl, n, "Unrolled Sort time (WCC) ");
    }

//    LinkedList classicLl = initLinkedList(CLASSIC);
//    benchmark(insertLinkedList, &classicLl, n, "Classic Insertion time");
//
//    LinkedList unrolledLl = initLinkedList(UNROLLED);
//    benchmark(insertLinkedList, &unrolledLl, n, "Unrolled Insertion time");
//
//    benchmark(iterLinkedList, &classicLl, n, "Classic Iteration time (Begin-End) ");
//    benchmark(iterLinkedList, &unrolledLl, n, "Unrolled Iteration time (Begin-End) ");
//
//    benchmark(fastIterLinkedList, &classicLl, n,
//                                                   "Classic Foreach Iteration time (Begin-End) ");
//    benchmark(fastIterLinkedList, &unrolledLl, n,
//                                                    "Unrolled Foreach Iteration time (Begin-End) ");
//
//    benchmark(sortLinkedList, &classicLl, n, "Classic Sort time (random) ");
//    benchmark(sortLinkedList, &unrolledLl, n, "Unrolled Sort time (random) ");
//
//    benchmark(destroyLinkedList, &classicLl, n, "Classic Destroy time ");
//    benchmark(destroyLinkedList, &unrolledLl, n, "Unrolled Destroy time ");


    /*
     * MY TEST AREA
     */

    /*
     * TESTS VANILLA LINKED LIST
     */
//    LinkedList mbLinkedList = initLinkedList(UNROLLED);
//    for (int i = 43; i >= 0; i--) {
//        mbLinkedList.addLast(&mbLinkedList, ((double) rand()/INT_MAX));
//    }
//    mbLinkedList.simplePrint(mbLinkedList);
////    printf("\n");
//    mbLinkedList.sort(&mbLinkedList);
//    mbLinkedList.simplePrint(mbLinkedList);
//    for (int i = 0; i <= 21; ++i) {
//        bool removed = mbLinkedList.delete(&mbLinkedList);
//    }

    return 0;
}
