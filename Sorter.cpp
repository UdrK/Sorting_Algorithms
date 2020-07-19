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

/*
Base idea:
sorted_array(Array) = min(Array) + max(Array)                   if size(Array) = 2
sorted_array(Array) = min(Array) + sorted(Array-min(Array))     if size(Array) > 2
*/
void Sorter::recursive_selection_sort(int* array, int array_size) {
    if(array_size == 2) {
        if (array[1] < array[0]) {
            __swap(array, 0, 1);
        } 
        return;
    } 
    else {
        // first element is min of array
        int min = __min_in_array(array, array_size);
        __swap(array, min, 0);

        // rest of array is sorted array
        recursive_selection_sort(array+1, array_size-1);
        return;
    }
};