#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;
float calculate(float *X, float *Y);
void print_array(float *arr, int size);
void find_sum_amount(float *arr, int size, float *sum, float *amount, bool is_positive);
void generate_array(float *arr, int size);

int main()
{
    srand(time(NULL));
    float *X = new float[10];
    float *Y = new float[15];

    cout << "Array X: ";
    generate_array(X, 10);
    print_array(X, 10);
    cout << endl;
    generate_array(Y, 15);
    cout << "Array Y: ";
    print_array(Y, 15);
    cout << endl;

    float Z = calculate(X, Y);
    cout << "Результат: ";
    cout << Z << endl;
    return 0;
}
float calculate(float *X, float *Y)
{
    float s1 = 0, k1 = 0, s2 = 0, k2 = 0;
    find_sum_amount(X, 10, &s1, &k1, true);
    find_sum_amount(Y, 15, &s2, &k2, false);
    cout << "Остаточна формула:" << endl;
    cout << "exp{" << s1 << "} + exp{" << s2 << "}";
    cout << "\n----------------------\n";
    cout << "        " << k1 << " · " << k2 << endl;
    return (exp(s1) + exp(s2)) / (k1 * k2);
}

void print_array(float *arr, int size)
{
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
}

void find_sum_amount(float *arr, int size, float *sum, float *amount, bool is_positive)
{
    for (int i = 0; i < size; i++)
    {
        if (is_positive && arr[i] > 0)
        {
            (*sum) += arr[i];
            (*amount)++;
            continue;
        }
        if (!is_positive && arr[i] < 0)
        {
            (*sum) += arr[i];
            (*amount)++;
            continue;
        }
    }
}

void generate_array(float *arr, int size)
{
    for (int i = 0; i < size; i++)
        arr[i] = (float)(rand() % 201 - 100) / 10;
}
