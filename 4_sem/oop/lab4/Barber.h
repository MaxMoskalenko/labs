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
    Barber(Barber &barber)
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
    virtual void print()
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

    friend bool operator==(Barber &, Barber &);
    friend bool operator!=(Barber &, Barber &);
    friend ostream &operator<<(ostream &, Barber &);
    friend istream &operator>>(istream &, Barber &);

    ~Barber() {}
};

bool operator==(Barber &a, Barber &b)
{
    return a.getName() == b.getName() && a.getSurname() == b.getSurname();
}

bool operator!=(Barber &a, Barber &b)
{
    return !(a == b);
}

ostream &operator<<(ostream &output, Barber &b)
{
    output << "Barber name and surname: " << b.name << " " << b.surname << endl;
    return output;
}

istream &operator>>(istream &input, Barber &b)
{
    printf("Input barber`s name: ");
    input >> b.name;

    printf("Input barber`s surname: ");
    input >> b.surname;
    return input;
}
