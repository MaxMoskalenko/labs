#include <iostream>
#include <ctime>
#include <cstring>

void print_array(int *arr, int size);
int *generate_array(int size, const char *type);
void insertion_sort(int *array, int arr_size, long &tr_num, long &cmp_num);
void print_answer(const char *sort_type, const char *arr_size, const char *gen_type, long tr_num, long cmp_num);

int main(int argc, char const *argv[])
{
    if (argc != 4)
    {
        std::cout << "Not enough arguments, I`m out" << std::endl;
        return -1;
    }

    int *array = generate_array(atoi(argv[2]), argv[3]);
    long transpostion_num = 0;
    long comparison_num = 0;
    if (!strcmp(argv[1], "I"))
    {
        insertion_sort(array, atoi(argv[2]), transpostion_num, comparison_num);
        print_answer(argv[1], argv[2], argv[3], transpostion_num, comparison_num);
    }

    delete[] array;
    return 0;
}

void print_array(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int *generate_array(int size, const char *type)
{
    int *array = new int[size];
    if (!strcmp(type, "a"))
        for (int i = 0; i < size; i++)
            array[i] = i;

    else if (!strcmp(type, "b"))
        for (int i = 0; i < size; i++)
            array[i] = rand() % size;

    else if (!strcmp(type, "c"))
        for (int i = 0; i < size; i++)
            array[i] = size - i;

    else
    {
        std::cout << "Unknown type of generation, I will generate by ascending" << std::endl;
        for (int i = 0; i < size; i++)
            array[i] = i;
    }

    return array;
}

void insertion_sort(int *array, int arr_size, long &tr_num, long &cmp_num)
{
    for (int i = 1; i < arr_size; i++)
    {
        int key = array[i];
        int j = i - 1;

        while (j >= 0 && array[j] > key)
        {
            tr_num++;
            cmp_num++;
            array[j + 1] = array[j];
            j = j - 1;
        }
        tr_num++;
        array[j + 1] = key;
    }
}

void print_answer(const char *sort_type, const char *arr_size, const char *gen_type, long tr_num, long cmp_num)
{
    printf("Array of size %s was sorted by ", arr_size);
    if (!strcmp(sort_type, "I"))
        std::cout << "INSERTION sort" << std::endl;
    else if (!strcmp(sort_type, "II"))
        std::cout << "HEAPSORT sort" << std::endl;
    else if (!strcmp(sort_type, "III"))
        std::cout << "RADIX sort" << std::endl;
    else
        std::cout << "INSERTION sort" << std::endl;

    std::cout << "Array was created with ";

    if (!strcmp(gen_type, "a"))
        std::cout << "ASCENDING order" << std::endl;
    else if (!strcmp(gen_type, "b"))
        std::cout << "RANDOM order" << std::endl;
    else if (!strcmp(gen_type, "c"))
        std::cout << "DESCENDING order" << std::endl;
    else
        std::cout << "ASCENDING order" << std::endl;

    printf("Result: %ld transpositions; %ld comparisons\n\n", tr_num, cmp_num);
}
