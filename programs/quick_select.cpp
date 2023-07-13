/* You are given a set of integers from [0..10^9] of size n.
Using the search algorithm for the kth order statistics, it is required to find
the following set parameters:
    - 10% percentile
    - median
    - 90% percentile

Requirements: additional memory: O(n).
Average running time: O(n)
There must be a separate partition function.
Recursion is prohibited.
The solution should support passing the compare function from outside.


The Partition function should be implemented by traversing two iterators in the
same direction. Description for the case of passing from the beginning of the
array to the end: The base element is selected. The reference element changes
with the last element of the array. During Partition operation, the beginning of
the array contains elements that are not larger than the reference. Then there
are elements that are strictly larger than the reference one. At the end of the
array are the unconsidered elements. The last element is the pivot. The iterator
(index) i points to the beginning of a group of elements strictly greater than
the reference one. The iterator j is greater than i, the iterator j points to
the first unexamined element. Algorithm step. The element pointed to by j is
considered. If it is greater than the reference, then we shift j. If it is not
greater than the reference, then we change a[i] and a[j] in places, shift i and
shift j. At the end of the algorithm, we change the reference element and the
element pointed to by the iterator i. Implement a “random element” pivot
selection strategy. Implement the Partition function by going through two
iterators from the end of the array to the beginning.

For example:
in                              out
10                              2
1 2 3 4 5 6 7 8 9 10            6
                                10


*/

#include <iostream>

template <typename T> T *generateValuesay(int size) {
  T *result = new int[size];
  for (int i = 0; i < size; i++) {
    std::cin >> result[i];
  }
  return result;
}

template <typename T> void cleanMemory(T *values) { delete[] values; }

template <typename data> struct Comparator {
  bool operator()(const data &a, const data &b) { return a < b; }
};

template <typename T, typename MyCmp = Comparator<T>>
int partition(T *values, int left, int right, MyCmp cmp = MyCmp()) {
  int random_position = (left + rand() % (right - left));
  int id = right - 1, second_id = id;
  T pivot = values[random_position];
  std::swap(values[random_position], values[left]);
  while (id != left) {
    if (cmp(values[id], pivot)) {
      { id--; }
    } else {
      id--;
      second_id--;
      std::swap(values[id], values[second_id]);
    }
  }
  std::swap(values[second_id], values[left]);
  return second_id;
}

template <typename T, typename MyCmp = Comparator<T>>
T kthStat(T *values, int size, int k, MyCmp cmp = MyCmp()) {
  int left = 0, right = size, part_result;
  while (left < right) {
    part_result = partition(values, left, right, cmp);
    if (part_result == k) {
      return values[k];
    } else if (part_result < k) {
      left = part_result + 1;
    } else {
      right = part_result;
    }
  }
  return 0;
}

template <typename T, typename MyCmp = Comparator<T>>
T *handlerKthStatisticInformation(T *values, int size, MyCmp cmp = MyCmp()) {
  T *result = new T[3];
  for (int i = 0; i < 3; i++) {
    switch (i) {
    case 0:
      result[i] = kthStat(values, size, size / 10, cmp);
      break;
    case 1:
      result[i] = kthStat(values, size, (size / 2), cmp);
      break;
    case 2:
      result[i] = kthStat(values, size, (9 * size) / 10, cmp);
      break;
    }
  }
  return result;
}

void task() {
  int size = 0;
  std::cin >> size;
  int *values = generateValuesay<int>(size);
  int *results = handlerKthStatisticInformation(values, size);
  for (int i = 0; i < 3; i++) {
    if (results[i] != 0)
      std::cout << results[i] << std::endl;
  }
  cleanMemory(values);
  cleanMemory(results);
}

int main() {
  task();
  
  return 0;
}
