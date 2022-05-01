#pragma once

#include <ctime>
using namespace std;

class Date
{
private:
    int day;
    int month;
    int year;

public:
    Date()
    {
        time_t now = time(0);

        tm *ltm = localtime(&now);

        day = ltm->tm_mday;
        month = 1 + ltm->tm_mon;
        year = 1900 + ltm->tm_year;
    }
    Date(int _day, int _month, int _year)
    {
        day = _day;
        month = _month;
        year = _year;
    }
    Date(Date &date)
    {
        day = date.day;
        month = date.month;
        year = date.year;
    }
    int getDay()
    {
        return day;
    }
    int getMonth()
    {
        return month;
    }
    int getYear()
    {
        return year;
    }
    void print()
    {
        printf("%02d:%02d:%02d", day, month, year % 100);
    }
    Date *setDay(int _day)
    {
        day = _day;
        return this;
    }
    Date *setMonth(int _month)
    {
        month = _month;
        return this;
    }
    Date *setYear(int _year)
    {
        year = _year;
        return this;
    }
    ~Date() {}
};
