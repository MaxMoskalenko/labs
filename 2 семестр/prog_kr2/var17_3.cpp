//Москаленко Максим КА-07 Visual Studio Code
#include <iostream>
#include <ctime>
#include <vector>

std::vector<int> findPrimes(int lastNumber);
std::vector<int> byLoop(int number);
std::vector<int> recResult;
void byRec(int number, std::vector<int> primes, int primeIndex);
void printVector(std::vector<int> v);

int main()
{
    srand(time(NULL));
    int number = 2 + rand() % 1000;
    std::cout << "Number: " << number << std::endl;
    std::vector<int> loopResult = byLoop(number);
    byRec(number, findPrimes(number), 0);
    std::cout << "Task by Loop: ";
    printVector(loopResult);
    std::cout << "Task by Reccursion: ";
    printVector(recResult);
    return 0;
}

std::vector<int> findPrimes(int lastNumber)
{
    std::vector<int> numbers;
    std::vector<int> primes;
    for (int i = 2; i <= lastNumber; i++)
        numbers.push_back(i);

    for (int i = 2; i <= lastNumber; i++)
    {
        if (numbers[i] == 0)
            continue;

        primes.push_back(i);
        for (int j = i; j <= lastNumber; j += i)
        {
            numbers[j] = 0;
        }
    }
    return primes;
}

std::vector<int> byLoop(int number)
{
    std::vector<int> primes = findPrimes(number);
    std::vector<int> result;
    int curPrimeIndex = 0;
    while (number != 1)
    {
        if (number % primes[curPrimeIndex] != 0)
        {
            curPrimeIndex++;
            continue;
        }
        number /= primes[curPrimeIndex];
        result.push_back(primes[curPrimeIndex]);
    }
    return result;
}

void printVector(std::vector<int> v)
{
    for (int i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
    std::cout << std::endl;
}

void byRec(int number, std::vector<int> primes, int primeIndex)
{
    if (number == 1)
        return;

    if (number % primes[primeIndex] != 0)
    {
        primeIndex = primeIndex + 1;
        byRec(number, primes, primeIndex++);
        return;
    }
    //byRec(number, primes, primeIndex, result);
    recResult.push_back(primes[primeIndex]);
    byRec(number / primes[primeIndex], primes, primeIndex);
}