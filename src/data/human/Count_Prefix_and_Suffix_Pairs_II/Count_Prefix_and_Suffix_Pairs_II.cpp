#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    struct TrieNode {
        unordered_map<int, TrieNode*> next;
        int count = 0;
    };

    long long countPrefixSuffixPairs(vector<string>& words) {
        TrieNode* root = new TrieNode();
        long long res = 0;
        for (const string& w : words) {
            TrieNode* x = root;
            for (int i = 0, n = w.size(); i < n; ++i) {
                x = x->next.insert({w[i] * 128 + w[n - 1 - i], new TrieNode()}).first->second;
                res += x->count;
            }
            x->count++;
        }
        return res;
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Simple case with one prefix-suffix pair
    std::vector<std::string> words = {"aba", "ababa", "abc"};
    int expected_result = 1;
    assert(solution.countPrefixSuffixPairs(words) == expected_result && "Test case 1 failed.");

    // Test case 2: Multiple prefix-suffix pairs
    words = {"a", "aa", "aaa", "aaaa"};
    expected_result = 6;
    assert(solution.countPrefixSuffixPairs(words) == expected_result && "Test case 2 failed.");

    // Test case 3: No valid prefix-suffix pairs
    words = {"abc", "def", "ghi"};
    expected_result = 0;
    assert(solution.countPrefixSuffixPairs(words) == expected_result && "Test case 3 failed.");

    // Test case 4: Pairs with different lengths but valid prefix-suffix
    words = {"aba", "b", "ababa", "ba"};
    expected_result = 1;
    assert(solution.countPrefixSuffixPairs(words) == expected_result && "Test case 4 failed.");

    // Test case 5: Additional test cases with different pairs
    words = {"a", "aba", "ababa", "aa"};
    expected_result = 4;
    assert(solution.countPrefixSuffixPairs(words) == expected_result && "Test case 5 failed.");

    words = {"pa", "papa", "ma", "mama"};
    expected_result = 2;
    assert(solution.countPrefixSuffixPairs(words) == expected_result && "Test case 6 failed.");

    words = {"abab", "ab"};
    expected_result = 0;
    assert(solution.countPrefixSuffixPairs(words) == expected_result && "Test case 7 failed.");

    // Test case 6: Multiple identical words
    words = {"aaa", "aaa", "aaa"};
    expected_result = 3;
    assert(solution.countPrefixSuffixPairs(words) == expected_result && "Test case 8 failed.");

    // Test case 7: Words with non-overlapping characters
    words = {"cat", "dog", "mouse", "bird"};
    expected_result = 0;
    assert(solution.countPrefixSuffixPairs(words) == expected_result && "Test case 9 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 327680; ++i) {
        testSolution(solution);  
    }
    return 0;
}
