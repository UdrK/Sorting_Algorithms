#include "Sorter.h"

// PRIVATE -------------------------------------------------------------------

void __swap(int* array, int a, int b) {
    int aux = array[a];
    array[a] = array[b];
    array[b] = aux;
}

int __min_in_array(int* array, int array_size) {
    int min = 0;
    for(int i=0; i<array_size; i++) {
        if(array[i] < array[min])
            min = i;
    }
    return min;
}

// PUBLIC --------------------------------------------------------------------

void Sorter::selection_sort(int* array, int array_size) {
    int min = 0;
    int aux = 0;
    for(int i=0; i<array_size-1; i++) {
        min = i;
        for(int j=i+1; j<array_size; j++) {
            if(array[j] < array[min]) {
                min = j;
            }  
        }
        if(min != i) {
            __swap(array, min, i);
        }
    }
    return;
};
