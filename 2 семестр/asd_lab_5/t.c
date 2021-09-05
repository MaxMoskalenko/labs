#include <stdio.h>

#include <stdlib.h>

#include <locale.h>

void Vyvid(char **array, int sum);
int FIRST(char **array, int sum);
int firstandlast(char **array, int sum);
int theempty(char **array, int sum);
int thesame(char **array, int sum);
void thenew(int h, int g, int f, int k);
int main()
{
    setlocale(LC_CTYPE, "rus");
    FILE *fp = fopen("ЛАБКА.txt", "r");
    char str[20];
    char **array = (char **)malloc(20 * sizeof(char *));
    for (int i = 0; i < 20; i++)
    {
        array[i] = (char *)malloc(20 * sizeof(char));
    }
    int sum;
    sum = 0;
    while (fgets(array[sum], 20, fp) != NULL)
    {
        // printf("%s", array[sum]);
        sum++;
    }
    fclose(fp);

    Vyvid(array, sum);
    int h = FIRST(array, sum);
    int g = firstandlast(array, sum);
    int f = theempty(array, sum);
    int k = thesame(array, sum);
    thenew(h, g, f, k);
    return 0;
}

void Vyvid(char **array, int sum)
{
    for (int i = 0; i < sum; i++)
    {
        printf("> %s", array[i]);
    }
    printf("\n");
}

int FIRST(char **array, int sum)
{
    char symbol;
    int h = 0;
    printf("введите символ который хотите найти в строке: \n");
    scanf("%c", &symbol);
    for (int i = 0; i < sum; i++)
    {
        if (array[i][0] == symbol)
        {
            h++;
        }
    }
    printf("%d\n", h);
    return h;
}

int firstandlast(char **array, int sum)
{
    int g = 0;
    int j = 0;
    for (int i = 0; i < sum; i++)
    {
        j = 0;
        while (array[i][j] != '\0' || array[i][j] != '\n')
        {
            if (array[i][j] == array[i][0] && (array[i][j + 1] == '\0' || array[i][j + 1] == '\n'))
            {
                g++;
            }
            j++;
        }
    }
    printf("%d\n", g);
    return g;
}

int theempty(char **array, int sum)
{
    int f = 0;
    for (int i = 0; i < sum; i++)
    {
        if (array[i][0] == '\n' || array[i][0] == '\0')
        {
            f++;
        }
    }
    printf("%d\n", f);
    return f;
}

int thesame(char **array, int sum)
{
    int k = sum;
    int j;
    for (int i = 0; i < sum; i++)
    {
        j = 0;
        while (array[i][j] != '\n' && array[i][j] != '\0')
        {
            if (array[i][j] != array[i][0])
            {
                k--;
                break;
            }
            j++;
        }
    }
    printf("%d\n", k);
    return k;
}

void thenew(int h, int g, int f, int k)
{
    FILE *fp = fopen("NEW.txt", "w");
    fprintf(fp, "%d\n", h);
    fprintf(fp, "%d\n", g);
    fprintf(fp, "%d\n", f);
    fprintf(fp, "%d\n", k);
    fclose(fp);
}