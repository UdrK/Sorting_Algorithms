#ifndef SORTER_H
#define SORTER_H

template <class T>
class Sorter {
    public:
        void selection_sort(T*, int);
        void recursive_selection_sort(T*, int);
        void quicksort(T*, int);
        // void insertion_sort(T*, int);
        // void bubble_sort(T*, int);
        // void heap_sort(T* array, int array_size);
        // void merge_sort(T* array, int array_size);
        // void sleep_sort(T* array, int array_size);
};

// PRIVATE -------------------------------------------------------------------

template <class T>
void __swap(T* array, int a, int b) {
    int aux = array[a];
    array[a] = array[b];
    array[b] = aux;
}

template <class T>
int __min_in_array(T* array, int array_size) {
    int min = 0;
    for(int i=0; i<array_size; i++) {
        if(array[i] < array[min])
            min = i;
    }
    return min;
}

template <class T>
int __quicksort_partition(T* array, int b, int e) {
    int pivot = array[e];
    int i = b-1;
    for(int j=b; j <= e-1; j++) {
        if(array[j] < pivot) {
            i+=1;
            __swap(array, i, j);
        }
    }
    i+=1;
    __swap(array, i, e);
    return i;
}

template <class T>
void __quicksort(T* array, int b, int e) {

    if(b < e) {
       int q = __quicksort_partition(array, b, e);
       __quicksort(array, b, q-1);
       __quicksort(array, q+1, e);
    }

}

// PUBLIC --------------------------------------------------------------------

template <class T>
void Sorter<T>::selection_sort(T* array, int array_size) {
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
template <class T>
void Sorter<T>::recursive_selection_sort(T* array, int array_size) {
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

// Calls implementation based on Cormen's Introduction to Algorithm
template <class T>
void Sorter<T>::quicksort(T* array, int array_size) {
    __quicksort(array, 0, array_size-1);
}

#endif