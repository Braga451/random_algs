#include <stdio.h>

void sol(int n) {
  printf("%s\n", (n > 2 && n % 2 == 0) ? "YES" : "NO");
}

int main(int argv, char ** argc) {
  int num = 0;
  scanf("%d", &num);
  sol(num);

  return 0;
}
