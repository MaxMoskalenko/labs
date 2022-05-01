#include <ctime>
#include <string>
#include "Date.h"
#include "BarberShop.h"
#include "Haircut.h"
#include "Barber.h"
using namespace std;

const int DEFAULT_ADDITIONAL_SERVICE_COST = 100;

int BarberShop::additionalServiceCost = DEFAULT_ADDITIONAL_SERVICE_COST;

int main()
{
    const Barber* barber1 = new Barber("Mike", "Wazowski");
    const Barber* barber2 = new Barber("James", "Sullivan");

    Haircut* haircut1 = new Haircut(womanDyeing, barber1, "As Cruella", 1000, true);
    Haircut* haircut2 = new Haircut(*haircut1);
    haircut2->setClient(womanHaircut);
    haircut2->setTitle("Marilyn Style");
    Haircut* haircut3 = new Haircut(man, barber2, "Postrygsya i Krasavchik", 100, false);

    BarberShop* barberShop1 = new BarberShop();

    barberShop1->setDate(new Date());
    barberShop1->setBarberNumber(1);
    barberShop1->addHaircut(haircut3);

    BarberShop* barberShop2 = new BarberShop(*barberShop1);
    barberShop2->setBarberNumber(12);
    
    barberShop2->addHaircut(haircut1);
    barberShop2->addHaircut(haircut2);

    printf("Barber shop 2 (long) before addition:\n");
    barberShop2->print();
    printf("\nBarber shop 2 (short) before addition:\n");
    barberShop2->shortPrint();

    barberShop2->addHaircut(haircut3);
    printf("\nBarber shop 2 (long) after addition:\n");
    barberShop2->print();
    printf("\nBarber shop 2 (short) after addition:\n");
    barberShop2->shortPrint();

    printf("\nBarber shop 1 (long) after addition:\n");
    barberShop1->print();

    printf("\n");

    delete barber1;
    delete barber2;
    delete haircut1;
    delete haircut2;
    delete haircut3;
    delete barberShop1;
    delete barberShop2;

}
