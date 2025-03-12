#include <stdio.h>
#include <string.h>

int strToint(char* num) {
  if (strlen(num) == 0) return -1;
  int pos = 1, res = 0, len = strlen(num);
  for (int i = len - 1; i >= 0; i--) {
    int n = num[i] - '0';
    res = res + (n * pos);
    pos *= 10;
  }
  return res;
}

int main(int argc, char** argv) {
  char str[] = "356";
  printf("%d\n", strToint(str));

  return 0;
}
