#include <iostream>
#include <time.h>
#include "Sorter.h"

template <typename T>
void print_array(T* array, int array_size) {
	for(int i=0; i < array_size; i++) {
		std::cout<<array[i]<<" ";
	}
	std::cout<<std::endl;
}

void initialize_random_array(int* array, int array_size, int max_element) {
	srand(time(NULL));
	for(int i=0; i < array_size; i++) {
		array[i] = rand() % max_element + 1;
	}
}

int main() {
	int array_size = 10;
	int max_element = 1000;
	int array[array_size];
	initialize_random_array(array, array_size, max_element);
	print_array(array, array_size);

	Sorter<int>* s = new Sorter<int>();
	std::cout<<"bubble_sort"<<std::endl;
	s->merge_sort(array, array_size);

	print_array(array, array_size);
}
