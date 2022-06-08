#include <cstdio>
#include <cstdlib>

#ifdef __cplusplus
extern "C" {
#endif

struct date {
    int a;
    struct date* next;
};
typedef struct date DATE;
typedef struct date* PDATE;

PDATE setnew(PDATE p, int a) {
    PDATE pt;
    pt = (PDATE)malloc(sizeof(DATE));
    pt->a = a;
    pt->next = p->next;
    p->next = pt;
    return pt;
}

int count;
PDATE del(PDATE p0) {
    if (!count) {
        printf("\n");
        count = 10;
    }
    printf("%d ", p0->a);
    PDATE p = p0->next;
    p0->a = p->a;
    p0->next = p->next;
    free(p);
    count--;
    return p0;
}

int main() {
    count = 10;
    int n = 0, k = 0, m = 0;
    scanf("%d,%d,%d", &n, &m, &k);
    if (!(n > 0 && m > 0 && k > 0))
        printf("n,m,k must bigger than 0.\n");
    else if (m > n)
        printf("k should not bigger than n.\n");
    else {
        PDATE p = NULL;
        PDATE head = (DATE*)malloc(sizeof(DATE));
        head->next = head;
        head->a = 1;
        p = head;
        for (int i = 2; i <= n; i++) p = setnew(p, i);
        while (p->a != m) p = p->next;
        while (n) {
            //	int temp=k;
            int temp = k % n + n;
            while (--temp) p = p->next;
            del(p);
            n--;
        }
        printf("\n");
    }
}

#ifdef __cplusplus
}
#endif