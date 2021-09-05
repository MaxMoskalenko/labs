#include <iostream>

#include <cmath>

using namespace std;

int convert(unsigned long long num, int from, int to);

int main() {
    //binary numbers may be is so long
    unsigned long long numberToConvert;
    bool isConvertToDecimal;
    int numberSize = 0;
    cout << "Введіть число, яке необхідно перевести в іншу систему числення:\n";
    cin >> numberToConvert;

    cout << "Введіть:\n  0 - якщо хочете перевести в двійкову систему\n  1 - якщо хочете перевести в десяткову систему\n";
    cin >> isConvertToDecimal;

    if (isConvertToDecimal)
        cout << "Дане число в десятковій системі числення має вигляд: " << convert(numberToConvert, 2, 10) << endl;
    else
        cout << "Дане число в десятковій системі числення має вигляд: " << convert(numberToConvert, 10, 2) << endl;

    return 0;
}

int convert(unsigned long long num, int from, int to){
    int size = 0, final_num = 0, i = 0;
    int digits[20];

    // making array from num
    while (num != 0) {
        digits[i] = num % to;
        num = num / to;
        ++i;
    }
    size = i;
    
    for (i = 0; i < size; ++i)
        final_num += digits[i] * pow(from, i);

    return final_num;
}
