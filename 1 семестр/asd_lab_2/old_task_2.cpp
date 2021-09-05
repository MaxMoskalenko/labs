#include <iostream>
#include <cmath>
using namespace std;

const int ARRAY_SIZE = 20;

void toBinary(char num[ARRAY_SIZE], int size);

int toDecimal(char num[ARRAY_SIZE]);

int main() {
	char numberToConvert[ARRAY_SIZE] = {'-'};
	bool isConvertToDecimal;
	int numberSize = 0;
	cout << "Введіть число, яке необхідно перевести в іншу систему числення:\n";
	cin >> numberToConvert;

	// calculates size of availiable digits. Loop break, when there is no more digits
	for (int i = 0; i < ARRAY_SIZE; i++)
    		if (numberToConvert[i] >= '0' && numberToConvert[i] <= '9')
        			numberSize+=1;
    		else
        			break;

	cout << "Введіть:\n  0 - якщо хочете перевести в двійкову систему\n  1 - якщо хочете перевести в десяткову систему\n";
	cin >> isConvertToDecimal;

	if (isConvertToDecimal)
    		cout << "Дане число в десятковій системі числення має вигляд: " << toDecimal(numberToConvert) << endl;
	else
    		toBinary(numberToConvert, numberSize);

	return 0;
}

void toBinary(char num[ARRAY_SIZE], int size){
	int realInteger = 0, i;
	char tempBinaryNumber[100];

	//makes ascii symbol code equal to int analog and multiply on numerical digit
	for (i = 0; i < size; ++i)
    		realInteger += ((num[i] - '0') * pow(10, size - i - 1));

	i = 0;
	cout << realInteger << '\n';
	while (realInteger > 0) {
    		//convert int to char type
    		tempBinaryNumber[i] = (realInteger%2) + '0';
    		realInteger /= 2;
    		++i;
	}

	//reverse tempBinaryNumber and output it
	cout << "Дане число в двійковій системі має вигляд: ";
	for (int j = 0; j < i; j++)
    		cout << tempBinaryNumber[i-j-1];
	cout << endl;

	return;
}

int toDecimal(char num[ARRAY_SIZE]){
	int size = 0, integer = 0;
	// calculates size of availiable digits. Loop break, when there is no more digits
	for (int i = 0; i < ARRAY_SIZE; i++)
    		if (num[i] >= '0' && num[i] <= '1')
        			size+=1;
    		else
        			break;

	for (int i = 0; i < size; i++)
    		integer+=(num[i] - '0')*pow(2, size-i-1);

	return integer;
}
