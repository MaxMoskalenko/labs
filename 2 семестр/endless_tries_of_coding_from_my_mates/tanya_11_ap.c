#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* gen();
int main()
{
    // setlocale (LC_CTYPE, "RUS");
    srand (time(NULL));

    char* array = gen();


    puts(array);
    getchar();
    free(array);
    return 0;
}

char* gen(){
    char* array = (char*)malloc(10* sizeof(char));

    char massiv[] = {'a','d'};
    for(int i = 0; i < 10; i++)
        array[i] = massiv[rand() % 2];
    array[10]='\0';
    return array;
}

















int i = search();
printf("%d", i);
