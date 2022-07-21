//
// 2.cpp
// Created by AUGUS on 2022/7/18.
//

#include <utils.h>

namespace leetcode {
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        auto *res = new ListNode(0);
        ListNode *p1 = l1, *p2 = l2, *p3 = res;
        auto carry = 0;
        while (p1 || p2) {
            if (p1) {
                carry += p1->val;
                p1 = p1->next;
            }
            if (p2) {
                carry += p2->val;
                p2 = p2->next;
            }
            p3->next = new ListNode(carry % 10);
            p3 = p3->next;
            carry /= 10;
        }

        if (carry == 1) {
            p3->next = new ListNode(1);
        }

        return res->next;
    }
}

int main() { return 1; }