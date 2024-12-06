#include <vector>
#include <string>
#include <climits>
using namespace std;

class Solution {
public:
    int minValidStrings(vector<string>& words, string target) {
        int n = target.size();
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;  // No strings are needed to form an empty prefix of target

        // Check each position in the target string
        for (int i = 0; i < n; ++i) {
            if (dp[i] == INT_MAX) continue;  // Skip if this position is not reachable

            // Check if any word in words can be used as a prefix from position i
            for (const string& word : words) {
                int len = word.size();
                if (i + len <= n && target.substr(i, len) == word) {
                    dp[i + len] = min(dp[i + len], dp[i] + 1);
                }
            }
        }

        // If we can reach the end of target, return the minimum number of strings, otherwise return -1
        return dp[n] == INT_MAX ? -1 : dp[n];
    }
};

//  Test cases for the C++ solution
#include <cassert>

void testSolution(Solution& solution) {
    // Test case 1: Exact match with words as prefixes
    std::vector<std::string> words = {"ab", "abc", "bc"};
    std::string target = "abc";
    int expected_result = 1;  // "abc" matches exactly with one of the words
    assert(solution.minValidStrings(words, target) == expected_result && "Test case 1 failed.");

    // Test case 2: Multiple valid prefixes required to form target
    words = {"a", "b", "c"};
    target = "abc";
    expected_result = 3;  // Minimum 3 strings: "a" + "b" + "c"
    assert(solution.minValidStrings(words, target) == expected_result && "Test case 2 failed.");

    // Test case 3: Target cannot be formed
    words = {"abc", "aaaaa", "bcdef"};
    target = "aabcdabc";
    expected_result = 3;  // No possible way to form "abcd" with given words
    assert(solution.minValidStrings(words, target) == expected_result && "Test case 3 failed.");

    // Test case 4: Single word matches the whole target
    words = {"hello", "world", "helloworld"};
    target = "helloworld";
    expected_result = 1;  // "helloworld" directly matches
    assert(solution.minValidStrings(words, target) == expected_result && "Test case 4 failed.");

    // Test case 5: Overlapping prefixes required
    words = {"abababab", "ab"};
    target = "ababaababa";
    expected_result = 2;  // Minimum 2 strings: "abababab" + "ab"
    assert(solution.minValidStrings(words, target) == expected_result && "Test case 5 failed.");

    // Test case 6: Words contain all characters but not in prefix form
    words = {"abcdef"};
    target = "xyz";
    expected_result = -1;  // "xyz" can't be formed using the words as prefixes
    assert(solution.minValidStrings(words, target) == expected_result && "Test case 6 failed.");

    // Test case 7: Prefixes with varying lengths
    words = {"ab", "a", "abc", "bc", "c"};
    target = "abc";
    expected_result = 1;  // "abc" can be matched directly
    assert(solution.minValidStrings(words, target) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 327680; ++i) {
        testSolution(solution);  
    }
    return 0;
}
