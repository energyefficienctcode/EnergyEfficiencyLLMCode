#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        vector<vector<bool>> dp(s.size() + 1, vector(p.size() + 1, false));
        dp[0][0] = true;
        for (int j = 0; j < p.size() && p[j] == '*'; ++j) {
            dp[0][j + 1] = true;
        }
        
        for (int i = 1; i <= s.size(); ++i) {
            for (int j = 1; j <= p.size(); ++j) {
                if (p[j - 1] == '*') {
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                } else {
                    dp[i][j] = (s[i - 1] == p[j - 1] || p[j - 1] == '?') && dp[i - 1][j - 1];
                }
            }
        }

        return dp[s.size()][p.size()];
    }
};

//  Test cases for the C++ solution
#include <cassert>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Simple match with exact pattern
    std::string s = "abcd";
    std::string p = "abcd";
    bool expected_result = true;
    assert(solution.isMatch(s, p) == expected_result && "Test case 1 failed.");

    // Test case 2: Pattern with '?' matching a single character
    s = "abcd";
    p = "a?cd";
    expected_result = true;
    assert(solution.isMatch(s, p) == expected_result && "Test case 2 failed.");

    // Test case 3: Pattern with '*' matching any sequence of characters
    s = "abcd";
    p = "a*d";
    expected_result = true;
    assert(solution.isMatch(s, p) == expected_result && "Test case 3 failed.");

    // Test case 4: Pattern with '*' matching an empty sequence
    s = "abcd";
    p = "a*cd";
    expected_result = true;
    assert(solution.isMatch(s, p) == expected_result && "Test case 4 failed.");

    // Test case 5: No match due to extra characters in pattern
    s = "abc";
    p = "abcd";
    expected_result = false;
    assert(solution.isMatch(s, p) == expected_result && "Test case 5 failed.");

    // Test case 6: Multiple '*' characters and '?' in the pattern
    s = "abefcdgiescdfimde";
    p = "ab*cd?i*de";
    expected_result = true;
    assert(solution.isMatch(s, p) == expected_result && "Test case 6 failed.");

    // Test case 7: Empty pattern matching an empty string
    s = "";
    p = "";
    expected_result = true;
    assert(solution.isMatch(s, p) == expected_result && "Test case 7 failed.");

    // Test case 8: Pattern with only '*' should match any string
    s = "anything";
    p = "*";
    expected_result = true;
    assert(solution.isMatch(s, p) == expected_result && "Test case 8 failed.");
}


int main() {
    Solution solution;
    for (int i = 0; i < 327680; ++i) {
        testSolution(solution);  
    }
    return 0;
}
