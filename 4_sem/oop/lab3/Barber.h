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
        printf("🛠 Barber created with empty constructor\n");
        name = "";
        surname = "";
    }
    Barber(string _name, string _surname)
    {
        printf("🛠 Barber created with parametric constructor\n");
        name = _name;
        surname = _surname;
    }
    Barber(Barber &barber)
    {
        printf("🛠 Barber created with copy constructor\n");
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
    ~Barber() {
        printf("🛠 Barber destructed\n");
    }
};
