#include <limits.h>
#include <time.h>

#define MIN_VAL 0
#define MAX_VAL INT_MAX


void
swap(int *arr, int i, int j)
{
    int tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}


void
sort(int *arr, int n, double *time)
{
    clock_t start, end;
    start = clock();
    for (int i = 0; i < (n-1); ++i) {
        int min = i;
        for (int j = i + 1; j < n; ++j)
            if (arr[j] < arr[min]) min = j;
        
        if (arr[min] < arr[i]) swap(arr, min, i);
    }
    end = clock();
    *time = ((double) (end - start)) / CLOCKS_PER_SEC;
}