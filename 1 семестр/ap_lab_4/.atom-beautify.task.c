#include "stdio.h"
#include "stdlib.h"
#include "time.h"

const int SIZE_OF_OUTPUT_ARRAY = 10;

int main() {
        float input_values[2 * SIZE_OF_OUTPUT_ARRAY];
        srand(time(NULL));
        //generates array of float numbers from 0 to 10
        for (int i = 0; i < 2 * SIZE_OF_OUTPUT_ARRAY; i++) {
                input_values[i] = (float)rand()/(float)RAND_MAX/0.1;
                printf("%f ", input_values[i]);
        }
        printf("\n\n" );
        for (int i = 0; i < SIZE_OF_OUTPUT_ARRAY; i++) {
                printf("%f ", input_values[i]);
                //the last index is SIZE.. - 1, because indexation starts from 0
                printf("+ %f ", input_values[2*SIZE_OF_OUTPUT_ARRAY-1-i]);
                printf("= %f\n", input_values[i] + input_values[2*SIZE_OF_OUTPUT_ARRAY-1-i]);
        }

        return 0;
}
