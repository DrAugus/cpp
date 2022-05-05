// 本test仅供娱乐，瞎调试
#include <stdio.h>
int main() {
    int d[5], i, max;
    for (i = 0; i < 5; i++) sscanf_s("%d", &d[i]);
    max = d[0];
    for (i = 1; i < 5; i++)
        if (max < d[i])
            max = d[i];
    printf("The max number is %f\n", max);
}