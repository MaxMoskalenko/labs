#include <stdio.h>

#include <stdlib.h>

#include <locale.h>

void Vyvid(char **array, int sum);
void FIRST(char **array, int sum);
void firstandlast(char **array, int sum);
void theempty(char **array, int sum);
void thesame(char **array, int sum);
void thenew(int *h, int *g, int *f, int *k);
int main()
{
    setlocale(LC_CTYPE, "rus");
    FILE *f = fopen("some_text.txt", "r");
    char str[20];
    char **array = (char **)malloc(20 * sizeof(char *));
    for (int i = 0; i < 20; i++)
    {
        array[i] = (char *)malloc(20 * sizeof(char));
    }
    int sum;
    sum = 0;
    while (!feof(f))
    {
        fgets(array[sum], 19, f);

        sum++;
    }
    int h = FIRST(array, sum);
    int *g;
    int *f;
    int *k;
    Vyvid(array, sum);
    printf("%d\n", h);
    printf("%d\n", g);
    printf("%d\n", f);
    printf("%d\n", k);
    thenew(h, &g, &f, &k);
    return 0;
}

void Vyvid(char **array, int sum)
{
    for (int i = 0; i < sum; i++)
    {
        printf("%s\n", array[i]);
    }
}

void FIRST(char **array, int sum)
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
    return h;
}

void firstandlast(char **array, int sum)
{
    int g = 0;
    int j = 0;
    for (int i = 0; i < sum; i++)
    {
        j = 0;
        while (array[i][j] != '\0')
        {
            if (array[i][j] == array[i][0] && (array[i][j + 1] == '\0' || array[i][j + 1] == '\n'))
            {
                g++;
            }
            j++;
        }
    }
    return g;
}

void theempty(char **array, int sum)
{
    int f = 0;
    for (int i = 0; i < sum; i++)
    {
        if (array[i][0] == '\n' || array[i][0] == '\0')
        {
            f++;
        }
    }
    return f;
}

void thesame(char **array, int sum)
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
    return k;
}

void thenew(int *h, int *g, int *f, int *k)
{
    FILE *fp = fopen("NEW.txt", "w");
    fprintf(fp, "К-ть строк з однак %d\n", 8);
    printf("4+4 = %d\n", 8);
    printf("%d\n", f);
    printf("%d\n", k);
    fclose(fp);
}