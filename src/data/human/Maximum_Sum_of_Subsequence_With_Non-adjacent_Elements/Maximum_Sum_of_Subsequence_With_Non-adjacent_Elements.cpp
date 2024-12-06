#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long inf = 1e18;
const long long mod = 1e9 + 7;

// Modified from https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LazySegmentTree.h
struct Node {
    Node *l = nullptr, *r = nullptr;
    unsigned int lo, hi;
    long long selected[2][2];

    Node(const vector<int> &nums, unsigned int lo, unsigned int hi) : lo(lo), hi(hi) {
        if (lo < hi) {
            unsigned int mid = (lo + hi) / 2;
            l = new Node(nums, lo, mid);
            r = new Node(nums, mid + 1, hi);

            combine();
        } else {
            selected[0][0] = 0;
            selected[0][1] = -inf;
            selected[1][0] = -inf;
            selected[1][1] = nums[lo];
        }
    }

    void combine() {
        selected[0][0] = max(l->selected[0][0] + r->selected[0][0], max(l->selected[0][1] + r->selected[0][0], l->selected[0][0] + r->selected[1][0]));
        selected[0][1] = max(l->selected[0][0] + r->selected[0][1], max(l->selected[0][1] + r->selected[0][1], l->selected[0][0] + r->selected[1][1]));
        selected[1][0] = max(l->selected[1][0] + r->selected[0][0], max(l->selected[1][1] + r->selected[0][0], l->selected[1][0] + r->selected[1][0]));
        selected[1][1] = max(l->selected[1][0] + r->selected[0][1], max(l->selected[1][1] + r->selected[0][1], l->selected[1][0] + r->selected[1][1]));
    }

    void update(int i, long long x) {
        if (i < lo || hi < i) {
            return;
        }

        if (lo == hi) {
            selected[0][0] = 0;
            selected[1][1] = x;
            return;
        }

        l->update(i, x);
        r->update(i, x);

        combine();
    }
};

class Solution {
  public:
    int maximumSumSubsequence(vector<int> &nums, vector<vector<int>> &queries) {
        Node segmentTree(nums, 0, nums.size() - 1);

        long long res = 0;
        for (auto &query : queries) {
            segmentTree.update(query[0], query[1]);
            res += max(segmentTree.selected[0][0], max(segmentTree.selected[0][1], max(segmentTree.selected[1][0], segmentTree.selected[1][1])));
            res %= mod;
        }
        return static_cast<int>(res);
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Small array with one query
    std::vector<int> nums = {3, 5, 9};
    std::vector<std::vector<int>> queries = {{1, -2}, {0, -3}};
    int expected_result = 21;  // After update nums = [3, 10, 5]; max sum of non-adjacent is 15
    assert(solution.maximumSumSubsequence(nums, queries) == expected_result && "Test case 1 failed.");

    // Test case 2: Multiple queries on the same position
    nums = {0, -1};
    queries = {{0, -5}};
    expected_result = 0;  // No non-adjacent subsequence gives sum > 0
    assert(solution.maximumSumSubsequence(nums, queries) == expected_result && "Test case 2 failed.");

    // Test case 3: Alternating updates on larger array
    nums = {3, 2, 1, 6, 4};
    queries = {{0, 7}, {3, 2}, {4, 9}};
    expected_result = 42;  // After updates, expected sum
    assert(solution.maximumSumSubsequence(nums, queries) == expected_result && "Test case 3 failed.");

    // Test case 4: All elements zero initially, single update
    nums = {0, 0, 0};
    queries = {{2, 5}};
    expected_result = 5;  // After update nums = [0, 0, 5]; max sum is 5
    assert(solution.maximumSumSubsequence(nums, queries) == expected_result && "Test case 4 failed.");

    // Test case 5: Single element update with zero value
    nums = {6, 5, 8};
    queries = {{1, 0}};
    expected_result = 14;  // After update nums = [6, 0, 8]; max sum is 14
    assert(solution.maximumSumSubsequence(nums, queries) == expected_result && "Test case 5 failed.");

    // Test case 6: Larger array with alternating high values
    nums = {5, 10, 5, 10, 5};
    queries = {{1, 5}, {3, 5}, {4, 20}};
    expected_result = 60;  // After updates: expected sum
    assert(solution.maximumSumSubsequence(nums, queries) == expected_result && "Test case 6 failed.");

    // Test case 7: No queries (should handle empty case)
    nums = {4, 6, 8, 10};
    queries = {};
    expected_result = 0;  // No updates; sum of answers = 0
    assert(solution.maximumSumSubsequence(nums, queries) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 1310720; ++i) {
        testSolution(solution);  
    }
    return 0;
}
