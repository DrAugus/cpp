//
// Created by AUGUS on 2021/8/9.
//

#ifndef AUGUS_CPP_PTR_HH
#define AUGUS_CPP_PTR_HH

#include <vector> // for std::vector
#include <iostream> // for std::cout
#include <fstream>
#include <valarray> // for std::valarray std::max_element std::min_element std::sort
#include <set> // for std::set
#include <string> // for memset
#include <map> // for std::map
#include <stack> // for std::stack
#include <memory>

#include "augus/augus.h"

namespace auto_ptr {

class Solution;

class Child;

class Parent;

class Solution
{
    Solution() = default;
    ~Solution() = default;
public:
    void merge1(std::vector<int> &nums1, int m, std::vector<int> &nums2, int n)
    {
        std::vector<int> array(m + n);
        int k = 0;
        int i = 0;
        int j = 0;
        while (i != m && j != n) {
            if (nums1[i] > nums2[j]) {
                array[k] = nums2[j];
                k++;
                j++;
            } else {
                array[k] = nums1[i];
                k++;
                i++;
            }
        }
        while (i < m) {
            array[k] = nums1[i];
            i++;
            k++;
        }
        while (j < n) {
            array[k] = nums2[j];
            j++;
            k++;
        }
        nums1.assign(array.begin(), array.end());
    }
public:
    void merge2(std::vector<int> &nums1, int m, std::vector<int> &nums2, int n)
    {
        int i = m - 1;
        int j = n - 1;
        int k = m + n - 1;
        while (i >= 0 && j >= 0) {
            if (nums1[i] > nums2[j]) {
                nums1[k] = nums1[i];
                k--;
                i--;
            } else {
                nums1[k] = nums2[j];
                k--;
                j--;
            }
        }
        while (i >= 0) {
            nums1[k] = nums1[i];
            k--;
            i--;
        }
        while (j >= 0) {
            nums1[k] = nums2[j];
            k--;
            j--;
        }
    }
};

class Parent
{
private:
    //std::shared_ptr<Child> ChildPtr;
    std::weak_ptr<Child> ChildPtr;
public:
    void setChild(std::shared_ptr<Child> child)
    {
        this->ChildPtr = child;
    }
    void doSomething()
    {
        //new shared_ptr
        if (this->ChildPtr.lock()) {

        }
    }
    ~Parent() = default;
};

class Child
{
private:
    std::shared_ptr<Parent> ParentPtr;

public:
    void setParent(std::shared_ptr<Parent> parent)
    {
        this->ParentPtr = parent;
    }

    void doSomething()
    {
        if (this->ParentPtr.use_count()) {

        }
    }

    ~Child() = default;
};

int test_shared_ptr();
int test_unique_ptr();
int test_weak_ptr();
int testAutoPtr();

}//namespace auto_ptr

#endif //AUGUS_CPP_PTR_HH
