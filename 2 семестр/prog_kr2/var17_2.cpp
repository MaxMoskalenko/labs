//Москаленко Максим КА-07 Visual Studio Code
#include <iostream>
#include <ctime>

char alphabet[] = {'o', 'l'};

std::string createString();
std::string removeOdd(std::string str, char c);

int main()
{
    srand(time(NULL));
    std::string S = createString();
    std::cout << "Input string: " << S << std::endl;
    S = removeOdd(S, 'l');
    std::cout << "Output string with removed 'l': " << S << std::endl;
    return 0;
}

std::string createString()
{
    int length = 10 + rand() % 20;
    std::string output = "";

    for (int i = 0; i < length; i++)
        output += alphabet[rand() % 2];
    return output;
}

std::string removeOdd(std::string str, char c)
{
    std::string output = "";
    output += str[0];

    int lastIndex = 0;
    for (std::string::size_type i = 1; i < str.size(); i++)
    {
        if (str[i] == c && output[lastIndex] == c)
            continue;

        output += str[i];
        lastIndex++;
    }
    return output;
}