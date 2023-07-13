/* Given a sorted array of integers A[0..n-1] and an array of integers
B[0..m-1]. For each element of array B[i] find the minimum index k of the
minimum element of array A equal to or greater than B[i]: A[k] >= B[i]. If there
is no such element, print n. n, m ≤ 10000. Requirements: Search running time k
for each element of B[i]: O(log(k)). Attention! In this problem, for each B[i],
you first need to determine the range for binary search with a size of order k
using exponential search, and then do binary search in it. Input data format.
The first line contains numbers n and m. In the second and third arrays A and B,
respectively. For example:

in		      out
4 3		      1 3 0
2 4 5 7
4 6 1

*/

#include <iostream>
#include <vector>

int binarySearch(const int numbers_A[], const int &result, int &first,
                 int &last) {
  while (first < last) {
    int middle = (first + last) / 2;

    if (numbers_A[middle] < result) {
      first = middle + 1;
    } else {
      last = middle;
    }
  }

  return (numbers_A[first] != result) ? last : first;
}

void parseLine(int numbers[], const int &count) {
  int buf;

  for (int i = 0; i < count; i++) {
    std::cin >> buf;
    numbers[i] = buf;
  }
}

int *exponentSearch(const int numbers_A[], const int numbers_B[],
                    const int &count_A, const int &count_B) {
  int first;
  int last;

  int *mas = new int[count_B];

  int num_A_size = count_A - 1;
  for (int i = 0; i < count_B; i++) {
    first = 0;
    last = 1;

    while (numbers_A[last] < numbers_B[i]) {
      first = last;
      last *= 2;
      if (last > num_A_size) {
        last = num_A_size;
        break;
      }
    }

    if (numbers_A[num_A_size] < numbers_B[i]) {
      mas[i] = num_A_size + 1;
    } else {
      mas[i] = binarySearch(numbers_A, numbers_B[i], first, last);
    }
  }

  return mas;
}

void display(int *buf, int &count_B) {
  for (int i = 0; i < count_B; i++) {
    std::cout << buf[i] << " ";
  }
}

void task() {
  int count_A, count_B;

  std::cin >> count_A;
  std::cin >> count_B;

  int *numbers_A = new int[count_A];
  int *numbers_B = new int[count_B];

  parseLine(numbers_A, count_A);
  parseLine(numbers_B, count_B);

  int *buf = exponentSearch(numbers_A, numbers_B, count_A, count_B);

  display(buf, count_B);

  delete[] buf;
  delete[] numbers_A;
  delete[] numbers_B;
}

int main() { 
  task();
  
  return 0;
}
