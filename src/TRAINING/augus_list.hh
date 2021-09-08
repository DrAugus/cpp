//
// Created by AUGUS on 2021/8/28.
//

#ifndef AUGUS_CPP_AUGUS_LIST_HH
#define AUGUS_CPP_AUGUS_LIST_HH

#include <memory>
#include <vector>

namespace augus_list {
    class ListSort;

    using ListSortSptr = std::shared_ptr<ListSort>;

    struct ListNode {
        int val;
        ListNode *next;

        explicit ListNode(int x) : val(x), next(nullptr) {}
    };

    class ListSort : public std::enable_shared_from_this<ListSort> {
    public:
        static ListSortSptr instance();

        //插入排序（算法中是直接交换节点，时间复杂度O（n^2）,空间复杂度O（1））
        ListNode *insertionSortList(ListNode *head) {
            // IMPORTANT: Please reset any member data you declared, as
            // the same Solution instance will be reused for each test case.
            if (head == nullptr || head->next == nullptr)return head;
            ListNode *p = head->next, *pstart = new ListNode(0), *pend = head;
            pstart->next = head; //为了操作方便，添加一个头结点
            while (p != nullptr) {
                ListNode *tmp = pstart->next, *pre = pstart;
                while (tmp != p && p->val >= tmp->val) //找到插入位置
                {
                    tmp = tmp->next;
                    pre = pre->next;
                }
                if (tmp == p)pend = p;
                else {
                    pend->next = p->next;
                    p->next = tmp;
                    pre->next = p;
                }
                p = pend->next;
            }
            head = pstart->next;
            delete pstart;
            return head;
        }

        //选择排序（算法中只是交换节点的val值，时间复杂度O（n^2）,空间复杂度O（1））
        ListNode *selectSortList(ListNode *head) {
            // IMPORTANT: Please reset any member data you declared, as
            // the same Solution instance will be reused for each test case.
            //选择排序
            if (head == nullptr || head->next == nullptr)return head;
            ListNode *pstart = new ListNode(0);
            pstart->next = head; //为了操作方便，添加一个头结点
            ListNode *sortedTail = pstart;//指向已排好序的部分的尾部

            while (sortedTail->next != nullptr) {
                ListNode *minNode = sortedTail->next, *p = sortedTail->next->next;
                //寻找未排序部分的最小节点
                while (p != nullptr) {
                    if (p->val < minNode->val)
                        minNode = p;
                    p = p->next;
                }
                std::swap(minNode->val, sortedTail->next->val);
                sortedTail = sortedTail->next;
            }

            head = pstart->next;
            delete pstart;
            return head;
        }



        //归并排序（算法交换链表节点，时间复杂度O（nlogn）,不考虑递归栈空间的话空间复杂度是O（1））
        //
        //首先用快慢指针的方法找到链表中间节点，然后递归的对两个子链表排序，把两个排好序的子链表合并成一条有序的链表。归并排序应该算是链表排序最佳的选择了，保证了最好和最坏时间复杂度都是nlogn，而且它在数组排序中广受诟病的空间复杂度在链表排序中也从O(n)降到了O(1)
        ListNode *mergeSortList(ListNode *head) {
            // IMPORTANT: Please reset any member data you declared, as
            // the same Solution instance will be reused for each test case.
            //链表归并排序
            if(head == NULL || head->next == NULL)return head;
            else
            {
                //快慢指针找到中间节点
                ListNode *fast = head,*slow = head;
                while(fast->next != NULL && fast->next->next != NULL)
                {
                    fast = fast->next->next;
                    slow = slow->next;
                }
                fast = slow;
                slow = slow->next;
                fast->next = NULL;
//                fast = sortList(head);//前半段排序
//                slow = sortList(slow);//后半段排序
                return merge(fast,slow);
            }

        }
        // merge two sorted list to one
        ListNode *merge(ListNode *head1, ListNode *head2)
        {
            if(head1 == NULL)return head2;
            if(head2 == NULL)return head1;
            ListNode *res , *p ;
            if(head1->val < head2->val)
            {res = head1; head1 = head1->next;}
            else{res = head2; head2 = head2->next;}
            p = res;

            while(head1 != NULL && head2 != NULL)
            {
                if(head1->val < head2->val)
                {
                    p->next = head1;
                    head1 = head1->next;
                }
                else
                {
                    p->next = head2;
                    head2 = head2->next;
                }
                p = p->next;
            }
            if(head1 != NULL)p->next = head1;
            else if(head2 != NULL)p->next = head2;
            return res;
        }




        //冒泡排序（算法交换链表节点val值，时间复杂度O（n^2）,空间复杂度O（1））
        ListNode *bubbleSortList(ListNode *head) {
            // IMPORTANT: Please reset any member data you declared, as
            // the same Solution instance will be reused for each test case.
            //链表快速排序
            if(head == NULL || head->next == NULL)return head;
            ListNode *p = NULL;
            bool isChange = true;
            while(p != head->next && isChange)
            {
                ListNode *q = head;
                isChange = false;//标志当前这一轮中又没有发生元素交换，如果没有则表示数组已经有序
                for(; q->next && q->next != p; q = q->next)
                {
                    if(q->val > q->next->val)
                    {
                        std::swap(q->val, q->next->val);
                        isChange = true;
                    }
                }
                p = q;
            }
            return head;
        }

        //对于希尔排序，因为排序过程中经常涉及到arr[i+gap]操作，其中gap为希尔排序的当前步长，这种操作不适合链表。
        //
        //对于堆排序，一般是用数组来实现二叉堆，当然可以用二叉树来实现，但是这么做太麻烦，还得花费额外的空间构建二叉树
    };
}


#endif //AUGUS_CPP_AUGUS_LIST_HH
