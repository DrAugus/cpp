// 鞍点
// 给定一个n*n矩阵A。矩阵A的鞍点是一个位置（i，j），在该位置上的元素是第i行上的最大数，第j列上的最小数。一个矩阵A也可能没有鞍点。
#include <stdio.h>

int max(int a[], int len) {
  int id = 0;
  for (int i = 0; i < len; i++) {
    if (a[i] > a[id]) {
      id = i;
    }
  }
  return id;
}

int min(int a[], int len) {
  int id = 0;
  for (int i = 0; i < len; i++) {
    if (a[i] < a[id]) {
      id = i;
    }
  }
  return id;
}

int main() {
  int n;
  //   scanf("%d", &n);
  n = 4;

  int A[4][4] = {{1, 7, 4, 1}, {4, 8, 3, 6}, {1, 6, 1, 2}, {0, 7, 8, 9}};
  //   for (int i = 0; i < n; i++) {
  //     for (int j = 0; j < n; j++) {
  //       scanf("%d", &A[i][j]);
  //     }
  //   }

  int row_max_id[n];
  for (int i = 0; i < n; i++) {
    row_max_id[i] = max(A[i], n);
  }

  int flag = 1;
  int row_id, col_id;
  for (int i = 0; i < n; i++) {
    col_id = row_max_id[i];
    flag = 1;
    row_id = i;
    int col_min_value = A[i][col_id];
    for (int j = 0; j < n; j++) {
      if (A[j][col_id] < col_min_value) {
        flag = 0;
        break;
      }
    }
    if (flag == 1) {
      break;
    }
  }
  if (flag == 0) {
    printf("NO");
  } else {
    printf("%d %d", row_id, col_id);
  }
  printf("\n");

  return 0;
}