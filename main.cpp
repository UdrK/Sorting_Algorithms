#include <chrono>
#include <iostream>
#include <stdlib.h>
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

void time(int* array, int array_size) {
	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	for(int i=0; i<array_size; i++) {
		array[i] -= 1;
	}
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds> (end - begin).count() << "[ms]" << std::endl;
}

int main() {

	int array_size = 5;
	int max_element = 12;
	int* array = (int*) malloc (sizeof(int) * array_size);
	initialize_random_array(array, array_size, max_element);
	print_array(array, array_size);

	Sorter<int>* s = new Sorter<int>();
	std::cout<<"cutting_sort"<<std::endl;
	s->cutting_sort(array, array_size);

	print_array(array, array_size);
	free(array);
}
