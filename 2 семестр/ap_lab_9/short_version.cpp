#include <iostream>
#include <ctime>
const int F_ARR_SIZE = 10;
const int S_ARR_SIZE = 7;
struct Person {
	std::string surname, address;
};
std::string surnames[20] = {"Мельник", "Шевченко", "Бойко", "Коваленко", "Бондаренко", "Ткаченко", "Ковальчук", "Кравченко", "Олійник", "Шевчук", "Поліщук", "Мороз", "Лисенко", "Руденко", "Савченко", "Андрієнко", "Кушнір", "Павлюк", "Василенко", "Білоус"};
std::string streets[10] = {"вул. Садова 23", "б-р. Шевченка 3-1а", "пл. Миру 12", "вул. Шкільна 2", "пр. Молодіжний 78", "вул. Гагаріна 19б", "вул. Лісова 66", "б-р. Лесі Українки 1", "вул. Котляревського 14", "пл. Богдана Хмельницького 7"};
void fill_array(Person* arr, int size){
	Person element;
	int available_index;
	for (int i = 0; i < size; i++) {
		element = {surnames[rand()%4], streets[rand()%4]};
		available_index = i;
		for(int j = i-1; j >= 0; j--)
			if(element.surname < arr[j].surname) {
				arr[available_index] = arr[j];
				available_index = j;
			} else break;
		arr[available_index] = element;
	}
}
void print_array(Person* arr, int size) {
	for (int i = 0; i < size; i++)
		if (arr[i].surname == "") continue;
		else std::cout << arr[i].surname << " проживає за адресою " << arr[i].address << std::endl;
}
bool is_element_in_array(Person* element, Person* array, int size){
    for (int i = 0; i < size; i++)
        if (element->surname == array[i].surname && element->address == array[i].address) return true;
    return false;
}
void concatenate(Person* result_array, Person* arr, int size, int* result_size){
	for (int i = 0; i < size; i++) {
		if (is_element_in_array(&arr[i], result_array, *result_size)) continue;
		result_array[*result_size] = arr[i];
        (*result_size)++;
	}
}
int main() {
	srand(time(NULL));
	Person *first_array = (Person*)malloc(F_ARR_SIZE*sizeof(Person));
	Person *second_array = (Person*)malloc(S_ARR_SIZE*sizeof(Person));
	Person *result_array = (Person*)malloc((S_ARR_SIZE+F_ARR_SIZE)*sizeof(Person));
    int result_size = 0;
	fill_array(first_array, F_ARR_SIZE);
	fill_array(second_array, S_ARR_SIZE);
    print_array(first_array, F_ARR_SIZE);
    print_array(second_array, S_ARR_SIZE);
	concatenate(result_array, first_array, F_ARR_SIZE, &result_size);
    concatenate(result_array, second_array, S_ARR_SIZE, &result_size);
	print_array(result_array, result_size);
	free(first_array);
	free(second_array);
    free(result_array);
	return 0;
}
