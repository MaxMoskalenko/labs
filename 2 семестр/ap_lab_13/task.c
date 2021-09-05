#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int import_data(float **arr);
float *get_line_coef(char *str);
char **get_type_of_lines(float **coefficients, int size);
void save_to_file(char **arr, int size);
int is_parallel(float *line1, float *line2);
int is_perpendicular(float *line1, float *line2);
int combinations(int n, int r);
int factorial(int n);

int main()
{
    // matrix of coefficients
    float **coefficients = (float **)malloc(20 * sizeof(float *));
    int n_rows = import_data(coefficients);

    char **results = get_type_of_lines(coefficients, n_rows);

    save_to_file(results, n_rows);
    for (int i = 0; i < n_rows; i++)
        free(coefficients[i]);
    free(coefficients);

    for (int i = 0; i < combinations(n_rows, 2); i++)
        free(results[i]);
    free(results);

    return 0;
}

int import_data(float **arr)
{
    FILE *f = fopen("./coefficients.txt", "r");
    char *string = (char *)malloc(15 * sizeof(char));

    int i = 0;
    while (fgets(string, 100, f) != NULL)
    {
        arr[i] = (float *)malloc(3 * sizeof(float));
        arr[i] = get_line_coef(string);
        i++;
    }
    fclose(f);
    free(string);
    return i;
}

float *get_line_coef(char *str)
{
    // Extract the first token
    char *token = strtok(str, " ");
    float *arr = (float *)malloc(3 * sizeof(float));
    int i = 0;
    // loop through the string to extract all other tokens
    while (token != NULL)
    {
        sscanf(token, "%f", &arr[i]);
        token = strtok(NULL, " ");
        i++;
    }
    return arr;
}

char **get_type_of_lines(float **coefficients, int size)
{
    char **result = (char **)malloc(combinations(size, 2) * sizeof(char *));
    int k = 0;
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            result[k] = (char *)malloc(60 * sizeof(char));
            if (is_parallel(coefficients[i], coefficients[j]))
                sprintf(result[k], "%g %g %g && %g %g %g паралельні\n", coefficients[i][0], coefficients[i][1], coefficients[i][2], coefficients[j][0], coefficients[j][1], coefficients[j][2]);
            else if (is_perpendicular(coefficients[i], coefficients[j]))
                sprintf(result[k], "%g %g %g && %g %g %g перепендикулярні\n", coefficients[i][0], coefficients[i][1], coefficients[i][2], coefficients[j][0], coefficients[j][1], coefficients[j][2]);
            else
                sprintf(result[k], "%g %g %g && %g %g %g просто перетинаються\n", coefficients[i][0], coefficients[i][1], coefficients[i][2], coefficients[j][0], coefficients[j][1], coefficients[j][2]);
            k++;
        }
    }
    return result;
}

void save_to_file(char **arr, int size)
{
    FILE *f = fopen("./results.txt", "wb");
    for (int i = 0; i < combinations(size, 2); i++)
    {
        fputs(arr[i], f);
    }
    fclose(f);
}

int is_parallel(float *line1, float *line2)
{
    return (line1[0] * line2[1]) == (line1[1] * line2[0]);
}

int is_perpendicular(float *line1, float *line2)
{
    return (line1[0] * line2[0] + line1[1] * line2[1]) == 0;
}
int factorial(int n)
{
    return (n <= 1) ? 1 : n * factorial(n - 1);
}
int combinations(int n, int r)
{
    return factorial(n) / (factorial(r) * factorial(n - r));
}
