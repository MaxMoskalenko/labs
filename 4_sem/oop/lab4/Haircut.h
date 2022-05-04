#pragma once

#include <string>
#include "Client.h"
#include "Barber.h"
#include <iostream>
#include <iomanip>

class Haircut : public Barber
{
private:
    Client client;
    string title;
    int cost;
    bool additionalService;

public:
    Haircut() : Barber()
    {
        client = man;
        title = "";
        cost = 0;
        additionalService = false;
    }
    Haircut(Client _client, string barberName, string barberSurname, string _title, int _cost, bool _additionalService) : Barber(barberName, barberSurname)
    {
        client = _client;
        title = _title;
        cost = _cost;
        additionalService = _additionalService;
    }
    Haircut(Haircut &haircut) : Barber(haircut.getName(), haircut.getSurname())
    {
        client = haircut.client;
        title = haircut.title;
        cost = haircut.cost;
        additionalService = haircut.additionalService;
    }
    Client getClient()
    {
        return client;
    }
    Barber *getBarber()
    {
        return new Barber(Barber::getName(), Barber::getSurname());
    }
    string getTitle()
    {
        return title;
    }
    int getCost()
    {
        return cost;
    }
    bool getAdditionalService()
    {
        return additionalService;
    }
    void print()
    {
        printf("%d ", client);
        Barber::print();
        printf(" %s %d %s", title.c_str(), cost, additionalService ? "true" : "false");
    }
    Haircut *setClient(Client _client)
    {
        client = _client;
        return this;
    }
    Haircut *setBarber(Barber *_barber)
    {
        Barber::setName(_barber->getName());
        Barber::setSurname(_barber->getSurname());
        return this;
    }
    Haircut *setTitle(string _title)
    {
        title = _title;
        return this;
    }
    Haircut *setCost(int _cost)
    {
        cost = _cost;
        return this;
    }
    Haircut *setAdditionalService(bool _additionalService)
    {
        additionalService = _additionalService;
        return this;
    }

    friend bool operator>(Haircut &, Haircut &);
    friend bool operator<(Haircut &, Haircut &);
    friend ostream &operator<<(ostream &output, Haircut &h);
    friend istream &operator>>(istream &input, Haircut &h);

    ~Haircut() {}
};
bool operator>(Haircut &a, Haircut &b)
{
    return a.getCost() > b.getCost();
}

bool operator<(Haircut &a, Haircut &b)
{
    return a.getCost() < b.getCost();
}

ostream &operator<<(ostream &output, Haircut &h)
{
    switch (h.client)
    {
    case man:
        output << "Man haircut";
        break;
    case womanDyeing:
        output << "Woman dyeing procedure";
        break;
    case womanHaircut:
        output << "Woman haircut";
        break;
    case womanLaying:
        output << "Woman laying procedure";
        break;
    case child:
        output << "Child haircut";
        break;
    }
    output << " \""
           << h.title
           << "\". Price: "
           << to_string(h.cost)
           << (h.additionalService
                   ? " + additional service price (depends on barber shop)"
                   : "")
           << endl;
    return output;
}

istream &operator>>(istream &input, Haircut &h)
{
    printf("Enter type of haircut:\n1 - Man haircut\n2 - Woman dyeing\n3 - Woman haircut\n4 - Woman laying\n5 - Child haircut\n");
    int choice;
    input >> choice;
    switch (choice)
    {
    case 1:
        h.client = man;
        break;
    case 2:
        h.client = womanDyeing;
        break;
    case 3:
        h.client = womanHaircut;
        break;
    case 4:
        h.client = womanLaying;
        break;
    case 5:
        h.client = child;
        break;
    default:
        printf("You choose wrong haircut, so it will be child haircut\n");
        h.client = child;
        break;
    }

    printf("Enter title of haircut\n");
    input >> h.title;

    printf("Enter price of haircut\n");
    input >> h.cost;

    printf("Enter do you need additional services (1 - yes, 0 - no)\n");
    input >> choice;

    switch (choice)
    {
    case 0:
        h.additionalService = false;
        break;
    case 1:
        h.additionalService = true;
        break;
    default:
        h.additionalService = false;
        break;
    }
    return input;
}
