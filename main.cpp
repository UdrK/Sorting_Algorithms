#include <iostream>
#include <time.h>
#include "Sorter.h"

void print_array(int* array, int array_size) {
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
	s->quicksort(array, array_size);

	print_array(array, array_size);
}
