#include <stdio.h>
#include <stdlib.h>
#include <time.h>
const int SIZE = 100;

void generate_array(int array[]);
void insertion_sort(int array[]);
void print_array(int array[]);

int main() {
	srand(time(NULL));
	int array[SIZE];

	generate_array(array);
	insertion_sort(array);
	print_array(array);
	return 0;
}

void generate_array(int array[]) {
	for (int i = 0; i < SIZE; i++)
		array[i] = rand()%2001 - 1000;
}

void insertion_sort(int array[]){
	int cur_element, available_index;
	for (int i = 0; i < SIZE; i++) {
		available_index = i;
		cur_element = array[i];
		for (int j = i-1; j >= 0; j--) {
			if (cur_element < array[j]) {
				array[available_index] = array[j];
				available_index = j;
			} else {
				break;
			}
		}
		array[available_index] = cur_element;
	}
}

void print_array(int array[]){
	for (int i = 0; i < SIZE; i++) {
		printf("%i ", array[i]);
	}
}
