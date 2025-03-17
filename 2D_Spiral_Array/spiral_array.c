#include <stdio.h>
#include <stdlib.h>

int isInvalid(int** res, int r, int c, int n) {
  if (r < 0 || c < 0 || r >= n || c >= n || res[r][c] != 0) {
    return 1;
  }
  return 0;
}

int** getSpiral(int n) {
  if (n <= 0) return NULL;

  int **res = (int**)malloc(n * sizeof(int*));
  for (int i = 0; i < n; i++) {
    res[i] = (int*)malloc(n * sizeof(int));
    for (int j = 0; j < n; j++) {
      res[i][j] = 0;
    }
  }

  int dc[] = {1, 0, -1, 0};
  int dr[] = {0, 1, 0, -1};
  int dir = 0, val = 0, r = 0, c = 0, limit = n * n;

  while (val++ < limit) {
    res[r][c] = val;
    r += dr[dir];
    c += dc[dir];
    if (isInvalid(res, r, c, n)) {
      r -= dr[dir];
      c -= dc[dir];
      dir = (dir + 1) % 4;
      r += dr[dir];
      c += dc[dir];
    }
  }
  return res;
}

void printSpiral(int** vecs, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d\t", vecs[i][j]);
    }
    printf("\n");
  }
}
void freeSpiral(int** vecs, int n) {
  for (int i = 0; i < n; i++) {
    free(vecs[i]);
  }
  free(vecs);
}

int main(int argc, char** argv) {
  int n = 8;
  int** vecs = getSpiral(n);
  printSpiral(vecs, n);

  freeSpiral(vecs, n);

  return 0;
}
