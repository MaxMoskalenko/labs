#include <iostream>

#include <ctime>

#include <locale.h>

#include <cmath>

#include <unordered_map>

using namespace std;

struct Data //создаем структуру
{
    string surname; //ее поля
    int hands;
    char sex;

    Data() //делаем массивчики
    {
        string surname1[8] = {
            "Sidorov",
            "Pushkin",
            "Onegin",
            "Larina",
            "Stepanov",
            "Korsakov",
            "Ibragimov",
            "Clark"};
        int hands1[7] = {
            2,
            3,
            4,
            5,
            6,
            7,
            8};
        char sex1[2] = {
            'W',
            'M'};

        surname = surname1[rand() % 8]; //из которых рандомно выбираем инфу
        hands = hands1[rand() % 7];
        sex = sex1[rand() % 2];
    }

    void vivod() //вывод инфы
    {
        cout
            << " Surname: " << surname << "\t"
            << " Hands : " << hands << "\t"
            << " Sex: " << sex << "\t" << endl;
    }
};

long long generate_key() //функция генератора ключа(ключ состоит из 11 цифр)
{
    long long key = 0;
    for (int i = 0; i < 11; i++) //каждая цифра в ключе
    {
        key += pow(11, i) * (rand() % 11); //ключ в свою очередь имеет такую формулу нахождения
    }
    return key; //возврат функцией ключа
}

struct openData
{
    Data *object = NULL;
    bool nextEmpty = true;
    long long key;
};

struct HashTable
{
    int capacity = 8;                                //к-ство пар
    int Size = 0;                                    //размер пока 0((
    openData *bucketsArray = new openData[capacity]; //динамическое выделение памяти
    double lf = 1;                                   //лоадфактор

    int hash(long long key)
    {
        return key % capacity; //знаем в какую пару вставлять ключ остача от деление на к-ство
    }

    bool pushHowHT(openData *ba, Data obj, long long key)
    {
        int h = hash(key); //допустим тут лежит объект с ключом
        do
        {
            if (ba[h].object != NULL && ba[h].key == key) //если объект не пуст и в  нем ключ
            {
                *(ba[h].object) = obj; //указатель на объект
                ba[h].key = key;       //в объкте ключ
                return false;          //эх...не получилось добавить потому что в элементе ключ есть((
            }
            else if (ba[h].object == NULL) //иф объект пуст и готов принять ключик
            {
                ba[h].object = new Data; //динамически выделяем память
                *(ba[h].object) = obj;   //любимый указатель
                ba[h].key = key;         //кладем ключик
                ba[h].nextEmpty = false; //если и следующий объект пуст
                return true;             //ураааа добавляем дальше
            }
            h++;              //так делаем со всеми объектами
            h = h % capacity; //как мы вообщем берем все эти объекты в массиве пар
        } while (1);          //все это мы делаем пока фактор 1
    }

    void insert(long long key, Data data)
    {
        if (Size >= lf * capacity) //если размер >= лоадфактору * на к-ство пар
        {
            capacity *= 2;                                    //удваиваем к-ство пар
            openData *bucketsArray0 = new openData[capacity]; //динамическая память для вместительности большего к-ства пар
            for (int i = 0; i < capacity / 2; i++)
                if (bucketsArray[i].object != NULL) //если пар не пуст
                {
                    pushHowHT(bucketsArray0, *(bucketsArray[i].object), bucketsArray[i].key); //дзаменяем то что лежало первоначально на новое значение
                }

            delete[] bucketsArray;        //удаляем массив стары х пар
            bucketsArray = bucketsArray0; //говорим что новый массив типо старый
        }

        bool isPushedNew = pushHowHT(bucketsArray, data, key); //говорим что булеая операция бул испушднью это в принципе добавление объекта
        if (isPushedNew)
            Size++; //если это происходит сайз увеличивается
    }

    Data *find(long long key) //нахождение значения под ключом
    {
        int h0;
        int h = hash(key); //таким способом мы понимаем в какой паре искать
        h0 = h;            //если ключи и там и там равны
        do
        {
            if (bucketsArray[h].object != NULL && bucketsArray[h].key == key)             //если объект не пуст и содержит ключ который над
                return bucketsArray[h].object;                                            //возврат указателя на объкет
            else if (bucketsArray[h].object == NULL && bucketsArray[h].nextEmpty == true) //иначе если объект пуст и следующий элемент тоже
                return NULL;                                                              //пустотаааа..
            h++;                                                                          //отакот делаем делаем и делаем
            h = h % capacity;                                                             //как из массива достаем элементы
        } while (h != h0);                                                                //делаем пока ключи равны

        return NULL; //иначе опять вернем пустоту
    }

    void erase(long long key) //удаление под нужным ключом
    {
        int h0;
        int h = hash(key);
        h0 = h;

        do
        {
            if (bucketsArray[h].object != NULL && bucketsArray[h].key == key)             //если объект не пуст и содержит нужный ключ
                break;                                                                    //выход
            else if (bucketsArray[h].object == NULL && bucketsArray[h].nextEmpty == true) //если объект пуст и след тоже
                return;                                                                   //ничего
            h++;
            h = h % capacity;
        } while (h0 != h); //делаем пока ключи равны

        delete bucketsArray[h].object;     //удаляем вообщем ключ
        bucketsArray[h].object = NULL;     //говорим что  объект пуст
        bucketsArray[h].nextEmpty = false; //следующий элемент не пуст
        Size--;                            //размер убывает
    }

    int size()
    {
        return Size; //возврат сайза
    }
};

bool testHashTable();
int main()
{
    srand(time(NULL));
    testHashTable();
}
bool testHashTable()
{
    const int iters = 20000;
    const int keysAmount = iters * 1;
    long long *keys = new long long[keysAmount];
    long long *keysToInsert = new long long[iters];
    long long *keysToErase = new long long[iters];
    long long *keysToFind = new long long[iters];
    for (int i = 0; i < keysAmount; i++)
    {
        keys[i] = generate_key();
    }
    for (int i = 0; i < iters; i++)
    {
        keysToInsert[i] = keys[generate_key() % keysAmount];
        keysToErase[i] = keys[generate_key() % keysAmount];
        keysToFind[i] = keys[generate_key() % keysAmount];
    }

    HashTable hashTable;
    clock_t myStart = clock();
    for (int i = 0; i < iters; i++)
    {
        hashTable.insert(keysToInsert[i], Data());
    }
    int myInsertSize = hashTable.size();
    for (int i = 0; i < iters; i++)
    {
        hashTable.erase(keysToErase[i]);
    }
    int myEraseSize = hashTable.size();
    int myFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (hashTable.find(keysToFind[i]) != NULL)
        {
            myFoundAmount++;
        }
    }
    clock_t myEnd = clock();
    float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;
    unordered_map<long long, Data> unorderedMap;
    clock_t stlStart = clock();
    for (int i = 0; i < iters; i++)
    {
        unorderedMap.insert({keysToInsert[i], Data()});
    }
    int stlInsertSize = unorderedMap.size();
    for (int i = 0; i < iters; i++)
    {
        unorderedMap.erase(keysToErase[i]);
    }
    int stlEraseSize = unorderedMap.size();
    int stlFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (unorderedMap.find(keysToFind[i]) != unorderedMap.end())
        {
            stlFoundAmount++;
        }
    }
    clock_t stlEnd = clock();
    float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC;
    cout << "My HashTable:" << endl;
    cout << "Time: " << myTime << ", size: " << myInsertSize << " -" << myEraseSize << ", found amount: " << myFoundAmount << endl;
    cout << "STL unordered_map:" << endl;
    cout << "Time: " << stlTime << ", size: " << stlInsertSize << " -" << stlEraseSize << ", found amount: " << stlFoundAmount << endl
         << endl;
    delete[] keys;
    delete[] keysToInsert;
    delete[] keysToErase;
    delete[] keysToFind;
    if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize && myFoundAmount == stlFoundAmount)
    {
        cout << "The lab is completed" << endl;
        return true;
    }
    cerr << ":(" << endl;
    return false;
}
