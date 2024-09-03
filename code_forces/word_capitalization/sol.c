#include <stdio.h>
const int MAX = 1000;

void sol() {
  char word[MAX];
  fgets(word, MAX, stdin);

  if (word[0] > 90) {
    word[0] -= 32;
  }

  printf("%s", word);
}

int main(int argv, char ** argc) {
  sol();
  return 0;
};
