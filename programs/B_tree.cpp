/*B-tree
Build a B-tree of minimum order t and output it layer by layer.
Numbers in the range [0..232-1] are used as a key

Requirements:

     - The B-tree must be implemented as a template class.
     - The solution must support the transfer of the compare function from the outside.
For example:

stdin                   stdout
2                       3
0 1 2 3 4 5 6 7 8 9     1 5 7
                        0 2 4 6 8 9

*/

#include <iostream>
#include <vector>

template<typename T, typename Comparator = std::less<T>>
class BTree
{
    struct Node
    {
        explicit Node(bool end_node);
        ~Node();

        bool end_node;
        std::vector<T> item;
        std::vector<Node *> sub_nodes;
    };

public:
    explicit BTree(int min);
    ~BTree();

    bool find(const T &hash_key) const;
    void insertKey(const T &hash_key);
    std::vector<std::vector<T>> treeByLevel();

private:
    bool isFull(Node *node) const;
    bool findElement(Node *node, const T &hash_key) const;
    void performSplit(Node *head, int index);
    void insertNoFull(Node *node, const T &hash_key);
    bool isEqual(const T &l, const T &r) const;
    bool isLess(const T &l, const T &r) const;
    bool isGreater(const T &l, const T &r) const;

    Node *head;
    int min;
    int height;
    Comparator comp = Comparator();
};

template<typename T, typename Comparator>
bool BTree<T, Comparator>::isEqual(const T &l, const T &r) const
{
    return l == r;
}
template<typename T, typename Comparator>
bool BTree<T, Comparator>::isLess(const T &l, const T &r) const
{
    return l < r;
}
template<typename T, typename Comparator>
bool BTree<T, Comparator>::isGreater(const T &l, const T &r) const
{
    return l > r;
}

template<typename T, typename Comparator>
BTree<T, Comparator>::Node::Node(bool end_node)
    : end_node(end_node)
{}

template<typename T, typename Comparator>
BTree<T, Comparator>::Node::~Node()
{
    for (Node *it : sub_nodes) {
        delete it;
    }
}

template<typename T, typename Comparator>
BTree<T, Comparator>::BTree(int min)
    : head(nullptr)
    , min(min)
    , height(0)
{
    if (min < 2) {
        min = 2;
    }
}

template<typename T, typename Comparator>
BTree<T, Comparator>::~BTree()
{
    delete head;
}

template<typename T, typename Comparator>
void BTree<T, Comparator>::insertKey(const T &hash_key)
{
    if (!head) {
        height++;
        head = new Node(true);
    }

    if (isFull(head)) {
        Node *root = new Node(false);

        root->sub_nodes.push_back(head);
        head = root;
        performSplit(head, 0);

        height++;
    }

    insertNoFull(head, hash_key);
}

template<typename T, typename Comparator>
bool BTree<T, Comparator>::find(const T &hash_key) const
{
    return findElement(head, hash_key);
}

template<typename T, typename Comparator>
bool BTree<T, Comparator>::isFull(BTree::Node *node) const
{
    return node->item.size() == 2 * min - 1;
}

template<typename T, typename Comparator>
bool BTree<T, Comparator>::findElement(BTree<T, Comparator>::Node *node, const T &hash_key) const
{
    int index = 0;
    while (isGreater(node->item[index] && index < node->item.size(), hash_key)) {
        index++;
    }

    if (isEqual(hash_key, node->item[index]) && node->item.size() > index) {
        return true;
    } else if (node->end_node) {
        return false;
    } else {
        return containsElement(node->sub_nodes[index], hash_key);
    }
}

template<typename T, typename Comparator>
void BTree<T, Comparator>::performSplit(BTree::Node *head, int index)
{
    auto split = head->sub_nodes[index];
    auto node = new Node(split->end_node);
    head->item.resize(head->item.size() + 1);

    int i = head->item.size() - 1;

    if (head->item.size() != 1) {
        while (i > index) {
            head->item[i] = head->item[i - 1];
            i--;
        }
    }

    head->item[index] = split->item[min - 1];
    head->sub_nodes.resize(head->sub_nodes.size() + 1);
    i = head->sub_nodes.size() - 1;

    while (i > index + 1) {
        head->sub_nodes[i] = head->sub_nodes[i - 1];
        i--;
    }

    head->sub_nodes[index + 1] = node;

    node->item.resize(min - 1);
    i = 0;
    while (i < min - 1) {
        node->item[i] = split->item[min + i];
        i++;
    }

    split->item.resize(min - 1);
    if (!split->end_node) {
        node->sub_nodes.resize(min);
        i = 0;
        while (i < min) {
            node->sub_nodes[i] = split->sub_nodes[min + i];
            i++;
        }
        split->sub_nodes.resize(min);
    }
}

template<typename T, typename Comparator>
void BTree<T, Comparator>::insertNoFull(BTree::Node *node, const T &hash_key)
{
    int index = node->item.size() - 1;

    if (node->end_node) {
        node->item.resize(node->item.size() + 1);

        while (isLess(hash_key, node->item[index]) && index >= 0) {
            node->item[index + 1] = node->item[index];
            index--;
        }

        node->item[index + 1] = hash_key;
    } else {
        while (isLess(hash_key, node->item[index]) && index >= 0) {
            index--;
        }

        if (isFull(node->sub_nodes[index + 1])) {
            performSplit(node, index + 1);

            if (node->item[index + 1] < hash_key) {
                index++;
            }
        }

        insertNoFull(node->sub_nodes[index + 1], hash_key);
    }
}

template<typename T, typename Comparator>
std::vector<std::vector<T>> BTree<T, Comparator>::treeByLevel()
{
    std::vector<Node *> nodes;
    std::vector<std::vector<T>> vec;

    nodes.push_back(head);
    while (!nodes.empty()) {
        std::vector<T> temp;

        int n = nodes.size();
        int i = 0;

        while (i < n) {
            Node *buf = nodes.front();
            nodes.erase(nodes.begin());

            for (const auto &it : buf->item) {
                temp.push_back(it);
            }

            for (const auto &node : buf->sub_nodes) {
                nodes.push_back(node);
            }

            i++;
        }
        vec.push_back(temp);
    }
    return vec;
}

void display(const std::vector<std::vector<int>> &other)
{
    for (const auto &o : other) {
        for (const auto &it : o) {
            std::cout << it << " ";
        }
        std::cout << std::endl;
    }
}

void task()
{
    std::string word;
    std::getline(std::cin, word);
    int n = std::stoi(word);

    std::string words;
    std::getline(std::cin, words);

    std::vector<int> keys;

    int index = 0;
    std::string token;
    while ((index = words.find(' ')) != std::string::npos) {
        token = words.substr(0, index);
        words.erase(0, index + 1);
        keys.push_back(std::stoi(token));
    }
    keys.push_back(std::stoi(words));

    BTree<int> tree(n);
    for (const auto &it : keys) {
        tree.insertKey(it);
    }

    auto it = tree.treeByLevel();

    display(it);
}

int main(int argc, const char *argv[])
{
    task();

    return 0;
}

