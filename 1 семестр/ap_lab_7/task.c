#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int SIZE_OF_ARRAY = 10;

void generate_array(float *array);
void print_array(float *array);
int find_heighbours(float *array);

int main() {
    srand(time(NULL));
    float *array = (float*)malloc(2 * SIZE_OF_ARRAY*sizeof(float));

    generate_array(array);
    print_array(array);

    printf("\nЧисло сусідств двох позитивних чисел: %i\n", find_heighbours(array));
    free(array);
    return 0;
}

void generate_array(float *array) {
	//generates array of float numbers from -10 to 10
	for (int i = 0; i < 2 * SIZE_OF_ARRAY; i++)
		*(array + i) = (float)rand()/(float)RAND_MAX/0.05-10;
}

int find_heighbours(float *array) {
    //from 1, we can`t check previous element for zero index
    int num_of_neighbourhoods = 0;
    for (int i = 1; i < SIZE_OF_ARRAY; i++)
        if (*(array + i) > 0 && *(array + i-1) > 0)
            num_of_neighbourhoods++;
    return num_of_neighbourhoods;
}

void print_array(float *array) {
	for (int i = 0; i < SIZE_OF_ARRAY; i++)
		printf("%.1f ", *(array + i));

}
