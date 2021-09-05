//Москаленко Максим КА-07 Visual Studio Code
#include <iostream>
#include <ctime>

void fillArray(float **array);
void printArray(float **array, int N, int M);
float **findSums(float **array);

int main()
{
    srand(time(NULL));

    float **A = new float *[3];
    float **B = new float *[3];
    for (int i = 0; i < 3; i++)
        A[i] = new float[30];

    fillArray(A);
    std::cout << "Input array A: " << std::endl;
    printArray(A, 3, 30);

    B = findSums(A);

    std::cout << "\nOutput array B: " << std::endl;
    printArray(B, 3, 3);

    for (int i = 0; i < 3; i++)
        delete[] A[i];
    delete[] A;

    for (int i = 0; i < 3; i++)
        delete[] B[i];
    delete[] B;

    return 0;
}

void fillArray(float **array)
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 30; j++)
            array[i][j] = (float)(rand() % 2000 - 1000) / 100;
}

float **findSums(float **array)
{
    float **output = new float *[3];

    float avrg;
    for (int i = 0; i < 3; i++)
    {
        avrg = 0.0;
        output[i] = new float[3];
        for (int j = 0; j < 30; j++)
        {
            avrg += array[i][j];
            if ((j + 1) % 10 == 0)
            {
                output[i][((j + 1) / 10) - 1] = avrg / 10;
                avrg = 0;
            }
        }
    }
    return output;
}

void printArray(float **array, int N, int M)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            printf("%.2f ", array[i][j]);

        std::cout << std::endl;
    }
}