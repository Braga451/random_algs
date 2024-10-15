#include <vector>
#include <iostream>
#define VEC_SIZE 100

void selectionSort(std::vector<int>& v) {
  for (int i = 0; i < v.size(); i++) {
    int j = i;
    
    while ( j > 0 && v[j] < v[j - 1]) {
      std::swap(v[j], v[j - 1]);
      j--;
    }
  }
}

void printVector(std::vector<int>& v) {
  std::cout << "V: ";
  for (auto e : v) std::cout << e << " ";
  std::cout << std::endl;
}

int main() {
  srand(time(0));

  std::vector<int> v(VEC_SIZE);
  
  for (int i = 0; i < VEC_SIZE; i++) v[i] = std::rand();

  printVector(v);
  selectionSort(v);
  printVector(v);

  return 0;
}
