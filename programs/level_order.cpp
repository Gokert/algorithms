/*  Given a number N < 106 and a sequence of integers from [-231..231] of length
N. It is required to build a binary tree given a naive insertion order. That is,
when adding the next number K to the tree with root root, if root→Key ≤ K, then
node K is added to the right subtree of root; otherwise, to the left subtree of
root. Requirements: Recursion is not allowed. Solution must support function
passing comparisons outside. Output the elements in level-order (by layers, “in
width").
Output the elements in level-order (by layers, “wide”).

For example:

in 		out
3
2 1 3		2 1 3


4
3 1 4 2		3 1 4 2
*/

#include <iostream>
#include <queue>
#include <vector>

template <typename T> struct DefaultComparator {
  int operator()(const T &left, const T &right) const {
    if (left > right) {
      return 1;
    }

    return 0;
  }
};

template <typename T, typename Comparator = DefaultComparator<T>> 
struct Node {
  Node(T value_) : value(value_), left(nullptr), right(nullptr) {}
  ~Node() {
    delete left;
    delete right;
  }

  T value;
  Node *left;
  Node *right;
};

void insertValue(Node<int> *&root, const int value) {
  if (!root) {
    root = new Node<int>(value);
    return;
  }

  DefaultComparator<int> comp;
  Node<int> *cur = root;
  while (true) {
    if (value > cur->value) {
      if (!cur->right) {
        cur->right = new Node<int>(value);
        return;
      }
      cur = cur->right;
    } else {
      if (!cur->left) {
        cur->left = new Node<int>(value);
        return;
      }
      cur = cur->left;
    }
  }
}

template <typename T> 
std::vector<T> traverseBFS(Node<T> *root) {
  if (root == nullptr) {
    return std::vector<T>();
  }

  std::queue<Node<T> *> buf_queue;
  std::vector<T> numbers;

  buf_queue.push(root);

  while (!buf_queue.empty()) {
    Node<T> *cur = buf_queue.front();
    buf_queue.pop();
    numbers.push_back(cur->value);

    if (cur->left != nullptr) {
      buf_queue.push(cur->left);
    }

    if (cur->right != nullptr) {
      buf_queue.push(cur->right);
    }
  }
  return numbers;
}

template <typename T> void display(std::vector<T> numbers) {
  for (auto &it : numbers) {
    std::cout << it << " ";
  }
}

template <typename T> void task() {
  int n = 0;
  int value = 0;

  std::cin >> n;
  Node<T> *root = NULL;

  for (int i = 0; i < n; i++) {
    std::cin >> value;
    insertValue(root, value);
  }

  std::vector<T> numbers = traverseBFS(root);

  display(numbers);

  delete root;
}

int main() {
  task<int>();

  return 0;
}
