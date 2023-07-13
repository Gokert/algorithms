/* N segments are colored on the number line.
The coordinates of the left and right ends of each segment [Li, Ri] are known.
Find the length of the colored part of the number line. N ≤ 10000. Li, Ri are
integers in the range [0, 109]. Input Format

The first line contains the number of segments.
Each subsequent line contains space-separated coordinates of the left and right
ends of the segment. Output Format

Print an integer — the length of the colored part.

In the task, it is necessary to implement and use merge sort as a template
function. The solution should support passing the compare function from outside.
The total running time of the algorithm is O(n log n).
For example:

in		out
3		5
1 4
7 8
2 5


*/
#include <iostream>

template <typename T> struct defaultComparator {
  bool operator()(const T &l, const T &r) const { return l < r; }
};

struct Point {
  Point() {}
  Point(int _num, bool _bl) : num(_num), bl(_bl) {}
  bool operator<(const Point &r) const { return this->num < r.num; }

  int num;
  bool bl;
};

template <typename T> class Line {
public:
  Line();
  Line(int num);
  ~Line();

  void push(T &);
  int calculation();
  int getSize() const;
  T *getArr() const;

private:
  void newSize();

  int size;
  int buf_size;
  T *arr;
};

template <typename T> Line<T>::Line(): size(2), buf_size(0), arr(new T[2]) {}

template <typename T> Line<T>::Line(int num): size(2), buf_size(0), arr(new T[num]) {}

template <typename T> Line<T>::~Line() { delete[] arr; };

template <typename T> T *Line<T>::getArr() const { return arr; }

template <typename T> int Line<T>::getSize() const { return buf_size; }

template <typename T> int Line<T>::calculation() {
  int count = 0;
  int sum = 0;
  int index = 0;

  for (int i = 0; i < buf_size; i++) {
    if (sum == 0) {
      index = i;
    }

    if (arr[i].bl == true) {
      sum++;
    } else
      sum--;
    if (sum == 0) {
      int buffer = arr[i].num - arr[index].num;
      count += buffer;
      index = i;
    }
  }
  return count;
}

template <typename T> void Line<T>::push(T &element) {
  if (size == buf_size) {
    newSize();
  }

  arr[buf_size] = element;
  buf_size++;
}

template <typename T> void Line<T>::newSize() {
  T *newbuf_size = new T[size * 2];

  for (int i = 0; i < size; i++) {
    newbuf_size[i] = arr[i];
  }

  delete[] arr;

  arr = newbuf_size;
  size *= 2;
}

template <typename T, typename Comparator = defaultComparator<T>>
void mergeSort(T *arr, int left, int right, T *buffer) {

  if (right - left < 2) {
    return;
  }

  bool first = (buffer == NULL);

  if (first) {
    buffer = new T[right - left];
  }

  int size = (right - left);
  int half = size / 2;

  mergeSort(arr, left, left + half, buffer);
  mergeSort(arr, left + half, right, buffer);
  merge(arr, left, right, first, buffer);
}

template <typename T, typename Comparator = defaultComparator<T>>
void merge(T *arr, int left, int right, bool first, T *buffer) {
  int i = 0;
  int j = 0;
  int size = right - left;
  int mid = size / 2;

  while (i < mid && j < size - mid) {
    if (arr[left + i] < arr[left + mid + j]) {
      buffer[i + j] = arr[left + i];
      i++;
    } else {
      buffer[i + j] = arr[left + mid + j];
      j++;
    }
  }

  if (i == mid) {
    for (; j < size - mid; j++) {
      buffer[i + j] = arr[left + mid + j];
    }
  } else {
    for (; i < mid; i++) {
      buffer[i + j] = arr[left + i];
    }
  }

  for (i = 0; i < size; i++) {
    arr[left + i] = buffer[i];
  }

  if (first) {
    delete[] buffer;
  }
}

template <typename T, typename Comparator = defaultComparator<T>>
void sort(Line<T> &ln) {
  Line<T> buf(ln.getSize());
  mergeSort(ln.getArr(), 0, ln.getSize(), buf.getArr());
}

template <typename T> 
void inputFunction(Line<T> &ln, int &n) {
  for (int i = 0; i < n; i++) {
    int left, right = 0;
    std::cin >> left >> right;

    Point buf1(left, true);
    Point buf2(right, false);

    ln.push(buf1);
    ln.push(buf2);
  }
}

void task() {
  int n = 0;
  std::cin >> n;

  Line<Point> ln;

  inputFunction(ln, n);

  sort(ln);

  std::cout << ln.calculation() << std::endl;
}

int main() { 
  task();
  
  return 0;
}
