#include <iostream>
#include <ctime>
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
struct Node
{
    std::unordered_map<std::string, Node *> map;
    bool isEnd = false;
    std::string symbol;
};

struct Trie
{
    Node *root;
    Trie()
    {
        root = new Node;
        root->symbol = "_";
    }
    void insert(std::string str)
    {
        insert(root, "_" + str);
    }
    Node *insert(Node *pos, std::string str)
    {
        if (pos == NULL)
        {
            pos = new Node;
            pos->symbol = str.substr(0, 1);
        }

        if (str.length() == 1)
        {
            pos->isEnd = true;
            return pos;
        }

        try
        {
            Node *next = pos->map.at(str.substr(1, 1));
            next = insert(next, str.substr(1));
        }
        catch (std::out_of_range)
        {
            Node *newNode = insert(NULL, str.substr(1));
            pos->map.insert({str.substr(1, 1), newNode});
        }
        return pos;
    }
    std::vector<std::string> findByPrefix(std::string prefix)
    {
        std::vector<std::string> result;
        Node *pIndex = findPrefixIndex(root, prefix);
        if (pIndex == NULL)
            return result;

        if (pIndex->isEnd)
            result.push_back(prefix);

        getAllWords(pIndex, result, prefix);
        return result;
    }
    Node *findPrefixIndex(Node *pos, std::string prefix)
    {

        try
        {
            Node *next = pos->map.at(prefix.substr(0, 1));

            if (prefix.length() == 1)
                return next;

            return findPrefixIndex(next, prefix.substr(1));
        }
        catch (std::out_of_range)
        {
            return NULL;
        }
    }
    void getAllWords(Node *root, std::vector<std::string> &vec, std::string prefix)
    {
        for (auto kv : root->map)
        {
            if (kv.second->isEnd)
                vec.push_back(prefix + kv.second->symbol);
            getAllWords(kv.second, vec, prefix + kv.second->symbol);
        }
    }
    void destroy(Node *tmp)
    {
        for (auto kv : tmp->map)
        {
            destroy(kv.second);
        }
        delete tmp;
    }
    ~Trie()
    {
        destroy(root);
    }
};
void printVector(std::vector<std::string> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        std::cout << vec[i] << ", ";
    }
}
void feelTree(Trie *tree)
{
    std::string word;
    std::ifstream file("words.txt");

    while (getline(file, word))
        tree->insert(word);

    file.close();
}

int main()
{

    Trie tree;
    std::string word;
    feelTree(&tree);
    while (true)
    {
        std::cout << "Input: ";
        std::cin >> word;

        std::cout << "Output: ";
        std::vector<std::string> result = tree.findByPrefix(word);
        printVector(result);
        std::cout << std::endl;

        std::string isContinue;
        std::cout << "Do you want to continue (y|n): ";
        std::cin >> isContinue;
        if (isContinue == "n")
            break;
    }

    return 0;
}
