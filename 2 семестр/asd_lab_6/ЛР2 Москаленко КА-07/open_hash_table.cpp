#include <iostream>
#include <ctime>
#include <cmath>

#include <unordered_map>
using namespace std;

long long generate_key();
const int LENGTH_OF_KEY = 13;
bool testHashTable();
std::string memplates[4] = {"Doge on steroids", "Drake reaction", "Pepe in depression", "Rich Winnie the Pooh"};

struct Data
{
    std::string memplate;
    short level_of_fun;
    int likes;
    Data()
    {
        memplate = memplates[rand() % 4];
        level_of_fun = rand() % 10 + 1;
        likes = rand() % 10001;
    }
    friend std::ostream &operator<<(std::ostream &out, const Data &plane);
};

struct HashNode
{
    bool isEmpty = true;
    long long key;
    Data *data = NULL;
};

struct HashTable
{
    int m;
    HashNode *bucketArray;
    int isize;
    float maxLoadFactor;
    HashTable()
    {
        m = 8;
        bucketArray = new HashNode[m];
        maxLoadFactor = 0.8;
        isize = 0;
    }
    int hash(long long key)
    {
        return key % m;
    }
    void insert(long long key, Data data)
    {
        int position = hash(key);

        while (true)
        {
            if (bucketArray[position].isEmpty)
            {
                bucketArray[position].isEmpty = false;
                bucketArray[position].key = key;
                bucketArray[position].data = &data;
                isize++;
                break;
            }
            if (bucketArray[position].key == key)
            {
                bucketArray[position].data = &data;
                break;
            }
            position = (position + 1) % m;
        }
        if (isize >= maxLoadFactor * m)
            increaseSize();
    }
    Data *find(long long key)
    {
        int position = hash(key);
        for (int i = 0; i < m; i++)
        {
            if (bucketArray[position].data == NULL)
                return NULL;
            if (bucketArray[position].key == key && !bucketArray[position].isEmpty)
                return bucketArray[position].data;

            position = (position + 1) % m;
        }

        return NULL;
    }
    void erase(long long key)
    {
        int position = hash(key);
        for (int i = 0; i < m; i++)
        {
            if (bucketArray[position].data == NULL)
                break;
            if (bucketArray[position].key == key && !bucketArray[position].isEmpty)
            {
                bucketArray[position].isEmpty = true;
                isize--;
                break;
            }
            position = (position + 1) % m;
        }
    }
    int size()
    {
        return isize;
    }
    void increaseSize()
    {
        m *= 2;
        HashNode *oldBuckets = bucketArray;
        bucketArray = new HashNode[m];
        isize = 0;

        for (int i = 0; i < m / 2; i++)
            if (!oldBuckets[i].isEmpty)
                insert(oldBuckets[i].key, *oldBuckets[i].data);

        delete[] oldBuckets;
    }
    ~HashTable()
    {
        delete[] bucketArray;
    }
    void print()
    {
        for (int i = 0; i < m; i++)
            if (!bucketArray[i].isEmpty)
                std::cout << i << "::" << bucketArray[i].key << std::endl;
    }
};

int main()
{
    srand(time(NULL));
    // HashTable table;
    // for (int i = 0; i < 10; i++)
    // {
    //     long long key = generate_key();
    //     std::cout << "add " << key << "; ";
    //     table.insert(key, Data());
    // }
    // std::cout << std::endl;
    // table.print();
    testHashTable();

    // testHashTable();

    return 0;
}

long long generate_key()
{
    long long number = 0;
    for (int i = 0; i < LENGTH_OF_KEY; i++)
        //if it is the last digit remove zero from possible variants
        if (i == LENGTH_OF_KEY - 1)
            number += (rand() % 9 + 1) * pow(10, i);
        else
            number += (rand() % 10) * pow(10, i);

    return number;
}

std::ostream &operator<<(std::ostream &out, const Data &Data)
{
    out << "Data about " << Data.memplate << " is funny on " << Data.level_of_fun << "/10 and got " << Data.likes << " likes" << std::endl;
    return out;
}

bool testHashTable()
{
    const int iters = 500000;
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
    clock_t myEnd = clock();
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

    float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;
    unordered_map<long long, Data> unorderedMap;
    clock_t stlStart = clock();
    for (int i = 0; i < iters; i++)
    {
        unorderedMap.insert({keysToInsert[i], Data()});
    }
    clock_t stlEnd = clock();
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