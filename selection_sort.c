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

void selection_sort(uint32_t* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        uint32_t min_index = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            swap(&arr[i], &arr[min_index]);
        }
    }
}

int main() {
    uint32_t* arr;
    uint32_t* selection;

    int i, j;
    double start, end;

    printf("Number\t   Selection Sor \n");

    for (i = SIZE_1; i <= SIZE_2; i += STEP) {
        arr = (uint32_t*)malloc(i * sizeof(uint32_t));
        selection = (uint32_t*)malloc(i * sizeof(uint32_t));

        for (j = 0; j < i; j++) {
            arr[j] = (uint32_t)getrand(0, 100001);
            selection[j] = arr[j];
        }

        printf("%d\t", i);

        start = wtime();
        selection_sort(selection, i);
        end = wtime() - start;
        printf("%15.7lf", end);

        printf("\n");
        free (arr);
        free(selection);
    }

    return 0;
}