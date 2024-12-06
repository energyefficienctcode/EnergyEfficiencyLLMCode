#include <string>
using namespace std;

class Solution {
public:
    int minStartingIndex(string s, string pattern) {
        int n = s.size(), m = pattern.size();
        if (m > n) return -1;

        for (int i = 0; i <= n - m; ++i) {
            int diffCount = 0;
            for (int j = 0; j < m; ++j) {
                if (s[i + j] != pattern[j]) {
                    diffCount++;
                    if (diffCount > 1) break;
                }
            }
            if (diffCount <= 1) return i;
        }

        return -1;
    }
};

//  Test cases for the C++ solution
#include <cassert>

void testSolution(Solution& solution) {
    // Test case 1: Exact match for pattern
    std::string s = "abcdef";
    std::string pattern = "cde";
    int expected_result = 2;  // "cde" matches exactly at index 2
    assert(solution.minStartingIndex(s, pattern) == expected_result && "Test case 1 failed.");

    // Test case 2: One character difference with pattern
    s = "abcdef";
    pattern = "cdf";
    expected_result = 2;  // Change 'e' to 'f' to match "cdf" starting at index 2
    assert(solution.minStartingIndex(s, pattern) == expected_result && "Test case 2 failed.");

    // Test case 3: No almost equal substring exists
    s = "abcdef";
    pattern = "xyz";
    expected_result = -1;  // No single character change can make "xyz" in any substring of "abcdef"
    assert(solution.minStartingIndex(s, pattern) == expected_result && "Test case 3 failed.");

    // Test case 4: Pattern is the last part of s
    s = "abcdefgh";
    pattern = "fgh";
    expected_result = 5;  // "fgh" matches exactly at index 5
    assert(solution.minStartingIndex(s, pattern) == expected_result && "Test case 4 failed.");

    // Test case 5: Pattern and substring with differing middle character
    s = "abcdefg";
    pattern = "bcdffg";
    expected_result = 1;  // Change 'a' at index 3 to 'b' to match "abc" starting at index 2
    assert(solution.minStartingIndex(s, pattern) == expected_result && "Test case 5 failed.");

    // Test case 6: Almost equal substring at start of s
    s = "xyzabc";
    pattern = "xya";
    expected_result = 0;  // Change 'z' to 'a' at index 2 to match "xya" starting at index 0
    assert(solution.minStartingIndex(s, pattern) == expected_result && "Test case 6 failed.");

    // Test case 7: Multiple valid substrings, select the first one
    s = "abababab";
    pattern = "aba";
    expected_result = 0;  // First occurrence is at index 0
    assert(solution.minStartingIndex(s, pattern) == expected_result && "Test case 7 failed.");
}

int main() {
    Solution solution;
    for (int i = 0; i < 655360; ++i) {
        testSolution(solution);  
    }
    return 0;
}
