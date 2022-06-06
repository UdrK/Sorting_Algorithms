#include <windows.h> 
#include "ThreadsafeQueue.h"
#include <iostream>
#include <list>

#ifndef SORTER_H
#define SORTER_H

template <class T>
class Sorter {
    public:
        void selection_sort(T*, int);
        void recursive_selection_sort(T*, int);
        void insertion_sort(T*, int);
        void bubble_sort(T*, int);
        void quicksort(T*, int);
        void merge_sort(T*, int);
        void sleep_sort(int*, int);
        void cutting_sort(int*, int);
        void cosmic_sort(T*, int);
        int stalin_sort(T*, int);
        std::list<T> smart_stalin_sort(T*, T, int, int);
};

// PRIVATE -------------------------------------------------------------------

template <class T>
void shift_array(T* array, int index, int array_size) {
    for(int i=index; i<array_size-1; i++) {
        array[i] = array[i+1];
    }
}

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
int __quicksort_partition(T* array, int start, int end) {
    int pivot = array[end];
    int i = start-1;
    for(int j=start; j <= end-1; j++) {
        if(array[j] < pivot) {
            i+=1;
            __swap(array, i, j);
        }
    }
    i+=1;
    __swap(array, i, end);
    return i;
}

template <class T>
void __quicksort(T* array, int start, int end) {

    if(start < end) {
       int q = __quicksort_partition(array, start, end);
       __quicksort(array, start, q-1);
       __quicksort(array, q+1, end);
    }

}

template <class T>
void __merge(T* array, int start, int middle, int end) {
    int size_l = middle - start + 1;
    int size_r = end - middle;
    T left[size_l], right[size_r];

    for(int i=0; i < size_l; i++)
        left[i] = array[start + i];

    for(int i=0; i < size_r; i++)
        right[i] = array[middle + 1 + i];


    int i=0, j=0, k = start;
    while(i < size_l && j < size_r) {
        if(left[i] <= right[j]) {
            array[k] = left[i];
            i++;
        }
        else {
            array[k] = right[j];
            j++;
        }
        k++;
    }

    while(i < size_l) {
        array[k] = left[i];
        i++;
        k++;
    }

    while(j < size_r) {
        array[k] = right[j];
        j++;
        k++;
    }
}

template <class T>
void __merge_sort(T* array, int start, int end) {

    if(start < end) {
       int middle = start + (end - start) / 2;
       __merge_sort(array, start, middle);
       __merge_sort(array, middle + 1, end);
       __merge(array, start, middle, end);
    }
}

struct __sleep_parameters {
    int* element;
    ThreadsafeQueue<int>* queue;
};

DWORD __sleep(LPVOID parameters)
{
    __sleep_parameters* sleep_p = (__sleep_parameters*)parameters;

    int val = *(sleep_p->element);

    Sleep((int)val * 1000);

    sleep_p->queue->push(val);

    return 0;
}

// PUBLIC --------------------------------------------------------------------

/*
Best case: O(n^2)
Worst case: O(n^2)
Average case: O(n^2)
*/
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
};

/*
Same complexity as iterative selection sort.
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

/*
Best case: O(n)
Worst case: O(n^2)
Average case: O(n^2)
*/
template <class T>
void Sorter<T>::insertion_sort(T* array, int array_size) {
    for(int i=0; i < array_size; i++) {
        for(int j=i; j > 0 && array[j-1] > array[j]; j--) {
            __swap(array, j, j-1);
        }
    }
}

/*
Best case: O(n)
Worst case: O(n^2)
Average case: O(n^2)
*/
template <class T>
void Sorter<T>::bubble_sort(T* array, int array_size) {
    int size_update;
    while(array_size > 1) {
        size_update = 0;
        for(int i=1; i < array_size; i++) {
            if(array[i-1] > array[i]) {
                __swap(array, i-1, i);
                size_update = i;
            }
        }
        array_size = size_update;
    }
}

/*
Best case: O(n logn)
Worst case: O(n^2)
Average case: O(n logn)
Wraps call to implementation based on Cormen's Introduction to algorithms, which needs starting and ending indeces
*/
template <class T>
void Sorter<T>::quicksort(T* array, int array_size) {
    __quicksort(array, 0, array_size-1);
}

/*
Best case: O(n logn)
Worst case: O(n logn)
Average case: O(n logn)
Wraps call to implementation based on Cormen's Introduction to algorithms, which needs starting and ending indeces
*/
template <class T>
void Sorter<T>::merge_sort(T* array, int array_size) {
    __merge_sort(array, 0, array_size - 1);
}

/*
PRE-CONDITION: elements must be int >= 0
SIMPLE-SOLUTION: new_array = min(array) + array[i] for i in range(0, len(array))
Best case: O(max(array))
Worst case: doesn't correctly sort the array
The algorithm starts a thread for element in the array. Each thread sleeps 'array[i]' seconds. After sleeping
each array writes its 'array[i]' in a thread safe queue. In this way, the queue is filled in order.
When array size is very large, some threads may end before each thread has started. 
To avoid this, ideally every thread should start at the same time.
*/
template <class T>
void Sorter<T>::sleep_sort(int* array, int array_size) {

    HANDLE handles[array_size];
    __sleep_parameters parameters[array_size];
    ThreadsafeQueue<int>* threadsafe_q = new ThreadsafeQueue<int>();

    for(int i = 0; i < array_size; i++)
        parameters[i] = { &array[i], threadsafe_q };

    for(int i = 0; i < array_size; i++)
        handles[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&__sleep, 
                                  (LPVOID)&parameters[i], 0, NULL);

    WaitForMultipleObjects(array_size, handles, 1, INFINITE);

    for(int i=0; threadsafe_q->size()>0; i++)
        array[i] = threadsafe_q->pop();
}

/*
PRE-CONDITION: elements must be int >= 0
SIMPLE-SOLUTION: new_array = min(array) + array[i] for i in range(0, len(array))
Best case: O(n)
Worst case: O(MAX_INT*n)
Average case: O(max(array)*n)
Inspired by sleep sort, this algorithm uses an increasing counter to determine the order of the elements:
a counter 'c' starts from zero, and keeps increasing, when array[i] - c == 0, array[i] is pushed at the beginning of the array.
*/
template <class T>
void Sorter<T>::cutting_sort(int* array, int array_size) {

    int* array_copy = (int*) malloc (sizeof(int) * array_size);
    for(int i=0; i<array_size; i++)
        array_copy[i] = array[i];


    int j=0, c=0;
    while(j<array_size) {
        for(int i=0; i<array_size; i++) {
            if((array_copy[i] - c) == 0) {
                array[j] = array_copy[i];
                j++;
            }
        }
        c++;
    }
    free(array_copy);
}
/*
Best case: O(1) (go buy a lottery ticket)
Worst case: ∞
Average case: > Heat death of the universe
Waits for cosmic rays to flip enough bits to order the array. More probably the bool variable in_order will be flipped before that happens
*/
template <class T>
void Sorter<T>::cosmic_sort(T* array, int array_size) {

    bool in_order = false;

    while (!in_order) {
        for(int i=0; i<array_size-1; i++) {
            if(array[i]>array[i+1]) {
                i=-1;
            }
        }
        in_order = true;
    }
}

/*
Best case: O(n)
Worst case: O(n)
Average case: O(n)
Orders the array by removing out of order elements
*/
template <class T>
int Sorter<T>::stalin_sort(T* array, int array_size) {

    for(int i=0; i<array_size-1; i++) {
        if(array[i+1] < array[i]) {
            shift_array(array, i+1, array_size);
            array_size -= 1;
            i -= 1;
        }
    }

    return array_size;
}

/*
Best case: ?
Worst case: ?
Average case: ?
Similar to Stalin Sort but this one is smart. It removes the minimum number of elements from the array in order to have the longest ordered non-consecutive subsequence
*/
template <class T>
std::list<T> Sorter<T>::smart_stalin_sort(T* array, T last_item, int index, int array_size) {
    if (index == array_size - 1)
        if (array[index] >= last_item)
            return {array[index]};
        else
            return {};
    else {
        if (array[index] >= last_item) {
            std::list<T> l1 = {array[index]};
            l1.splice(l1.end(), smart_stalin_sort(array, array[index], index+1, array_size));
            std::list<T> l2 = smart_stalin_sort(array, last_item, index+1, array_size);
            if (l1.size() > l2.size())
                return l1;
            else return l2;
        } else
            return smart_stalin_sort(array, last_item, index+1, array_size);
    }
}
#endif
