#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    bool isScramble(string s1, string s2) {
        int n = s1.length();
        if (n != s2.length()) return false;
        if (s1 == s2) return true;

        vector<vector<vector<bool>>> dp(n, vector<vector<bool>>(n, vector<bool>(n + 1, false)));

        // Initialize the base case: substrings of length 1
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (s1[i] == s2[j]) {
                    dp[i][j][1] = true;
                }
            }
        }

        // Build the solution for substrings of length k > 1
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                for (int j = 0; j <= n - len; j++) {
                    for (int k = 1; k < len; k++) {
                        if ((dp[i][j][k] && dp[i + k][j + k][len - k]) ||
                            (dp[i][j + len - k][k] && dp[i + k][j][len - k])) {
                            dp[i][j][len] = true;
                            break;
                        }
                    }
                }
            }
        }

        return dp[0][0][n];
    }
};


//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Simple scrambled string
    std::string s1 = "great";
    std::string s2 = "rgeat";
    bool expected_result = true;
    assert(solution.isScramble(s1, s2) == expected_result && "Test case 1 failed.");

    // Test case 2: Not a scrambled string
    s1 = "abcde";
    s2 = "caebd";
    expected_result = false;
    assert(solution.isScramble(s1, s2) == expected_result && "Test case 2 failed.");

    // Test case 3: Identical strings (trivial scramble)
    s1 = "a";
    s2 = "a";
    expected_result = true;
    assert(solution.isScramble(s1, s2) == expected_result && "Test case 3 failed.");

    // Test case 4: Scrambled with multiple swaps
    s1 = "abc";
    s2 = "bca";
    expected_result = true;
    assert(solution.isScramble(s1, s2) == expected_result && "Test case 4 failed.");

    // Test case 5: Strings of length 1 that are different
    s1 = "a";
    s2 = "b";
    expected_result = false;
    assert(solution.isScramble(s1, s2) == expected_result && "Test case 5 failed.");

    // Test case 6: Longer string with multiple possible scrambles
    s1 = "abcdefghijkl";
    s2 = "efghijklabcd";
    expected_result = true;
    assert(solution.isScramble(s1, s2) == expected_result && "Test case 6 failed.");

    // Test case 7: Strings that look scrambled but aren't due to character counts
    s1 = "aabbcc";
    s2 = "abccba";
    expected_result = true;
    assert(solution.isScramble(s1, s2) == expected_result && "Test case 7 failed.");
}


int main() {
    Solution solution;
    for (int i = 0; i < 131072; ++i) {
        testSolution(solution);  
    }
    return 0;
}
