#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size();
        vector<vector<long>> dp(m + 1, vector<long>(n + 1, 0));

        for (int i = 0; i <= m; ++i) {
            dp[i][0] = 1;
        }

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }

        return dp[m][n];
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Simple case with one subsequence
    std::string s = "rabbbit";
    std::string t = "rabbit";
    int expected_result = 3;
    assert(solution.numDistinct(s, t) == expected_result && "Test case 1 failed.");

    // Test case 2: No subsequence matches
    s = "abcdef";
    t = "gh";
    expected_result = 0;
    assert(solution.numDistinct(s, t) == expected_result && "Test case 2 failed.");

    // Test case 3: Identical strings (only one way to match)
    s = "abc";
    t = "abc";
    expected_result = 1;
    assert(solution.numDistinct(s, t) == expected_result && "Test case 3 failed.");

    // Test case 4: Subsequence with repeated characters
    s = "babgbag";
    t = "bag";
    expected_result = 5;
    assert(solution.numDistinct(s, t) == expected_result && "Test case 4 failed.");

    // Test case 5: t is longer than s (no possible subsequence)
    s = "abc";
    t = "abcd";
    expected_result = 0;
    assert(solution.numDistinct(s, t) == expected_result && "Test case 5 failed.");

    // Test case 6: Empty t (one way to match by deleting all characters)
    s = "anything";
    t = "";
    expected_result = 1;
    assert(solution.numDistinct(s, t) == expected_result && "Test case 6 failed.");

    // Test case 7: Large input with multiple subsequences
    s = "aaaaa";
    t = "aa";
    expected_result = 10;
    assert(solution.numDistinct(s, t) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 2621440; ++i) {
        testSolution(solution);  
    }
    return 0;
}
