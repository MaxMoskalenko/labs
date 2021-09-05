#include <iostream>
#include <ctime>
#include <cmath>
#include <queue>
#include <cstdlib>
struct Data
{
    int interest;
    int usefulness;
    int hardness;
    int days_to_deadline;
    Data()
    {
        interest = rand() % 100 + 1;
        usefulness = rand() % 10 + 1;
        hardness = rand() % 10 + 1;
        days_to_deadline = rand() % 10 + 1;
    }
    void show_data()
    {
        std::cout << "i:" << interest << " u:" << usefulness << " h:" << hardness << " d:" << days_to_deadline << "\n";
    }
    friend bool operator<(Data left, Data right);
    friend bool operator==(Data left, Data right);
    friend bool operator>(Data left, Data right);
};

struct DynamicArray
{
    Data *array;
    int length; // length shows how many elements we have in array
    int cap;

    // cap show current max size of our array
    DynamicArray(int capacity)
    {                                       //constructor of array
        cap = capacity <= 0 ? 1 : capacity; // if start capacity lower or equal to zero make it equals to 1
        array = new Data[cap];
        length = 0;
    }
    DynamicArray()
    {
        cap = 8; // if start capacity lower or equal to zero make it equals to 1
        array = new Data[cap];
        length = 0;
    }

    void push_back(Data *Data)
    {
        //add value to array
        array[length] = *Data;

        length++;
        // if we need more space for future pushes, then extend our array
        if (length == cap)
            extend_array();
    }
    void push_front(Data *Data)
    {
        // if we need more space for future pushes, then extend our array
        if (length == cap)
            extend_array();

        for (int i = length - 1; i >= 0; i--)
            array[i + 1] = array[i];

        //add value to array
        array[0] = *Data;
        //if front and back points on the same location we should move both of them

        length++;
    }
    Data pop_back()
    {
        // if back equals to -1, then it starts to point on the end of array
        //pin structure to return
        if (length == 0)
            return {};

        Data Data = array[length - 1];
        length--;
        //if it was last element, back and front returns to default
        return Data;
    }

    Data pop_front()
    {
        if (length == 0)
            return {};
        //pin structure to return
        Data Data = array[0];
        for (int i = 0; i < length; i++)
            array[i] = array[i + 1];
        length--;

        return Data;
    }
    Data get(int n)
    {
        //get n element starting from front+1
        Data Data = array[n];
        return Data;
    }
    int size()
    {
        return length;
    }

    void extend_array()
    {
        //increase capacity in 2 times
        cap *= 2;
        //allocating memory for new array
        Data *new_array = new Data[cap];
        //copy elements from old array to the new one
        relocate_elements(new_array);
        // free memory, which was allocating for the old array
        delete[] array;
        //old array points on the new version of it
        array = new_array;
    }
    void relocate_elements(Data *new_array)
    {
        //copy all elements from front+1 index to 0 index
        for (int i = 0; i < length; i++)
            //cap/2 because we need old memory size
            new_array[i] = array[i];
        //actualy back is length of array and front is -1
    }
};

struct PriorityQueue
{
    DynamicArray list;

    int getParent(int index)
    {
        if (index == 0)
            return -1;

        return floor((index - 1) / 2);
    }
    int getLeftChild(int index)
    {
        return 2 * index + 1;
    }
    int getRightChild(int index)
    {

        return 2 * index + 2;
    }
    void siftUp(int index)
    {
        int pIndex = getParent(index);
        if (pIndex == -1)
            return;
        if (list.get(pIndex) > list.get(index))
            return;

        changeElements(index, pIndex);
        siftUp(pIndex);
    }
    void siftDown(int index)
    {
        int lIndex = getLeftChild(index);
        int rIndex = getRightChild(index);

        int largest = index;
        if (lIndex < list.size() && list.get(lIndex) > list.get(largest))
            largest = lIndex;

        if (rIndex < list.size() && list.get(rIndex) > list.get(largest))
            largest = rIndex;

        if (largest == index)
            return;

        changeElements(index, largest);
        siftDown(largest);
    }
    void changeElements(int i1, int i2)
    {
        Data tmp = list.get(i1);
        list.array[i1] = list.get(i2);
        list.array[i2] = tmp;
    }
    void push(Data task)
    {
        int index = list.size();
        list.push_back(&task);
        siftUp(index);
    }
    Data top()
    {
        return list.get(0);
    }
    void pop()
    {
        list.array[0] = list.pop_back();
        siftDown(0);
    }
    int size()
    {
        return list.size();
    }
    bool empty()
    {
        return list.size() == 0 ? true : false;
    }
    void print()
    {
        for (int i = 0; i < list.size(); i++)
            list.get(i).show_data();
    }
};
bool testPriorityQueue();
void testSorting();
Data *insertion_sort(Data array[], int size);
Data *heap_sort(Data array[], int size);
bool compare_sorted(Data *arr1, Data *arr2, int size);
int main(int argc, char const *argv[])
{
    srand(time(NULL));
    testPriorityQueue();
    testSorting();
    return 0;
}

bool operator<(Data left, Data right)
{
    if (left.interest < right.interest)
        return true;

    else if (left.interest == right.interest && left.usefulness < right.usefulness)
        return true;

    return false;
}
bool operator==(Data left, Data right)
{
    if (left.interest == right.interest && left.usefulness == right.usefulness)
        return true;

    return false;
}

bool operator>(Data left, Data right)
{
    return (right < left);
}

using namespace std;
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
            // myPriorQueue.print();
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
void testSorting()
{
    int size_of_sort = 50000;
    cout << "Sorting result for " << size_of_sort << " elements" << endl;
    Data unsorted_array[size_of_sort];
    Data *insertion_array = new Data[size_of_sort];
    Data *heap_array = new Data[size_of_sort];
    for (int i = 0; i < size_of_sort; i++)
        unsorted_array[i] = Data();

    clock_t time_start, time_end;
    time_start = clock();
    insertion_array = insertion_sort(unsorted_array, size_of_sort);
    time_end = clock();
    cout << "Insertion sort time: " << float(time_end - time_start) / CLOCKS_PER_SEC << endl;

    time_start = clock();
    heap_array = heap_sort(unsorted_array, size_of_sort);
    time_end = clock();
    cout << "Heap sort time: " << float(time_end - time_start) / CLOCKS_PER_SEC << endl;

    if (compare_sorted(insertion_array, heap_array, size_of_sort))
        cout << "And arrays are completly equal 😀\n";
    else
        cout << "But arrays are different 😢\n";

    delete[] insertion_array;
    delete[] heap_array;
}

Data *insertion_sort(Data array[], int size)
{
    Data *sorted = new Data[size];
    Data tmp;
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = i - 1; j >= 0; j--)
        {
            if (sorted[j] > array[i])
                break;

            sorted[j + 1] = sorted[j];
        }
        sorted[j + 1] = array[i];
    }
    return sorted;
}

Data *heap_sort(Data array[], int size)
{
    PriorityQueue heap;
    Data *sorted = new Data[size];
    for (int i = 0; i < size; i++)
        heap.push(array[i]);

    for (int i = 0; i < size; i++)
    {
        sorted[i] = heap.top();
        heap.pop();
    }

    return sorted;
}

bool compare_sorted(Data *arr1, Data *arr2, int size)
{
    for (int i = 0; i < size; i++)
        if (!(arr1[i] == arr2[i]))
            return false;
    return true;
}