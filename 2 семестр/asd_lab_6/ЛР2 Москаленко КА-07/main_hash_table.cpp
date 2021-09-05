#include <iostream>
#include <ctime>
#include <cmath>

#include <unordered_map>
using namespace std;

long long generate_key();
bool testHashTable();

struct Data
{
    std::string memplate;
    short level_of_fun;
    int likes;
    Data()
    {
        std::string memplates[4] = {"Doge on steroids", "Drake reaction", "Pepe in depression", "Rich Winnie the Pooh"};
        memplate = memplates[rand() % 4];
        level_of_fun = rand() % 10 + 1;
        likes = rand() % 10001;
    }
    friend std::ostream &operator<<(std::ostream &out, const Data &plane);
};

struct HashNode
{
    long long key;
    Data data;
    HashNode *next;
    HashNode *prev;
};

struct LinkedList
{
    HashNode *head;
    int length;
    LinkedList()
    {
        head = NULL;
        length = 0;
    }
    void add(long long key, Data data)
    {
        HashNode *node = new HashNode;
        node->data = data;
        node->key = key;

        node->next = head;

        if (head != NULL)
            head->prev = node;

        head = node;
        node->prev = NULL;
        length++;
    }

    bool remove(long long key)
    {
        HashNode *tmp = head;

        for (int i = 0; i < length; i++)
        {
            if (tmp->key == key)
            {
                if (tmp->prev != NULL)
                    tmp->prev->next = tmp->next;
                if (tmp->next != NULL)
                    tmp->next->prev = tmp->prev;
                if (tmp->next == NULL && tmp->prev == NULL)
                    head = NULL;
                if (tmp->prev == NULL)
                    head = tmp->next;

                length--;
                delete tmp;
                return true;
            }
            tmp = tmp->next;
        }
        return false;
    }
    HashNode *pop()
    {
        HashNode *tmp = head;
        head = head->next;
        if (head != NULL)
            head->prev = NULL;
        length--;
        return tmp;
    }
    Data *find(long long key)
    {
        HashNode *tmp = head;
        for (int i = 0; i < length; i++)
        {
            if (tmp->key == key)
                return &tmp->data;
            tmp = tmp->next;
        }
        return NULL;
    }

    ~LinkedList()
    {
        if (head == NULL)
        {
            return;
        }

        for (int i = 0; i < length; i++)
        {
            HashNode *tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    void print()
    {
        HashNode *tmp = head;
        std::cout << "head - ";
        for (int i = 0; i < length; i++)
        {
            std::cout << tmp->key << " - ";
            tmp = tmp->next;
        }

        std::cout << " NULL" << std::endl;
    }
};

struct HashTable
{
    int m;
    LinkedList *bucketArray;
    int isize;
    float loadFactor;
    HashTable()
    {
        m = 8;
        bucketArray = new LinkedList[m];
        isize = 0;
        loadFactor = 0.75;
    }
    int hash(long long key)
    {
        return key % m;
    }
    void insert(long long key, Data data)
    {

        isize = bucketArray[hash(key)].remove(key) ? isize : isize + 1;
        bucketArray[hash(key)].add(key, data);
        if (isize >= loadFactor * m)
            increaseSize();
    }
    Data *find(long long key)
    {
        return bucketArray[hash(key)].find(key);
    }
    void erase(long long key)
    {
        isize = bucketArray[hash(key)].remove(key) ? isize - 1 : isize;
    }
    int size()
    {
        return isize;
    }
    void increaseSize()
    {
        m *= 2;
        LinkedList *tmpBuckets = new LinkedList[m];
        HashNode *tmp;

        for (int i = 0; i < m / 2; i++)
            while (bucketArray[i].head != NULL)
            {
                tmp = bucketArray[i].pop();
                tmpBuckets[hash(tmp->key)].add(tmp->key, tmp->data);
                delete tmp;
            }

        delete[] bucketArray;
        bucketArray = tmpBuckets;
    }
    ~HashTable()
    {
        for (int i = 0; i < m; i++)
            bucketArray[i].~LinkedList();

        delete[] bucketArray;
    }
    void print()
    {
        for (int i = 0; i < m; i++)
        {
            std::cout << i << "::";
            bucketArray[i].print();
        }
    }
};

int main()
{
    srand(time(NULL));
    testHashTable();
    // HashTable table;
    // for (int i = 0; i < 6000000; i++)
    // {
    //     table.insert(generate_key(), Data());
    // }
    // table.print();
    // cout << table.size() << endl;
    // testHashTable();

    return 0;
}

long long generate_key()
{
    long long number = 0;
    for (int i = 0; i < 13; i++)
        //if it is the last digit remove zero from possible variants
        if (i == 12)
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