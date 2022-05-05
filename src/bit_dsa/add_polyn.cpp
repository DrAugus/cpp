#include <cstdlib>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

struct date {
    int a;
    int b;
    struct date* pnext;
};
typedef struct date DATE;
typedef struct date* PDATE;

void output(PDATE p) {
    int f = 0;
    p = p->pnext;
    while (p != NULL) {
        if (p->a != 0) {
            f = 1;
            cout << "<" << p->a << "," << p->b << ">";
            if (p->pnext == NULL)
                cout << endl;
            else
                cout << ",";
        }
        p = p->pnext;
    }
    if (f == 0)
        cout << "<0,0>" << endl;
}

void add(PDATE a, PDATE b, PDATE c) {
    PDATE p1, p2, p3;
    p1 = a;
    p2 = b;
    p3 = c;
    if (p1 != NULL)
        p1 = p1->pnext;  // skip head
    if (p2 != NULL)
        p2 = p2->pnext;
    while ((p1 != NULL) && (p2 != NULL)) {
        if (p1->b > p2->b) {
            p3->pnext = (PDATE)malloc(sizeof(DATE));
            p3 = p3->pnext;
            p3->a = p2->a;
            p3->b = p2->b;
            p3->pnext = NULL;
            p2 = p2->pnext;
        } else if (p1->b < p2->b) {
            p3->pnext = (PDATE)malloc(sizeof(DATE));
            p3 = p3->pnext;
            p3->a = p1->a;
            p3->b = p1->b;
            p3->pnext = NULL;
            p1 = p1->pnext;
        } else {
            p3->pnext = (PDATE)malloc(sizeof(DATE));
            p3 = p3->pnext;
            p3->a = p1->a + p2->a;
            p3->b = p1->b;
            p3->pnext = NULL;
            p1 = p1->pnext;
            p2 = p2->pnext;
        }
    }  // end while

    if (p1 == NULL)
        p3->pnext = p2;
    if (p2 == NULL)
        p3->pnext = p1;
}

int main() {
    int flag;
    int n;
    PDATE P[6] = {NULL};
    PDATE p = NULL;
    for (int i = 0; i < 6; i++) {
        P[i] = (PDATE)malloc(sizeof(DATE));
        P[i]->a = 0;
        P[i]->b = 0;
        P[i]->pnext = NULL;
    }
    cin >> flag;
    if (flag == 1) {
        for (int i = 1; i < 4; i++) {
            p = P[i];
            cin >> n;
            while (n-- != 0) {
                p->pnext = (PDATE)malloc(sizeof(DATE));
                p = p->pnext;
                cin >> p->a >> p->b;
                p->pnext = NULL;
            }
            output(P[i]);
        }
    }
    add(P[1], P[2], P[4]);
    output(P[4]);
    add(P[4], P[3], P[5]);
    output(P[5]);
}
