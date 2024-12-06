#include <string>
#include <vector>
#include <algorithm>
using namespace std;


auto z_function = [](const string& s) -> vector<int> {
        int n = s.size(), l = 0, r = 0;
        vector<int> z(n, 0);
        for (int i = 1; i < n; ++i) {
            if (i <= r) {
                z[i] = min(r - i + 1, z[i - l]);
            }
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
                ++z[i];
            }
            if (i + z[i] - 1 > r) {
                l = i;
                r = i + z[i] - 1;
            }
        }
        return z;
    };

class Solution {
public:
    int minStartingIndex(string s, string pattern) {
        int n = s.size(), m = pattern.size();
        string pattern2(pattern.rbegin(), pattern.rend());
        string s2(s.rbegin(), s.rend());
        vector<int> z1 = z_function(pattern + s);
        vector<int> z2 = z_function(pattern2 + s2);
        for (int i = 0; i <= n - m; ++i)
            if (z1[m + i] + 1 + z2[n - i] >= m)
                return i;
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
