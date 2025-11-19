#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "selection_sort.h"


int
main(int argc, char *argv[])
{
    double time[3];
    int arr[SIZE];
    for (int i = 0; i < SIZE; ++i)
        arr[i] = (rand() % (INT_MAX / 10));
    
    fprintf(stdout, "Ordenando array aleatório\n");
    sort(arr, SIZE, &time[0]);
    fprintf(stdout, "Ordenacao concluida\n");
    
    fprintf(stdout, "Ordenando array ja ordenado\n");
    sort(arr, SIZE, &time[1]);
    fprintf(stdout, "Ordenacao concluida\n");
    
    invert(arr, SIZE);
    fprintf(stdout, "Ordenando array invertido\n");
    sort(arr, SIZE, &time[2]);
    fprintf(stdout, "Ordenacao concluida\n\n");
    
    fprintf(stdout, "Tempo total da ordenacao aleatoria: %lf segundos\n", time[0]);
    fprintf(stdout, "Tempo total da re-ordenacao: %lf segundos\n", time[1]);
    fprintf(stdout, "Tempo total da ordenacao invertida: %lf segundos\n", time[2]);

    return 0;
}