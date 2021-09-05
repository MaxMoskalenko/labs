#include <iostream>
#include <ctime>
using namespace std;

struct Student
{
    string name;
    int average_point;
    struct Student create_student()
    {
        struct Student newstudent;
        newstudent.average_point = rand() % 1000;
        int k = rand() % 10 + 1;
        for (int i = 0; i < k; i++)
        {
            int a = rand() % 255 + 1;
            newstudent.name += (char)a;
        }
        return newstudent;
    }
    bool operator<(const struct Student &newstudent) const
    {
        if (this->average_point < newstudent.average_point)
            return true;
        else
            return false;
    }
    bool operator==(const struct Student &newstudent) const
    {
        if (this->average_point == newstudent.average_point)
            return true;
        else
            return false;
    }
};
struct Node
{
    Node *parent = NULL;
    Student data;
    Node *right_node = NULL;
    Node *left_node = NULL;
    int balance = 0;
};

struct BinarySeatchTree
{
    Node *top = NULL;
    int height(Node *pointer)
    {
        if (pointer == NULL)
        {
            return 0;
        }
        else
        {
            int left_height = height(pointer->left_node);
            int right_height = height(pointer->right_node);
            return 1 + max(left_height, right_height);
        }
    }
    void preOrder(Node *temp)
    {
        if (temp == NULL)
            return;
        cout << temp->data.average_point << endl;
        preOrder(temp->left_node);
        preOrder(temp->right_node);
    }

    Node *rotateleft(Node *temp)
    {
        int h1;
        int h2;
        Node *p = (temp)->right_node;
        if (temp->parent != NULL)
            temp->parent->right_node = p;
        p->parent = temp->parent;
        if (p->left_node != NULL)
        {
            p->left_node->parent = temp;
            temp->right_node = p->left_node;
        }
        else
            temp->right_node = NULL;
        temp->parent = p;

        p->left_node = temp;
        h1 = height(p->left_node);
        h2 = height(p->right_node);
        p->balance = h1 - h2;
        h1 = height(temp->left_node);
        h2 = height(temp->right_node);
        temp->balance = h1 - h2;
        if (p->parent == NULL)
            top = p;
        return p;
    }

    Node *rotateright(Node *temp)
    {
        int h1;
        int h2;
        Node *p = (temp)->left_node;
        if (temp->parent != NULL)
            temp->parent->left_node = p;
        p->parent = temp->parent;
        if (p->right_node != NULL)
        {
            p->right_node->parent = temp;
            temp->left_node = p->right_node;
        }
        else
            temp->left_node = NULL;

        temp->parent = p;
        p->right_node = temp;
        h1 = height(p->left_node);
        h2 = height(p->right_node);
        p->balance = h1 - h2;
        h1 = height(temp->left_node);
        h2 = height(temp->right_node);
        temp->balance = h1 - h2;
        if (p->parent == NULL)
            top = p;
        return p;
    }

    Node *rotateleftlong(Node *temp)
    {
        return (rotateleft(rotateright(temp->right_node)->parent));
    }

    Node *rotaterightlong(Node *temp)
    {
        return (rotateright(rotateleft(temp->left_node)->parent));
    }
    void balance(Node **temp)
    {
        if (((*temp)->right_node != NULL) && ((*temp)->balance == -2 && ((*temp)->right_node->balance == -1 || (*temp)->right_node->balance == 0)))
        {
            *temp = rotateleft(*temp);
            return;
        }
        if ((*temp)->right_node != NULL && (*temp)->right_node->left_node != NULL && (*temp)->balance == -2 && (*temp)->right_node->balance == 1 && (*temp)->right_node->left_node->balance != 2 && (*temp)->right_node->left_node->balance != -2)
        {
            *temp = rotateleftlong(*temp);
            return;
        }
        if (((*temp)->left_node != NULL) && ((*temp)->balance == 2 && ((*temp)->left_node->balance == 1 || (*temp)->left_node->balance == 0)))
        {
            *temp = rotateright(*temp);
            return;
        }
        if ((*temp)->left_node != NULL && (*temp)->left_node->right_node != NULL && ((*temp)->balance == 2 && (*temp)->left_node->balance == -1 && (*temp)->left_node->right_node->balance != 2 && (*temp)->left_node->right_node->balance != -2))
        {
            *temp = rotaterightlong(*temp);
            return;
        }
    }

    void up(Node **temp)
    {
        int x = 0;
        int n;
        while ((*temp)->parent != NULL)
        {
            if ((*temp)->data.average_point < (*temp)->parent->data.average_point)
            {
                (*temp)->parent->balance++;
                n = (*temp)->parent->balance;
            }
            else
            {
                (*temp)->parent->balance--;
                n = (*temp)->parent->balance;
            }
            if (n == 0 && x == 0)
                return;
            else if (n == 1 || n == -1 || n == 0)
                (*temp) = (*temp)->parent;
            else
            {
                (*temp) = (*temp)->parent;
                balance(&(*temp));
                return;
            }
            x++;
        }
    }
    void insert(struct Student data)
    {
        if (top == NULL)
        {
            top = new Node;
            top->data.average_point = data.average_point;
            top->data.name = data.name;
            top->parent = NULL;
            top->left_node = top->right_node = NULL;
            return;
        }
        else
        {
            Node *temp = top;
            while ((data.average_point < temp->data.average_point && temp->left_node != NULL) || (temp->right_node != NULL && !(data.average_point < temp->data.average_point)))
            {
                if (data.average_point < temp->data.average_point)
                    temp = temp->left_node;

                else if (data.average_point == temp->data.average_point)
                    return;

                else
                {
                    temp = temp->right_node;
                }
            }
            if (data.average_point < temp->data.average_point)
            {
                temp->left_node = new Node;
                temp->left_node->data.name = data.name;
                temp->left_node->data.average_point = data.average_point;
                temp->left_node->parent = temp;
                temp->left_node->left_node = NULL;
                temp->left_node->right_node = NULL;
                temp = temp->left_node;
                up(&temp);
            }
            else if (data.average_point == temp->data.average_point)
                return;
            else
            {
                temp->right_node = new Node;
                temp->right_node->data.name = data.name;
                temp->right_node->data.average_point = data.average_point;
                temp->right_node->parent = temp;
                temp->right_node->left_node = NULL;
                temp->right_node->right_node = NULL;
                temp = temp->right_node;
                up(&temp);
            }
        }
    }
    void test()
    {
        print(top);
        cout << endl;
        // int i = size(top);
        // cout << i << endl;
        // cout << top->data.average_point << endl
        //      << endl;
        // preOrder(top);
    }

    void print(Node *temp)
    {
        if (temp == NULL)
            return;

        /* first recur on left child */
        print(temp->left_node);

        /* then print the data of node */
        cout << temp->data.average_point << " ";

        /* now recur on right child */
        print(temp->right_node);
    }
    int size(Node *temp)
    {
        if (temp == NULL)
        {
            return 0;
        }
        return 1 + size(temp->left_node) + size(temp->right_node);
    }
};
int main()
{
    srand(time(NULL));
    BinarySeatchTree x;
    Student u;
    u.name = "fg";
    for (int i = 0; i < 10; i++)
    {
        u.average_point = rand() % 20;
        cout << u.average_point;
        x.insert(u);
    }

    cout << endl;
    x.test();

    //for (n; n < 100; n++)
    //x.insert(y.create_student());
    // x.test();
}