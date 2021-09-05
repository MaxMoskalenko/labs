#include <iostream>

#include <ctime>

using namespace std;
struct dekanat
{
    string robitnyk;
    string hours;
    string produktiv;
};
struct Node
{
    dekanat buf;
    Node *next;
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

struct list
{
    Node *hat;
    Node *tail;
    int count;
    list()
    {
        hat = NULL;
        tail = NULL;
        count = 0;
    }

    void push_front(dekanat *el)
    {

        Node *n_node = new Node;
        n_node->buf = *el;
        n_node->next = hat;
        if (hat == NULL)
        {
            tail = n_node;
        }
        hat = n_node;
        count++;
    }
    void push_back(dekanat *elem)
    {
        Node *new_node = new Node;
        new_node->buf = *elem;
        new_node->next = NULL;
        if (tail == NULL)
        {
            hat = new_node;
        }
        else
        {
            tail->next = new_node;
        }
        tail = new_node;
        count++;
    }
    dekanat pop_front()
    {
        if (hat == NULL)
        {
            return {};
        }
        if (hat->next == NULL)
        {
            tail = NULL;
        }
        Node *acd = hat;
        hat = hat->next;

        dekanat zb;
        zb = acd->buf;
        delete acd;
        count--;
        return zb;
    }
    dekanat pop_back()
    {
        if (tail == NULL)
        {
            return {};
        }
        if (hat->next == NULL)
        {
            hat = NULL;
        }
        Node *tmp;
        tmp = hat;
        for (int i = 0; i < count - 2; i++)
        {
            tmp = tmp->next;
        }
        tail = tmp;

        dekanat zb;
        zb = tmp->next->buf;
        tmp->next = NULL;
        delete tmp->next;
        count--;
        return zb;
    }
    dekanat vibirka(int k)
    {
        Node *tmp;
        tmp = hat;
        for (int i = 0; i < k; i++)
        {
            tmp = tmp->next;
        }
        dekanat opa = tmp->buf;

        return opa;
    }

    int weight()
    {
        return count;
    }
    void vyvid()
    {
        Node *tmp;
        tmp = hat;
        for (int i = 0; i < count; i++)
        {

            cout << " Рабочий : " << tmp->buf.robitnyk << "\t"
                 << " К-во рабочих часов: " << tmp->buf.hours << "\t"
                 << "Продуктивность:" << tmp->buf.produktiv << endl;
            tmp = tmp->next;
        }
    }
};

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "RUS");
    list spisok;
    for (int i = 0; i < 50000; i++)
    {
        dekanat chlovek = exp();
        spisok.push_back(&chlovek);
    }
    cout << "1" << endl;
    for (int i = 0; i < 10000; i++)
    {
        dekanat chlovek = exp();
        spisok.push_front(&chlovek);
    }
    cout << "2" << endl;
    for (int i = 0; i < 20000; i++)
    {
        spisok.vibirka(rand() % 60000);
    }
    cout << "3" << endl;
    for (int i = 0; i < 5000; i++)
    {
        spisok.pop_front();
    }
    cout << "4" << endl;

    for (int i = 0; i < 5000; i++)
    {
        spisok.pop_back();
    }
    cout << "5" << endl;
}
2