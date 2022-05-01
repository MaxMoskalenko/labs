#include <ctime>
#include <string>
#include "Date.h"
#include "BarberShop.h"
#include "Haircut.h"
#include "Barber.h"
using namespace std;

int DEFAULT_ADDITIONAL_SERVICE_COST = 100;

int BarberShop::additionalServiceCost = DEFAULT_ADDITIONAL_SERVICE_COST;

int main()
{
    Haircut* haircut = new Haircut(womanDyeing, "Mike", "Wazowski", "As Cruella", 1000, true);
    printf("------\n");
    BarberShop* barberShop = new BarberShop();

    barberShop->setDate(new Date());
    barberShop->setBarberNumber(1);
    barberShop->addHaircut(haircut);

    printf("\n");
    haircut->print();
    printf("\n\n");

    barberShop->print();
    printf("\n\n");

    delete haircut;
    printf("------\n");
    delete barberShop;

}
