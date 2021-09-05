#include <iostream>

using namespace std;
const int ARRAY_SIZE = 200;


int * fy_shuffle(int array[]);
int biggest_digit(int num);
bool is_condition_true(int old_num, int new_num);
int * selection_sort(int array[]);

int main() {
	int array[ARRAY_SIZE];
	for (int i = 1; i <= ARRAY_SIZE; i++)
		array[i-1] = i;

	int * p_array = fy_shuffle(array);

	p_array = selection_sort(p_array);

	cout << "Відсортований масив: " << endl;
	for (int i = 0; i < ARRAY_SIZE; i++)
		cout << p_array[i] << " ";



	return 0;
}

int * fy_shuffle(int array[]) {
	srand(time(NULL));
	int j, tmp;
	for (int i = ARRAY_SIZE-1; i >= 1; i--) {
		j = rand()%(i + 1);

		// element swap
		tmp = array[i];
		array[i] = array[j];
		array[j] = tmp;
	}
	return array;
}

int * selection_sort(int array[]) {
	int min_index, tmp;
    //standart selection sort: finds the smallest element from [i, end] and swap it with i element
	for (int i = 0; i < ARRAY_SIZE-1; i++) {
		min_index = i;
		for (int j = i+1; j < ARRAY_SIZE; j++)
        //searching the smallest element
			if (is_condition_true(array[min_index], array[j]))
				min_index = j;
        //swap
		tmp = array[i];
		array[i] = array[min_index];
		array[min_index] = tmp;

	}
	return array;
}

bool is_condition_true(int old_num, int new_num){
    //if the biggest digit of previous number is bigger than current one condition is true
	if (biggest_digit(new_num) < biggest_digit(old_num))
		return true;
    // if they are equal we should look at their absolute values
	if (biggest_digit(new_num) == biggest_digit(old_num))
		return (new_num < old_num) ? true : false;
	return false;
}

int biggest_digit(int num) {
	int biggest_digit = 0, numeric_digit[3] = {100, 10, 1};
	for (int i = 0; i < 3; i++) {
        //get integer part of number on 10 in some power, it will our digit, which we will compare
		if(num/numeric_digit[i] > biggest_digit)
			biggest_digit = num/numeric_digit[i];
        //remove this integer part.. for example after 845 we will get 45
		num = num%numeric_digit[i];
	}
	return biggest_digit;
}
