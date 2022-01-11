//
// Created by AUGUS on 2021/3/9.
//

#include "for_training.hh"

basic_cpp::ComplexDefine::ComplexDefine()
{
    void *( *(*fp1)(int))[10];
    float (*(*fp2)(int, int, int))(int);
    //int (*( *fp355)())[10]();
    int id[sizeof(unsigned long)];
}

basic_cpp::ComplexDefine::~ComplexDefine() = default;

basic_cpp::OPChar::OPChar()
{
    char str1[] = "abc";
    char str2[] = "abc";
    const char str3[] = "abc";
    const char str4[] = "abc";
    const char *str5 = "abc";
    const char *str6 = "abc";
    char *str7 = "abc";
    char *str8 = "abc";
    std::cout << (str1 == str2) << std::endl;
    std::cout << (str3 == str4) << std::endl;
    std::cout << (str5 == str6) << std::endl;
    std::cout << (str7 == str8) << std::endl;
}

int basic_cpp::OPChar::opWchar()
{
    wchar_t szName1[16] = {'1', '2', '3', '4', '5', '7', '7'},
        szName2[16] = {'1', '2', '3', '4', '5'};
    auto res = wcscmp(szName2, szName1);
    std::cout << "compare res " << res << std::endl;
    return 0;
}

basic_cpp::OPSwap::OPSwap(int *a, int *b)
{
    for (auto i = 0; i < 5; i++) {
        std::swap(*(a + i), *(b + i));
    }
}

int basic_cpp::OPSwap::test()
{
    int a0929[] = {0, 1, 3, 5, 8},
        b0929[] = {2, 4, 9, 12, 31};
    OPSwap(a0929, b0929);
    return 0;
}

int basic_cpp::SomeSort::libFuc()
{
    int a[20] = {2, 4, 1, 1, 2, 23, 5, 76, 0, 43, 24, 65}, i;
    for (i = 0; i < 20; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
    sort(a, a + 20, std::greater_equal<int>());
    for (i = 0; i < 20; i++) {
        std::cout << a[i] << " ";
    }
    return 0;
}

int sizeof_val::test()
{
    std::cout << "sizeof test\n";

    std::cout << "sizeof string " << sizeof(std::string) << std::endl;
    std::cout << "sizeof long double " << sizeof(long double) << std::endl;
    std::cout << "sizeof double " << sizeof(double) << std::endl;
    std::cout << "sizeof size_t " << sizeof(size_t) << std::endl;
    std::cout << "sizeof float " << sizeof(float) << std::endl;
    std::cout << "sizeof unsigned " << sizeof(unsigned) << std::endl;
    std::cout << "sizeof short " << sizeof(short) << std::endl;
    std::cout << "sizeof wchar_t " << sizeof(wchar_t) << std::endl;

    std::cout << "sizeof long long " << sizeof(long long) << std::endl;
    std::cout << "sizeof long " << sizeof(long) << std::endl;
    std::cout << "sizeof int " << sizeof(int) << std::endl;
    std::cout << "sizeof bool " << sizeof(bool) << std::endl;
    std::cout << "sizeof char " << sizeof(char) << std::endl;

    std::cout << "sizeof unsigned long long " << sizeof(unsigned long long) << std::endl;
    std::cout << "sizeof unsigned long " << sizeof(unsigned long) << std::endl;
    std::cout << "sizeof unsigned int " << sizeof(unsigned int) << std::endl;
    std::cout << "sizeof unsigned char " << sizeof(unsigned char) << std::endl;

    auto f_lam = [](int a) -> int { return a + 1; };
    std::cout << "sizeof f_lam " << sizeof(f_lam) << std::endl;
    return 0;
}


bool op_list::op_array::Duplicate::isContainsDuplicate(const std::vector<int> &v)
{
    std::unordered_set<int> s(v.size() * 2);
    for (auto x : v) {
        if (!s.insert(x).second) {    /// insert failed -> repeat insert，conclude have duplicate
            return true;
        }
    }
    return false;
}

int op_list::op_array::Duplicate::findDuplicateElements(int *arr, int length, std::set<int> s, std::vector<int> &output)
{
    if (arr == nullptr || length <= 0) {
        ///数组为空
        return -1;
    }
    for (int i = 0; i < length; i++) {
        /// 为什么要让 arr[i] > length - 1 ?????
        if (arr[i] < 0 /*|| arr[i] > length - 1*/) {
            ///输入数据超出范围
            return -1;
        }
    }
    std::sort(arr, arr + length);
    int k = 0, j = 0;
    ///拿数组中第k个位置和第j+1个位置的数据相比，只能是arr[k] <= arr[j + 1]
    while (k < length - 1 && j < length - 1) {
        ///arr[k] < arr[j + 1]的时候，只存在两种情况k == j或k < j
        if (arr[k] < arr[j + 1]) {
            if (k == j) {
                k++;
                j++;
            }
                ///k<j时，就让k+1
            else {
                k++;
            }
        }
            ///arr[k] = arr[j + 1],就把arr[k]插入到集合中，避免出现多次的数据重复出现
        else {
            ///重复数字为 arr[k]
            s.insert(arr[k]);
            j++;
        }
    }
    std::set<int>::iterator it;
    for (it = s.begin(); it != s.end(); it++)  ///使用迭代器对集合进行遍历
    {
        output.push_back(*it);
    }
    return 0;
}

int op_list::op_array::Duplicate::Test()
{
    /// Record 4 First to know set and Finding duplicate value. Duplicate times just using <count> method
    std::cout
        << "\nRecord 4 First to know set and Finding duplicate value. Duplicate times just using <count> method\n";
    std::set<int> set_temp;
    const int kDuplicateTemp[] = {6, 5, 12, 94, 12, 15, 15, 3, 6, 5, 5, 12, 12, 3, 1, 5, 3, 4, 3, 2, 7, 5};
    int duplicate_temp[] = {6, 5, 12, 94, 12, 15, 15, 3, 6, 5, 5, 12, 12, 3, 1, 5, 3, 4, 3, 2, 7, 5};
    std::vector<int> vec_output;
    findDuplicateElements(duplicate_temp, sizeof(duplicate_temp) / sizeof(duplicate_temp[0]), set_temp, vec_output);
    std::cout << "\niterator Traverse -> ";
    for (int &iter : vec_output) { /// auto -> std::vector<int>::iterator
        std::cout << iter << " ";
    }
    std::cout << std::endl;
    std::vector<int>
        vec_duplicate_temp(duplicate_temp, duplicate_temp + sizeof(duplicate_temp) / sizeof(duplicate_temp[0]));
    for (auto i : vec_output) {
        std::cout << "duplicate value <" << i << "> has "
                  << count(vec_duplicate_temp.begin(), vec_duplicate_temp.end(), i)
                  << " repeats" << std::endl;
    }

    return 0;
}


// 寻找元素在Vector的位置
int op_list::op_array::VectorCtrl::findPosVector(std::vector<int> input, int number)
{
    auto iter = find(input.begin(), input.end(), number);//返回的是一个迭代器指针
    if (iter == input.end()) {
        return -1;
    } else {
        return distance(input.begin(), iter);
    }
}

int op_list::op_array::VectorCtrl::findVectorSub()
{
    /// Record 5 finding subscript
    std::vector<int> vec_test2 = {5, 6, 8, 5, 4, 3, 2};
    std::cout << std::endl << "Record 5 Finding subscript in std::vector" << std::endl;
    std::vector<int> vecFind = vec_test2;
    const int findVal = 5;
    auto isFind = find(vecFind.begin(), vecFind.end(), findVal); /// auto -> std::vector<int>::iterator
    if (isFind != vecFind.end()) {
        std::cout << "I can find this value -> " << findVal << std::endl;
        int res = isFind - vecFind.begin();    ///res即是target在vector数组中的下标
        int indexBack = &*isFind - &vecFind[0];  ///other way
        std::cout << "  -> It's subscript is " << res << std::endl;
        std::cout << "  -> Other way find the subscript is " << indexBack << std::endl;
    } else {
        std::cout << "I can't find this value -> " << findVal << std::endl;
    }
    vecFind.at(25);
    vecFind.at(5);
    return 0;
}

//容器vector中元素的去重
std::vector<int> op_list::op_array::VectorCtrl::unique_element_in_vector(std::vector<int> v)
{
    std::vector<int>::iterator vector_iterator;
    sort(v.begin(), v.end());
    vector_iterator = unique(v.begin(), v.end());
    if (vector_iterator != v.end()) {
        v.erase(vector_iterator, v.end());
    }
    return v;
}

//两个vector求交集
std::vector<int> op_list::op_array::VectorCtrl::vectors_intersection(std::vector<int> v1, std::vector<int> v2)
{
    std::vector<int> v;
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v));//求交集
    return v;
}

//两个vector求并集
std::vector<int> op_list::op_array::VectorCtrl::vectors_set_union(std::vector<int> v1, std::vector<int> v2)
{
    std::vector<int> v;
    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());
    set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v));//求交集
    return v;
}


op_list::op_array::ArrayLength::ArrayLength()
{
    /// Record 2 Compute Array Length
    /// array length Two-dimensional array
    std::cout << std::endl << "Record 2 Compute Array Length" << std::endl;
    int two_dimensional_array[3][5] = {0};
    int len = sizeof(two_dimensional_array) / sizeof(int);
    int second_dimension_length = sizeof(two_dimensional_array[0]) / sizeof(two_dimensional_array[0][0]);
    int first_dimension_length = len / second_dimension_length;
    /// 不要想着去在二维数组入参的时候求长度，能求出来个锤子？？？
    /// 二维数组寻址方式
    /// 对于数组 int p[m][n];
    /// 如果要取 p[i][j] 的值（i>=0 && m<=0 && j>=0 && n<=0)，编译器是这样寻址的，它的地址为：
    ///     p + i*n + j;
    /// 所以不能省略第二维，省去编译器将不知道如何正确的寻址
    std::cout << "This array -> First dimension length is " << first_dimension_length <<
              ", Second dimension length is " << second_dimension_length << std::endl;

}

int op_list::op_array::LC::pivotIndex(std::vector<int> &nums)
{
    if (nums.empty()) { return -1; }
    int sumL = 0, sumR = 0;
    for (auto val : nums) {
        sumR += val;
    }
    for (auto i = 0; i < nums.size(); i++) {
        if (i - 1 >= 0) { sumL += nums[i - 1]; }
        sumR -= nums[i];
        if (sumR == sumL) { return i; }
    }
    return -1;
}

int op_list::op_array::LC::searchInsert(std::vector<int> &nums, int target)
{
    if (nums.empty()) { return 0; }
    int res = 0;
    for (auto i = 0; i < nums.size(); i++) {
        if (target == nums[i]) { return i; }
        if (target > nums[i]) { res = i + 1; }
    }
    return res;
}

void op_list::op_array::LC::rotate(std::vector<std::vector<int>> &matrix)
{
    //上下翻转
    for (auto i = 0; i < matrix.size() / 2; i++) {
        for (auto j = 0; j < matrix.size(); j++) {
            std::swap(matrix[i][j], matrix[matrix.size() - 1 - i][j]);
        }
    }
    //对角翻转
    for (auto i = 0; i < matrix.size(); i++) {
        for (auto j = 0; j <= i; j++) {
            std::swap(matrix[i][j], matrix[j][i]);
        }
    }
}

void op_list::op_array::LC::setZeroes(std::vector<std::vector<int>> &matrix)
{
    int M = matrix.size(), N = matrix[0].size();
    std::vector<int> A, B;
    for (auto i = 0; i < M; i++) {
        for (auto j = 0; j < N; j++) {
            if (!matrix[i][j]) {
                A.push_back(i);
                B.push_back(j);
            }
        }
    }
    for (auto a : A) {
        for (auto j = 0; j < N; j++) {
            matrix[a][j] = 0;
        }
    }
    for (auto b : B) {
        for (auto i = 0; i < M; i++) {
            matrix[i][b] = 0;
        }
    }
}

std::string op_list::op_array::LC::longestCommonPrefix(std::vector<std::string> &strs)
{
    if (strs.empty()) { return ""; }
    std::string res;
    for (int i = 0; i < strs[0].size(); i++) {
        auto s = strs[0][i];
        res += s;
        for (auto subStr : strs) {
            if (subStr[i] != s) {
                res.erase(res.size() - 1);
                return res;
            }
        }
    }
    return res;
}

void op_list::op_array::LC::test()
{
    std::vector<std::string> as = {"flower", "flow", "flight"};
    std::string s = longestCommonPrefix(as);
    std::string s2 = s;
}

std::vector<int> op_list::op_array::mergeTest(std::vector<int> &nums1, unsigned m, std::vector<int> &nums2, unsigned n)
{
    std::vector<int> res(m + n);
    unsigned p1 = m - 1, p2 = n - 1, p = m + n - 1;
    while ((p1 >= 0) && (p2 >= 0)) {
        res[p--] = (nums1[p1] > nums2[p2]) ? nums1[p1--] : nums2[p2--];
    }
    while (p1 >= 0) {
        res[p--] = nums1[p1--];
    }
    while (p2 >= 0) {
        res[p--] = nums2[p2--];
    }
    return res;
}

int op_list::op_array::findMaxInArray()
{
    std::vector<int> v{6, 54, 31, 62, 23, 46, 89, 8};
    auto biggest = max_element(begin(v), end(v));
    ///or std::vector<int>::iterator biggest = max_element(v.begin(), v.end);
    std::cout << "Max element is " << *biggest << " at position " << distance(begin(v), biggest) << std::endl;
    ///另一方面，取最大位置也可以这样来写：
    ///int nPos = (int)(max_element(v.begin(), v.end()) - (v.begin());
    ///效果和采用distance(...)函数效果一致
    ///说明：max_element(v.begin(), v.end()) 返回的是vector<int>::iterator,
    ///相当于指针的位置，减去初始指针的位置结果即为最大值得索引。
    auto smallest = min_element(begin(v), end(v));
    std::cout << "min element is " << *smallest << " at position " << distance(begin(v), smallest) << std::endl;
    ///对于普通数组
    ///总体实现：（索引值是通过计算数组的起始地址和最大值或最小值的地址之间距离的来计算的）
    int TempArr[] = {2, 3, 1, 6, 7, 3};
    ///求数组最大值以及最大值的索引
    std::cout << "Max element: " << *std::max_element(TempArr, TempArr + sizeof(TempArr) / sizeof(TempArr[0])) << "\n";
    std::cout << "Max element location: " <<
              std::distance(TempArr, std::max_element(TempArr, TempArr + sizeof(TempArr) / sizeof(TempArr[0]))) << "\n";
    ///求数组最小值以及最小值的索引
    std::cout << "Min element: " << *std::min_element(TempArr, TempArr + sizeof(TempArr) / sizeof(TempArr[0])) << "\n";
    std::cout << "Min element location: " <<
              std::distance(TempArr, std::min_element(TempArr, TempArr + sizeof(TempArr) / sizeof(TempArr[0]))) << "\n";
    ///求数组的和
    std::valarray<int> ValTempArr(TempArr, sizeof(TempArr) / sizeof(TempArr[0]));
    std::cout << ValTempArr.sum();

    return 0;
}

int op_list::op_array::commonVectorOP()
{
    std::cout << std::endl;
    std::cout << "BELOW ARE VECTOR COMMON OPERATE ->\n";
    std::cout << "vec_test1 source->";
    std::vector<int> vec_test1 = {0, 1, 2, 5, 6, 9, 8, 2, 0, 7, 55, 24, 3};

    auto begin = vec_test1.begin(), end = vec_test1.end();
    while (begin != end) {
        *begin = 0;
        ++begin;
    }


    augus::printTest(vec_test1);
    /// case 1 copy
    const std::vector<int> &vec_test2 = vec_test1;
    std::cout << "case 1 copy -> vec_test2 copy from vec_test1";
    augus::printTest(vec_test2);
    /// case 2 copy
    std::vector<int> vec_test3(vec_test1);
    std::cout << "case 2 copy -> vec_test3 copy from vec_test1";
    augus::printTest(vec_test3);
    /// std::swap vec
    std::vector<int> vec_test4 = {0, 1, 2, 5, 6, 9, 8, 2, 0, 7};
    /// clear vec_test4
    std::cout << "vec_test4 clear before->";
    augus::printTest(vec_test4);
    std::vector<int>().swap(vec_test4);
    std::cout << "vec_test4 cleared";
    augus::printTest(vec_test4);
    std::vector<int> vec_test5 = {0, 1, 2, 5, 6,};
    std::cout << "vec_test5 source->";
    augus::printTest(vec_test5);
    vec_test5.swap(vec_test1);
    std::cout << "std::swap vec_test5 vec_test1-> Now vec_test5";
    augus::printTest(vec_test5);
    /// assign
    std::vector<int> vec_test6 = {0, 1, 2, 5, 6, 8, 56};
    std::cout << "vec_test6 source";
    augus::printTest(vec_test6);
    std::cout << "vec_test6 assign vec_test1";
    vec_test6.assign(vec_test1.begin(), vec_test1.end());
    augus::printTest(vec_test6);
    std::cout << "vec_test6 set 3 0s";
    vec_test6.assign(3, 0);
    augus::printTest(vec_test6);
    /// concat std::vector
    int arr_test0817[][13] = {
        {0, 1, 2, 5, 6, 9, 8, 2, 0, 7, 55, 24, 3},
        {5, 1, 2, 5, 6, 9, 8, 2, 0, 7, 55, 24, 3},
        {21, 1, 2, 5, 6, 9, 8, 2, 0, 7, 55, 24, 3},
    };
    std::vector<int> vec_res0817;
    for (auto &i : arr_test0817) {
        vec_res0817.insert(vec_res0817.end(), i, i + 13);
    }
    std::cout << "vec_res0817";
    augus::printTest(vec_res0817);

    return 0;
}

int op_list::op_array::switchArr2Vec()
{
    /// Record 3 Switch Arr to Vec
    std::cout << std::endl << "Record 3 Switch Arr to Vec" << std::endl;
    int hand_card[] = {0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x18,
                       0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x4E, 0x4F, 0x05, 0x08, 0x09, 0x0A, 0x0B};
    const int kCountPutBack = 8;
    std::vector<int> vec_hand_card(hand_card, hand_card + sizeof(hand_card) / sizeof(hand_card[0]));
    /// sort
    sort(vec_hand_card.begin(), vec_hand_card.end()); /// Ascend
    sort(vec_hand_card.rbegin(), vec_hand_card.rend());  /// Descend
    reverse(vec_hand_card.rbegin(), vec_hand_card.rend());  ///change to back
    std::vector<int> vec_put_back_card;
    vec_put_back_card.reserve(kCountPutBack);
    for (int i = 0; i < kCountPutBack; i++) {
        vec_put_back_card.push_back(vec_hand_card[i]);
    }

//  int *put_back_card = new int[8];
    int put_back_card[kCountPutBack];
    if (!vec_put_back_card.empty()) {
        memcpy(put_back_card,
               &vec_put_back_card[0],
               vec_put_back_card.size() * sizeof(vec_put_back_card[0])); /// copy all
        memcpy(put_back_card, &vec_put_back_card[5], kCountPutBack - 5);  /// copy last 3
        memcpy(put_back_card, &vec_put_back_card[0], 3);  /// copy first 3
    }
    std::cout << "smallest back card is \n";
    for (auto i : put_back_card) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}

//[1,2,2,3,1,4,2]
int op_list::op_array::findShortestSubArray(std::vector<int> &nums)
{
    std::map<int, std::vector<int>> NumPos;
    for (int i = 0; i < nums.size(); ++i) {
        auto it2 = NumPos.find(nums[i]);
        if (it2 != NumPos.end()) {
            it2->second.push_back(i);
        } else {
            NumPos.insert(std::pair<int, std::vector<int>>(nums[i], {i}));
        }
    }
    std::vector<int> MaxCount;
    for (auto it = NumPos.begin(); it != NumPos.end(); ++it) {
        if (MaxCount.empty()) {
            MaxCount.push_back(it->first);
        } else {
            if (NumPos[MaxCount[0]].size() == NumPos[it->first].size()) {
                MaxCount.push_back(it->first);
            } else {
                if (NumPos[MaxCount[0]].size() < NumPos[it->first].size()) {
                    MaxCount.clear();
                    MaxCount.push_back(it->first);
                }
            }
        }
    }
    int Min = 50000;
    for (int &i : MaxCount) {
        auto V = NumPos[i];
        int Dis = V[V.size() - 1] - V[0];
        Min = std::min(Min, Dis);
    }
    return Min + 1;
}

int op_list::commonOP()
{
    int valueInitial[13] = {
        0x2b, 0x2a, 0x29,
        0x19, 0x18, 0x1a, 0x1b, 0x1c,
        0x06, 0x05, 0x04, 0x03, 0x02
    };
    /// list 使用
    std::cout << "list exercise" << std::endl;
    std::list<int> list(valueInitial, valueInitial + 13);
    auto listBegin = list.begin();
    for (int i = 0; i < 12; i++) {
        ++listBegin;
    }
    std::cout << *(listBegin) << std::endl;
    std::cout << "there is the copy nature?" << std::endl;
    int test09093[13] = {0};
    for (int i = 0; i < 13; i++) {
        *(test09093 + i) = *(valueInitial + i);
    }
    for (int i : test09093) {
        std::cout << i << " ";
    }
    std::vector<int> test09091221(valueInitial, valueInitial + 13);
    augus::printTest(test09091221);
    std::cout << "\nWHICH ONE\n";
    std::vector<int> test09091222(&valueInitial[0], &valueInitial[0] + 13);
    test09091222.capacity();
    std::vector<int>().swap(test09091222);
    int count_del = 4;
    int cbCardData[50] = {0};
    if (!test09091222.empty()) {
        memcpy(cbCardData, &test09091222[0], 50 - count_del);
    }
    augus::printTest(test09091222);

    return 0;
}


using BINARY_TREE_BASIC_OP = binary_tree::BinaryTree;

void BINARY_TREE_BASIC_OP::preOrderRecur(TreeNode *head)
{
    if (head == nullptr) {
        return;
    }
    std::cout << head->value << ",";
    preOrderRecur(head->left);
    preOrderRecur(head->right);
}

void BINARY_TREE_BASIC_OP::inOrderRecur(TreeNode *head)
{
    if (head == nullptr) {
        return;
    }
    inOrderRecur(head->left);
    std::cout << head->value << ",";
    inOrderRecur(head->right);
}

void BINARY_TREE_BASIC_OP::posOrderRecur(TreeNode *head)
{
    if (head == nullptr) {
        return;
    }
    posOrderRecur(head->left);
    posOrderRecur(head->right);
    std::cout << head->value << ",";
}

void BINARY_TREE_BASIC_OP::preOrderUnRecur(TreeNode *head)
{
    if (head == nullptr) {
        return;
    }
    std::stack<TreeNode *> nstack;
    nstack.push(head);
    while (!nstack.empty()) {
        TreeNode *head = nstack.top();  // get std::stack top
        std::cout << head->value << ",";
        nstack.pop();
        if (head->right != nullptr) {
            nstack.push(head->right);
        }
        if (head->left != nullptr) {
            nstack.push(head->left);
        }
    }
}

void BINARY_TREE_BASIC_OP::inOrderUnRecur(TreeNode *head)
{
    if (head == nullptr) {
        return;
    }
    std::stack<TreeNode *> nstack;
    while (!nstack.empty() || head != nullptr) {
        if (head != nullptr) {
            nstack.push(head);
            head = head->left;
        } else {
            head = nstack.top();
            std::cout << head->value << ",";
            nstack.pop();
            head = head->right;
        }
    }
}

void BINARY_TREE_BASIC_OP::posOrderUnRecur(TreeNode *head)
{
    if (head == nullptr) {
        return;
    }
    std::stack<TreeNode *> nstack1, nstack2;
    nstack1.push(head);
    while (!nstack1.empty()) {
        TreeNode *head = nstack1.top();
        nstack2.push(head);
        nstack1.pop();
        if (head->left != nullptr) {
            nstack1.push(head->left);
        }
        if (head->right != nullptr) {
            nstack1.push(head->right);
        }
    }

    while (!nstack2.empty()) {
        std::cout << nstack2.top()->value << ",";
        nstack2.pop();
    }
}

int BINARY_TREE_BASIC_OP::test()
{
    BinaryTree BinaryTree;

    auto *head = new TreeNode(5);
    head->left = new TreeNode(3);
    head->right = new TreeNode(8);
    head->left->left = new TreeNode(2);
    head->left->right = new TreeNode(4);
    head->right->left = new TreeNode(7);
    head->right->right = new TreeNode(10);
    head->right->left->left = new TreeNode(6);
    head->right->right->left = new TreeNode(9);
    head->right->right->right = new TreeNode(11);

    std::cout << "==============recursive==============";
    std::cout << "\npre-order: ";
    BinaryTree.preOrderRecur(head);
    std::cout << "\nin-order: ";
    BinaryTree.inOrderRecur(head);
    std::cout << "\npos-order: ";
    BinaryTree.posOrderRecur(head);
    std::cout << "\n==============un-recursive==============";
    std::cout << "\npre-order: ";
    BinaryTree.preOrderUnRecur(head);
    std::cout << "\nin-order: ";
    BinaryTree.inOrderUnRecur(head);
    std::cout << "\npos-order: ";
    BinaryTree.posOrderUnRecur(head);
    return 0;
}

//Permutation and Combination
namespace combination {
void Cij(int i,
         int j,
         std::vector<int> &r,
         int num,
         std::vector<std::vector<int> > &result)
{
    //排列组合公式Cij
    //std::cout << n << ' ' << i << ' ' << j << std::endl;
    if (j == 1) {
        for (int k = 0; k < i; k++) {
            std::vector<int> temp(num);
            r[num - 1] = k;
            for (int i = 0; i < num; i++) {
                temp[i] = r[i];
                //std::cout << r[i] << ' ';
            }
            result.push_back(temp);
            //std::cout << std::endl;
        }
    } else if (j == 0) {
        //do nothing!
    } else {
        for (int k = i; k >= j; k--) {
            r[j - 2] = k - 1;
            Cij(k - 1, j - 1, r, num, result);
        }
    }
}

std::vector<std::string> &
combination(std::vector<std::string> &res, const size_t &choose, std::string &working, const size_t &pos)
{
    if (choose > working.size() - pos) { return res; }
    for (size_t i = pos; i != working.size(); ++i) {
        working[i] = '0';
    }
    if (choose == 0 || pos == working.size()) {
        res.push_back(working);
        return res;
    }
    working[pos] = '1';
    combination(res, choose - 1, working, pos + 1);
    working[pos] = '0';
    combination(res, choose, working, pos + 1);
    return res;
}

int testCombination()
{
    //字符串打印组合
    std::vector<std::string> res;
    const size_t choose = 2;
    std::string working(4, '0');
    combination(res, choose, working, 0);
    for (size_t i = 0; i != res.size(); ++i) {
        std::cout << res[i] << '\t';
        for (size_t j = 0; j != working.size(); ++j) {
            if (res[i][j] == '1') {
                std::cout << j + 1 << ' ';
            }
        }
        std::cout << std::endl;
    }
    return 0;
}

}//namespace combination

namespace lambda_learning {
void lambda_learning()
{
    /// lambda 表达式的价值在于，就地封装短小的功能闭包，可以极其方便地表达出我们希望执行的具体操作，并让上下文结合得更加紧密。
    /// lambda 表达式的类型在 C++11 中被称为“闭包类型（Closure Type）”。它是一个特殊的，匿名的非 union 的类类型。
    //////lambda表达式有如下优点：
    /// 声明式编程风格：就地匿名定义目标函数或函数对象，不需要额外写一个命名函数或者函数对象。以更直接的方式去写程序，好的可读性和可维护性。
    /// 简洁：不需要额外再写一个函数或者函数对象，避免了代码膨胀和功能分散，让开发者更加集中精力在手边的问题，同时也获取了更高的生产率。
    /// 在需要的时间和地点实现功能闭包，使程序更灵活。
    //// 语法形式   [ capture ] ( params ) opt -> ret { body; };
    /// 其中 capture 是捕获列表，params 是参数表，opt 是函数选项，ret 是返回值类型，body是函数体。
    //// lambda 表达式还可以通过捕获列表捕获一定范围内的变量：
    /// [] 不捕获任何变量。
    /// [&] 捕获外部作用域中所有变量，并作为引用在函数体中使用（按引用捕获）。
    /// [=] 捕获外部作用域中所有变量，并作为副本在函数体中使用（按值捕获）。
    /// [=, &foo] 按值捕获外部作用域中所有变量，并按引用捕获 foo 变量。
    /// [bar] 按值捕获 bar 变量，同时不捕获其他变量。
    /// [this] 捕获当前类中的 this 指针，让 lambda 表达式拥有和当前类成员函数同样的访问权限。如果已经使用了 & 或者 =，就默认添加此选项。捕获 this 的目的是可以在 lambda 中使用当前类的成员函数和成员变量。
    std::cout << "\nLearningLambda TEST\n";
    /// Lambda表达式完整的声明格式如下：
    /// [capture list] (params list) mutable exception-> return type { function body }
    ///  各项具体含义如下
    /// capture list：捕获外部变量列表
    ///  params list：形参列表
    /// mutable指示符：用来说用是否可以修改捕获的变量
    ///  exception：异常设定
    /// return type：返回类型
    /// function body：函数体
    /// 此外，我们还可以省略其中的某些成分来声明“不完整”的Lambda表达式，常见的有以下几种：
    ///
    /// 1 [capture list] (params list) -> return type {function body}
    /// 2	[capture list] (params list) {function body}
    /// 3 [capture list] {function body}
    ///  其中：
    /// 格式1声明了const类型的表达式，这种类型的表达式不能修改捕获列表中的值。
    ///  格式2省略了返回值类型，但编译器可以根据以下规则推断出Lambda表达式的返回类型：
    ///     （1）：如果function body中存在return语句，则该Lambda表达式的返回类型由return语句的返回类型确定；
    ///     （2）：如果function body中没有return语句，则返回值为void类型。
    ///  格式3中省略了参数列表，类似普通函数中的无参函数。
    class Simple
    {
    public:
        static void func()
        {
            auto f = [](int a) -> int { return a + 1; };
            std::cout << "Simple \n - f(1): " << f(1) << std::endl;
            //// C++11 中会根据 return 语句自动推导出返回值类型
            auto y = [](int a) { return a + 1; };
            std::cout << " - y(1): " << y(1) << std::endl;
            /// 需要注意 -> 初始化列表不能用于返回值的自动推导
            auto x1 = [](int i) { return i; };  // OK: return type is int
            //  auto x2 = [](){ return { 1, 2 }; };  // error: 无法推导出返回值类型
            /// lambda 表达式在没有参数列表时，参数列表是可以省略的。因此像下面的写法都是正确的：
            auto y1 = []() { return 1; };
            auto y2 = [] { return 1; };  // 省略空参数表
            std::cout << " - x1(0): " << x1(0) << std::endl;
            std::cout << " - y1: " << y1 << std::endl;
            std::cout << " - y2: " << y2 << std::endl;
        }
    };

    Simple::func();
    class Example
    {
        /// lambda 表达式的捕获列表精细地控制了 lambda 表达式能够访问的外部变量，以及如何访问这些变量。
    public:
        int i_ = 0;

        void func(int x, int y)
        {
            //      auto x1 = [] { return i_; };                    // error，没有捕获外部变量
            auto x2 = [=] { return i_ + x + y; };           // OK，捕获所有外部变量
            auto x3 = [&] { return i_ + x + y; };           // OK，捕获所有外部变量
            auto x4 = [this] { return i_; };                // OK，捕获this指针
            //      auto x5 = [this] { return i_ + x + y; };        // error，没有捕获x、y
            auto x6 = [this, x, y] { return i_ + x + y; };  // OK，捕获this指针、x、y
            auto x7 = [this] { return i_++; };              // OK，捕获this指针，并修改成员的值
            std::cout << "Example\n -x2 -> " << x2() << std::endl
                      << " -x4 -> " << x4() << std::endl;
        }
    };
//  Example::func()
    Example ex;
    ex.i_ = 2;
    ex.func(3, 4);
    int a = 0, b = 1;
    //  auto f1 = [] { return a; };               // error，没有捕获外部变量
    auto f2 = [&] { return a++; };            // OK，捕获所有外部变量，并对a执行自加运算
    auto f3 = [=] { return a; };              // OK，捕获所有外部变量，并返回a
//  auto f4 = [=] { return a++; };            // error，a是以复制方式捕获的，无法修改
//  auto f5 = [a] { return a + b; };          // error，没有捕获变量b
    auto f6 = [a, &b] { return a + (b++); };  // OK，捕获a和b的引用，并对b做自加运算
    auto f7 = [=, &b] { return a + (b++); };  // OK，捕获所有外部变量和b的引用，并对b做自加运算
    /// 默认状态下 lambda 表达式无法修改通过复制方式捕获的外部变量。如果希望修改这些变量的话，我们需要使用引用方式进行捕获。

    //// 关于 lambda 表达式的延迟调用的
    class B
    {
    public:
        static void func()
        {
            int a = 0;
            auto f = [=] { return a; };      /// 按值捕获外部变量
            a += 1;                         /// a被修改了 ？当然没有
            std::cout << f() << std::endl;  /// 输出？
            /// lambda 表达式按值捕获了所有外部变量。在捕获的一瞬间，a 的值就已经被复制到f中了。之后 a 被修改，但此时 f 中存储的 a 仍然还是捕获时的值，因此，最终输出结果是 0。
            /// 希望 lambda 表达式在调用时能够即时访问外部变量，我们应当使用引用方式捕获。
            auto f2 = [&] { return a; };
            a += 1;
            std::cout << f2() << std::endl;
        }
    };
    B::func();
    /// WARNING 被 mutable 修饰的 lambda 表达式就算没有参数也要写明参数列表

    /// 闭包类型 Closure Type
    class Type
    {
    public:
        /// 可以认为它是一个带有 operator() 的类，即仿函数。因此，我们可以使用 function 和 bind 来存储和操作 lambda 表达式：
        std::function<int(int)> f1 = [](int a) { return a; };

        std::function<int(void)> f2 = std::bind([](int a) { return a; }, 123);
        /// 另外，对于没有捕获任何变量的 lambda 表达式，还可以被转换成一个普通的函数指针：
        using func_t = int (*)(int);

        func_t f = [](int a) { return a; };
    };
    Type Type;
    std::cout << "Type f -> " << Type.f(123) << std::endl;

    typedef void(*Ptr)(int *);
    Ptr p = [](int *p) { delete p; };  // 正确，没有状态的lambda（没有捕获）的lambda表达式可以直接转换为函数指针
//  Ptr p1 = [&](int* p){delete p;};  // 错误，有状态的lambda不能直接转换为函数指针
    std::vector<int> v = {1, 2, 3, 4, 5, 6};
    int even_count = 0;
    /// change to Lambda before
    class CountEven
    {
        int &count_;

    public:
        explicit CountEven(int &count) : count_(count) {}

        void operator()(int val)
        {
            if (!(val & 1)) {
                ++count_;
            }
        }
    };
    for_each(v.begin(), v.end(), CountEven(even_count));
    std::cout << "The number of even is " << even_count << std::endl;
    /// change to lambda
    even_count = 0;
    for_each(v.begin(), v.end(), [&even_count](int val) {
      if (!(val & 1)) { /// value % 2 == 0
          ++even_count;
      }
    });
    std::cout << "The number of even is " << even_count << std::endl;
//  sort(v.begin(), v.end(), [=](int a, int b) {
//    return b - a;
//  });
    sort(v.rbegin(), v.rend());
    for (auto i : v) {
        std::cout << i << std::endl;
    }
}

}//namespace lambda_learning

namespace dfs {
void dfs(int pos, int cnt, int n, int k, int a[], bool visited[])
{
    //已标记了k个数，输出结果
    if (cnt == k) {
        for (int i = 0; i < n; i++) {
            if (visited[i]) { std::cout << a[i] << ' '; }
        }
        std::cout << std::endl;
        return;
    }

    //处理到最后一个数，直接返回
    if (pos == n) { return; }

    //如果a[pos]没有被选中
    if (!visited[pos]) {
        //选中a[pos]
        visited[pos] = true;
        //处理在子串a[pos+1, n-1]中取出k-1个数的子问题
        dfs(pos + 1, cnt + 1, n, k, a, visited);
        //回溯
        visited[pos] = false;
    }
    //处理在子串a[pos+1, n-1]中取出k个数的问题
    dfs(pos + 1, cnt, n, k, a, visited);
}

int testDfs()
{
    int ii, n, k;
    while (std::cin >> n >> k, n || k) {
        int *a = new int[n];
        bool *visited = new bool[n];
        for (ii = 0; ii < n; ii++) {
            a[ii] = ii + 1;
            visited[ii] = false;
        }
        dfs(0, 0, n, k, a, visited);
        delete[] a;
        delete[] visited;
    }
    getchar();
    return 0;
}

} // namespace dfs


TEST(dontknow, whattest)
{
//    std::cin.get();
//    op_list::op_array::LC::test();
}

int primary_algorithms::pa_array::removeDuplicates(std::vector<int> &nums, double point)
{
    if (nums.empty()) { return 0; }
    int left = 0;
    unsigned len = nums.size();
    for (unsigned right = 1; right < len; ++right) {
        if (nums[right] != nums[left]) {
            nums[++left] = nums[right];
        }
    }
    return ++left;
}

int primary_algorithms::pa_array::removeDuplicates(std::vector<int> &nums)
{
    if (nums.empty()) { return 0; }
    int count = 0;
    unsigned len = nums.size();
    for (unsigned right = 1; right < len; ++right) {
        if (nums[right] == nums[right - 1]) {
            count++;
        } else {
            nums[right - count] = nums[right];
        }
    }
    return len - count;
}

int primary_algorithms::pa_array::removeDuplicates(std::vector<int> &nums, bool)
{
    nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
    return nums.size();
}

TEST(pa_array, removeDuplicates_1)
{
    auto p = new primary_algorithms::pa_array;
    std::vector<int> arr = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    int res = p->removeDuplicates(arr);
    EXPECT_EQ(res, 5);
}

TEST(pa_array, removeDuplicates_2)
{
    auto p = new primary_algorithms::pa_array;
    std::vector<int> arr = {1, 1, 2};
    int res = p->removeDuplicates(arr);
    EXPECT_EQ(res, 2);
}


int primary_algorithms::pa_array::maxProfit(std::vector<int> &prices)
{
    if (prices.empty()) { return 0; }
    unsigned len = prices.size();
    int res = 0;
    for (unsigned i = 0; i < len - 1; ++i) {
        int d_value = prices[i + 1] - prices[i];
        if (d_value > 0) {
            res += d_value;
        }
    }
    return res;
}

TEST(pa_array, maxProfit_1)
{
    auto p = new primary_algorithms::pa_array;
    std::vector<int> t = {7, 1, 5, 3, 6, 4};
    int res = p->maxProfit(t);
    EXPECT_EQ(res, 7);
}


TEST(pa_array, maxProfit_2)
{
    auto p = new primary_algorithms::pa_array;
    std::vector<int> t = {1, 2, 3, 4, 5};
    int res = p->maxProfit(t);
    EXPECT_EQ(res, 4);
}

TEST(pa_array, maxProfit_3)
{
    auto p = new primary_algorithms::pa_array;
    std::vector<int> t = {7, 6, 4, 3, 1};
    int res = p->maxProfit(t);
    EXPECT_EQ(res, 0);
}

void primary_algorithms::pa_array::rotate(std::vector<int> &nums, int k)
{
    if (nums.empty()) { return; }
    int len = nums.size();
    if (len == 1) { return; }
    int kk = k % len;
    primary_algorithms::reverse_array(nums, 0, len - 1);
    primary_algorithms::reverse_array(nums, 0, kk - 1);
    primary_algorithms::reverse_array(nums, kk, len - 1);

    //执行用时：32 ms, 在所有C++提交中击败了54.04%的用户
    //内存消耗：24.4 MB, 在所有C++提交中击败了25.15%的用户
}

void primary_algorithms::pa_array::rotate(std::vector<int> &nums, int k, double other_array)
{
    if (nums.empty()) { return; }
    int len = nums.size();
    if (len == 1) { return; }
    std::vector<int> temp = nums;
    for (int i = 0; i < len; ++i) {
        nums[(i + k) % len] = temp[i];
    }

    //执行用时：48 ms, 在所有 C++ 提交中击败了7.76%的用户
    //内存消耗：25.1 MB, 在所有 C++ 提交中击败了7.06%的用户
}

void primary_algorithms::pa_array::rotate(std::vector<int> &nums, int k, bool use_stl)
{
    if (nums.empty()) { return; }
    int len = nums.size();
    if (len == 1) { return; }
    int kk = k % len;
    std::reverse(nums.rbegin(), nums.rend());
    std::reverse(nums.begin(), nums.begin() + kk);
    std::reverse(nums.begin() + kk, nums.end());

    //执行用时：36 ms, 在所有C++提交中击败了38.58%的用户
    //内存消耗：24.3 MB, 在所有C++提交中击败了48.88%的用户
}

TEST(pa_array, rotate_1)
{
    //checks that vector v is {5, 10, 15}
    //ASSERT_THAT(v, ElementsAre(5, 10, 15));

    //checks that map m only have elements 1 => 10, 2 => 20
    //ASSERT_THAT(m, ElementsAre(Pair(1, 10), Pair(2, 20)));

    //checks that in vector v all the elements are greater than 10 and less than 20
    //ASSERT_THAT(v, Each(AllOf(Gt(10), Lt(20))));

    //checks that vector v consist of
    //   5, number greater than 10, anything.
    //ASSERT_THAT(v, ElementsAre(5, Gt(10), _));

    //相同元素判定 不考虑顺序
    //EXPECT_TRUE(std::is_permutation(source.begin(), source.end(), t.begin()));

    auto p = new primary_algorithms::pa_array;
    std::vector<int> t = {1, 2, 3, 4, 5, 6, 7};
    int k = 3;
    p->rotate(t, k);
    ASSERT_THAT(t, testing::ElementsAre(5, 6, 7, 1, 2, 3, 4));
    t = {1, 2, 3, 4, 5, 6, 7};
    p->rotate(t, k, true);
    ASSERT_THAT(t, testing::ElementsAre(5, 6, 7, 1, 2, 3, 4));
    t = {1, 2, 3, 4, 5, 6, 7};
    p->rotate(t, k, 1.2);
    ASSERT_THAT(t, testing::ElementsAre(5, 6, 7, 1, 2, 3, 4));
}

TEST(pa_array, rotate_2)
{
    auto p = new primary_algorithms::pa_array;
    std::vector<int> t = {-1, -100, 3, 99};
    int k = 2;
    p->rotate(t, k);
    ASSERT_THAT(t, testing::ElementsAre(3, 99, -1, -100));
    t = {-1, -100, 3, 99};
    p->rotate(t, k, true);
    ASSERT_THAT(t, testing::ElementsAre(3, 99, -1, -100));
    t = {-1, -100, 3, 99};
    p->rotate(t, k, 1.3);
    ASSERT_THAT(t, testing::ElementsAre(3, 99, -1, -100));
}

TEST(pa_array, rotate_3)
{
    auto p = new primary_algorithms::pa_array;
    std::vector<int> t = {1, 2};
    int k = 3;
    p->rotate(t, k);
    ASSERT_THAT(t, testing::ElementsAre(2, 1));
    t = {1, 2};
    p->rotate(t, k, true);
    ASSERT_THAT(t, testing::ElementsAre(2, 1));
    t = {1, 2};
    p->rotate(t, k, 1.3);
    ASSERT_THAT(t, testing::ElementsAre(2, 1));
}

bool primary_algorithms::pa_array::containsDuplicate(std::vector<int> &nums)
{
    std::set<int> s;
    for (auto n : nums) {
        auto p = s.insert(n);
        if (!p.second) {
            return true;
        }
    }
    return false;

    //执行用时：56 ms, 在所有C++提交中击败了19.24%的用户
    //内存消耗：20.4 MB, 在所有C++提交中击败了14.56%的用户
}

bool primary_algorithms::pa_array::containsDuplicate(std::vector<int> &nums, bool use_stl)
{
    std::sort(nums.begin(), nums.end());
    return (std::unique(nums.begin(), nums.end()) != nums.end());

    //执行用时：28 ms, 在所有C++提交中击败了78.88%的用户
    //内存消耗：15.1 MB, 在所有C++提交中击败了85.08%的用户
}

TEST(pa_array, containsDuplicate_1)
{
    auto p = new primary_algorithms::pa_array;
    std::vector<int> t = {1, 1, 1, 3, 3, 4, 3, 2, 4, 2};
    bool res = p->containsDuplicate(t);
    EXPECT_TRUE(res);
    res = p->containsDuplicate(t, true);
    EXPECT_TRUE(res);
}

int primary_algorithms::pa_array::singleNumber(std::vector<int> &nums)
{
    int res = 0;
    for (auto n : nums) { res ^= n; }
    return res;

    //执行用时：20 ms, 在所有C++提交中击败了72.97%的用户
    //内存消耗：16.6 MB, 在所有C++提交中击败了19.50%的用户
}

int primary_algorithms::pa_array::singleNumber(std::vector<int> &nums, bool use_set)
{
    std::set<int> s;
    for (auto n : nums) {
        auto p = s.insert(n);
        if (!p.second) {
            s.erase(n);
        }
    }
    return *(s.begin());

    //执行用时：60 ms, 在所有C++提交中击败了5.12%的用户
    //内存消耗：20.1 MB, 在所有C++提交中击败了5.06%的用户
}

TEST(pa_array, singleNumber_1)
{
    auto p = new primary_algorithms::pa_array;
    std::vector<int> t = {4, 1, 2, 1, 2};
    int res = p->singleNumber(t);
    EXPECT_EQ(res, 4);
    res = p->singleNumber(t, true);
    EXPECT_EQ(res, 4);
}

TEST(pa_array, singleNumber_2)
{
    auto p = new primary_algorithms::pa_array;
    std::vector<int> t = {2, 2, 1};
    int res = p->singleNumber(t);
    EXPECT_EQ(res, 1);
    t = {2, 2, 1}; // t为什么在singleNumber_2用例中被修改，而singleNumber_1中未被修改
    res = p->singleNumber(t, true);
    EXPECT_EQ(res, 1);
}

std::vector<int> primary_algorithms::pa_array::intersect(std::vector<int> &nums1, std::vector<int> &nums2)
{
    return {};
}

std::vector<int> primary_algorithms::pa_array::intersect(std::vector<int> &nums1, std::vector<int> &nums2, bool use_stl)
{
    auto p = new op_list::op_array::VectorCtrl;
    return p->vectors_intersection(nums1, nums2);

    //执行用时：8 ms, 在所有C++提交中击败了55.26%的用户
    //内存消耗：9.8 MB, 在所有C++提交中击败了62.19%的用户
}

TEST(pa_array, intersect_1)
{
    auto p = new primary_algorithms::pa_array;
    std::vector<int> t1 = {1, 2, 2, 1},
        t2 = {2, 2};
    auto res = p->intersect(t1, t2);
    ASSERT_THAT(res, testing::ElementsAre(2, 2));
}

TEST(pa_array, intersect_2)
{
    auto p = new primary_algorithms::pa_array;
    std::vector<int> t1 = {4, 9, 5},
        t2 = {9, 4, 9, 8, 4};
    auto res = p->intersect(t1, t2);
    ASSERT_THAT(res, testing::ElementsAre(4, 9));
}


void primary_algorithms::reverse_array(std::vector<int> &nums, int begin, int end)
{
//    while (begin < end) {
//        int temp = nums[begin];
//        nums[begin++] = nums[end];
//        nums[end--] = temp;
//    }

    //stl也即这么交换的
    while (begin < end) {
        std::swap(nums[begin++], nums[end--]);
    }
}

void modern_cpp::usabilityEnhancements() {
    std::vector<int> vec = {1, 2, 3, 4};
    // 将临时变量放到 if 语句内
    if (const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 3); itr != vec.end()) {
        *itr = 4;
    }
}


std::tuple<int, double, std::string> modern_cpp::fTuple() {
    return std::make_tuple(1, 1.2, "nb");
}


TEST(fTuple, fTuple) {
    auto[x, y, z] = modern_cpp::fTuple();
    std::cout << x << " " << y << " " << z << std::endl;
}











