#pragma once
#include <string>

using namespace std;

class Barber
{
private:
    string name;
    string surname;

public:
    Barber()
    {
        name = "";
        surname = "";
    }
    Barber(string _name, string _surname)
    {
        name = _name;
        surname = _surname;
    }
    Barber(const Barber &barber)
    {
        name = barber.name;
        surname = barber.surname;
    }
    string getName()
    {
        return name;
    }
    string getSurname()
    {
        return surname;
    }
    void print()
    {
        printf("%s %s", name.c_str(), surname.c_str());
    }
    Barber *setName(string _name)
    {
        name = _name;
        return this;
    }
    Barber *setSurname(string _surname)
    {
        surname = _surname;
        return this;
    }
    ~Barber() {}
};
