#pragma once

#include <string>
#include "Client.h"
#include "Barber.h"

class Haircut
{
private:
    Client client;
    Barber *barber;
    string title;
    int cost;
    bool additionalService;

public:
    Haircut()
    {
        client = man;
        barber = new Barber();
        title = "";
        cost = 0;
        additionalService = false;
    }
    Haircut(Client _client, const Barber *_barber, string _title, int _cost, bool _additionalService)
    {
        client = _client;
        barber = new Barber(*_barber);
        title = _title;
        cost = _cost;
        additionalService = _additionalService;
    }
    Haircut(const Haircut &haircut)
    {
        client = haircut.client;
        barber = new Barber(*haircut.barber);
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
        return barber;
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
        barber->print();
        printf(" %s %d %s", title.c_str(), cost, additionalService ? "true" : "false");
    }
    Haircut *setClient(Client _client)
    {
        client = _client;
        return this;
    }
    Haircut *setBarber(Barber *_barber)
    {
        delete barber;
        barber = new Barber(*_barber);
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
    ~Haircut()
    {
        delete barber;
    }
};
