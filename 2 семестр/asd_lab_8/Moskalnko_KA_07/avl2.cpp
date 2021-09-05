#include <iostream>
#include <ctime>
#include <set>
#include <vector>
#include <cstdlib>
#include <cmath>
using namespace std;

std::string possibleNames[] = {"OG", "Nigma", "TNC Pro Team", "PSD.LGD", "EHOME", "Thunder Predator", "Vikin.gg", "Team Secret"};

struct Data
{
    std::string teamName;
    int numberOfWins;
    int yearOfCreation;
    long id;
    Data()
    {
        teamName = possibleNames[rand() % 8];
        numberOfWins = rand() % 2000;
        yearOfCreation = 1980 + rand() % 40;
        id = rand() % 999999999 + 1;
        // id = rand() % 100;
    }
    friend bool operator<(Data left, Data right);
    friend bool operator==(Data left, Data right);
    friend bool operator>(Data left, Data right);
};

struct Node
{
    Data data;
    Node *left;
    Node *right;
    int height;

    Node(Data _team)
    {
        data = _team;
        left = NULL;
        right = NULL;
        height = 1;
    }
    Node() {}
};

struct AVLTree
{
    Node *root = NULL;
    int treeSize = 0;

    void insert(Data data)
    {
        root = insert(data, root);
    }
    Node *insert(Data data, Node *tmp)
    {
        if (tmp == NULL)
        {
            Node *newNode = new Node(data);
            treeSize++;
            tmp = newNode;
            return tmp;
        }
        if (data == tmp->data)
        {
            tmp->data = data;
            return tmp;
        }
        if (data < tmp->data)
            tmp->left = insert(data, tmp->left);
        else
            tmp->right = insert(data, tmp->right);

        tmp->height = getHeight(tmp);

        if (getBalance(tmp) == 2 && getBalance(tmp->left) == 1)
            tmp = turnLeft(tmp);

        else if (getBalance(tmp) == -2 && getBalance(tmp->right) == -1)
            tmp = turnRight(tmp);

        else if (getBalance(tmp) == -2 && getBalance(tmp->right) == 1)
            tmp = turnRightLeft(tmp);

        else if (getBalance(tmp) == 2 && getBalance(tmp->left) == -1)
            tmp = turnLeftRight(tmp);

        return tmp;
    }
    void erase(Data data)
    {
        root = erase(root, data);
    }
    Node *erase(Node *tmp, Data data)
    {
        if (tmp == NULL)
        {
            return tmp;
        }

        if (tmp->left == NULL && tmp->right == NULL && tmp->data == data)
        {
            if (tmp == root)
                root = NULL;
            delete tmp;
            treeSize--;
            return NULL;
        }

        if (tmp->data < data)
        {
            tmp->right = erase(tmp->right, data);
        }
        else if (tmp->data > data)
        {
            tmp->left = erase(tmp->left, data);
        }
        else
        {
            Node *changer;
            if (tmp->left != NULL)
            {
                changer = getMax(tmp->left);
                tmp->data = changer->data;
                tmp->left = erase(tmp->left, changer->data);
            }
            else
            {
                changer = getMin(tmp->right);
                tmp->data = changer->data;
                tmp->right = erase(tmp->right, changer->data);
            }
        }

        if (getBalance(tmp) == 2 && getBalance(tmp->left) == 1)
        {
            tmp = turnLeft(tmp);
        }
        else if (getBalance(tmp) == 2 && getBalance(tmp->left) == -1)
        {
            tmp = turnLeftRight(tmp);
        }
        else if (getBalance(tmp) == 2 && getBalance(tmp->left) == 0)
        {
            tmp = turnLeft(tmp);
        }
        else if (getBalance(tmp) == -2 && getBalance(tmp->right) == -1)
        {
            tmp = turnRight(tmp);
        }
        else if (getBalance(tmp) == -2 && getBalance(tmp->right) == 1)
        {
            tmp = turnRightLeft(tmp);
        }
        else if (getBalance(tmp) == -2 && getBalance(tmp->right) == 0)
        {
            tmp = turnRight(tmp);
        }

        return tmp;
    }

    bool find(Data data)
    {
        Node *tmp = root;
        if (root == NULL)
            return false;
        while (true)
        {
            if (tmp->data == data)
                return true;
            if (tmp->data > data)
            {
                if (tmp->left == NULL)
                    return false;
                else
                    tmp = tmp->left;
            }
            if (tmp->data < data)
            {
                if (tmp->right == NULL)
                    return false;
                else
                    tmp = tmp->right;
            }
        }
    }
    int findInRange(Data min, Data max, Node *tmp)
    {
        int amount = 0;
        if (tmp == NULL || min > max)
            return 0;

        if ((tmp->data > min && tmp->data < max) || tmp->data == min || tmp->data == max)
            amount += 1;

        if (tmp->data > min || tmp->data == min)
            amount += findInRange(min, max, tmp->left);

        if (tmp->data < max || tmp->data == max)
            amount += findInRange(min, max, tmp->right);

        return amount;
    }
    int findInRange(Data min, Data max)
    {
        return findInRange(min, max, root);
    }

    Node *getMax(Node *root)
    {
        while (root->right)
            root = root->right;
        return root;
    }
    Node *getMin(Node *root)
    {
        while (root->left)
            root = root->left;
        return root;
    }

    int getHeight(Node *tmp)
    {
        if (tmp->left && tmp->right)
            if (tmp->left->height < tmp->right->height)
                return tmp->right->height + 1;
            else
                return tmp->left->height + 1;

        else if (tmp->left && tmp->right == NULL)
            return tmp->left->height + 1;

        else if (tmp->left == NULL && tmp->right)
            return tmp->right->height + 1;

        return 1;
    }

    int getBalance(Node *tmp)
    {
        if (tmp->left && tmp->right)
        {
            return tmp->left->height - tmp->right->height;
        }
        else if (tmp->left && tmp->right == NULL)
        {
            return tmp->left->height;
        }
        else if (tmp->left == NULL && tmp->right)
        {
            return -tmp->right->height;
        }
        return 0;
    }

    Node *turnLeft(Node *n)
    {
        Node *nr;
        nr = n->left;

        n->left = nr->right;
        nr->right = n;

        n->height = getHeight(n);
        nr->height = getHeight(nr);

        return nr;
    }
    Node *turnRight(Node *n)
    {
        Node *nr = n->right;

        n->right = nr->left;
        nr->left = n;

        n->height = getHeight(n);
        nr->height = getHeight(nr);

        return nr;
    }
    Node *turnRightLeft(Node *n)
    {
        Node *n2 = n->right;
        Node *nr = n->right->left;

        n->right = nr->left;
        n2->left = nr->right;
        nr->left = n;
        nr->right = n2;

        n->height = getHeight(n);
        n2->height = getHeight(n2);
        nr->height = getHeight(nr);

        return nr;
    }
    Node *turnLeftRight(Node *n)
    {
        Node *n2 = n->left;
        Node *nr = n->left->right;

        n->left = nr->right;
        n2->right = nr->left;
        nr->right = n;
        nr->left = n2;

        n->height = getHeight(n);
        n2->height = getHeight(n2);
        nr->height = getHeight(nr);

        return nr;
    }

    int height()
    {
        return root->height;
    }

    void print__(Node *tmp)
    {
        if (tmp == NULL)
        {
            return;
        }
        cout << "   " << tmp->data.id << endl;
        cout << "  /  \\" << endl;
        cout << (tmp->left == NULL ? 0 : tmp->left->data.id) << "      " << (tmp->right == NULL ? 0 : tmp->right->data.id) << endl;
        print__(tmp->left);
        print__(tmp->right);
    }
    int size()
    {
        return treeSize;
    }

    void destroy(Node *tmp)
    {
        if (tmp == NULL)
            return;
        if (tmp->left != NULL)
            destroy(tmp->left);
        if (tmp->right != NULL)
            destroy(tmp->right);
        delete tmp;
    }
    ~AVLTree()
    {
        destroy(root);
    }
};

long generateRandLong()
{
    return rand();
}

bool operator<(Data left, Data right)
{
    return (left.id < right.id);
}
bool operator==(Data left, Data right)
{

    return (left.id == right.id);
}

bool operator>(Data left, Data right)
{
    return (right < left);
}

bool testBinarySearchTree()
{
    srand(time(NULL));
    const int iters = 80000;
    const int keysAmount = iters * 2;
    const int itersToRangeQueries = 1000;
    vector<Data> data(keysAmount);
    vector<Data> dataToInsert(iters);
    vector<Data> dataToErase(iters);
    vector<Data> dataToFind(iters);
    vector<pair<Data, Data>> dataToRangeQueries;

    for (int i = 0; i < iters; i++)
    {
        dataToInsert[i] = data[generateRandLong() % keysAmount];
        dataToErase[i] = data[generateRandLong() % keysAmount];
        dataToFind[i] = data[generateRandLong() % keysAmount];
    }
    for (int i = 0; i < itersToRangeQueries; i++)
    {
        Data minData = Data();
        Data maxData = Data();
        if (maxData < minData)
        {
            swap(minData, maxData);
        }
        dataToRangeQueries.push_back({minData, maxData});
    }
    AVLTree myTree;
    clock_t myStart = clock();
    for (int i = 0; i < iters; i++)
    {
        myTree.insert(dataToInsert[i]);
    }
    int myInsertSize = myTree.size();
    int myTreeHeight = myTree.height();
    int optimalTreeHeight = log2(myInsertSize) + 1;
    for (int i = 0; i < iters; i++)
    {
        myTree.erase(dataToErase[i]);
    }
    int myEraseSize = myInsertSize - myTree.size();
    int myFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (myTree.find(dataToFind[i]))
        {
            myFoundAmount++;
        }
    }
    clock_t myEnd = clock();
    float myTime = (float(myEnd - myStart)) / CLOCKS_PER_SEC;
    set<Data> stlTree;
    clock_t stlStart = clock();
    for (int i = 0; i < iters; i++)
    {
        stlTree.insert(dataToInsert[i]);
    }
    int stlInsertSize = stlTree.size();
    for (int i = 0; i < iters; i++)
    {
        stlTree.erase(dataToErase[i]);
    }
    int stlEraseSize = stlInsertSize - stlTree.size();
    int stlFoundAmount = 0;
    for (int i = 0; i < iters; i++)
    {
        if (stlTree.find(dataToFind[i]) != stlTree.end())
        {
            stlFoundAmount++;
        }
    }
    clock_t stlEnd = clock();
    float stlTime = (float(stlEnd - stlStart)) / CLOCKS_PER_SEC;

    clock_t myRangeStart = clock();
    int myRangeFoundAmount = 0;
    for (int i = 0; i < itersToRangeQueries; i++)
    {
        myRangeFoundAmount += myTree.findInRange(dataToRangeQueries[i].first, dataToRangeQueries[i].second);
    }
    clock_t myRangeEnd = clock();
    float myRangeTime = (float(myRangeEnd - myRangeStart)) / CLOCKS_PER_SEC;
    clock_t stlRangeStart = clock();
    int stlRangeFoundAmount = 0;
    for (int i = 0; i < itersToRangeQueries; i++)
    {
        const auto &low = stlTree.lower_bound(dataToRangeQueries[i].first);
        const auto &up = stlTree.upper_bound(dataToRangeQueries[i].second);
        stlRangeFoundAmount += distance(low, up);
    }
    clock_t stlRangeEnd = clock();
    float stlRangeTime = (float(stlRangeEnd - stlRangeStart)) / CLOCKS_PER_SEC;
    cout << "My BinaryTree: height = " << myTreeHeight << ", optimal height = " << optimalTreeHeight << endl;
    cout << "Time: " << myTime << ", size: " << myInsertSize << " - " << myEraseSize << ", found amount: " << myFoundAmount << endl;
    cout << "Range time: " << myRangeTime << ", range found amount: " << myRangeFoundAmount << endl
         << endl;
    cout << "STL Tree:" << endl;
    cout << "Time: " << stlTime << ", size: " << stlInsertSize << " - " << stlEraseSize << ", found amount: " << stlFoundAmount << endl;
    cout << "Range time: " << stlRangeTime << ", range found amount: " << stlRangeFoundAmount << endl
         << endl;
    if (myInsertSize == stlInsertSize && myEraseSize == stlEraseSize &&
        myFoundAmount == stlFoundAmount && myRangeFoundAmount == stlRangeFoundAmount)
    {
        cout << "The lab is completed" << endl;
        return true;
    }
    cerr << ":(" << endl;
    return false;
}

int main()
{
    testBinarySearchTree();

    return 0;
}
