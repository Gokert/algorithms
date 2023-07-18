/*MSD for strings. Given an array of strings. The number of rows is not more
than 105. Sort the array using the MSD bitwise sorting method by characters. The
size of the alphabet is 256 characters. Last character of the string = '\0' .Do not use ready-made dynamic data structures.

For example:
in		out
ab		a
a		  aa
aaa		aaa
aa		ab



*/

#include <cstring>
#include <iostream>

const int MAX_LENGTH = 256;
const int BUF_ = 256;

void parseLine(std::string *words, int &count) {
  std::string buf_word = "";
  while (std::cin.good()) {
    std::cin >> buf_word;
    words[count] = buf_word;
    count++;
  }
}

int getKey(char c) { return static_cast<int>(c); }

void sort(std::string *words, int count, int index, int *buf) {
  for (int i = 0; i < count; i++)
    buf[getKey(words[i][index])] += 1;

  int start = 0;
  for (int i = 0; i < BUF_; i++) {
    int symbol_count = buf[i];
    buf[i] = start;
    start += symbol_count;
  }

  std::string *sort_words = new std::string[count];
  std::string *buffer = new std::string[count];

  for (int i = 0; i < count; i++) {
    buffer[i] = words[i];
  }

  for (int i = 0; i < count; i++) {
    int past_pos = buf[getKey(words[i][index])];
    sort_words[past_pos] = buffer[i];
    buf[getKey(words[i][index])]++;
  }

  for (int i = 0; i < count; i++) {
    words[i] = sort_words[i];
  }

  delete[] sort_words;
  delete[] buffer;
}

void msdSort(std::string *words, int count, int radix = 0) {
  int *buf = new int[BUF_ + 1];
  for (int i = 0; i < BUF_; i++) {
    buf[i] = 0;
  }

  buf[BUF_] = count;

  sort(words, count, radix, buf);
  for (int i = 0; i < BUF_; i++) {
    int buf_size = buf[i + 1] - buf[i];
    if (buf_size > 1) {
      msdSort(words + buf[i], buf_size, radix + 1);
    }
  }

  delete[] buf;
}

void display(std::string *words, int &count) {
  for (int i = 0; i < count; i++)
    std::cout << words[i] << std::endl;
}

void task() {
  int count = 0;
  std::string *words = new std::string[100000];
  parseLine(words, count);

  count--;
  msdSort(words, count);
  display(words, count);

  delete[] words;
}

int main() { 
  task();
  
  return 0;
}
