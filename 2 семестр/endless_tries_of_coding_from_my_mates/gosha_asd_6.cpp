#include <ctime>
#include <cstdlib>
#include <cmath>
#include <unordered_map>
#include <iostream>
using namespace std;
struct Data
{
    char sex;
    int hands;
    int speak;
    Data()
    {
        hands = rand() % 11;
        speak = rand() % 2;
        int b = rand() % 2;
        switch (b)
        {
        case 0:
            sex = 'w';
            break;
        case 1:
            sex = 'm';
            break;
        default:
            sex = '?';
        }
    }
};
//states: "deleted 0 exists 0"-не существовал, "deleted 1 exists 0"-удален, "deleted 0 exists 1"-существует

struct HashNode
{
    long long key;
    Data Robot;
    bool deleted = 0;
    bool exists = 0;
};

struct HashTable
{
    HashNode *array = new HashNode;
    double LoadFactor = 0.75;
    int size = 0;
    int capacity = 2;
    int find_identical_key(int h, long long k, struct Data Robot)
    {
        while (array[h].exists == 1 || array[h].deleted == 1)
        {
            if (array[h].key == k)
            {
                array[h].Robot = Robot;
                return 1;
            }
            h++;
            if (h == capacity)
                h = 0;
        }
        return 0;
    }
    void realloc()
    {
        capacity = capacity * 2;
        HashNode *new_mass = new HashNode[capacity];
        for (int q = 0; q < capacity / 2; q++)
        {
            if (array[q].exists == 1)
            {
                int h = hash(array[q].key);
                while (new_mass[h].exists == 1)
                {
                    h++;
                    if (h == capacity)
                        h = 0;
                }
                new_mass[h] = array[q];
            }
        }
        HashNode *ToDelete = array;
        array = new_mass;
        delete ToDelete;
    }
    void insert(long long k, struct Data Robot)
    {
        // std::cout << k << " ";
        if (find_identical_key(hash(k), k, Robot) == 0)
        {
            int h = hash(k);
            while (array[h].exists == 1)
            {
                h++;
                if (h == capacity)
                    h = 0;
            }
            array[h].Robot = Robot;
            array[h].deleted = 0;
            array[h].exists = 1;
            array[h].key = k;
            size++;
        }
        if (size >= capacity * LoadFactor)
            realloc();
        // cout << size << std::endl;
    }
    HashNode *find_key(long long k)
    {
        if (size >= 1)
        {
            int h = hash(k);
            while (array[h].exists == 1 || array[h].deleted == 1)
            {
                if (array[h].key == k)
                    return &array[h];
                h++;
                if (h == capacity)
                    h = 0;
            }
            return NULL;
        }
        return NULL;
    }

    Data *erase(long long k)
    {
        if (size >= 1)
        {
            int h = hash(k);
            HashNode *p = find_key(k);
            if (p != NULL)
            {
                p->exists = 0;
                p->deleted = 1;
                p->key = -1;
                size--;
                return &(p->Robot);
            }
        }
        return NULL;
    }
    int hash(long long key)
    {
        return key % capacity;
    }
    int sizee()
    {
        return size;
    }
};

long long generate_key()
{
    long long key = 0;
    int digits[10];
    int z;
    for (int i = 9; i >= 0; i--)
    {
        z = rand() % 10;
        if (i == 0 && z == 0)
        {
            while (z == 0)
            {
                z = rand() % 10;
            }
            digits[i] = z;
        }
        else
            digits[i] = rand() % 10;
    }

    for (int i = 9; i >= 0; i--)
    {
        long long power = pow(10, i);
        key = key + power * digits[i];
    }
    return key;
}
bool testHashTable();
int main()
{
    srand(time(NULL));
    testHashTable();
}

bool testHashTable()
{
    const int iters = 10000;
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
    int myInsertSize = hashTable.sizee();
    for (int i = 0; i < iters; i++)
    {
        hashTable.erase(keysToErase[i]);
    }
    int myEraseSize = hashTable.sizee();
    int myFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (hashTable.find_key(keysToFind[i]) != NULL)
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
