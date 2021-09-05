#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int SIZE_OF_OUTPUT_ARRAY = 10;

void generate_array(float *array);
void print_array(float *array, int size);
void get_output_values(float *output_array, float *input_array);

int main() {
	srand(time(NULL));

	//allocates memory for arrays
	float *input_values = (float*)malloc(2*SIZE_OF_OUTPUT_ARRAY*sizeof(float));
	float *output_values = (float*)malloc(SIZE_OF_OUTPUT_ARRAY*sizeof(float));
	//generates input array and perform task by filling output_values
	generate_array(input_values);
	get_output_values(output_values, input_values);
	//printing arrays of input and output values ​​to demonstrate the results of the program
	printf("Вхідний масив випадкових чисел:\n");
	print_array(input_values, SIZE_OF_OUTPUT_ARRAY*2);

	printf("\nВихідний масив чисел:\n");
	print_array(output_values, SIZE_OF_OUTPUT_ARRAY);
	//free allocated memory
	free(input_values);
	free(output_values);
	return 0;
}

void generate_array(float *array) {
	//generates array of float numbers from 0 to 10
	for (int i = 0; i < 2 * SIZE_OF_OUTPUT_ARRAY; i++)
		*(array + i) = (float)rand()/(float)RAND_MAX/0.1;
}

void print_array(float *array, int size) {
	for (int i = 0; i < size; i++)
		printf("%.3f ", *(array + i));

}

void get_output_values(float *output_array, float  *input_array){
	for (int i = 0; i < SIZE_OF_OUTPUT_ARRAY; i++)
		//the last index is SIZE.. - 1, because indexation starts from 0
		*(output_array+i) = *(input_array + i) + *(input_array + 2*SIZE_OF_OUTPUT_ARRAY-1-i);

}
