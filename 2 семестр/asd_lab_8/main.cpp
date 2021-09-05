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
    Data(Data *copy)
    {
        teamName = copy->teamName;
        numberOfWins = copy->numberOfWins;
        yearOfCreation = copy->yearOfCreation;
        id = copy->id;
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
    Node *parent;

    Node(Data _team, Node *_parent)
    {
        data = _team;
        parent = _parent;
        left = NULL;
        right = NULL;
    }
    Node() {}
};
struct BinarySearchTree;
struct SplitedTree;
BinarySearchTree merge(BinarySearchTree tree1, BinarySearchTree tree2);

SplitedTree split(BinarySearchTree tree, Data splitter);

struct BinarySearchTree
{
    Node *root = NULL;
    int treeSize = 0;

    void insert(Data data)
    {
        Node *parent = root;
        if (root == NULL)
        {
            Node *newNode = new Node(data, NULL);
            root = newNode;
            treeSize++;
            return;
        }
        while (true)
        {
            if (parent->data < data)
            {
                if (parent->right == NULL)
                {
                    Node *newNode = new Node(data, parent);
                    parent->right = newNode;
                    treeSize++;
                    return;
                }
                parent = parent->right;
                continue;
            }
            if (parent->data > data)
            {
                if (parent->left == NULL)
                {
                    Node *newNode = new Node(data, parent);
                    parent->left = newNode;

                    treeSize++;
                    return;
                }
                parent = parent->left;
                continue;
            }
            if (parent->data == data)
            {
                parent->data = data;
                return;
            }
        }
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
    void erase(Data data)
    {
        Node *tmp = root;
        while (tmp != NULL)
        {
            if (tmp->data == data)
            {
                Node *p = tmp->parent;
                //delete leaf
                if (tmp->left == NULL && tmp->right == NULL)
                {
                    if (p == NULL)
                        root = NULL;
                    else
                    {
                        p->right = p->right == tmp ? NULL : p->right;
                        p->left = p->left == tmp ? NULL : p->left;
                    }
                    delete tmp;
                    treeSize--;
                }
                //delete with one child
                else if (tmp->left == NULL)
                {
                    tmp->right->parent = p;
                    if (p == NULL)
                        root = tmp->right;
                    else
                    {
                        p->right = p->right == tmp ? tmp->right : p->right;
                        p->left = p->left == tmp ? tmp->right : p->left;
                    }
                    delete tmp;
                    treeSize--;
                }
                else if (tmp->right == NULL)
                {
                    tmp->left->parent = p;
                    if (p == NULL)
                        root = tmp->left;
                    else
                    {
                        p->right = p->right == tmp ? tmp->left : p->right;
                        p->left = p->left == tmp ? tmp->left : p->left;
                    }
                    delete tmp;
                    treeSize--;
                }
                //two childs
                else
                {
                    Node *changer = tmp->right;
                    while (changer->left != NULL)
                        changer = changer->left;
                    Data changerTeam = changer->data;
                    erase(changerTeam);
                    tmp->data = changerTeam;
                }
                break;
            }

            if (tmp->data < data)
                tmp = tmp->right;
            else
                tmp = tmp->left;
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
    int size()
    {
        return treeSize;
    }
    int height(Node *tmp)
    {
        if (tmp == NULL)
            return 0;
        int lHeight = height(tmp->left);
        int rHeight = height(tmp->right);
        return (lHeight > rHeight ? lHeight : rHeight) + 1;
    }
    int height()
    {
        return height(root);
    }
    void print(Node *tmp = NULL)
    {
        if (root == NULL)
            return;
        if (tmp == NULL)
            tmp = root;
        if (tmp->left != NULL)
            print(tmp->left);
        std::cout << tmp->data.id << " ";
        if (tmp->right != NULL)
            print(tmp->right);
    }
    Data getMax()
    {
        Node *tmp = root;
        while (tmp->right != NULL)
            tmp = tmp->right;
        return tmp->data;
    }
    Data getMin()
    {
        Node *tmp = root;
        while (tmp->left != NULL)
            tmp = tmp->left;
        return tmp->data;
    }
    void concatenate(Node *tmp)
    {
        if (tmp == NULL)
            return;
        if (tmp->left != NULL)
            concatenate(tmp->left);

        insert(tmp->data);
        if (tmp->right != NULL)
            concatenate(tmp->right);
    }
    void slice(Data from, Data to, Node *tmp)
    {
        if (tmp == NULL || from > to)
            return;

        if ((tmp->data > from && tmp->data < to) || tmp->data == from || tmp->data == to)
            insert(tmp->data);

        if (tmp->data > from || tmp->data == from)
            slice(from, to, tmp->left);

        if (tmp->data < to || tmp->data == to)
            slice(from, to, tmp->right);
    }
};

struct SplitedTree
{
    BinarySearchTree left;
    BinarySearchTree right;
    SplitedTree(Node *root1, Node *root2)
    {
        Data zeroData = Data();
        zeroData.id = 0;
        left.root = root1;
        right.root = root2;

        if (left.root == NULL)
            left.treeSize = 0;
        else
            left.treeSize = left.findInRange(zeroData, left.root->data);

        if (right.root == NULL)
            right.treeSize = 0;
        else
            right.treeSize = left.findInRange(zeroData, right.getMax());
    }
    SplitedTree(BinarySearchTree tree1, BinarySearchTree tree2)
    {
        left = tree1;
        right = tree2;
    }
};

long generateRandLong()
{
    return rand();
}

BinarySearchTree merge(BinarySearchTree tree1, BinarySearchTree tree2)
{
    BinarySearchTree returnTree = BinarySearchTree();
    returnTree.concatenate(tree1.root);
    returnTree.concatenate(tree2.root);
    return returnTree;
}

SplitedTree split(BinarySearchTree tree, Data splitter)
{
    BinarySearchTree tree1;
    BinarySearchTree tree2;
    tree1.slice(tree.getMin(), splitter, tree.root);
    tree2.slice(splitter, tree.getMax(), tree.root);
    return SplitedTree(tree1, tree2);
}

void eraseRange(BinarySearchTree *tree, Data min, Data max)
{
    SplitedTree byMin = split(*tree, min);
    SplitedTree byMax = split(*tree, max);
    BinarySearchTree leftPart = byMin.left;
    BinarySearchTree rightPart = byMax.right;
    *tree = merge(leftPart, rightPart);
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
    BinarySearchTree myTree;
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

int main()
{
    srand(time(NULL));
    testBinarySearchTree();
    BinarySearchTree tree1;
    BinarySearchTree tree2;
    Data data = Data();

    for (int i = 0; i < 10; i++)
    {
        data = Data();
        data.id = rand() % 100;
        tree1.insert(data);
        data = Data();
        data.id = rand() % 100;
        tree2.insert(data);
    }
    cout << "Start tree 1: ";
    tree1.print();
    cout << endl;
    cout << "Start tree 2: ";
    tree2.print();
    cout << endl;
    BinarySearchTree merged = merge(tree1, tree2);
    // merged.print();
    // cout << endl;
    cout << "splited by " << data.id << endl;
    tree1 = split(merged, data).left;
    tree2 = split(merged, data).right;
    cout << "Left part of splited: ";
    tree1.print();
    cout << "   size: " << tree1.size() << endl;
    cout << "Right part of splited: ";
    tree2.print();
    cout << "   size: " << tree2.size() << endl;
    cout << "Merged started ones: ";
    merged.print();
    cout << "   size: " << merged.size() << endl;

    Data from = Data();
    from.id = rand() % 100;
    tree1.insert(data);
    Data to = Data();
    to.id = from.id + rand() % 50;
    eraseRange(&merged, from, to);
    cout << "Merged with erased (from " << from.id << " to " << to.id << ") range: ";
    merged.print();
    cout << "   size: " << merged.size() << endl;
    return 0;
}
