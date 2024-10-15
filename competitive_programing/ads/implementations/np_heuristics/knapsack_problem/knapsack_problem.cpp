#include <functional>
#include <vector>
#include <iostream>
#include <format>
#include <bits/stdc++.h>

int firstFit(int t, std::vector<int> &v) {
  int s = 0;
  for (int e : v) {
    if (s == t) break;
    if (s + e <= t) s+= e;
  }
  return s;
}

int bestFit (int t, std::vector<int> v) {
  std::sort(v.begin(), v.end());
  int s = 0;
  for (int e : v) {
    if (s + e > t || s == t) break;
    s += e;
  }
  return s;
}

int largestFit(int t, std::vector<int> v) {
  std::sort(v.begin(), v.end(), std::greater<int>());
  int s = 0;
  for (int e : v) {
    if (s == t) break;
    if (s + e <= t) s += e;
  }
  return s;
}

int main(int argc, char ** argv) {
  std::vector<int> v{1, 2, 5, 9, 10};
  int t = 22;
  
  std::cout << std::format("({}) ({}) ({})", firstFit(t, v), bestFit(t, v), largestFit(t, v)) << std::endl;

}
