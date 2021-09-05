#include <ctime>
#include <iostream>

using namespace std;
const int ARRAY_SIZE = 1000;

int * bubble_sort(int array[]);
int inline_search(int element, int array[]);
int binary_search(int element, int array[], int low, int high);

int main() {
	srand(time(NULL));
	int array[ARRAY_SIZE];
	//generates array
	for (int i = 0; i < ARRAY_SIZE; i++)
		array[i] = (rand() % 4000) - 2000;


	int *sorted_array = bubble_sort(array);

	cout << "Час виконання пошуків для " << ARRAY_SIZE << " елементів\n";
	clock_t start = clock();
	inline_search(sorted_array[728], sorted_array);
	clock_t end = clock();
	cout << "Час виконання лінйного пошуку: " << (float(end - start)) / CLOCKS_PER_SEC << " секунд\n";

	start = clock();
	binary_search(sorted_array[728], sorted_array, 0, ARRAY_SIZE-1);
	end = clock();
	cout << "Час виконання бінарного пошуку: " << (float(end - start)) / CLOCKS_PER_SEC << " секунд\n";

	return 0;
}

int * bubble_sort(int array[]) {
	int tmp;
	for (int i = 0; i < ARRAY_SIZE; i++)
		//the biggest element moves to the last position, so we shouldn`t check it
		for (int j = 0; j < ARRAY_SIZE - i - 1; j++)
			if(array[j] > array[j+1]) {
				tmp = array[j];
				array[j] = array[j+1];
				array[j+1] = tmp;
			}
	return array;
}

int inline_search(int element, int array[]){
	for (int i = 0; i < ARRAY_SIZE; i++)
		if (array[i] == element)
			return i;
	return -1;
}

int binary_search(int element, int array[], int low, int high) {
	if (high < low)
		return -1;
	int mid = (low + high)/2;
	if (array[mid] > element)
		return binary_search(element, array, low, mid-1);
	else if (array[mid] < element)
		return binary_search(element, array, mid+1, high);
	else
		return mid;
}
