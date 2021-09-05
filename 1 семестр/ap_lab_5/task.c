#include <stdio.h>
#include <stdlib.h>
#include <time.h>
const int SIZE_OF_FIRST_ARRAY = 12;
const int SIZE_OF_SECOND_ARRAY = 15;

void generate_sorted_array(int *array, int size);
void print_array(int *array, int size);
void merge(int* first_array, int* second_array, int* merged_array);

int main() {
	srand(time(NULL));
	int *first_array = (int*)malloc(SIZE_OF_FIRST_ARRAY*sizeof(int));
	int *second_array = (int*)malloc(SIZE_OF_SECOND_ARRAY*sizeof(int));
	int *merged_array = (int*)malloc((SIZE_OF_FIRST_ARRAY + SIZE_OF_SECOND_ARRAY)*sizeof(int));

	generate_sorted_array(first_array, SIZE_OF_FIRST_ARRAY);
	generate_sorted_array(second_array, SIZE_OF_SECOND_ARRAY);

	printf("Перший масив, розміру %i\n", SIZE_OF_FIRST_ARRAY);
	print_array(first_array, SIZE_OF_FIRST_ARRAY);
	printf("\nДругий масив, розміру %i\n", SIZE_OF_SECOND_ARRAY);
	print_array(second_array, SIZE_OF_SECOND_ARRAY);

    merge(first_array, second_array, merged_array);

    printf("\nОтриманий в результаті злиття масив:\n");
    print_array(merged_array, SIZE_OF_FIRST_ARRAY + SIZE_OF_SECOND_ARRAY);

    printf("\n");
    free(first_array);
    free(second_array);
    free(merged_array);
	return 0;
}

void generate_sorted_array(int *array, int size){
	int element, available_index;
	//generates sorted array of random numbers [-100 100] (~inserion sort)
	for (int i = 0; i < size; i++) {
		//new element
		element = (rand()%201) -100;
		//available position for new element
		available_index = i;
		/* searching position for element in sorted array, started from previous
		   index and going backwards to zero*/
		for(int j = i-1; j >= 0; j--)
			/* if new element less than previous, previous element goes to previous
			   available position, and its index becomes new available position.
			   Otherwise loop breaks*/
			if(element < *(array + j)) {
				*(array + available_index) = *(array + j);
				available_index = j;
			} else
				break;
		//new element goes to last available position
		*(array + available_index) = element;
	}
}

void print_array(int *array, int size) {
	for (int i = 0; i < size; i++)
		printf("%i ", *(array + i));
}

void merge(int* first_array, int* second_array, int* merged_array){
	for (int i = 0,j = 0,k = 0; i < SIZE_OF_FIRST_ARRAY+SIZE_OF_SECOND_ARRAY; i++)
		/* this condition works when current element of first array less then
		   current element of second array and current element of first array
		   exist, or when current element of second array doesn`t exist

		   it choses the smallest element between two smallest elements (in their
		   array and pushes it to merged_array) */
		if((*(first_array + j) < *(second_array + k) && j != SIZE_OF_FIRST_ARRAY) || k == SIZE_OF_SECOND_ARRAY) {
			*(merged_array + i) = *(first_array + j);
			j++;
		} else {
			*(merged_array + i) = *(second_array + k);
			k++;
		}
}
