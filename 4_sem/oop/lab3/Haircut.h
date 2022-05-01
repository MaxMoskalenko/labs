#pragma once

#include <string>
#include "Client.h"
#include "Barber.h"

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
        printf("🛠 Haircut created with empty constructor\n");
        client = man;
        title = "";
        cost = 0;
        additionalService = false;
    }
    Haircut(Client _client, string barberName, string barberSurname, string _title, int _cost, bool _additionalService) : Barber(barberName, barberSurname)
    {
        printf("🛠 Haircut created with parametric constructor\n");
        client = _client;
        title = _title;
        cost = _cost;
        additionalService = _additionalService;
    }
    Haircut(Haircut &haircut) : Barber(haircut.getName(), haircut.getSurname())
    {
        printf("🛠 Haircut created with copy constructor\n");
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
    ~Haircut() {
        printf("🛠 Haircut destructed\n");
    }
};
