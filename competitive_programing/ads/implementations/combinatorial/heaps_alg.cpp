#include <iostream>
#include <ostream>
#include <vector>

// https://en.wikipedia.org/wiki/Heap's_algorithm lmao
void permutate(int k, std::vector<int>& a, std::vector<std::vector<int>>& p) {
  if (k == 1) {
    p.push_back(a);
    return;
  }
  
  for (int i = 0; i < k; i++) {
    permutate(k - 1, a, p);
    
    if (i < k - 1) {
      if (k % 2 == 0) {
        std::swap(a[i], a[k - 1]);
      }
      else {
        std::swap(a[0], a[k - 1]);
      }
    }
  }

}

int main() {
  std::vector<int> e;
  for (int i = 1; i < 10; i++) e.push_back(i);
  std::vector<std::vector<int>> p;

  permutate(e.size(), e, p);

  for (std::vector<int> perm : p) {
    for (int element : perm) {
      std::cout << element << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
