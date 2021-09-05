#include <iostream>

#include <ctime>

#include <cmath>

using namespace std;

bool isPrime(int num);

void sieve(int endBorder);

int main() {
    sieve(541);
    cout << "\n\n";
    int primeNumIndex = 0, naturalNumber = 2;

    clock_t start = clock();
    while (primeNumIndex < 100) {
        if (isPrime(naturalNumber)) {
            cout << naturalNumber << ' ';
            ++primeNumIndex;
        }
        ++naturalNumber;
    }

    clock_t end = clock();
    float seconds = (float(end - start)) / CLOCKS_PER_SEC;
    cout << "\nfunction time: " << seconds << '\n';

    return 0;
}

bool isPrime(int num) {
    // if this loop finds remainder, which not equal 0, it mean num is not prime
    for (int i = 2; i < num; ++i)
        if (num % i == 0)
            return false;

    return true;
}

void sieve(int endBorder) {
    //generate array of natural numbers
    int naturalNumbers[endBorder];

    for (int i = 0; i <= endBorder; ++i)
        naturalNumbers[i] = i;

    //remove 0 and 1
    naturalNumbers[0] = 0;
    naturalNumbers[1] = 0;

    clock_t start = clock();

    //p^2 <= n, where p is a prime number, and n is the next number, which will divide on p without remainder
    for (int i = 2; i < ceil(sqrt(endBorder)); ++i)
        if (naturalNumbers[i] != 0)
            for (int j = i * i; j < endBorder; j += i)
                naturalNumbers[j] = 0;

    clock_t end = clock();
    float seconds = (float(end - start)) / CLOCKS_PER_SEC;

    cout << "sieve time: " << seconds << '\n';
    for (int i = 0, primeNums = 0; primeNums < 100; ++i)
        if (naturalNumbers[i] != 0) {
            cout << naturalNumbers[i] << " ";
            ++primeNums;
        }
}
