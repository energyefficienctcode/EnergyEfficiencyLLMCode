#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    unordered_map<long long, int> cache;
    string s;
    int k;

    int maxPartitionsAfterOperations(string s, int k) {
        this->s = s;
        this->k = k;
        return dp(0, 0, true) + 1;
    }

private:
    int dp(long long index, long long currentSet, bool canChange) {
        long long key = (index << 27) | (currentSet << 1) | canChange;

        if (cache.count(key)) {
            return cache[key];
        }

        if (index == s.size()) {
            return 0;
        }

        int characterIndex = s[index] - 'a';
        int currentSetUpdated = currentSet | (1 << characterIndex);
        int distinctCount = __builtin_popcount(currentSetUpdated);

        int res;
        if (distinctCount > k) {
            res = 1 + dp(index + 1, 1 << characterIndex, canChange);
        } else {
            res = dp(index + 1, currentSetUpdated, canChange);
        }

        if (canChange) {
            for (int newCharIndex = 0; newCharIndex < 26; ++newCharIndex) {
                int newSet = currentSet | (1 << newCharIndex);
                int newDistinctCount = __builtin_popcount(newSet);

                if (newDistinctCount > k) {
                    res = max(res, 1 + dp(index + 1, 1 << newCharIndex, false));
                } else {
                    res = max(res, dp(index + 1, newSet, false));
                }
            }
        }

        return cache[key] = res;
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Single character string
    std::string s = "a";
    int k = 1;
    int expected_result = 1;
    assert(solution.maxPartitionsAfterOperations(s, k) == expected_result && "Test case 1 failed.");

    // Test case 2: No change needed to partition optimally
    s = "accca";
    k = 2;
    expected_result = 3;
    assert(solution.maxPartitionsAfterOperations(s, k) == expected_result && "Test case 2 failed.");

    // Test case 3: Change one character to maximize partitions
    s = "abac";
    k = 2;
    expected_result = 2;
    assert(solution.maxPartitionsAfterOperations(s, k) == expected_result && "Test case 3 failed.");

    // Test case 4: Entire string has more than k distinct characters, requiring changes
    s = "aabaab";
    k = 3;
    expected_result = 1;
    assert(solution.maxPartitionsAfterOperations(s, k) == expected_result && "Test case 4 failed.");

    // Test case 5: Optimal choice without changing characters
    s = "xxyz";
    k = 1;
    expected_result = 4;
    assert(solution.maxPartitionsAfterOperations(s, k) == expected_result && "Test case 5 failed.");

    // Test case 6: Large k that allows full string as one partition
    s = "abcdefgh";
    k = 8;
    expected_result = 1;
    assert(solution.maxPartitionsAfterOperations(s, k) == expected_result && "Test case 6 failed.");

    // Test case 7: k smaller than distinct characters in s, requiring multiple partitions
    s = "abcabcabc";
    k = 1;
    expected_result = 9;
    assert(solution.maxPartitionsAfterOperations(s, k) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 1342177280; ++i) {
        testSolution(solution);  
    }
    return 0;
}
