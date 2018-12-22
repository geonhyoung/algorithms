/*
 * File Name: main.cc
 * Creation Date: Sat Dec 22, 2018 07:52PM
 * Description:
 * Author: jogeonhyeong-ui-MacBook-Pro
 *
 * Last modified: Sat Dec 22, 2018 08:19PM
 */

#include <iostream>
#include <vector>

using namespace std;
using datatype = int;

class QuickSort {
 public:
  void push(datatype val) { list_.push_back(val); }

  void sort(int left, int right) {
    if (left < right) {
      int pivot = partition(left, right);

      sort(left, pivot - 1);
      sort(pivot + 1, right);
    }
  }

  void print() const {
    for (vector<datatype>::size_type i = 0; i < list_.size(); i++)
      (cout << list_.at(i)) << " ";
    cout << endl;
  }

 private:
  vector<datatype> list_;

  int partition(int left, int right) {
    if (list_.empty()) return -1;

    int pivot = list_.at(left);

    int low = left;
    int high = right + 1;
    do {
      do {
        low++;
      } while (low <= right && list_.at(low) < pivot);

      do {
        high--;
      } while (left <= high && list_.at(high) > pivot);

      if (low < high) swap(list_.at(low), list_.at(high));

    } while (low < high);

    swap(list_.at(left), list_.at(high));
    return high;
  }
};

int main() {
  vector<datatype> vec;
  vec.push_back(1);
  vec.push_back(8);
  vec.push_back(3);
  vec.push_back(10);
  vec.push_back(22);
  vec.push_back(-1);
  vec.push_back(32);
  vec.push_back(7);

  QuickSort qs;

  for (vector<datatype>::size_type i = 0; i < vec.size(); i++)
    qs.push(vec.at(i));

  qs.print();

  qs.sort(0, vec.size() - 1);

  qs.print();

  return 0;
}
