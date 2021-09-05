#include <iostream>
#include <vector>
#include <cstring>
#include <iomanip>
#include <cmath>
// #include <OpenGL/gl.h>
// #include <OpenGL/glu.h>
// #include <OpenGL/OpenGL.h>
// #include <GLUT/glut.h>

std::vector<std::string> get_tokens(std::string input);
void print_vector(std::vector<std::string> vec);
bool is_in(std::string searchable, std::string arr[], int size);
void define_priority(std::vector<std::string> &tokens, std::vector<int> &priorities, int &cur_priority, int fi, int li);

std::string digits[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "."}; //10
std::string signs[] = {"+", "-", "*", "/", "^", "x", "(", ")", "|"};            //10
std::string l3_operator[] = {"sin", "cos", "tan", "ctg", "cot"};
std::string l2_operator[] = {"ln", "tg"};

std::string operation_priorities[][7] = {{"sin", "cos", "tan", "ctg", "cot", "ln", "tg"},
                                         {"^"},
                                         {"*", "/"},
                                         {"+", "-"}};
int op_sizes[4] = {7, 1, 2, 2};

struct FunctionalNode
{
    FunctionalNode *left;
    FunctionalNode *right;
    FunctionalNode *pred;
    std::string entity;
    double value;
};

class LexicalTree
{
public:
    std::vector<int> priorities;
    std::vector<std::string> tokens;
    FunctionalNode *root;
    std::vector<double *> x_pointers;

    LexicalTree(std::vector<int> pr, std::vector<std::string> tok)
    {
        priorities = pr;
        tokens = tok;
        root = divide_tokens(0, tokens.size() - 1, root);
    }
    void fill_X(double X)
    {
        for (int i = 0; i < x_pointers.size(); i++)
            *x_pointers[i] = X;
    }
    double calculate(FunctionalNode *node)
    {
        double left_value = 0, right_value = 0;
        if (isnan(node->value))
        {
            if (node->left != NULL)
                left_value = calculate(node->left);
            if (node->right != NULL)
                right_value = calculate(node->right);
            std::cout << node->entity << ":" << define_operation(node->entity, left_value, right_value) << std::endl;
            return define_operation(node->entity, left_value, right_value);
        }
        std::cout << node->entity << ":" << node->value << std::endl;
        return node->value;
    }
    void print_tree(FunctionalNode *pred, int depth)
    {
        std::cout << std::endl;
        for (int i = 0; i < depth; i++)
            std::cout << "-";
        std::cout << " " << pred->entity;
        if (pred->left != NULL)
        {
            print_tree(pred->left, depth + 2);
        }
        if (pred->right != NULL)
        {
            print_tree(pred->right, depth + 2);
        }
    }

private:
    FunctionalNode *divide_tokens(int li, int ri, FunctionalNode *pred)
    {
        //if tokens is empty
        if (li == -1)
            return NULL;
        if (li > ri)
        {
            // std::cout << "Error" << std::endl;
            return NULL;
        }
        FunctionalNode *node = new FunctionalNode;

        int max_pos = find_max_pos(li, ri);
        // std::cout << "we get " << li << ":" << ri << " for " << tokens[max_pos] << std::endl;
        node->pred = pred;
        node->entity = tokens[max_pos];

        //not for operators: numbers or x
        if (priorities[max_pos] == 0)
        {
            node->left = NULL;
            node->right = NULL;
            if (tokens[max_pos] == "x")
            {
                x_pointers.push_back(&node->value);
                node->value = NAN;
            }
            else
                node->value = std::stof(tokens[max_pos]);

            return node;
        }

        node->value = NAN;
        //for unary operators
        if (is_in(tokens[max_pos], operation_priorities[0], 7))
        {
            node->left = divide_tokens(max_pos + 1, ri, node);
            node->right = NULL;
            return node;
        }
        node->left = divide_tokens(li, max_pos - 1, node);
        node->right = divide_tokens(max_pos + 1, ri, node);

        return node;
    }
    int find_max_pos(int li, int ri)
    {
        int max_index = li;
        for (int i = li; i <= ri; i++)
            if (priorities[i] > priorities[max_index])
                max_index = i;
        return max_index;
    }
    double define_operation(std::string operation, double left, double right)
    {
        if (operation == "+")
            return left + right;
        if (operation == "-")
            return left - right;
        if (operation == "*")
            return left * right;
        if (operation == "/")
            return left / ((right == 0) ? 1 : right);
        if (operation == "^")
            return pow(left, right);
        if (operation == "sin")
            return sin(left);
        if (operation == "cos")
            return cos(left);
        if (operation == "ln")
            return log(left);
        if (operation == "tan" || operation == "tg")
            return tan(left);
        if (operation == "ctg" || operation == "cot")
            return 1 / tan(left);
        return 0;
    }
};

void build_graph(LexicalTree *tr);
int main(int argc, char *argv[])
{
    // glutInit(&argc, argv);
    // glutInitWindowSize(400, 300);
    // glutInitWindowPosition(100, 100);

    // glutInitDisplayMode(GLUT_RGB);
    // glutCreateWindow("Romka Demo");

    // // glutReshapeFunc(Reshape);
    // // glutDisplayFunc(Draw);
    // glClearColor(0, 0, 0, 0);

    // glutMainLoop();

    std::string input;
    // std::cin >> input;
    input = "(4+3)*ln((x*(4.2 - 5))^2)/ ((23 + 90.4) * (2/4))";
    // input = "(4+3)*ln(x*(6 - 5))";
    // input = "1+x";

    std::vector<std::string> tokens = get_tokens(input);
    std::vector<int> priorities(tokens.size(), 0);
    int p = 0;
    print_vector(tokens);
    define_priority(tokens, priorities, p, 0, tokens.size() - 1);
    for (int i = 0; i < priorities.size(); i++)
        printf("%3d ", priorities.at(i));

    std::cout << std::endl;
    LexicalTree tree(priorities, tokens);

    tree.print_tree(tree.root, 0);
    build_graph(&tree);

    return 0;
}

std::vector<std::string> get_tokens(std::string input)
{
    std::vector<std::string> tokens;
    int length = 0;

    for (int i = 0; i < input.length() + 1; i++)
    {
        std::string element = input.substr(i, 1);
        if (is_in(element, digits, 11))
        {
            length++;
            continue;
        }
        else if (length >= 1)
        {
            tokens.push_back(input.substr(i - length, length));
            length = 0;
        }
        if (is_in(element, signs, 10))
        {
            tokens.push_back(element);
        }

        if (is_in(input.substr(i, 3), l3_operator, 5))
        {
            tokens.push_back(input.substr(i, 3));
            i += 2;
        }
        if (is_in(input.substr(i, 2), l2_operator, 2))
        {
            tokens.push_back(input.substr(i, 2));
            i += 1;
        }
    }

    return tokens;
}
void print_vector(std::vector<std::string> vec)
{
    for (int i = 0; i < vec.size(); i++)
        printf("%3d ", i);
    std::cout << std::endl;
    for (int i = 0; i < vec.size(); i++)
        printf("%3s ", vec.at(i).c_str());

    std::cout << std::endl;
}

bool is_in(std::string searchable, std::string *arr, int size)
{
    bool flag = false;
    for (int i = 0; i < size; i++)
    {
        // std::cout << searchable << arr[i] << std::endl;
        if (searchable == arr[i])
            flag = true;
    }
    return flag;
}

void define_priority(std::vector<std::string> &tokens, std::vector<int> &priorities, int &cur_priority, int fi, int li)
{
    //search for parentheses in range
    int nested_level = 0;
    int first_br_index;
    for (int i = fi; i <= li; i++)
    {
        //firstly recognize inner parentheses
        if (tokens[i] == "(" && nested_level == 0)
        {
            nested_level++;
            first_br_index = i;
        }
        else if (tokens[i] == "(")
            nested_level++;
        else if (tokens[i] == ")" && nested_level > 1)
            nested_level--;
        else if (tokens[i] == ")" && nested_level == 1)
        {
            //delete parenthesis in tokens and priorities arrays
            tokens[i] = "";
            priorities[i] = -1;
            tokens[first_br_index] = "";
            priorities[first_br_index] = -1;
            define_priority(tokens, priorities, cur_priority, first_br_index, i);
            nested_level--;
        }
    }
    //check first priority
    for (int i = 0; i < 4; i++)
        for (int j = fi; j <= li; j++)

            if (is_in(tokens[j], operation_priorities[i], op_sizes[i]) && priorities[j] == 0)

                priorities[j] = ++cur_priority;

    // for (int i = 0; i < priorities.size(); i++)

    //     printf("%4d ", priorities.at(i));
}

void build_graph(LexicalTree *tr)
{
    // glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    tr->fill_X(6);
    std::cout << std::endl
              << tr->calculate(tr->root);
    std::cout << std::endl;
}
