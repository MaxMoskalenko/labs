/*
Створити масив структур. Кожна структура складається з таких елементів: літак і рейс. 
Для літака задати тип, кількість вільних місць, вартість квитка. 
Для рейсу задати номер, дата польоту. Створений масив записати до бінарного файлу. 
Передбачити можливість доповнити файл, замінити дані в файлі, видалити дані з файлу. 
Реалізувати запити: 1) скласти список номерів авіаційних рейсів, на які є вільні місця; 
2) вивести типи літаків і відповідні номери авіаційних рейсів на задану дату; 
3) упорядкувати масив за умови зростання вартості квитків по кожній даті.
*/

/*
Boing23-44 300 400
434 2020.05.31
y
An24 120 90
521 2020.06.07
y
Mriya 5000 23
90 2020.03.01
y
Voyager 3 4000
567 2030.01.14
n
*/

#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>

struct Plane
{
    std::string type;
    int free_places;
    float ticket_price;
    //operator overloading for convience input  and output
    //friend operator needs for some incapsulation tricks
    friend std::ostream &operator<<(std::ostream &out, const Plane &plane);
    friend std::istream &operator>>(std::istream &in, Plane &plane);
    void print()
    {
        std::cout << "Plane " << type << " has " << free_places << " seats for $" << ticket_price << " each" << std::endl;
    }
    void get()
    {
        std::cout << "Enter type of plane: ";
        std::getline(std::cin >> std::ws, type);
        // std::cin >> type;
        std::cout << "Enter number of free places: ";
        std::cin >> free_places;
        std::cout << "Enter price of tickets: ";
        std::cin >> ticket_price;
    }
};
struct Flight
{
    int number;
    std::string date;
    friend std::istream &operator>>(std::istream &in, Flight &flight);
    friend std::ostream &operator<<(std::ostream &out, const Flight &flight);
    void print()
    {
        std::cout << "Flight number " << number << " sheduled on " << date << std::endl;
    }
    void get()
    {
        std::cout << "Enter flight number: ";
        std::cin >> number;
        std::cout << "Enter date in format (yyyy.mm.dd): ";
        std::cin >> date;
    }
};
struct Info
{
    Plane plane;
    Flight flight;
    //simple constructor
    Info(Plane pl, Flight fl)
    {
        plane = pl;
        flight = fl;
    }
    Info() {}
    void print()
    {
        plane.print();
        flight.print();
    }
    void get()
    {
        plane.get();
        flight.get();
    }
};

void add_manual_data();
void add_random_data(int n);
void display_data();
void delete_data();
void edit_data();
void display_free_places();
void flights_on_date();
void sort_array();
long filesize();

int main()
{
    srand(time(NULL));
    std::cout << "Enter:" << std::endl;
    std::cout << "1 to add data" << std::endl;
    std::cout << "2 to edit data" << std::endl;
    std::cout << "3 to delete data" << std::endl;
    std::cout << "4 to display flights with free places" << std::endl;
    std::cout << "5 to display plane`s types and flights for the specific date" << std::endl;
    std::cout << "6 to to sort array by ticket`s cost in ascending order" << std::endl;
    std::cout << "7 to display data" << std::endl;
    std::cout << "0 to exit" << std::endl;

    while (true)
    {
        int request;
        std::cout << "You entered: ";
        std::cin >> request;
        switch (request)
        {
        case 0:
            return 0;
        case 1:
        {
            add_random_data(4);
            break;
        }
        case 2:
        {
            edit_data();
            break;
        }
        case 3:
        {
            delete_data();
            break;
        }
        case 4:
        {
            display_free_places();
            break;
        }
        case 5:
        {
            flights_on_date();
            break;
        }
        case 6:
        {
            sort_array();
            break;
        }
        case 7:
        {
            display_data();
            break;
        }
        }
    }
    return 0;
}

void add_manual_data()
{
    /* function for adding new info tabs (plane- flight) by user,
    allows to add new elements until user forbid it*/

    FILE *fp = fopen("data.dat", "ab");
    int i = 0;
    do
    {
        Plane new_plane;
        new_plane.get();

        Flight new_flight;
        new_flight.get();

        Info *line = new Info(new_plane, new_flight);

        std::cout << "Do you want to continue? y/n: ";
        char is_cont;
        std::cin >> is_cont;

        fwrite(&line, sizeof(Info), 1, fp);

        i++;

        if (is_cont == 'n')
            break;

    } while (true);
    fclose(fp);
}
void add_random_data(int n)
{
    /*function for adding new info tabs (plane- flight) by God`s holy dices
    rand() function, I mean.
    Adds n elemnts, n is given in parameters*/
    FILE *fp = fopen("data.dat", "ab");
    std::string dates[] = {"2020.01.20", "2020.01.21", "2020.01.22", "2020.01.23"};
    std::string planes[] = {"Boeing Next Generation 737", "Boeing 737 MAX", "Boeing 777", "Boeing Dreamliner"};

    for (int i = 0; i < n; i++)
    {
        Plane new_plane;
        new_plane.type = planes[rand() % 4];
        new_plane.free_places = (rand() % 3 == 2) ? 0 : rand() % 501 + 500;
        new_plane.ticket_price = rand() % 301 + 100;

        Flight new_flight;
        new_flight.date = dates[rand() % 4];
        new_flight.number = rand() % 9000 + 1000;

        Info *line = new Info(new_plane, new_flight);
        fwrite(line, sizeof(Info), 1, fp);
    }
    fclose(fp);
}
void display_data()
{
    /*displays data from file, nothing special*/
    FILE *fp = fopen("data.dat", "rb");
    Info line;

    for (int i = 0; i < filesize() / sizeof(Info); i++)
    {
        fread(&line, sizeof(Info), 1, fp);
        line.print();
        std::cout << std::endl;
    }

    fclose(fp);
}

void delete_data()
{
    /*requires flight number and rewrites .dat file without info tab with such flight number*/
    FILE *old_file = fopen("data.dat", "rb");
    int size = filesize() / sizeof(Info) - 1;

    Info line;
    Info *list = new Info[size];

    int number;
    std::cout << "Enter flight number to delete: ";
    std::cin >> number;

    bool is_deleted = false;
    for (int i = 0; i < size; i++)
    {
        fread(&line, sizeof(Info), 1, old_file);

        if (line.flight.number == number && !is_deleted)
        {
            is_deleted = true;
            fread(&line, sizeof(Info), 1, old_file);
            continue;
        }
        list[i] = line;
    }
    fclose(old_file);

    FILE *new_file = fopen("data.dat", "wb");
    for (int i = 0; i < size; i++)
        fwrite(&list[i], sizeof(Info), 1, new_file);

    fclose(new_file);
    delete[] list;
}

void edit_data()
{
    /* requires flight number and allows to change all info of this info tab, 
    results are rewrited to the same .dat */
    FILE *old_file = fopen("data.dat", "rb");
    int size = filesize() / sizeof(Info);

    Info line;
    Info *list = new Info[size];

    int number;
    std::cout << "Enter flight number to edit: ";
    std::cin >> number;

    Plane new_plane;
    new_plane.get();

    Flight new_flight;
    new_flight.get();

    Info new_line(new_plane, new_flight);

    for (int i = 0; i < size; i++)
    {
        fread(&line, sizeof(Info), 1, old_file);

        if (line.flight.number == number)
            list[i] = new_line;
        else
            list[i] = line;
    }

    fclose(old_file);

    FILE *new_file = fopen("data.dat", "wb");
    for (int i = 0; i < size; i++)
        fwrite(&list[i], sizeof(Info), 1, new_file);

    fclose(new_file);
    delete[] list;
}

void display_free_places()
{
    /*function displays all flights with free seats*/
    std::cout << "Flights with free seats:" << std::endl;
    FILE *f = fopen("data.dat", "rb");
    int size = filesize() / sizeof(Info);

    Info line;

    int i = 0;
    for (int i = 0; i < size; i++)
    {
        fread(&line, sizeof(Info), 1, f);
        if (line.plane.free_places > 0)
            std::cout << line.flight;
    }

    fclose(f);
}

void flights_on_date()
{
    /*requires date, and shows planes and flight numbers from info tab with that date*/
    std::string date;
    std::cout << "Enter specific date: ";
    std::cin >> date;
    std::cout << "Flights on " << date << ":" << std::endl;
    FILE *f = fopen("data.dat", "rb");
    int size = filesize() / sizeof(Info);

    Info line;

    int i = 0;
    for (int i = 0; i < size; i++)
    {
        fread(&line, sizeof(Info), 1, f);
        if (line.flight.date == date)
            std::cout << line.plane.type << " fligh number: " << line.flight.number << std::endl;
    }

    fclose(f);
}

void sort_array()
{
    /*sorts array in ascending order by ticket price and rewrite it to the same file*/
    FILE *old_file = fopen("data.dat", "rb");
    int size = filesize() / sizeof(Info);

    Info line;
    Info *list = new Info[size];

    int available_index;
    for (int i = 0; i < size; i++)
    {
        fread(&line, sizeof(Info), 1, old_file);
        available_index = i;

        for (int j = i - 1; j >= 0; j--)

            if (line.plane.ticket_price < list[j].plane.ticket_price)
            {
                list[available_index] = list[j];
                available_index = j;
            }
            else
                break;

        list[available_index] = line;
    }
    fclose(old_file);

    FILE *new_file = fopen("data.dat", "wb");
    for (int i = 0; i < size; i++)
        fwrite(&list[i], sizeof(Info), 1, new_file);

    fclose(new_file);
    delete[] list;
}

long filesize()
{
    /*returns file size in bits*/
    FILE *f = fopen("data.dat", "rb");

    long size = 0;
    if (fseek(f, 0, SEEK_END) == 0)
        size = ftell(f);
    fclose(f);
    return size;
}

std::istream &operator>>(std::istream &in, Plane &plane)
{
    std::cout << "Enter type of plane: ";
    in >> plane.type;
    std::cout << "Enter number of free places: ";
    in >> plane.free_places;
    std::cout << "Enter price of tickets: ";
    in >> plane.ticket_price;

    return in;
}

std::ostream &operator<<(std::ostream &out, const Plane &plane)
{
    out << "Plane " << plane.type << " has " << plane.free_places << " seats for $" << plane.ticket_price << " each" << std::endl;
    return out;
}

std::istream &operator>>(std::istream &in, Flight &flight)
{
    std::cout << "Enter flight number: ";
    in >> flight.number;
    std::cout << "Enter date: ";
    in >> flight.date;

    return in;
}

std::ostream &operator<<(std::ostream &out, const Flight &flight)
{
    out << "Flight number " << flight.number << " sheduled on " << flight.date << std::endl;
    return out;
}