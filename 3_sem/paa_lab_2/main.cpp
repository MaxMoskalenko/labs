#include <iostream>
#include <list>
#include <cmath>

int INPUT_ARRAY[] = {15, 14, 26, 19, 28, 22, 7, 29, 1, 17, 3, 4, 27, 8, 0, 9};

int SIZE_OF_INPUT_ARRAY = 16;

// TODO linked type of array
// Запрограмувати алгоритм перетворення. Покроково вивести етапи
// перетворення дерева у звіт (скріншоти екрану).?

struct Node
{
    int value;
    Node *left;
    Node *right;
    int leftSum;
    int rightSum;
    Node(int v)
    {
        value = v;
        left = NULL;
        right = NULL;
        leftSum = 0;
        rightSum = 0;
    }
};

struct Tree
{
    Node *root;

    Tree(int value)
    {
        root = new Node(value);
    }

    void add(int value)
    {
        add(value, root);
    }

    void add(int value, Node *root)
    {
        if (value > root->value)
        {
            if (root->right == NULL)
            {
                root->right = new Node(value);
                return;
            }
            add(value, root->right);
            return;
        }
        if (value < root->value)
        {
            if (root->left == NULL)
            {
                root->left = new Node(value);
                return;
            }
            add(value, root->left);
            return;
        }
    }

    void print()
    {
        printf("root:%i (%i|%i)\n", root->value, root->leftSum, root->rightSum);

        // std::cout << "root: " << root->value << std::endl;
        print(root, 1);
    }

    void print(Node *n, int level)
    {
        if (n->left != NULL)
        {
            for (int i = 0; i < level; i++)
            {
                std::cout << "--";
            }
            printf(" l:%i (%i|%i)\n", n->left->value, n->left->leftSum, n->left->rightSum);
            // std::cout << " l: " << n->left->value << std::endl;
            print(n->left, level + 1);
        }
        if (n->right != NULL)
        {
            for (int i = 0; i < level; i++)
            {
                std::cout << "--";
            }
            printf(" r:%i (%i|%i)\n", n->right->value, n->right->leftSum, n->right->rightSum);

            // std::cout << " r: " << n->right->value << std::endl;
            print(n->right, level + 1);
        }
    }

    void removeNode(Node *n)
    {
        if (n == NULL)
        {
            return;
        }

        removeNode(n->left);
        removeNode(n->right);

        delete n;
    }

    void balance()
    {
        balance(root, root, 0);
    }

    void calculate_sum(Node *n)
    {
        if (n == NULL)
            return;

        calculate_sum(n->right);
        calculate_sum(n->left);

        if (n->left == NULL && n->right == NULL)
        {
            n->leftSum = 0;
            n->rightSum = 0;
            return;
        }

        if (n->right != NULL)
            n->rightSum = n->right->rightSum + n->right->leftSum + 1;
        if (n->left != NULL)
            n->leftSum = n->left->rightSum + n->left->leftSum + 1;
    }

    void balance(Node *n, Node *p, int dir)
    {
        if (n == NULL)
            return;

        calculate_sum(n);

        while (std::abs(n->leftSum - n->rightSum) > 1)
        {
            n = balanceNode(n);
            calculate_sum(n);

            if (dir == 0)
                p = n;
            if (dir == -1)
                p->left = n;
            if (dir == 1)
                p->right = n;
        }

        balance(n->left, n, -1);
        balance(n->right, n, 1);
    }

    Node *balanceNode(Node *n)
    {
        if (balance_factor(n) >= 2)
        {
            if (balance_factor(n->left) > 0)
                return LL_rotation(n);
            else
                return LR_rotation(n);
        }
        if (balance_factor(n) <= -2)
        {
            if (balance_factor(n->right) > 0)
                return RL_rotation(n);
            else
                return RR_rotation(n);
        }
        std::cout << "ERROR. I don`t suppose to be here" << std::endl;
        return NULL;
    }

    Node *LL_rotation(Node *n)
    {
        Node *left = n->left;

        n->left = left->right;

        left->right = n;

        return left;
    }

    Node *LR_rotation(Node *n)
    {
        Node *left = n->left;
        Node *left_right = left->right;

        n->left = left_right->right;
        left->right = left_right->left;

        left_right->left = left;
        left_right->right = n;

        return left_right;
    }

    Node *RL_rotation(Node *n)
    {
        Node *right = n->right;
        Node *right_left = right->left;

        n->right = right_left->left;
        right->left = right_left->right;

        right_left->left = n;
        right_left->right = right;

        return right_left;
    }

    Node *RR_rotation(Node *n)
    {
        Node *right = n->right;

        n->right = right->left;

        right->left = n;

        return right;
    }

    int balance_factor(Node *n)
    {
        return n->leftSum - n->rightSum;
    }

    int height(Node *n)
    {
        if (n == NULL)
        {
            return 0;
        }
        return std::max(height(n->left), height(n->right)) + 1;
    }

    ~Tree()
    {
        removeNode(root);
    }
};

void printArray()
{
    for (int i = 0; i < SIZE_OF_INPUT_ARRAY; i++)
    {
        std::cout << INPUT_ARRAY[i] << " ";
    }
    std::cout << std::endl;
}

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i)
    {
        std::swap(arr[i], arr[largest]);

        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--)
    {
        std::swap(arr[0], arr[i]);

        heapify(arr, i, 0);
    }
}

int main()
{
    Tree *tree = new Tree(INPUT_ARRAY[0]);
    for (int i = 1; i < SIZE_OF_INPUT_ARRAY; i++)
    {
        tree->add(INPUT_ARRAY[i]);
    }
    std::cout << std::endl
              << "------BINARY TREE------" << std::endl;
    tree->calculate_sum(tree->root);
    tree->print();

    std::cout << std::endl
              << "------SORTED ARRAY-----" << std::endl;

    heapSort(INPUT_ARRAY, SIZE_OF_INPUT_ARRAY);
    printArray();

    std::cout << std::endl
              << "------BALANCED ARRAY-----" << std::endl;

    tree->balance();
    tree->print();
    return 0;
}
