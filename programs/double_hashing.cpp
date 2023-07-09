/* Implement a multi-row data structure based on a publicly addressable dynamic hash table. Stored strings are non-empty and consist of lowercase Latin letters.
The string hash function must be implemented using Horner's polynomial value calculation.
The initial size of the table must be equal to 8. Perform rehashing when adding elements in the case when the table fill factor reaches 3/4.
The data structure must support the operations of adding a string to a set, deleting a string from a set, and checking whether a given string belongs to a set.
Use double hashing to resolve collisions.
Requirements: It is forbidden to store pointers to the element descriptor in the table.

Each line of the input defines one operation on the set. An operation entry consists of the type of operation followed by a space-separated line on which the operation is performed.
The operation type is one of three characters:
     + means adding the given string to the set;
     - means deleting a string from the set;
     ? means checking whether the given string belongs to the set.
When an element is added to a set, it is NOT GUARANTEED that it is not present in the set. When an element is removed from a set, it is NOT GUARANTEED that it is present in that set.
Output format
The program should output for each operation one of the two lines OK or FAIL, depending on whether the given word occurs in our set.

For example:
stdin         stdout
+ hello       OK
+ bye         OK
? bye         OK
+ bye         FAIL
- bye         OK
? bye         FAIL
? hello       OK


*/

#include <iostream>
#include <string>
#include <vector>

class HashTabel {
    struct Node {
    std::string hash_key;
    bool is_rem;
    bool is_dem;
    int hash;

    Node(std::string key, int hash): hash_key(std::move(key)), is_rem(false), is_dem(false), hash(hash) {}
    bool is_demmy() const { return is_dem; }
    Node() : hash_key(""), hash(-1), is_rem(true), is_dem(true) {}
    void change(std::string key, int hash) {
      hash_key = std::move(key);
      this->hash = hash;

      is_rem = false;
      is_dem = false;
    }
  };

public:
  explicit HashTabel(int size);

  ~HashTabel();

  bool push(const std::string &hash_key);
  bool check(const std::string &hash_key);
  bool remove(const std::string &hash_key);

private:
  std::vector<Node> table;
  int findIndex(int hash, const std::string &hash_key);
  int find(int hash, const std::string &hash_key);
  int hash1(const std::string &hash_key);
  int hash2(const std::string &hash_key);
  void grow();

  const double factor = 0.75;
  int num_elements;
  const int hash_map = 71;
};

HashTabel::HashTabel(int size) : table(size), num_elements(0) {}

HashTabel::~HashTabel() {}

bool HashTabel::check(const std::string &hash_key) {
  int hash = hash1(hash_key);
  return find(hash, hash_key) >= 0;
}

int HashTabel::find(int hash, const std::string &hash_key) {
  int real_size = table.size();
  int pos = ((hash % real_size) + real_size) % real_size;

  if (table.at(pos).is_demmy()) {
    return -1;
  }

  int res_hash2 = hash2(hash_key) % real_size;
  int new_pos = pos;

  while (true) {
    Node other = table.at(new_pos);
    if (other.is_demmy()) {
      return -1;
    }

    if (other.hash_key == hash_key && other.is_rem) {
      return -1;
    }

    if (other.hash_key == hash_key && !other.is_rem) {
      return new_pos;
    }

    new_pos = (new_pos + res_hash2) % real_size;
  }
}

int HashTabel::hash1(const std::string &hash_key) {
  int hash = 0;
  for (const char &c : hash_key) {
    hash = (hash * hash_map + c);
  }
  return hash;
}

int HashTabel::hash2(const std::string &hash_key) {
  int hash = 5;
  for (const char &c : hash_key) {
    hash += c;
  }
  return 2 * hash + 1;
}

bool HashTabel::push(const std::string &hash_key) {
  int hash = hash1(hash_key);
  int index = findIndex(hash, hash_key);

  if (index < 0) {
    return false;
  }

  table.at(index).change(hash_key, hash);
  num_elements++;

  double load = static_cast<double>(num_elements) / table.capacity();
  if (load >= factor) {
    grow();
  }
  return true;
}

void HashTabel::grow() {
  std::vector<Node> old = table;
  table = std::vector<Node>(2 * table.size());

  for (Node &nd : old) {
    if (nd.is_demmy()) {
      continue;
    }
    if (nd.is_rem) {
      continue;
    }
    int index = findIndex(nd.hash, nd.hash_key);

    table.at(index).change(nd.hash_key, nd.hash);
  }
  std::vector<Node>().swap(old);
}

int HashTabel::findIndex(int hash, const std::string &hash_key) {
  int real_size = table.size();
  int pos = ((hash % real_size) + real_size) % real_size;

  if (table.at(pos).is_demmy()) {
    return pos;
  }

  int res_hash2 = hash2(hash_key) % real_size;
  int new_pos = pos;
  int pos_put = -1;

  while (true) {
    Node other = table.at(new_pos);

    if (other.is_demmy()) {
      if (pos_put < 0) {
        pos_put = new_pos;
      }
      break;
    }

    if (pos_put < 0 && other.is_rem) {
      pos_put = new_pos;
    }

    if (!other.is_rem && other.hash_key == hash_key) {
      return -1;
    }

    new_pos = (new_pos + res_hash2) % real_size;
  }
  return pos_put;
}

bool HashTabel::remove(const std::string &hash_key) {
  int hash = hash1(hash_key);
  int index = find(hash, hash_key);

  if (index < 0) {
    return false;
  }

  table.at(index).is_rem = true;
  return true;
}

void task() {
  HashTabel table(8);

  char command;
  std::string value;

  while (std::cin >> command >> value) {
    switch (command) {
    case '+': {
      if (table.push(value)) {
        std::cout << "OK" << std::endl;
        break;
      }
      std::cout << "FAIL" << std::endl;
      break;
    }
    case '-': {
      if (table.remove(value)) {
        std::cout << "OK" << std::endl;
        break;
      }
      std::cout << "FAIL" << std::endl;
      break;
    }
    case '?': {
      if (table.check(value)) {
        std::cout << "OK" << std::endl;
        break;
      }
      std::cout << "FAIL" << std::endl;
      break;
    }
    }
  }
}

int main() {
  task();

  return 0;
}
