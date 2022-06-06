# Sorting_Algorithms
Implementing some sorting algorithms in c++. The implemented algorithms are:

* Selection sort
* A recursive version of selection sort
* Insertion sort
* Bubble sort
* Quicksort
* Mergesort
* Sleep sort
* Cutting sort
* Cosmic sort
* Stalin sort
* Smart Stalin sort

As of the last update, the algorithms are implemented using template types, except for Sleep and Cutting sort which assume the input to be an array of positive integers.
While most of the algorithms implemented are the usual ones, i'm now looking into adding more strange and fun algorithms like sleep sort and cutting sort.

## What is sleep sort?
Sleep sort generates a thread for each element in the array, and makes the thread sleep __element__ seconds. In this way the threads end in order
and add the element to a thread-safe queue in order to return the ordered array once all threads have terminated. 

## What is cutting sort?
Cutting sort is an idea of mine: it was inspired by sleep sort and what it does is use a counter, which starts from 0, and compare it with each element of the array. Those that match the counter will be pushed into the ordered list. The counter is increased by 1, and the cycle continues until the ordered list is completed. I've called it cutting sort because i imagine the counter to be an axe, chopping away at the elements: when an element has been completely chopped it goes into the ordered list.

## What is cosmic sort?

Cosmic sort waits for cosmic rays (which can cause bit flips) to order the array for you. Error correction systems correct for this, especially when few bits are flipped, however it's theoretically
possible that cosmic rays could flip enough bits to order the array. Of course such an event isn't probable and if such a large number of bit flipping occurs in the array then it's much more probable that
the new array does not even include the original items, let alone them being in order. 

## What is stalin sort?

Stalin sort orders the array by removing out of order elements.

## What is smart stalin sort?

Smart Stalin sort is an idea of mine: it's Stalin sort but it removes the least elements possible, which means it finds the longest ordered non consecutive subsequence in the array. To highlight the difference between stalin sort and smart stalin sort, consider the array: [5, 3, 12, 4, 6]. Stalin Sort will return the array: [5, 12]. Smart Stalin Sort will return the array: [3, 4, 6]. 
