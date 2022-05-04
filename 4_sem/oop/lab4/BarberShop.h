#pragma once

#include <string>
#include "Haircut.h"
#include "Date.h"

class BarberShop
{
private:
    int barberNumber;
    Date *date;
    Haircut **completedHaircuts;
    int completedHaircutsSize;

    void copyArray(Haircut **array, int size)
    {
        completedHaircutsSize = size;
        completedHaircuts = new Haircut *[completedHaircutsSize];
        for (int i = 0; i < completedHaircutsSize; i++)
        {
            completedHaircuts[i] = new Haircut(*array[i]);
        }
    }
    void deleteArray()
    {
        for (int i = 0; i < completedHaircutsSize; i++)
        {
            delete completedHaircuts[i];
        }
        delete completedHaircuts;
    }

public:
    static int additionalServiceCost;
    BarberShop()
    {
        barberNumber = 0;
        date = new Date();
        completedHaircuts = nullptr;
        completedHaircutsSize = 0;
    }
    BarberShop(int _barberNumber, Date *_date, Haircut **_completedHaircuts, int _completedHaircutsSize)
    {
        barberNumber = _barberNumber;
        date = new Date(*_date);
        copyArray(_completedHaircuts, _completedHaircutsSize);
    }
    BarberShop(BarberShop &barberShop)
    {
        barberNumber = barberShop.barberNumber;
        date = new Date(*barberShop.date);
        copyArray(barberShop.completedHaircuts, barberShop.completedHaircutsSize);
    }
    int getBarberNumber()
    {
        return barberNumber;
    }
    Date *getDate()
    {
        return date;
    }
    Haircut **getCompletedHaircuts()
    {
        return completedHaircuts;
    }
    int getCompletedHaircutsSize()
    {
        return completedHaircutsSize;
    }
    virtual void print()
    {
        printf("%d ", barberNumber);
        date->print();
        printf(" {");
        for (int i = 0; i < completedHaircutsSize; i++)
        {
            if (i == 0)
            {
                printf("\n");
            }
            printf("\t");
            completedHaircuts[i]->print();
            printf("\n");
        }
        printf("} %d", completedHaircutsSize);
    }
    virtual void printShort()
    {
        printf("%d ", barberNumber);
        date->print();
        int totalCost = 0;
        for (int i = 0; i < completedHaircutsSize; i++)
        {
            totalCost += completedHaircuts[i]->getCost();
            totalCost += completedHaircuts[i]->getAdditionalService() ? additionalServiceCost : 0;
        }
        printf(" %d", totalCost);
    }
    BarberShop *setBarberNumber(int _barberNumber)
    {
        barberNumber = _barberNumber;
        return this;
    }
    BarberShop *setDate(Date *_date)
    {
        date = new Date(*_date);
        return this;
    }
    BarberShop *setCompletedHaircuts(Haircut **_completedHaircuts, int _completedHaircutsSize)
    {
        deleteArray();
        copyArray(_completedHaircuts, _completedHaircutsSize);
        return this;
    }
    void addHaircut(Haircut *haircut)
    {
        Haircut **newArray = new Haircut *[completedHaircutsSize + 1];

        for (int i = 0; i < completedHaircutsSize; i++)
        {
            newArray[i] = new Haircut(*completedHaircuts[i]);
        }
        newArray[completedHaircutsSize] = new Haircut(*haircut);
        deleteArray();

        completedHaircutsSize++;
        completedHaircuts = newArray;
    }

    Haircut& operator[](int index)
    {
        if (index >= completedHaircutsSize) {
            printf("Array index out of bound, exiting\n");
            exit(0);
        }
        return *completedHaircuts[index];
    }

    ~BarberShop()
    {
        delete date;
        deleteArray();
    }
};

