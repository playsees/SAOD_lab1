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

uint32_t find_max(uint32_t* arr, int n) {
    uint32_t max = 0;
    for (int i = 0; i < n; i++) {
        if (max < arr[i]) {
            max = arr[i];
        }
    }
    return max;
}

void radix_sort(uint32_t* arr, int n) {
	int i;
    uint32_t comma = 1;
	uint32_t max = find_max(arr, n);
	uint32_t *buffer = (uint32_t*)malloc(sizeof(uint32_t) * n);
	
	while ((max / comma) > 0)
	{
		uint32_t nums[10] = {0};
		for(i = 0; i < n; i++) {
			nums[arr[i] / comma % 10]++;
        }

		for(i = 1; i < 10; i++) {
			nums[i] += nums[i - 1];
        }

		for(i = n - 1; i >= 0; i--) {
            buffer[--nums[arr[i] / comma % 10]] = arr[i];
        }

		for(i = 0; i < n; i++) {
			arr[i] = buffer[i];
        }

		comma *= 10;
	}

	free(buffer);
}

int main() {
    uint32_t* arr;
    uint32_t* radix;

    int i, j;
    double start, end;

    printf("Number\t Radix Sort\n");

    for (i = SIZE_1; i <= SIZE_2; i += STEP) {
        arr = (uint32_t*)malloc(i * sizeof(uint32_t));
        radix = (uint32_t*)malloc(i * sizeof(uint32_t));

        for (j = 0; j < i; j++) {
            arr[j] = (uint32_t)getrand(0, 100001);
            radix[j] = arr[j];
        }

        printf("%d\t", i);

        start = wtime();
        radix_sort(radix, i);
        end = wtime() - start;
        printf("%15.7lf", end);

        printf("\n");
        free(arr);
        free(radix);
    }

    return 0;
}