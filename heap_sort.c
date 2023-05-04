#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <inttypes.h>
#include <math.h>

#define SIZE_1 50000
#define SIZE_2 1000000
#define STEP 50000

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

void swap(uint32_t* x, uint32_t* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}


void heapify(uint32_t* arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heap_sort(uint32_t* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    uint32_t* arr;
    uint32_t* heap;

    int i, j;
    double start, end;

    printf("Number\t Heap sort\n");

    for (i = SIZE_1; i <= SIZE_2; i += STEP) {
        arr = (uint32_t*)malloc(i * sizeof(uint32_t));
        heap = (uint32_t*)malloc(i * sizeof(uint32_t));

        for (j = 0; j < i; j++) {
            arr[j] = (uint32_t)getrand(0, 100001);
            heap[j] = arr[j];
        }

        printf("%d\t", i);

        start = wtime();
        heap_sort(heap, i);
        end = wtime() - start;
        printf("%15.7lf", end);

        printf("\n");
        free(arr);
        free(heap);
    }

    return 0;
}