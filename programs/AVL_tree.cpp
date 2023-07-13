/*AVL trees
The solution should support passing the compare function from outside. 
Given a number of N and N rows. Each line contains a command to add or remove
natural numbers, as well as a request to get the k-th order statistics.
The command to add the number A is given by the positive number A, the command to remove
number A is given by a negative number “-A”. Request for k-th ordinal
statistics is given by the number k. The required query execution speed is O(log n).
For example:

in            out 
5             
40 0          40
10 1          40
4 1           10
-10 0         4
50 2          50

*/

#include <iostream>
#include <vector>

template <typename T, typename Comparator = std::less<T>> class AVLTree {
  struct Node {
    explicit Node(const T &data)
        : data(data), tree_height(1), num(1), left(nullptr), right(nullptr) {}

    T data;
    int tree_height;
    int num;
    Node *left;
    Node *right;
  };

public:
  AVLTree();
  ~AVLTree();

  T statistics(const int k);
  void push(const T &value);
  void remove(const T &value);

private:
  void changeNodes(Node *node);
  void changeHeight(Node *node);

  int treeHeight(const Node *node);
  int balancer(const Node *node);

  Node *push(Node *node, const T &value);
  Node *leftRotation(Node *node);
  Node *rightRotation(Node *node);
  Node *balance(Node *node);
  Node *remove(Node *node, const T &value);
  Node *minRemove(Node *node, Node *&min);
  T statistics(Node *node, const int k);

  Comparator comp;
  Node *head;
};

template <typename T, typename Comparator>
AVLTree<T, Comparator>::AVLTree() : head(nullptr), comp(Comparator()) {}

template <typename T, typename Comparator> AVLTree<T, Comparator>::~AVLTree() {
  if (!head) {
    return;
  }

  std::vector<Node *> vec;

  vec.push_back(head);

  while (!vec.empty()) {
    Node *node = vec.back();
    vec.pop_back();

    if (node->left) {
      vec.push_back(node->left);
    }

    if (node->right) {
      vec.push_back(node->right);
    }

    delete node;
  }
}

template <class T, class Comparator>
int AVLTree<T, Comparator>::treeHeight(const Node *node) {
  if (node) {
    return node->tree_height;
  }

  return 0;
}

template <class T, class Comparator>
int AVLTree<T, Comparator>::balancer(const Node *node) {
  return treeHeight(node->right) - treeHeight(node->left);
}

template <class T, class Comparator>
void AVLTree<T, Comparator>::changeHeight(Node *node) {
  int right_height = treeHeight(node->right);
  int left_height = treeHeight(node->left);

  if (right_height < left_height) {
    node->tree_height = left_height + 1;
  } else {
    node->tree_height = right_height + 1;
  }
}

template <class T, class Comparator>
void AVLTree<T, Comparator>::changeNodes(Node *node) {
  node->num = 1;

  if (node->right) {
    node->num += node->right->num;
  }

  if (node->left) {
    node->num += node->left->num;
  }
}

template <typename T, typename Comparator>
typename AVLTree<T, Comparator>::Node *
AVLTree<T, Comparator>::leftRotation(Node *node) {
  Node *right(node->right);

  node->right = right->left;
  right->left = node;

  changeHeight(node);
  changeHeight(right);

  changeNodes(node);
  changeNodes(right);

  return right;
}

template <typename T, typename Comparator>
typename AVLTree<T, Comparator>::Node *
AVLTree<T, Comparator>::rightRotation(Node *node) {
  Node *left(node->left);

  node->left = left->right;
  left->right = node;

  changeHeight(node);
  changeHeight(left);

  changeNodes(node);
  changeNodes(left);

  return left;
}

template <typename T, typename Comparator>
typename AVLTree<T, Comparator>::Node *
AVLTree<T, Comparator>::balance(Node *node) {
  changeHeight(node);
  changeNodes(node);

  int b = balancer(node);

  if (b == -2) {
    if (balancer(node->left) > 0) {
      node->left = leftRotation(node->left);
    }

    return rightRotation(node);
  }

  if (b == 2) {
    if (balancer(node->right) < 0) {
      node->right = rightRotation(node->right);
    }

    return leftRotation(node);
  }

  return node;
}

template <typename T, typename Comparator>
void AVLTree<T, Comparator>::push(const T &value) {
  head = push(head, value);
}

template <typename T, typename Comparator>
typename AVLTree<T, Comparator>::Node *
AVLTree<T, Comparator>::push(Node *node, const T &value) {
  if (!node) {
    return new Node(value);
  }

  if (comp(value, node->data)) {
    node->left = push(node->left, value);
  } else {
    node->right = push(node->right, value);
  }

  return balance(node);
}

template <typename T, typename Comparator>
void AVLTree<T, Comparator>::remove(const T &value) {
  head = remove(head, value);
}

template <typename T, typename Comparator>
typename AVLTree<T, Comparator>::Node *
AVLTree<T, Comparator>::remove(Node *node, const T &value) {
  if (!node) {
    return nullptr;
  }

  if (!comp(node->data, value) && !comp(value, node->data)) {
    Node *left = node->left;
    Node *right = node->right;

    delete node;

    if (!right) {
      return left;
    }

    Node *min = nullptr;
    Node *replaced = minRemove(right, min);

    min->right = replaced;
    min->left = left;

    return balance(min);
  }

  if (comp(value, node->data)) {
    node->left = remove(node->left, value);
  } else {
    node->right = remove(node->right, value);
  }

  return balance(node);
}

template <typename T, typename Comparator>
typename AVLTree<T, Comparator>::Node *
AVLTree<T, Comparator>::minRemove(Node *node, Node *&min) {
  if (!node->left) {
    min = node;
    return node->right;
  }

  node->left = minRemove(node->left, min);
  return balance(node);
}

template <typename T, typename Comparator>
T AVLTree<T, Comparator>::statistics(const int k) {
  return statistics(head, k + 1);
}

template <typename T, typename Comparator>
T AVLTree<T, Comparator>::statistics(Node *node, const int k) {
  int value_left;
  int value_right;
  int cur;

  if (node->left) {
    value_left = node->left->num;
  } else {
    value_left = 0;
  }

  if (node->right) {
    value_right = node->right->num;
  } else {
    value_right = 0;
  }

  cur = node->num - value_right;

  if (k < cur) {
    return statistics(node->left, k);
  }

  if (k > cur) {
    return statistics(node->right, k - value_left - 1);
  }

  return node->data;
}

template <typename T> void display(std::vector<T> &vec) {
  for (auto &it : vec) {
    std::cout << it << " ";
  }
}

void task() {
  AVLTree<int> tree;

  std::vector<int> buf;

  int n = 0;
  std::cin >> n;

  int k = 0;
  int value = 0;

  for (int i = 0; i < n; i++) {
    std::cin >> value >> k;

    if (value < 0) {
      tree.remove(-value);
    } else {
      tree.push(value);
    }

    buf.push_back(tree.statistics(k));
  }
  display(buf);
  std::cout << std::endl;
}

int main() {
  task();

  return 0;
}
