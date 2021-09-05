#include <iostream>
#include <queue>

using namespace std;

struct Data
{
    int interest = rand() % 100;
    int usefulness = rand() % 200 - 100;
    int complexity = rand() % 200;
    int deadline = rand() % 100;

    bool operator<(const Data &B) const
    {
        return (interest + usefulness + complexity + deadline) < (B.interest + B.usefulness + B.complexity + B.deadline);
    }

    bool operator>(const Data &B) const
    {
        return (interest + usefulness + complexity + deadline) > (B.interest + B.usefulness + B.complexity + B.deadline);
    }

    bool operator==(const Data &B) const
    {
        return (interest + usefulness + complexity + deadline) == (B.interest + B.usefulness + B.complexity + B.deadline);
    }
};

struct kol
{

    Data *array;
    int position = 0;
    int counter;
    kol()
    { //конструктор
        counter = 10;
        array = new Data[counter];
    }
    void doublesize()
    { //удваиваем размер
        counter = counter * 2;
        Data *array2;
        array2 = new Data[counter];
        for (int i = 0; i < position; i++)
        {
            array2[i] = array[i];
        }
        delete[] array;
        array = array2;
    }

    void push_back(Data *elem)
    {                            //добавление
        array[position] = *elem; //всовываем в ячейку значение
        position++;              //всовываем дальше
        if (position >= counter)
        { //если уже некуда сувать а надо вызываем функцию удвоение размера
            doublesize();
        }
    }
    Data pop_back()
    {                              //удаление
        Data tmp;                  //создаем ячейку
        tmp = array[position - 1]; //вкладываем ячейку которую хотим уничтожить
        position--;                //размер уменьшается
        return tmp;                //ячейка возвращается
    }

    void push_front(Data *r)
    {
        Data abc; //создаем ячейку
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
    Data pop_front()
    {
        Data def = array[0]; //вкладываем в ячейку корень
        for (int i = 0; i < position; i++)
        {                            //идем по массиву
            array[i] = array[i + 1]; //передвигаем значения
        }
        position--; //размер уменьшается
        return def; //возвращаем ячейку которую ремембер
    }
    Data get(int i)
    {
        return array[i]; //возвращаем ячейку которую хотим
    }

    int size()
    {
        return position; //возвращаем размер
    }

    ~kol()
    { //деструктор
        delete[] array;
    }
};

struct PriorityQueue
{
    kol binaryTree; //конструктор что где когда какие ячейки занимает правый, левый эл и их папочка

    int right(int elem)
    {
        return 2 * elem + 2;
    }

    int left(int elem)
    {
        return 2 * elem + 1;
    }

    int parent(int elem)
    {
        return (elem - 1) / 2;
    }

    void siftDown(int elem)
    {
        int max;
        while (elem < binaryTree.size() / 2) //пока элемент меньше чем размер деленый на два
        {
            max = left(elem);                                                                                  //говорим что максимальный и высшей касты будет левый дочерний элемент
            if (right(elem) <= binaryTree.size() - 1 && binaryTree.array[right(elem)] > binaryTree.array[max]) //если правый элемент не последний и правый больше чем максимальный
            {
                max = right(elem); //говорим а-а-а теперь правый рулит
            }

            if (binaryTree.array[elem] == binaryTree.array[max] ||
                binaryTree.array[elem] > binaryTree.array[max]) //если элемент максимальный или больше максимального
            {
                return; //ауф все работает харашо
            }

            Data temp = binaryTree.array[elem];             //наша любимая схема запоминаем элемент
            binaryTree.array[elem] = binaryTree.array[max]; //присваиваем звание максимального
            binaryTree.array[max] = temp;                   //так бы сказать подтверждаем - вставляем на

            elem = max; //элемент максимальный
        }
    }

    void siftUp(int elem)
    {
        while (elem > 0 && binaryTree.array[elem] > binaryTree.array[parent(elem)]) //если элемент больше нуля и элемент больше чем его батька
        {
            Data temp = binaryTree.array[elem];                      //запомнили єлемент
            binaryTree.array[elem] = binaryTree.array[parent(elem)]; //присвоили
            binaryTree.array[parent(elem)] = temp;                   //вставили

            elem = parent(elem); //элемент который был в подчинении сам стал батькой
        }
    }

    int size()
    {
        return binaryTree.size(); //возвращаем размер
    }

    bool empty()
    {
        if (binaryTree.size() == 0) //если размер 0 возвращаем тру или фолс если сайз не 0
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void push(Data data)
    {
        binaryTree.push_back(&data); //добавляем эл взад
        siftUp(size() - 1);          //просеиваем снизу вверх
    }

    Data top()
    {
        return binaryTree.get(0); //ну тип возвращаем нулячий размер
    }

    void pop()
    {
        Data temp = binaryTree.array[size() - 1];           //запомнили
        binaryTree.array[size() - 1] = binaryTree.array[0]; //присвоили
        binaryTree.array[0] = temp;                         //всунули

        binaryTree.pop_back(); //удалили
        siftDown(0);           //просеяли
    }
};

template <typename T>
float testPriorityQueueSpeed(T &&priorityQueue)
{
    const int iters = 100000;
    clock_t timeStart = clock();
    for (int i = 0; i < iters; i++)
    {
        int insertDataAmount = rand() % 6 + 5;
        for (int j = 0; j < insertDataAmount; j++)
        {
            priorityQueue.push(Data());
        }
        priorityQueue.top();
        priorityQueue.pop();
    }
    clock_t timeEnd = clock();
    float time = (float(timeEnd - timeStart)) / CLOCKS_PER_SEC;
    return time;
}

bool testPriorityQueue()
{
    srand(time(NULL));
    const int iters = 20000;
    PriorityQueue myPriorQueue;
    priority_queue<Data> stlPriorQueue;
    bool isDataEqual = true;
    for (int i = 0; i < iters; i++)
    {
        int insertDataAmount = rand() % 6 + 5;
        for (int j = 0; j < insertDataAmount; j++)
        {
            Data randData = Data();
            myPriorQueue.push(randData);
            stlPriorQueue.push(randData);
        }
        if (!(myPriorQueue.top() == stlPriorQueue.top()))
        {
            isDataEqual = false;
            cerr << "Comparing failed on iteration " << i << endl
                 << endl;
            break;
        }
        int removeDataAmount = rand() % insertDataAmount;
        for (int j = 0; j < removeDataAmount; j++)
        {
            myPriorQueue.pop();
            stlPriorQueue.pop();
        }
    }
    int myQueueSize = myPriorQueue.size();
    int stlQueueSize = stlPriorQueue.size();
    float stlTime = testPriorityQueueSpeed<priority_queue<Data>>(priority_queue<Data>());
    float myTime = testPriorityQueueSpeed<PriorityQueue>(PriorityQueue());
    cout << "My PriorityQueue:" << endl;
    cout << "Time: " << myTime << ", size: " << myQueueSize << endl;
    cout << "STL priority_queue:" << endl;
    cout << "Time: " << stlTime << ", size: " << stlQueueSize << endl
         << endl;
    if (isDataEqual && myQueueSize == stlQueueSize)
    {
        cout << "The lab is completed" << endl
             << endl;
        return true;
    }
    cerr << ":(" << endl
         << endl;
    return false;
}

int left(int elem) //где правые где левые
{
    return 2 * elem + 1;
}

int right(int elem)
{
    return 2 * elem + 2;
}

void siftDown(int *toSortArray, int Amount, int elem)
{
    int j = elem;
    int l, r;
    while (j < Amount / 2) // siftDown
    {
        l = left(j);
        r = right(j);

        int max = l;                                              //максимальный в свою очередь левый дочерний эл
        if (r <= Amount - 1 && toSortArray[max] < toSortArray[r]) //правый не последний и максимальный меньше правого
        {
            max = r; //максимальным становится правый
        }

        if (toSortArray[max] <= toSortArray[j]) //если максимальный<=отсортированому эл
        {
            break; //выход
        }

        int temp = toSortArray[max];       //запоминаем макс эл
        toSortArray[max] = toSortArray[j]; //присваиваем
        toSortArray[j] = temp;             //всовываем

        j = max; //дело сделано
    }
}

void heap(int *toSortArray, int Amount)
{
    PriorityQueue heap;
    Data *new_arr = new Data[Amount];
    for (int i = 0; i < Amount; i++)
        heap.push(toSortArray[i]);

    for (int i = 0; i < Amount / 2; i++)
    {
        new_arr[i] = heap.top();
        heap.pop();
    }
}

int main()
{
    srand(time(NULL));
    testPriorityQueue();

    Data *testArray = new Data[50000];
    Data *testArray2 = new Data[50000];
    Data data;
    for (int i = 0; i < 50000; i++)
    {
        testArray[i] = Data();
    }
    for (int i = 0; i < 50000; i++)
    {
        testArray2[i] = testArray[i];
    }

    clock_t time_start = clock();
    heap(testArray, 50000);
    clock_t time_end = clock();

    float time1 = float(time_end) - float(time_start);
    cout << time1 << endl;

    clock_t time_start2 = clock();
    sort(begin(testArray2), end(testArray2));
    clock_t time_end2 = clock();

    float time2 = float(time_end2) - float(time_start2);
    cout << time2 << endl;

    int error = 0;
    for (int i = 0; i < 50000; i++)
    {
        if (testArray[i] != testArray2[i])
            error += 1;
    }

    cout << "Error: " << error << endl;
}
