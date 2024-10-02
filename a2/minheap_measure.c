#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "minheap.h"

// Function prototypes
void fillArrayDescending(int values[], int size);
double measureTime(MinHeap* (*buildHeap)(int[], int), int values[], int size, int repetitions);

int main() {
    int sizes[] = {10, 100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    int repetitions = 10;

    for (int i = 0; i < numSizes; i++) {
        int size = sizes[i];
        int* values = (int*)malloc(size * sizeof(int));

        fillArrayDescending(values, size);

        double timeSajad = measureTime(buildHeap_Sajad, values, size, repetitions);
        double timeElaheh = measureTime(buildHeap_Elaheh, values, size, repetitions);

        printf("Size: %d, Sajad Time: %f, Elaheh Time: %f\n", size, timeSajad, timeElaheh);

        free(values);
    }

    return 0;
}

void fillArrayDescending(int values[], int size) {
    for (int i = 0; i < size; i++) {
        values[i] = size - i;
    }
}

double measureTime(MinHeap* (*buildHeap)(int[], int), int values[], int size, int repetitions) {
    clock_t start, end;
    double totalTime = 0.0;

    for (int i = 0; i < repetitions; i++) {
        start = clock();
        MinHeap* heap = buildHeap(values, size);
        deleteHeap(heap);
        end = clock();

        totalTime += (double)(end - start) / CLOCKS_PER_SEC;
    }

    return totalTime * 10;
}