/*Implement a queue with a dynamic loopback buffer.
Requirements: Queue must be implemented as a class.
Input data format.
The first line contains n commands. n ≤ 1000000.
Each command is specified as 2 integers: a b.
a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back
Add element commands 1 and 3 are specified with non-negative parameter b.
For the queue, commands 2 and 3 are used. For the deck, all four commands are
used. If the pop* command is given, then the number b is the expected value. If
the pop command is called on an empty data structure, "-1" is expected. Output
data format. It is required to print YES - if all the expected values matched.
Otherwise, if at least one expectation was not justified, then print NO. For
Example:

in		out
3
3 44		YES
3 50
2 44

2
3 44		NO
2 66

*/

#include <cstring>
#include <iostream>

class Queue {
public:
  Queue(int size);
  ~Queue();

  bool isEmpty() const;
  void grow();
  void push(int);
  int pop();

private:
  int size;
  int buf_size;
  int head;
  int tail;
  int *buf;
};

Queue::Queue(int size) : size(size), buf_size(0), head(0), tail(0), buf(new int[size]) {} 

bool Queue::isEmpty() const { return (head == tail || buf_size == 0); }

Queue::~Queue() { delete[] buf; }

void Queue::grow() {
  int iterator = head;
  size *= 2;
  int *newBuf = new int[size];

  int i = 0;
  for (; iterator != (tail); i++) {

    newBuf[i] = buf[iterator];
    iterator = (iterator + 1) % size;
  }

  newBuf[i] = buf[iterator];

  delete[] buf;

  buf = newBuf;

  head = 0;
  tail = (buf_size) % size;
}

int Queue::pop() {
  if (head != tail) {
    int result = buf[head];
    head = (head + 1) % size;
    buf_size--;

    int iterator = head;
    for (int i = 0; iterator != tail; i++) {
      iterator = (iterator + 1) % size;
    }

    return result;
  }

  int iterator = head;
  for (int i = 0; iterator != tail; i++) {
    iterator = (iterator + 1) % size;
  }

  return -1;
}

void Queue::push(int value) {
  if ((tail + 1) % size != head) {
    buf[tail % size] = value;
    tail = (tail + 1) % size;
    buf_size++;
  } else if (buf_size < size) {
    buf[(tail) % size] = value;
    buf_size++;
  } else if (buf_size == size) {
    grow();
    buf[buf_size] = value;
    buf_size++;
    tail = (tail + 1) % size;
  }

  int iterator = head;
  for (int i = 0; iterator != tail; i++) {
    iterator = (iterator + 1) % size;
  }
}

int inputOutput(Queue &vector, const int n) {
  int a = 0;
  int b = 0;

  for (int i = 0; i < n; i++) {
    std::cin >> a;
    std::cin >> b;

    if (a == 2)
      if (vector.isEmpty())
        if (b == -1)
          continue;
        else {
          std::cout << "NO" << std::endl;
          return -1;
        }
      else if (vector.pop() == b)
        continue;
      else {
        std::cout << "NO" << std::endl;
        return -1;
      }
    else if (a == 3)
      vector.push(b);
  }

  std::cout << "YES" << std::endl;
  return 0;
}

void task() {
  int n = 0;
  std::cin >> n;
  Queue vector(2);
  inputOutput(vector, n);
}

int main() { 
  task();
  
  return 0;
}
