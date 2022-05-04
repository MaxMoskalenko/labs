#include <ctime>
#include <string>
#include <iostream>
#include "Date.h"
#include "BarberShop.h"
#include "Haircut.h"
#include "Barber.h"
using namespace std;

int DEFAULT_ADDITIONAL_SERVICE_COST = 100;

int BarberShop::additionalServiceCost = DEFAULT_ADDITIONAL_SERVICE_COST;

void printBarberFunc (Barber* b) {
    b->print();
    printf("\n");
}

int main()
{
    printf("🛠 Demonstrate overloaded input and output of barber\n");
    Barber b;
    cin >> b;
    cout << b;

    printf("\n🛠 Demonstrate overloaded input and output of haircut\n");
    Haircut h;
    cin >> h;
    cout << h;

    printf("\n🛠 Demonstare overloaded comparison operators\n");
    Haircut *h2 = new Haircut();
    h2->setCost(1000);
    if (h > *h2)
    {
        printf("Price of entered haircut bigger than 1000\n");
    }

    if (h < *h2)
    {
        printf("Price of entered haircut lower or equal than 1000\n");
    }

    printf("\n🛠 Demonstrate overloaded equality operator\n");
    Barber *marySue = new Barber("Mary", "Sue");

    if (*marySue == b)
    {
        printf("Entered barber is Mary Sue\n");
    }
    if (*marySue != b)
    {
        printf("Entered barber is not Mary Sue\n");
    }

    printf("\n🛠 Virtual function:\n");
    
    printBarberFunc(&h);
    printBarberFunc(&b);
    printf("\n");
}
