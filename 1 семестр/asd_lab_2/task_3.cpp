#include <iostream>
#include <cmath>
using namespace std;


void findInterval(int A, int B);

int main() {
	int A, B;
	cout << "Введіть числа А та В\nA:";
	cin >> A;
	cout << "B:";
	cin >> B;
	cout << "Ряд цілих чисел від А до В:\n";

	if (A <= B)
    		findInterval(A, B);
	else
    		findInterval(B, A);
	cout << endl;
	return 0;
}

void findInterval(int A, int B){
	cout << A << ' ';
	if (A == B) return;
	findInterval(A+1, B);
}
