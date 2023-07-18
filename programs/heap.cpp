/*Process Scheduler
The Technux operating system has a process scheduler.
Each process is characterized by:

     -priority P
     -the time he has already worked t
     -the time it takes to complete the process T

The process scheduler selects the process with the minimum value P * (t + 1),
executes it for time P, and puts it back in the process queue. If the condition
t >= T is met, then the process is considered completed and removed from the
queue. The solution to the problem involves the use of a heap implemented as a
template class. It is required to count the number of processor switches. The
solution should support passing the compare function from outside. The heap must
be dynamic. Do not use ready-made dynamic data structures. For example:

in		  out
3		    18
1 10
1 5
2 5

*/

#include <iostream>

template <typename T> struct MyComparator {
  bool operator()(T &l, T &r) const {
    return l.P * (l.t + 1) > r.P * (r.t + 1);
  }
};

struct Process {
  Process(){};
  Process(int i, int j, int k) : P(i), T(j), t(k){};

  int P;
  int T;
  int t;
};

template <typename MyStruct, typename Comparator = MyComparator<MyStruct> > class Heap {
public:
  Heap();
  Heap(int n);

  ~Heap();

  void insert(int, int);
  bool isEmpty();
  int display();


  void siftDown(int);
  void siftUp(int);
  MyStruct &operator[](int);

  int size;

private:
  int real_size;
  MyStruct *arr;
  Comparator cmp;
};

template <typename MyStruct, typename Comparator>
Heap<MyStruct, Comparator>::Heap() : size(0), real_size(0), arr(new MyStruct[0]) {}

template <typename MyStruct, typename Comparator>
Heap<MyStruct, Comparator>::Heap(int n) : size(0), real_size(n), arr(new MyStruct[n]) {}

template <typename MyStruct, typename Comparator>
bool Heap<MyStruct, Comparator>::isEmpty() {
  return real_size;
}

template <typename MyStruct, typename Comparator>
Heap<MyStruct, Comparator>::~Heap() {
  delete[] arr;
}

template <typename MyStruct, typename Comparator>
MyStruct &Heap<MyStruct, Comparator>::operator[](int index) {
  return arr[index];
}

template <typename MyStruct, typename Comparator>
void Heap<MyStruct, Comparator>::siftDown(int index) {
  int left = 2 * index + 1;
  int right = 2 * index + 2;

  int lagest = index;

  if (left < size && cmp(arr[index], arr[left])) {
    lagest = left;
  }
  if (right < size && cmp(arr[lagest], arr[right])) {
    lagest = right;
  }
  if (lagest != index) {
    std::swap(arr[index], arr[lagest]);
    siftDown(lagest);
  }
}

template <typename MyStruct, typename Comparator>
void Heap<MyStruct, Comparator>::siftUp(int index) {
  while (index > 0) {
    int parent = (index - 1) / 2;
    if (cmp(arr[index], arr[parent])) {
      return;
    }
    std::swap(arr[index], arr[parent]);
    index = parent;
  }
}

template <typename MyStruct, typename Comparator>
void Heap<MyStruct, Comparator>::insert(int _P, int _T) {
  MyStruct buf(_P, _T, 0);
  arr[size++] = buf;

  siftUp(size - 1);
}

template <typename MyStruct, typename Comparator>
int processing(Heap<MyStruct, Comparator> &hp) {
  int count = 0;

  while (hp.size != 0) {
    int result = hp[0].P * (hp[0].t + 1);
    hp[0].t = hp[0].t + hp[0].P;
    count++;

    if (hp[0].t < hp[0].T) {
      hp.siftDown(0);
    } else {
      std::swap(hp[0], hp[hp.size - 1]);

      hp.size--;

      hp.siftDown(0);
    }
  }
  return count;
}

void task() {
  int n = 0;
  std::cin >> n;
  Heap<Process> hp(n);

  for (int i = 0; i < n; i++) {
    int P, T = 0;
    std::cin >> P >> T;
    hp.insert(P, T);
  }

  std::cout << processing(hp) << std::endl;
}

int main() { 
  task();
  
  return 0;
}
