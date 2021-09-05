#include <iostream>
#include <ctime>

using namespace std;

//Inputing future array sizes
const int F_ARR_SIZE = 6;
const int S_ARR_SIZE = 4;

//Creating structure "Person" with fields "surname" and "address"
struct Person {
	string surname;
	string address;
};

//Some data for rand() function
string surnames[20] = {"Мельник", "Шевченко", "Бойко", "Коваленко", "Бондаренко", "Ткаченко", "Ковальчук", "Кравченко", "Олійник", "Шевчук", "Поліщук", "Мороз", "Лисенко", "Руденко", "Савченко", "Андрієнко", "Кушнір", "Павлюк", "Василенко", "Білоус"};
string streets[10] = {"вул. Садова 23", "б-р. Шевченка 3-1а", "пл. Миру 12", "вул. Шкільна 2", "пр. Молодіжний 78", "вул. Гагаріна 19б", "вул. Лісова 66", "б-р. Лесі Українки 1", "вул. Котляревського 14", "пл. Богдана Хмельницького 7"};


void fill_array(Person* arr, int size);
Person generate_person();
void print_array(Person* arr, int size);
void concatenate(Person* result_array, Person* arr, int size, int* result_size);
bool is_element_in_array(Person* element, Person* array, int size);

int main() {
	srand(time(NULL));
	// allocating memory for arrays
	Person *first_array = new Person [F_ARR_SIZE];
	Person *second_array = new Person [S_ARR_SIZE];
	Person *result_array = new Person [S_ARR_SIZE+F_ARR_SIZE];
    int result_size = 0;
	//creating two array of Persons
	fill_array(first_array, F_ARR_SIZE);
	fill_array(second_array, S_ARR_SIZE);

    cout << "-----Перший масив-----"<<endl;
    print_array(first_array, F_ARR_SIZE);
    cout << "-----Другий масив-----"<<endl;
    print_array(second_array, S_ARR_SIZE);

	// performing main task
	concatenate(result_array, first_array, F_ARR_SIZE, &result_size);
    concatenate(result_array, second_array, S_ARR_SIZE, &result_size);

    cout << "-----Вихідний масив-----"<<endl;
	print_array(result_array, result_size);

	// free previously allocating memory
	delete [] first_array;
	delete [] second_array;
    delete [] result_array;
	return 0;
}

//filling array with random data from generate_person function
void fill_array(Person* arr, int size){
	Person element;
	int available_index;
	//generates sorted array (~inserion sort)
	for (int i = 0; i < size; i++) {
		//new element
		element = generate_person();
		//available position for new element
		available_index = i;
		/* searching position for element in sorted array, started from previous
		   index and going backwards to zero*/
		for(int j = i-1; j >= 0; j--)
			/* if new element less than previous, previous element goes to previous
			   available position, and its index becomes new available position.
			   Otherwise loop breaks*/
			if(element.surname < arr[j].surname) {
				arr[available_index] = arr[j];
				available_index = j;
			} else
				break;
		//new element goes to last available position
		arr[available_index] = element;
	}
}

//creating random persons
Person generate_person(){
	return {surnames[rand()%20], streets[rand()%10]};
}

//printing persons from array
void print_array(Person* arr, int size) {
	for (int i = 0; i < size; i++) {
		//if structure is empty - miss it
		if (arr[i].surname == "")
			continue;
		cout << arr[i].surname << " проживає за адресою " << arr[i].address << endl;
	}
}

//add to first array second one without repeats
void concatenate(Person* result_array, Person* arr, int size, int* result_size){
	for (int i = 0; i < size; i++) {
        //check if we already have this element
		if (is_element_in_array(&arr[i], result_array, *result_size))
            continue;
        //add element and increase result array "size"
		result_array[*result_size] = arr[i];
        (*result_size)++;
	}
}

bool is_element_in_array(Person* element, Person* array, int size){
    for (int i = 0; i < size; i++)
    // if we have element with the same surname and address it means we found repeating
        if (element->surname == array[i].surname && element->address == array[i].address)
            return true;

    return false;
}
