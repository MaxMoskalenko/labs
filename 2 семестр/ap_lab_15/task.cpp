#include <iostream>
#include <fstream>
#include <string.h>
#include <locale>

std::string **read_file(int &lines);
void change_to_template(std::string **strings, int size);
void write_file(std::string **strings, int size);

int main()
{
    setlocale(LC_CTYPE, "ukr");
    std::string **strings;
    int lines;
    strings = read_file(lines);

    change_to_template(strings, lines);
    write_file(strings, lines);

    for (int i = 0; i < 3; i++)
        delete[] strings[i];

    delete[] strings;
    return 0;
}

std::string **read_file(int &lines)
{
    std::ifstream f("input.txt");
    std::string input;

    getline(f, input);
    int n = input.length();
    std::string **result = new std::string *[10];

    int cur_pos = 0; //position for each new word
    lines = 0;       // position of name, surname etc array
    int status = 0;  //position of array in line
    result[0] = new std::string[3];
    int i = 0;
    for (i = 0; i < n; i++)
    {
        if (input[i] == ' ' || input[i] == ',')
        {
            //get substring from indexes
            result[lines][status] = input.substr(i - cur_pos, cur_pos);
            cur_pos = 0;
            if (input[i] == ' ')
                status++;
            else
            {
                status = 0;
                lines++;
                result[lines] = new std::string[3];
                i++; //miss the next space
            }
            continue;
        }
        cur_pos++;
    }
    //for the last word, because input doesn`t end with comma
    result[lines][status] = input.substr(i - cur_pos, cur_pos);

    f.close();
    lines++;
    return result;
}

void change_to_template(std::string **strings, int size)
{
    std::string tmp;
    for (int i = 0; i < size; i++)
    {
        tmp = strings[i][2];
        strings[i][2] = strings[i][1];
        strings[i][1] = strings[i][0];
        strings[i][0] = tmp;
    }
}

void write_file(std::string **strings, int size)
{
    std::ofstream f;
    f.open("output.txt");
    std::string output = "";
    //concatete all strings to the result one
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            output += strings[i][j];
            if (j != 2)
                output += ' ';
        }
        if (i != size - 1)
            output += ", ";
    }
    f << output;
    f.close();
}