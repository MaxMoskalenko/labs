#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int MATRIX_ORDER = 3;

void generate_array(float** matrix);
void find_sums(float* upper_sum, float* lower_sum, float** matrix);
int main() {
    srand(time(NULL));
    float **matrix = (float**)malloc(MATRIX_ORDER*sizeof(float*));
    float upper_sum = 0, lower_sum = 0;


    generate_array(matrix);
    find_sums(&upper_sum, &lower_sum, matrix);

    printf("Сума елменентів нижче головної діагоналі: %f\n", lower_sum);
    printf("Сума елементів вище головної діагоналі: %f\n", upper_sum);

    for (int i = 0; i < MATRIX_ORDER; i++)
        free(matrix[i]);
    free(matrix);
    return 0;
}

//generates two-dimension array of float numbers from -10 to 10
void generate_array(float** matrix){
    for (int i = 0; i < MATRIX_ORDER; i++) {
        matrix[i] = (float*)malloc(MATRIX_ORDER*sizeof(float));
        for (int j = 0; j < MATRIX_ORDER; j++) {
            matrix[i][j] = (float)rand()/(float)RAND_MAX/0.05 - 10;
            printf("%5.1f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void find_sums(float* upper_sum, float* lower_sum, float** matrix){
    for (int i = 0; i < MATRIX_ORDER; i++) {
        if (matrix[i][0] > 0)
            continue;
        for (int j = 0; j < MATRIX_ORDER; j++)
            //if row number more then column one - its lower triangle, and vice versa
            if (j-i > 0)
                *lower_sum += matrix[i][j];
            else if (j-i < 0)
                *upper_sum += matrix[i][j];
    }
}
