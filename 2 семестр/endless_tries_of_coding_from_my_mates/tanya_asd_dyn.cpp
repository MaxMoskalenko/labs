#include <iostream>

#include <ctime>

using namespace std;

struct dekanat
{
    string robitnyk;
    string hours;
    string produktiv;
};

struct kol
{

    dekanat *array;
    int position = 0;
    int counter;
    kol()
    {
        counter = 10;
        array = new dekanat[counter];
    }
    void doublesize()
    {
        counter = counter * 2;
        dekanat *array2;
        array2 = new dekanat[counter];
        for (int i = 0; i < position; i++)
        {
            array2[i] = array[i];
        }
        delete[] array;
        array = array2;
    }

    void push_back(dekanat *elem)
    {
        array[position] = *elem;
        position++;
        if (position >= counter)
        {
            doublesize();
        }
    }
    dekanat pop_back()
    {
        dekanat tmp;
        tmp = array[position - 1];
        position--;
        return tmp;
    }

    void push_front(dekanat *r)
    {
        dekanat abc;
        for (int i = position - 1; i >= 0; i--)
        {
            array[i + 1] = array[i];
        }
        array[0] = *r;
        position++;
        if (position >= counter)
        {
            doublesize();
        }
    }
    dekanat pop_front()
    {
        dekanat def = array[0];
        for (int i = 0; i < position; i++)
        {
            array[i] = array[i + 1];
        }
        position--;
        return def;
    }
    dekanat get(int i)
    {
        return array[i];
    }

    int weight()
    {
        return position;
    }

    void vyvid()
    {
        for (int i = 0; i < position; i++)
        {
            cout << " Рабочий : " << array[i].robitnyk << "\t"
                 << " К-во рабочих часов: " << array[i].hours << "\t"
                 << "Продуктивность:" << array[i].produktiv << endl;
        }
    }

    ~kol()
    {
        delete[] array;
    }
};

dekanat exp()
{
    string robitnyk[10] = {
        "Макиавелли",
        "Пушкин",
        "Лермонтов",
        "Маяковский",
        "Притула",
        "Зеленский",
        "Федоров",
        "Литвак",
        "Иванов",
        "Середюк"};
    string hours[3] = {
        "десять ",
        "девять ",
        "восемь "};
    string produktiv[4] = {
        "отлично",
        "хорошо",
        "средне",
        "плохо"};

    dekanat chlovek = {
        robitnyk[rand() % 10],
        hours[rand() % 3],
        produktiv[rand() % 4]};
    return chlovek;
}

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "RUS");
    kol din_array;
    clock_t t_start, t_end;
    float seconds;

    t_start = clock();
    for (int i = 0; i < 50000; i++)
    {
        dekanat chlovek = exp();
        din_array.push_back(&chlovek);
    }
    t_end = clock();
    seconds = (float(t_end - t_start)) / CLOCKS_PER_SEC;
    cout << "push_back : " << seconds << endl;

    t_start = clock();
    for (int i = 0; i < 10000; i++)
    {
        dekanat chlovek = exp();
        din_array.push_front(&chlovek);
    }
    t_end = clock();
    seconds = (float(t_end - t_start)) / CLOCKS_PER_SEC;
    cout << "push_front : " << seconds << endl;

    t_start = clock();
    for (int i = 0; i < 20000; i++)
    {
        din_array.get(rand() % 60000);
    }
    t_end = clock();
    seconds = (float(t_end - t_start)) / CLOCKS_PER_SEC;
    cout << "get: " << seconds << endl;

    t_start = clock();
    for (int i = 0; i < 5000; i++)
    {
        din_array.pop_front();
    }
    t_end = clock();
    seconds = (float(t_end - t_start)) / CLOCKS_PER_SEC;
    cout << "pop_front: " << seconds << endl;

    t_start = clock();
    for (int i = 0; i < 5000; i++)
    {
        din_array.pop_back();
    }
    t_end = clock();
    seconds = (float(t_end - t_start)) / CLOCKS_PER_SEC;
    cout << "pop_back : " << seconds << endl;

    return 0;
}