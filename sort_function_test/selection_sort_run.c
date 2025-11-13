#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "selection_sort.h"


int
main(int argc, char *argv[])
{
    double time;
    int arr[SIZE];
    for (int i = 0; i < SIZE; ++i)
        arr[i] = (rand() % (INT_MAX / 10));
    
    fprintf(stdout, "Ordenando array\n");
    sort(arr, SIZE, &time);
    fprintf(stdout, "Array ordenado\n");
    
    fprintf(stdout, "Tempo total da ordenacao: %lf segundos\n", time);

    return 0;
}