//
// Created by Augus on 2020/6/6.
//

#include "training.hh"

using namespace leetcode;
using namespace codewars;

std::vector<int> TrainingTreeNode::preorderTraversal(TreeNode *root)
{
    if (root == nullptr) { return {}; }
    std::stack<TreeNode *> sTree;
    std::vector<int> res;
    TreeNode *p = root;
    while (p != nullptr || !sTree.empty()) {
        if (p) {
            res.push_back(p->value);
            sTree.push(p);
            p = p->left;
        } else {
            p = sTree.top();
            p = p->right;
            sTree.pop();
        }
    }
    return res;
}

std::vector<int> TrainingTreeNode::inorderTraversal(TreeNode *root)
{
    if (root == nullptr) { return {}; }
    std::stack<TreeNode *> sTree;
    std::vector<int> res;
    TreeNode *p = root;
    while (p != nullptr || !sTree.empty()) {
        if (p) {
            res.push_back(p->value);
            sTree.push(p);
            p = p->left;
        } else {
            p = sTree.top();
            p = p->right;
            sTree.pop();
        }
    }
    return res;
}

TreeNode *TrainingTreeNode::insertNode(TreeNode *root, int val)
{
    if (root == nullptr) {
        return new TreeNode(val);
    }

    if (val > root->value) {
        root->right = insertNode(root->right, val);
    } else if (val < root->value) {
        root->left = insertNode(root->left, val);
    } else {
        return root;
    }

    root->height = std::max(getHeight(root->left), getHeight(root->right)) + 1;

    int balance = getBalance(root);
    //LL型
    if (balance > 1 && val < root->left->value) {
        return ll_rotate(root);
    }
    //RR型
    if (balance < -1 && val > root->right->value) {
        return rr_rotate(root);
    }
    //LR型
    if (balance > 1 && val > root->left->value) {
        root->left = rr_rotate(root->left);
        return ll_rotate(root);
    }
    //RL型
    if (balance < -1 && val < root->right->value) {
        root->right = ll_rotate(root->right);
        return rr_rotate(root);
    }

    return root;
}

int TrainingTreeNode::getBalance(TreeNode *root)
{
    if (root == nullptr) { return 0; }
    return getHeight(root->left) - getHeight(root->right);
}

int TrainingTreeNode::getHeight(TreeNode *root)
{
    if (root == nullptr) { return 0; }
    return root->height;
}

TreeNode *TrainingTreeNode::ll_rotate(TreeNode *y)
{
    TreeNode *x = y->left;
    y->left = x->right;
    x->right = y;

    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}

TreeNode *TrainingTreeNode::rr_rotate(TreeNode *y)
{
    TreeNode *x = y->right;
    y->right = x->left;
    x->left = y;

    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}


int TrainingTreeNode::buildAVL()
{
    int root = 2;
    int configData[] = {1, 0, 3, 4, 5, 6, 9, 8, 7};
    auto *treeAVL = new TreeNode(root);
    for (int insertVal : configData) {
        insertNode(treeAVL, insertVal);
    }


    std::cout << "preorderTraversal ==== >";
    augus::PrintTest(preorderTraversal(treeAVL));
    std::cout << "inorderTraversal ==== >";
    augus::PrintTest(inorderTraversal(treeAVL));
    return 0;
}

LCSolution_sptr LCSolution::instance() {
    static LCSolution_sptr sptr = nullptr;
    if(sptr== nullptr){
        sptr = std::make_shared<LCSolution>();
    }
    return sptr;
}

std::vector<int> LCSolution::twoSum(std::vector<int> &nums, int target)
{
    std::unordered_map<int, int> map;
    for (int i = 0; i < nums.size(); i++) {
        auto iter = map.find(target - nums[i]);
        if (iter != map.end()) {
            return {iter->second, i};
        }
        map.insert(std::pair<int, int>(nums[i], i));
    }
    return {};
}

ListNode *LCSolution::addTwoNumbers(ListNode *l1, ListNode *l2)
{
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

    if (carry == 1) { p3->next = new ListNode(1); }

    return res->next;

}

int LCSolution::lengthOfLongestSubstring(std::string s)
{
    std::stack<int> temp;
    return 0;
}

double LCSolution::findMedianSortedArrays(std::vector<int> &nums1, std::vector<int> &nums2)
{
    if (nums1.empty() && nums2.empty()) { return 0; }
    unsigned length1 = nums1.size(), length2 = nums2.size();
    std::vector<int> mergeArr = ::op_list::op_array::mergeTest(nums1, length1, nums2, length2);

    double res = 0;
    unsigned sub = (length1 + length2) / 2;
    if ((length1 + length2) % 2) {
        res = (double) (mergeArr[sub]);
    } else {
        res = ((double) (mergeArr[sub - 1] + mergeArr[sub])) / (double) 2;
    }
    std::cout << res << std::endl;
    return res;
}

int LCSolution::reverse(int x)
{
    long n = 0;
    while (x) {
        n = n * 10 + x % 10;
        x /= 10;
    }
    return n > INT_MAX || n < INT_MIN ? 0 : n;
    //			执行耗时:4 ms,击败了49.18% 的C++用户
    //			内存消耗:5.9 MB,击败了11.60% 的C++用户
}

TEST(LCSolution, reverse)
{
    auto p = new LCSolution;
    int x = 321;
    int res = p->reverse(x);
    EXPECT_EQ(res, 123);
    x = -132;
    res = p->reverse(x);
    EXPECT_EQ(res, -231);
}

std::vector<int> LCSolution::searchRange(std::vector<int> &nums, int target)
{
    std::vector<int> res(2, -1);
    if (nums.empty()) { return res; }
    int len = nums.size();
    int left = 0;
    int right = len - 1;
    while (left < right) {
        int mid = (left + right) / 2;
        if (nums[mid] >= target) {
            right = mid;
        } else if (nums[mid] < target) {
            left = mid + 1;
        }
    }
    if (nums[left] != target) { return res; }
    res[0] = left;
    right = len;
    while (left < right) {
        int mid = (left + right) / 2;
        if (nums[mid] <= target) {
            left = mid + 1;
        } else if (nums[mid] > target) {
            right = mid;
        }
    }
    res[1] = right - 1;
    return res;
    //			解答成功:
    //			执行耗时:8 ms,击败了81.80% 的C++用户
    //			内存消耗:13.2 MB,击败了85.95% 的C++用户
}

TEST(LCSolution, searchRange)
{
    std::vector<int> v = {5, 7, 7, 8, 8, 10};
    int t = 6;
    auto p = new LCSolution;
    std::vector<int> res = {-1, -1};
    EXPECT_EQ(p->searchRange(v, t), res);
    v = {2, 2};
    t = 2;
    res = {0, 1};
    EXPECT_EQ(p->searchRange(v, t), res);
}

int LCSolution::jump(std::vector<int> &nums)
{

    if (nums[0] == 0) {
        return 0;
    }

    int LastIndex = nums.size() - 1;
    if (LastIndex <= 1) {
        return LastIndex;
    }

    for (int i = 0; i <= LastIndex; i++) {
        if (nums[i] == 0) {
            continue;
        }
        if (nums[i] + i >= LastIndex) {
            if (i == 0) {
                return 1;
            } else {
                for (int j = nums.size() - 1; j > i; j--) {
                    nums.pop_back();
                }
                return 1 + jump(nums);
            }

        }
    }

    return 0;

}

int LCSolution::maxSubArray(std::vector<int> &nums) {
  int res = 0, max = nums[0];
  for (auto v:nums) {
    res = std::max(v + res, v);
    max = std::max(max, res);
  }
  return max;
}

TEST(LCSolution, maxSubArray) {
  auto p = new LCSolution;
  std::vector<int> v =
      {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  int res = 6;
  EXPECT_EQ(p->maxSubArray(v), res);
}

int LCSolution::lengthOfLastWord(std::string s)
{

    int sub_begin = -1, sub_end = s.length() - 1;
    if (s.empty() || s == " ") { return 0; }

    for (int i = s.length() - 1; i >= 0; i--) {
        if (isalpha(s[i])) {
            sub_end = i;
            break;
        }
    }
    for (int i = sub_end; i >= 0; i--) {
        if (!isalpha(s[i])) {
            sub_begin = i;
            break;
        }
    }

    return sub_end - sub_begin;
}

int LCSolution::minDepth(TreeNode *root)
{
    if (root == nullptr) { return 0; }

    int lDepth = minDepth(root->left);
    int rDepth = minDepth(root->right);

    if (lDepth == 0) {
        return rDepth + 1;
    } else if (rDepth == 0) {
        return lDepth + 1;
    } else {
        return std::min(lDepth, rDepth) + 1;
    }
}

int LCSolution::maxProfit(int k, std::vector<int> &prices)
{
    if (prices.empty() || prices.size() == 1) { return 0; }

    std::vector<int> resGoal(k - 1);


    std::vector<int> resDiff;
    resDiff.reserve(prices.size() - 1);
    for (auto i = 0; i < prices.size() - 1; i++) {
        for (auto j = i + 1; j < prices.size(); j++) {
            resDiff.push_back(prices[j] - prices[i]);
        }
    }
    sort(resDiff.rbegin(), resDiff.rend());
    int res = 0;
    for (int i = 0; i < k; i++) {
        int tempRes = res;
        res += resDiff[i];
        if (res < tempRes) {
            res -= resDiff[i];
        }
    }
    return res;
}

int LCSolution::maximumGap(std::vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    int max_differ = 0;
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] - nums[i - 1] >= max_differ) {
            max_differ = nums[i] - nums[i - 1];
        }
    }
    return max_differ;
}

std::string LCSolution::convertToTitle(int columnNumber)
{
    std::string ans;
    while (columnNumber > 0) {
        ans += --columnNumber % 26 + 'A';
        columnNumber /= 26;
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
    //			解答成功:
    //			执行耗时:0 ms,击败了100.00% 的C++用户
    //			内存消耗:5.9 MB,击败了9.69% 的C++用户
}

TEST(LCSolution, convertToTitle)
{
    std::array<int, 4> test{1, 28, 701, 2147483647};
    std::vector<std::string> ans{"A", "AB", "ZY", "FXSHRXW"};
    auto p = new LCSolution;
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(p->convertToTitle(test[i]), ans[i]);
    }
}

int LCSolution::titleToNumber(std::string columnTitle)
{
//    int res = 0;
//    int mul = 1;
//    for (int i = columnTitle.size() - 1; i >= 0; --i) {
//        int k = (columnTitle[i] - 'A' + 1);
//        res += k * mul;
//        mul *= 26;
//    }
//    return res;

//above越界


    int n = columnTitle.length() - 1;
    int res = 0;
    for (int i = 0; i <= n; i++) {
        res = columnTitle.at(i) - 'A' + 1 + 26 * res;
    }
    return res;
//			执行耗时:0 ms,击败了100.00% 的C++用户
//			内存消耗:5.8 MB,击败了55.66% 的C++用户
}

TEST(LCSolution, titleToNumber)
{
    std::array<int, 4> test{1, 28, 701, 2147483647};
    std::vector<std::string> ans{"A", "AB", "ZY", "FXSHRXW"};
    auto p = new LCSolution;
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(p->titleToNumber(ans[i]), test[i]);
    }
}

int LCSolution::trailingZeroes(int n) {
    //有多少个5就有多少个0
    int res = 0;
    int divider = 5;
    while (n / divider > 0) {
        res += n / divider;
        divider *= 5;
    }
    return res;
}

std::vector<int> LCSolution::maxSlidingWindow(std::vector<int> &nums, int k)
{
    std::vector<int> res;
    if (k >= nums.size()) {
        res.push_back(*max_element(nums.begin(), nums.end()));
        return res;
    }

    int begin = 0;
    std::vector<std::vector<int>> des(nums.size() - k + 1);
    for (int i = 0; i <= nums.size() - k; i++) {
        for (int j = begin; j < begin + k; j++) {
            des[i].push_back(nums[j]);
        }
        begin++;
    }

    for (int i = 0; i <= nums.size() - k; i++) {
        res.push_back(*max_element(des[i].begin(), des[i].end()));
    }

    return res;
}

std::vector<int> LCSolution::maxSlidingWindow(std::vector<int> &nums, int k, bool isOthers)
{
    std::vector<int> res;
    std::deque<int> q;
    for (int i = 0; i < nums.size(); ++i) {
        if (!q.empty() && q.front() == i - k) {
            q.pop_front();
        }
        while (!q.empty() && nums[q.back()] < nums[i]) {
            q.pop_back();
        }
        q.push_back(i);
        if (i >= k - 1) {
            res.push_back(nums[q.front()]);
        }
    }

    return res;
}

std::vector<std::string> LCSolution::readBinaryWatch(int turnedOn, bool brute_force)
{
    switch (turnedOn) {
        case 0:
            return {"0:00"};
        case 1:
            return {"0:01", "0:02", "0:04", "0:08", "0:16", "0:32", "1:00", "2:00", "4:00", "8:00"};
        case 2:
            return {"0:03", "0:05", "0:06", "0:09", "0:10", "0:12", "0:17", "0:18", "0:20", "0:24", "0:33", "0:34",
                    "0:36", "0:40", "0:48", "1:01", "1:02", "1:04", "1:08", "1:16", "1:32", "2:01", "2:02", "2:04",
                    "2:08", "2:16", "2:32", "4:01", "4:02", "4:04", "4:08", "4:16", "4:32", "8:01", "8:02", "8:04",
                    "8:08", "8:16", "8:32", "3:00", "5:00", "6:00", "9:00", "10:00"};
        case 3:
            return {"0:07", "0:11", "0:13", "0:14", "0:19", "0:21", "0:22", "0:25", "0:26", "0:28", "0:35", "0:37",
                    "0:38", "0:41", "0:42", "0:44", "0:49", "0:50", "0:52", "0:56", "1:03", "1:05", "1:06", "1:09",
                    "1:10", "1:12", "1:17", "1:18", "1:20", "1:24", "1:33", "1:34", "1:36", "1:40", "1:48", "2:03",
                    "2:05", "2:06", "2:09", "2:10", "2:12", "2:17", "2:18", "2:20", "2:24", "2:33", "2:34", "2:36",
                    "2:40", "2:48", "4:03", "4:05", "4:06", "4:09", "4:10", "4:12", "4:17", "4:18", "4:20", "4:24",
                    "4:33", "4:34", "4:36", "4:40", "4:48", "8:03", "8:05", "8:06", "8:09", "8:10", "8:12", "8:17",
                    "8:18", "8:20", "8:24", "8:33", "8:34", "8:36", "8:40", "8:48", "3:01", "3:02", "3:04", "3:08",
                    "3:16", "3:32", "5:01", "5:02", "5:04", "5:08", "5:16", "5:32", "6:01", "6:02", "6:04", "6:08",
                    "6:16", "6:32", "9:01", "9:02", "9:04", "9:08", "9:16", "9:32", "10:01", "10:02", "10:04", "10:08",
                    "10:16", "10:32", "7:00", "11:00"};
        case 4:
            return {"0:15", "0:23", "0:27", "0:29", "0:30", "0:39", "0:43", "0:45", "0:46", "0:51", "0:53", "0:54",
                    "0:57", "0:58", "1:07", "1:11", "1:13", "1:14", "1:19", "1:21", "1:22", "1:25", "1:26", "1:28",
                    "1:35", "1:37", "1:38", "1:41", "1:42", "1:44", "1:49", "1:50", "1:52", "1:56", "2:07", "2:11",
                    "2:13", "2:14", "2:19", "2:21", "2:22", "2:25", "2:26", "2:28", "2:35", "2:37", "2:38", "2:41",
                    "2:42", "2:44", "2:49", "2:50", "2:52", "2:56", "4:07", "4:11", "4:13", "4:14", "4:19", "4:21",
                    "4:22", "4:25", "4:26", "4:28", "4:35", "4:37", "4:38", "4:41", "4:42", "4:44", "4:49", "4:50",
                    "4:52", "4:56", "8:07", "8:11", "8:13", "8:14", "8:19", "8:21", "8:22", "8:25", "8:26", "8:28",
                    "8:35", "8:37", "8:38", "8:41", "8:42", "8:44", "8:49", "8:50", "8:52", "8:56", "3:03", "3:05",
                    "3:06", "3:09", "3:10", "3:12", "3:17", "3:18", "3:20", "3:24", "3:33", "3:34", "3:36", "3:40",
                    "3:48", "5:03", "5:05", "5:06", "5:09", "5:10", "5:12", "5:17", "5:18", "5:20", "5:24", "5:33",
                    "5:34", "5:36", "5:40", "5:48", "6:03", "6:05", "6:06", "6:09", "6:10", "6:12", "6:17", "6:18",
                    "6:20", "6:24", "6:33", "6:34", "6:36", "6:40", "6:48", "9:03", "9:05", "9:06", "9:09", "9:10",
                    "9:12", "9:17", "9:18", "9:20", "9:24", "9:33", "9:34", "9:36", "9:40", "9:48", "10:03", "10:05",
                    "10:06", "10:09", "10:10", "10:12", "10:17", "10:18", "10:20", "10:24", "10:33", "10:34", "10:36",
                    "10:40", "10:48", "7:01", "7:02", "7:04", "7:08", "7:16", "7:32", "11:01", "11:02", "11:04",
                    "11:08", "11:16", "11:32"};
        case 5:
            return {"0:31", "0:47", "0:55", "0:59", "1:15", "1:23", "1:27", "1:29", "1:30", "1:39", "1:43", "1:45",
                    "1:46", "1:51", "1:53", "1:54", "1:57", "1:58", "2:15", "2:23", "2:27", "2:29", "2:30", "2:39",
                    "2:43", "2:45", "2:46", "2:51", "2:53", "2:54", "2:57", "2:58", "4:15", "4:23", "4:27", "4:29",
                    "4:30", "4:39", "4:43", "4:45", "4:46", "4:51", "4:53", "4:54", "4:57", "4:58", "8:15", "8:23",
                    "8:27", "8:29", "8:30", "8:39", "8:43", "8:45", "8:46", "8:51", "8:53", "8:54", "8:57", "8:58",
                    "3:07", "3:11", "3:13", "3:14", "3:19", "3:21", "3:22", "3:25", "3:26", "3:28", "3:35", "3:37",
                    "3:38", "3:41", "3:42", "3:44", "3:49", "3:50", "3:52", "3:56", "5:07", "5:11", "5:13", "5:14",
                    "5:19", "5:21", "5:22", "5:25", "5:26", "5:28", "5:35", "5:37", "5:38", "5:41", "5:42", "5:44",
                    "5:49", "5:50", "5:52", "5:56", "6:07", "6:11", "6:13", "6:14", "6:19", "6:21", "6:22", "6:25",
                    "6:26", "6:28", "6:35", "6:37", "6:38", "6:41", "6:42", "6:44", "6:49", "6:50", "6:52", "6:56",
                    "9:07", "9:11", "9:13", "9:14", "9:19", "9:21", "9:22", "9:25", "9:26", "9:28", "9:35", "9:37",
                    "9:38", "9:41", "9:42", "9:44", "9:49", "9:50", "9:52", "9:56", "10:07", "10:11", "10:13", "10:14",
                    "10:19", "10:21", "10:22", "10:25", "10:26", "10:28", "10:35", "10:37", "10:38", "10:41", "10:42",
                    "10:44", "10:49", "10:50", "10:52", "10:56", "7:03", "7:05", "7:06", "7:09", "7:10", "7:12", "7:17",
                    "7:18", "7:20", "7:24", "7:33", "7:34", "7:36", "7:40", "7:48", "11:03", "11:05", "11:06", "11:09",
                    "11:10", "11:12", "11:17", "11:18", "11:20", "11:24", "11:33", "11:34", "11:36", "11:40", "11:48"};
        case 6:
            return {"1:31", "1:47", "1:55", "1:59", "2:31", "2:47", "2:55", "2:59", "4:31", "4:47", "4:55", "4:59",
                    "8:31", "8:47", "8:55", "8:59", "3:15", "3:23", "3:27", "3:29", "3:30", "3:39", "3:43", "3:45",
                    "3:46", "3:51", "3:53", "3:54", "3:57", "3:58", "5:15", "5:23", "5:27", "5:29", "5:30", "5:39",
                    "5:43", "5:45", "5:46", "5:51", "5:53", "5:54", "5:57", "5:58", "6:15", "6:23", "6:27", "6:29",
                    "6:30", "6:39", "6:43", "6:45", "6:46", "6:51", "6:53", "6:54", "6:57", "6:58", "9:15", "9:23",
                    "9:27", "9:29", "9:30", "9:39", "9:43", "9:45", "9:46", "9:51", "9:53", "9:54", "9:57", "9:58",
                    "10:15", "10:23", "10:27", "10:29", "10:30", "10:39", "10:43", "10:45", "10:46", "10:51", "10:53",
                    "10:54", "10:57", "10:58", "7:07", "7:11", "7:13", "7:14", "7:19", "7:21", "7:22", "7:25", "7:26",
                    "7:28", "7:35", "7:37", "7:38", "7:41", "7:42", "7:44", "7:49", "7:50", "7:52", "7:56", "11:07",
                    "11:11", "11:13", "11:14", "11:19", "11:21", "11:22", "11:25", "11:26", "11:28", "11:35", "11:37",
                    "11:38", "11:41", "11:42", "11:44", "11:49", "11:50", "11:52", "11:56"};
        case 7:
            return {"3:31", "3:47", "3:55", "3:59", "5:31", "5:47", "5:55", "5:59", "6:31", "6:47", "6:55", "6:59",
                    "9:31", "9:47", "9:55", "9:59", "10:31", "10:47", "10:55", "10:59", "7:15", "7:23", "7:27", "7:29",
                    "7:30", "7:39", "7:43", "7:45", "7:46", "7:51", "7:53", "7:54", "7:57", "7:58", "11:15", "11:23",
                    "11:27", "11:29", "11:30", "11:39", "11:43", "11:45", "11:46", "11:51", "11:53", "11:54", "11:57",
                    "11:58"};
        case 8:
            return {"7:31", "7:47", "7:55", "7:59", "11:31", "11:47", "11:55", "11:59"};
        default:
            return {};
    }
    //	执行耗时:4 ms,击败了40.02% 的C++用户
    //	内存消耗:6.6 MB,击败了11.17% 的C++用户
}

std::vector<std::string> LCSolution::readBinaryWatch(int turnedOn, int brute_force)
{
    std::vector<std::string> res;
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 60; ++j) {
            if (count1(i) + count1(j) == turnedOn) {
                res.emplace_back(std::to_string(i) + (j < 10 ? ":0" : ":") + std::to_string(j));
            }
        }
    }
    return res;
    //			执行耗时:0 ms,击败了100.00% 的C++用户
    //			内存消耗:6.2 MB,击败了85.67% 的C++用户
}

TEST(LCSolution, readBinaryWatch)
{
    auto p = new LCSolution;
    std::vector<std::string> t = {"0:01", "0:02", "0:04", "0:08", "0:16", "0:32", "1:00", "2:00", "4:00", "8:00"};
    std::vector<std::string> res = p->readBinaryWatch(1, true);
    EXPECT_EQ(res, t);
}

int LCSolution::numberOfArithmeticSlices(std::vector<int>& nums){
    if (nums.empty()) { return 0; }
    if (nums.size() < 3) { return 0; }
    int count = 0;
    int addend = 0;

    for (int i = 2; i < nums.size(); i++) {
        if (nums[i - 1] - nums[i] == nums[i - 2] - nums[i - 1]) {
            count += ++addend;
        } else {
            addend = 0;
        }
    }
    return count;
}

TEST(LCSolution, numberOfArithmeticSlices)
{
    std::vector<int> t = {1,2,3,4,5};
    int res = LCSolution::instance()->numberOfArithmeticSlices(t);
    EXPECT_EQ(res, 6);
}


int LCSolution::findMaximumXOR(std::vector<int> &nums)
{
    if (nums.empty()) { return 0; }
    auto biggest = max_element(begin(nums), end(nums));
    int res = 0;
    for (auto compare:nums) {
        int max = compare ^ *biggest;
        if (max > res) {
            res = max;
        }
//    res = (compare ^ *biggest) > res ? (compare ^ *biggest) : res;
    }
    return res;
}

int LCSolution::maxPoints(std::vector<std::vector<int>> &points)
{

    if (points.size() <= 2) {
        return points.size();
    }

    int res = 2;
    long abx, aby, bcx, bcy;
    for (int i = 0; i < points.size(); i++) {
        int duplicate = 0;
        int sameSlope = 1;
        for (int j = i + 1; j < points.size(); j++) {

            abx = points[i][0] - points[j][0];
            aby = points[i][1] - points[j][1];

            if (abx == 0 && aby == 0) {
                /// duplicate points
                duplicate++;
            } else {
                /// same slope
                sameSlope++;
                for (int k = j + 1; k < points.size(); k++) {
                    bcx = points[j][0] - points[k][0];
                    bcy = points[j][1] - points[k][1];
                    if (abx * bcy == aby * bcx) {
                        /// 3 points in line
                        sameSlope++;
                    }
                }
            }
            res = std::max(res, duplicate + sameSlope);
            sameSlope = 1;
        }
    }
    return res;
}

std::vector<int> LCSolution::findDuplicates(std::vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    std::vector<int> des;
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] == nums[i - 1]) {
            des.push_back(nums[i]);
            if (i != nums.size() - 1) {
                i++;
            }
        }
    }
    return des;

//  if (nums.empty()) return {};
//  std::vector<int> res;
//  for (auto i = 0; i < nums.size(); i++) {
//    while (nums[i] != i) {
//      if (nums[i] != nums[nums[i]]) {
//        int temp = nums[i];
//        nums[i] = nums[temp];
//        nums[temp] = temp;
//      } else {
//        res.push_back(nums[i]);
//      }
//    }
//  }
//  return res;

}

std::vector<int> LCSolution::findDisappearedNumbers(std::vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    std::vector<int> des;
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] != nums[i - 1] + 1) {
            des.push_back(nums[i - 1] + 1);
        }
    }
    return des;
}

bool LCSolution::findTarget(TreeNode *root, int k) {
    if (!root) return false;
    if (ss653.count(k - root->value)) {
        return true;
    }
    ss653.insert(root->value);
    return findTarget(root->left, k) || findTarget(root->right, k);
}

int LCSolution::calPoints(std::vector<std::string> &ops) {
    std::stack<std::string> s;
    int res = 0;
    for (const auto &info: ops) {
        s.push(info);
        if (s.top() == "C") {
            s.pop();
            res -= std::stoi(s.top());
            s.pop();
            continue;
        }
        if (s.top() == "D") {
            s.pop();
            s.push(std::to_string(std::stoi(s.top()) * 2));
        }
        if (s.top() == "+") {
            s.pop();
            std::string second = s.top();
            s.pop();
            std::string first = s.top();
            s.pop();
            s.push(first);
            s.push(second);
            s.push(std::to_string(std::stoi(first) + std::stoi(second)));
        }
        res += std::stoi(s.top());
    }
    return res;
}

int LCSolution::maxIceCream(std::vector<int> &costs, int coins)
{
    if (costs.empty()) { return 0; }
    std::sort(costs.begin(), costs.end());
    int use = 0, res = 0;
    for (auto co : costs) {
        if (co > coins) {
            //最小的都买不起
            return res;
        }
        use += co;
        ++res;
        if (use >= coins) {
            //没有那么多钱 减去最后加的
            if (use > coins) { --res; }
            return res;
        }
    }
    return res;
//			执行耗时:256 ms,击败了5.17% 的C++用户
//			内存消耗:74.7 MB,击败了9.88% 的C++用户
}

TEST(LCSolution, maxIceCream)
{
    auto p = new LCSolution;
    std::vector<int> t{1, 3, 2, 4, 1};
    EXPECT_EQ(p->maxIceCream(t, 7), 4);

    t = {10, 6, 8, 7, 7, 8};
    EXPECT_EQ(p->maxIceCream(t, 5), 0);

    t = {7, 3, 3, 6, 6, 6, 10, 5, 9, 2};
    EXPECT_EQ(p->maxIceCream(t, 56), 9);
}

int LCSolution::maximumElementAfterDecrementingAndRearranging(std::vector<int> &arr)
{
    if (arr.empty()) { return 0; }
    std::sort(arr.begin(), arr.end());
    if (arr[0] != 1) { arr[0] = 1; }
    for (int i = 1; i < arr.size(); ++i) {
        int val = arr[i - 1] - arr[i];
        int a = val > 0 ? val : (-val);
        if (val > 1) { arr[i - 1] -= (a - 1); }
        if (val < -1) { arr[i] -= (a - 1); }
    }
    return arr[arr.size() - 1];
    //			解答成功:
    //			执行耗时:132 ms,击败了9.93% 的C++用户
    //			内存消耗:50 MB,击败了59.04% 的C++用户
}

int LCSolution::minPairSum(std::vector<int>& nums){
    std::sort(nums.begin(), nums.end());
    int res = 0;
    int len = nums.size();
    for (int i = 0; i < len / 2; ++i) {
        res = std::max(res, nums[i] + nums[len - 1 - i]);
    }
    return res;
    //			解答成功:
    //			执行耗时:220 ms,击败了97.90% 的C++用户
    //			内存消耗:94.1 MB,击败了26.69% 的C++用户
}

TEST(LCSolution,minPairSum){
    std::vector<int> v = {3, 5, 4, 2, 4, 6};
    int res = 8;
    EXPECT_EQ(LCSolution::instance()->minPairSum(v), res);

    v = {3, 5, 2, 3};
    res = 7;
    EXPECT_EQ(LCSolution::instance()->minPairSum(v), res);

    v = {4, 1, 5, 1, 2, 5, 1, 5, 5, 4};
    res = 8;
    EXPECT_EQ(LCSolution::instance()->minPairSum(v), res);
}

bool LCSolution::isCovered(std::vector<std::vector<int>>& ranges, int left, int right){
    for (int i = left; i <= right; ++i) {
        bool flag = false;
        for (auto &item:ranges) {
            if (item[0] <= i && item[1] >= i) {
                flag = true;
                break;
            }
        }
        if (!flag) { return false; }
    }
    return true;
    //			解答成功:
    //			执行耗时:4 ms,击败了88.43% 的C++用户
    //			内存消耗:8.7 MB,击败了27.40% 的C++用户
}

std::vector<int> LCSolution::missingRolls(std::vector<int> &rolls, int mean, int n) {
    int temp = mean * (rolls.size() + n);
    int total_rolls = 0;
    for (auto v: rolls) {
        total_rolls += v;
    }
    int sum = temp - total_rolls;
    int v = sum / n;
    if (v > 6 || sum < n) {
        return {};
    }
    std::vector<int> res(n, v);
    int remain = sum;
    for(auto i : res){

    }

}

std::vector<std::vector<int>> LCSolution::prefixSum(std::vector<std::vector<int>> a){
    std::vector<std::vector<int>> b;
    int n = a.size();//n行
    int m = a[0].size();//m列
    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < m; ++x) {
            if (x == 0 && y == 0) {
                b[y][x] = a[y][x];//左上角的值
            } else if (x == 0) {
                b[y][x] = b[y - 1][x] + a[y][x];//第一列
            } else if (y == 0) {
                b[y][x] = b[y][x - 1] + a[y][x];//第一行
            } else { b[y][x] = b[y - 1][x] + b[y][x - 1] - b[y - 1][x - 1] + a[y][x]; }
        }
    }
    return b;
}

/// 6 kyu
///If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
///Finish the solution so that it returns the sum of all the multiples of 3 or 5 below the number passed in.
///Note: If the number is a multiple of both 3 and 5, only count it once.
int codewars::Multiples3Or5(int number)
{
    /// < number
    /// 商
    int a1 = number / 3,
        a2 = number / 5,
        a3 = number / 15;
    /// 余数
    int b1 = number % 3,
        b2 = number % 5,
        b3 = number % 15;
    /// 3、5、15的倍数的数目
    int c1 = 0,
        c2 = 0,
        c3 = 0;
    /// < number
    if (!b1) { a1 -= 1; }
    if (!b2) { a2 -= 1; }
    if (!b3) { a3 -= 1; }

    for (int i = 1; i <= a1; i++) {
        c1 += i;
    }
    for (int i = 1; i <= a2; i++) {
        c2 += i;
    }
    for (int i = 1; i <= a3; i++) {
        c3 += i;
    }
    return c1 * 3 + c2 * 5 - c3 * 15;
}

int codewars::Multiples3Or5(int number, bool others)
{
    int sum = 0;
    for (int n = 3; n < number; n++) {
        if ((n % 3 == 0) || (n % 5 == 0)) {
            sum += n;
        }
    }
    return sum;
}

/// 6 kyu Valid Braces
bool codewars::validBraces(const std::string &braces)
{
    /// Others Written
    /// learning stack
    std::stack<char> s;
    std::string bracketLeft = "{[(";
    std::string bracketRight = "}])";

    for (char chr : braces) {
        int indexLeft = -1, indexRight = -1;
        indexLeft = bracketLeft.find(chr);
        indexRight = bracketRight.find(chr);
        // 是左括号
        if (indexLeft >= 0) {
            s.push(chr);    // 入栈
            // 是右括号
        } else if (indexRight >= 0) {
            // 匹配成功
            if (!s.empty() && s.top() == bracketLeft[indexRight]) {
                s.pop();    // 出栈
            } else {
                return false;
            }
        }
    }

    return s.empty();
}

bool codewars::validBraces(std::string s)
{
    std::regex r(R"(\(\)|\[\]|\{\})");
    while (regex_search(s, r)) { s = regex_replace(s, r, ""); }
    return s.length() == 0;
}

int codewars::SnailSort::GetDirection(bool Direction[4])
{
    for (int i = 0; i < 4; i++) {
        if (Direction[i]) {
            return i;
        }
    }
    return 0;
}

bool codewars::SnailSort::IsArrived(int CurrentPosX, int CurrentPosY, int FinalPosX, int FinalPosY)
{
    return CurrentPosX == FinalPosX && CurrentPosY == FinalPosY;
}

std::vector<int> codewars::SnailSort::snail(const std::vector<std::vector<int>> &snail_map, bool isOthers)
{
    if (snail_map.size() <= 1) {
        return snail_map[0];
    }

    std::vector<int> Res;
    int FinalPosX = 0;
    int FinalPosY = 0;
    if (snail_map.size() % 2 == 0) {
        FinalPosX = snail_map.size() - snail_map.size() / 2;
        FinalPosY = snail_map.size() / 2 - 1;
    } else {
        FinalPosX = snail_map.size() / 2;
        FinalPosY = snail_map.size() / 2;
    }

    int CurrentPosX = 0;
    int CurrentPosY = 0;

    int RightFrame = snail_map[0].size() - 1;
    int DownFrame = snail_map.size() - 1;
    int LeftFrame = 0;
    int UpFrame = 0;

    bool DirectionGo[4] = {true, false, false, false};
    while (CurrentPosX != FinalPosX || CurrentPosY != FinalPosY) {
        switch (GetDirection(DirectionGo)) {
            case RIGHT:

                CurrentPosX = UpFrame;
                for (int StartPos = LeftFrame; StartPos <= RightFrame; StartPos++) {
                    Res.push_back(snail_map[UpFrame][StartPos]);
                    CurrentPosY = StartPos;
                    if (IsArrived(CurrentPosX, CurrentPosY, FinalPosX, FinalPosY)) {
                        return Res;
                    }
                }

                UpFrame++;

                DirectionGo[RIGHT] = false;
                DirectionGo[(RIGHT + 1) % 4] = true;
                break;
            case DOWN:

                CurrentPosY = RightFrame;
                for (int StartPos = UpFrame; StartPos <= DownFrame; StartPos++) {
                    Res.push_back(snail_map[StartPos][RightFrame]);
                    CurrentPosX = StartPos;
                    if (IsArrived(CurrentPosX, CurrentPosY, FinalPosX, FinalPosY)) {
                        return Res;
                    }
                }

                RightFrame--;

                DirectionGo[DOWN] = false;
                DirectionGo[(DOWN + 1) % 4] = true;
                break;
            case LEFT:

                CurrentPosX = DownFrame;
                for (int StartPos = RightFrame; StartPos >= LeftFrame; StartPos--) {
                    Res.push_back(snail_map[DownFrame][StartPos]);
                    CurrentPosY = StartPos;
                    if (IsArrived(CurrentPosX, CurrentPosY, FinalPosX, FinalPosY)) {
                        return Res;
                    }
                }

                DownFrame--;

                DirectionGo[LEFT] = false;
                DirectionGo[(LEFT + 1) % 4] = true;
                break;
            case UP:

                CurrentPosY = LeftFrame;
                for (int StartPos = DownFrame; StartPos >= UpFrame; StartPos--) {
                    Res.push_back(snail_map[StartPos][LeftFrame]);
                    CurrentPosX = StartPos;
                    if (IsArrived(CurrentPosX, CurrentPosY, FinalPosX, FinalPosY)) {
                        return Res;
                    }
                }

                LeftFrame++;

                DirectionGo[UP] = false;
                DirectionGo[(UP + 1) % 4] = true;
                break;
        }

    }
    return Res;
}

std::vector<int> codewars::SnailSort::snail(const std::vector<std::vector<int>> &snail_map)
{

    ///// GOT CycleTimes
    //// 5x5
    //// 5 4 4 3
    //// 3 2 2 1
    //// 1

    //// 6x6
    //// 6 5 5 4
    //// 4 3 3 2
    //// 2 1 1

    //// 7x7
    //// 7 6 6 5
    //// 5 4 4 3
    //// 3 2 2 1
    //// 1

    if (snail_map.empty()) { return {}; }

    std::vector<int> res;

    if (snail_map.size() == 1) {
//    res.push_back(snail_map[0][0]); /// 内存泄漏
        res = snail_map[0];
        return res;
    }

    //// n x n
    const int rank = snail_map.size();

    int begin = 0,
        end = rank;

    int CycleTimes = ((rank * 2) - 1) / 4;
    if (((rank * 2) - 1) % 4) {
        //// CycleTimes 矫正
        CycleTimes++;
    }

    while (CycleTimes) {
        //////正向 横竖
        for (int i = begin; i < end; i++) {
            res.push_back(snail_map[begin][i]);
        }
        for (int i = begin + 1; i < end; i++) {
            res.push_back(snail_map[i][end - 1]);
        }
        //////反向 横竖
        for (int i = end - 2; i >= begin; i--) {
            res.push_back(snail_map[end - 1][i]);
        }
        for (int i = end - 2; i >= begin + 1; i--) {
            res.push_back(snail_map[i][begin]);
        }
        begin++;
        end--;

        CycleTimes--;
    }

    return res;
}

int codewars::Casino::ColorCount(std::vector<int> v)
{
    int Count = 0;
    for (int i = 0; i < 3; i++) {
        if (v[i] > 0) {
            Count++;
        }
    }
    return Count++;
}

int codewars::Casino::solution(std::vector<int> v)
{
    int DayCount = 0;
    bool HaveColor[3] = {v[0] > 0, v[1] > 0, v[2] > 0};

    while (ColorCount(v) >= 2) {
        bool bTaken[3] = {false, false, false};
        for (int j = 0; j < 2; j++) {
            int TempColorMaxCount = 0;
            int TempColor = 0;
            for (int i = 0; i < 3; i++) {
                if (!bTaken[i] && HaveColor[i] && v[i] >= TempColorMaxCount) {
                    TempColor = i;
                    TempColorMaxCount = v[i];
                }
            }
            v[TempColor]--;
            bTaken[TempColor] = true;
            HaveColor[TempColor] = v[TempColor] > 0;
        }
        DayCount++;
    }

    return DayCount;
}

TEST(codewars_t1, Casino)
{
    auto p = new codewars::Casino;
    EXPECT_EQ(p->solution({1, 1, 1}), 1);//because after you pick on day one, there will be only one chip left
    EXPECT_EQ(p->solution({1, 2, 1}), 2);// you can pick twice; you pick two chips on day one then on day two
    EXPECT_EQ(p->solution({4, 1, 1}), 2);
}


int Palindrome::maxSlidingWindow(const std::vector<int> &nums, int k, int MaxValue, std::vector<int> &AllNum)
{
    int Count = 0;

    int EndPos = k;
    for (int StartPos = 0; EndPos <= nums.size(); StartPos++, EndPos++) {
        int TempSum = 0;
        for (int i = StartPos; i < EndPos; i++) {
            TempSum += pow(nums[i], 2);
            if (TempSum > MaxValue || TempSum < 0) {
                break;
            }
        }

        if (TempSum > MaxValue || TempSum < 0) {
            return Count;
        } else {
            auto res = any_of(AllNum.begin(), AllNum.end(), [=](int i) { return i == TempSum; });
            if (res) {
                continue;
            }

            if (TempSum < 10) {
                Count++;
                AllNum.push_back(TempSum);
                continue;
            }

            int MaxDigit = ((int) log10(TempSum)) + 1;
            bool IsCorrectNum = true;
            for (int StartDigit = 1, LastDigit = MaxDigit; StartDigit < LastDigit; StartDigit++, LastDigit--) {
                int FirstNum = ((int) (TempSum / ((int) pow(10, MaxDigit - StartDigit)))) % 10;
                int SecondNum = ((int) (TempSum / ((int) (pow(10, MaxDigit - LastDigit))))) % 10;

                if (FirstNum != SecondNum) {
                    IsCorrectNum = false;
                    break;
                }
            }

            if (IsCorrectNum) {
                AllNum.push_back(TempSum);
                Count++;
                continue;
            }
        }

    }

    return Count;
}

int Palindrome::values(int v)
{
    if (v < pow(1, 2) + pow(2, 2)) {
        return 0;
    }

    int MaxSquare = 1;

    while (pow(MaxSquare, 2) < v) {
        MaxSquare++;
    }

    MaxSquare--;

    std::vector<int> num;
    for (int j = 1; j <= MaxSquare; j++) {
        num.push_back(j);
    }

    int Count = 0;
    std::vector<int> AllNum;
    for (int i = 2; i <= MaxSquare; i++) {
        Count += maxSlidingWindow(num, i, v, AllNum);
    }

    return Count;
}

int main(int argc, char *argv[]){
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();

    return ret;
}