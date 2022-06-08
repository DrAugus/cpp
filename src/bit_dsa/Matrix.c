#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
/**稀疏矩阵压缩存储**/
#define MAXSIZE 100
typedef struct {
    int i;
    int j;
    int e;
} Triple;
typedef struct {
    Triple data[MAXSIZE];
    int m, n, len;
} Matrix;
// 函数声明
int CreateMatrix(Matrix *M);
void DestroyMatrix(Matrix *M);
void PrintMatrix(Matrix M);
void CopyMatrix(Matrix M, Matrix *N);
int CompareNumber(int a, int b);
int AddMatrix(Matrix M, Matrix N, Matrix *Q);
int SubMatrix(Matrix M, Matrix N, Matrix *Q);
void TransposeMatrix(Matrix M, Matrix *N);
/**创建一个稀疏矩阵**/
int CreateMatrix(Matrix *M) {
    // 创建成功返回1
    int i, m, n, len;
    int e;
    int flag;
    printf("Input the Matrix's row,col and the number of non-zero element:");
    scanf("%d%d%d", &m, &n, &len);
    if (len > MAXSIZE)
        return 0;
    M->len = len;
    M->m = m;
    M->n = n;
    // 以行为主录入非零元素
    for (i = 0; i < len; i++) {
        do {
            printf(
                "%d、Input the row(1-%d) and col(i-%d) of element by the order of row:",
                i, M->m, M->n);
            scanf("%d%d%d", &m, &n, &e);
            flag = 0;
            if (m < 0 || n < 0 || m > M->m || n > M->n)
                flag = 1;
            if (i > 0 && m < M->data[i - 1].i ||
                m == M->data[i - 1].i && n < M->data[i - 1].j)
                flag = 1;
        } while (flag);
        M->data[i].i = m;
        M->data[i].j = n;
        M->data[i].e = e;
    }
    return 1;
}
/**销毁一个稀疏矩阵**/
void DestroyMatrix(Matrix *M) {
    M->len = 0;
    M->m = 0;
    M->n = 0;
}
/**打印矩阵**/
void PrintMatrix(Matrix M) {
    int len = M.len;
    printf("k\ti\tj\te\n");
    for (int i = 0; i < len; i++) {
        printf("%d\t%d\t%d\t%d\n", i, M.data[i].i, M.data[i].j, M.data[i].e);
    }
}
/**矩阵复制**/
void CopyMatrix(Matrix M, Matrix *N) {
    int len = M.len;
    N->len = len;
    N->m = M.m;
    N->n = M.n;
    for (int i = 0; i < len; i++) {
        N->data[i].i = M.data[i].i;
        N->data[i].j = M.data[i].j;
        N->data[i].e = M.data[i].e;
    }
}
int CompareNumber(int a, int b) {
    if (a < b)
        return -1;
    if (a == b)
        return 0;
    return 1;
}
/**矩阵加法**/
int AddMatrix(Matrix M, Matrix N, Matrix *Q) {
    // 相加成功返回1
    if (M.m != N.m || M.n != N.n)
        return 0;
    int m = 0, n = 0, k = -1;
    Q->m = M.m;
    Q->n = M.n;
    while (m < M.len && n < M.len) {
        switch (CompareNumber(M.data[m].i, N.data[n].i)) {
            case -1:
                Q->data[++k] = M.data[m++];
                break;
            case 0:
                switch (CompareNumber(M.data[m].j, N.data[n].j)) {
                    case -1:
                        Q->data[++k] = M.data[m++];
                        break;
                    case 0:
                        Q->data[++k] = M.data[m++];
                        Q->data[k].e += N.data[n++].e;
                        if (Q->data[k].e == 0) {
                            k--;
                        }
                        break;
                    case 1:
                        Q->data[++k] = N.data[n++];
                        break;
                }
                break;
            case 1:
                Q->data[++k] = N.data[n++];
                break;
        }
    }
    while (m < M.len) {
        Q->data[++k] = M.data[m++];
    }
    while (n < N.len) {
        Q->data[++k] = N.data[n++];
    }
    Q->len = k + 1;
    if (k > MAXSIZE) {
        printf("ERROR!Out of bound!");
        return 0;
    }
    return 1;
}
/**矩阵减法**/
// 只需要将第二个矩阵的每个元素取反然后进行加法即可
int SubMatrix(Matrix M, Matrix N, Matrix *Q) {
    // 相减成功返回1
    int len = N.len;
    for (int i = 0; i < len; i++) {
        N.data[i].e = -N.data[i].e;
    }
    return AddMatrix(M, N, Q);
}
/**转置矩阵**/
void TransposeMatrix(Matrix M, Matrix *N) {
    int i, k, t, col, *num, *position;
    num = (int *)malloc((M.n + 1) * sizeof(int));
    position = (int *)malloc((M.n + 1) * sizeof(int));
    N->m = M.m;
    N->n = M.n;
    N->len = M.len;
    if (N->len) {
        for (col = 0; col < M.n; ++col) {
            num[col] = 0;
        }
        for (t = 0; t < M.len; t++) {
            num[M.data[t].j]++;
        }
        position[0] = 0;
        for (col = 1; col < M.n; col++) {
            position[col] = position[col - 1] + num[col - 1];
        }
        for (i = 0; i < M.len; i++) {
            col = M.data[i].j;
            k = position[col];
            N->data[k].i = M.data[i].j;
            N->data[k].j = M.data[i].i;
            N->data[k].e = M.data[i].e;
            position[col]++;
        }
    }
    free(num);
    free(position);
}
int main() {
    Matrix m1, m2, m3, m4, m5;
    CreateMatrix(&m1);
    PrintMatrix(m1);
    CopyMatrix(m1, &m2);
    printf("--------------\n\n");
    PrintMatrix(m2);
    AddMatrix(m1, m2, &m3);
    printf("--------------\n\n");
    PrintMatrix(m3);
    SubMatrix(m3, m2, &m4);
    printf("--------------\n\n");
    PrintMatrix(m4);
    TransposeMatrix(m4, &m5);
    printf("--------------\n\n");
    PrintMatrix(m5);
    DestroyMatrix(&m1);
    printf("--------------\n\n");
    PrintMatrix(m1);
    system("pause");
    return 0;
}
