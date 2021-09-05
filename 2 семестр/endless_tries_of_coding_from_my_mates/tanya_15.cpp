#include <stdio.h>

#include <stdlib.h>

#include <locale.h>

#include <string.h>

int main()
{
    setlocale(LC_CTYPE, "RUS");
    char str[10];
    FILE *fp = fopen("some_text.txt", "r");
    if (fp == NULL)
    {
        printf("Ощибка\n");
    }
    else
    {
        printf("выполнено\n");
    }
    fgets(str, sizeof(str), fp);

    while (fgets(str, sizeof(str), fp))
    {

        if (strcmp(str, "abcd"))
        {
            printf("%s", estr);
            printf("данная строчка есть в файле\n");
        }
        else
        {
            printf("данной строки в файле нет\n");
        }
    }

    fclose(fp);
    return 0;
}

/*
asfgsg
adfgbhue
aвіапц4й3уц
йуауцуеп    
wrgtey
*/

while (getline(fp, word))
{
    cout << word;
}

while (getline(fp, word))
{
    if (is_substr(word))
    {
        cout << "+";
    }
    else
    {
        cout << "-"
    }
}

a = [ "asfas", "sgdhh", "qwrtey", "wethy" ]

    for (int i = 0; i < 4; i++)
{
    a[i]
}

int i = 0;
while (getelement(a, el))
{
    el //a[i]
}

while (getline(fp, word))
{
    word //a[i]
}

for (int i = 0; i < word.length() - 3; i++)
{
    if (word.substr(i, 4) == "abcd")
    {
        return true
    }
    else
    {
        return false
    }
}

//asdfgs