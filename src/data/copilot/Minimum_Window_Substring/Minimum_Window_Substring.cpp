#include <string>
#include <unordered_map>
#include <cassert>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        if (t.size() > s.size()) return "";

        unordered_map<char, int> tFreq, windowFreq;
        for (char c : t) tFreq[c]++;

        int required = tFreq.size();
        int formed = 0;
        int left = 0, right = 0;
        int minLen = INT_MAX, minLeft = 0;

        while (right < s.size()) {
            char c = s[right];
            windowFreq[c]++;
            if (tFreq.count(c) && windowFreq[c] == tFreq[c]) {
                formed++;
            }

            while (left <= right && formed == required) {
                c = s[left];
                if (right - left + 1 < minLen) {
                    minLen = right - left + 1;
                    minLeft = left;
                }

                windowFreq[c]--;
                if (tFreq.count(c) && windowFreq[c] < tFreq[c]) {
                    formed--;
                }
                left++;
            }
            right++;
        }

        return minLen == INT_MAX ? "" : s.substr(minLeft, minLen);
    }
};

//  Test cases for the C++ solution
#include <string>

// Test cases for the C++ solution
void testSolution(Solution& solution) {
    // Test case 1: Small substring found at the beginning
    std::string s = "ADOBECODEBANC";
    std::string t = "ABC";
    std::string expected_result = "BANC";
    assert(solution.minWindow(s, t) == expected_result && "Test case 1 failed.");

    // Test case 2: t is the same as s, so the entire string is the minimum window
    s = "a";
    t = "a";
    expected_result = "a";
    assert(solution.minWindow(s, t) == expected_result && "Test case 2 failed.");

    // Test case 3: No valid substring found
    s = "a";
    t = "aa";
    expected_result = "";
    assert(solution.minWindow(s, t) == expected_result && "Test case 3 failed.");

    // Test case 4: Multiple minimum windows, return the first found
    s = "aabdec";
    t = "abc";
    expected_result = "abdec";
    assert(solution.minWindow(s, t) == expected_result && "Test case 4 failed.");

    // Test case 5: Characters of t spread throughout s
    s = "aaflslflsldkalskaaa";
    t = "aks";
    expected_result = "ska";
    assert(solution.minWindow(s, t) == expected_result && "Test case 5 failed.");

    // Test case 6: t is at the end of s
    s = "qwertyabcd";
    t = "abcd";
    expected_result = "abcd";
    assert(solution.minWindow(s, t) == expected_result && "Test case 6 failed.");

    // Test case 7: Multiple occurrences of characters in t
    s = "aaabbbccc";
    t = "abc";
    expected_result = "abc";
    assert(solution.minWindow(s, t) == expected_result && "Test case 7 failed.");
}


int main() {
    Solution solution;
    for (int i = 0; i < 3342170; ++i) {
        testSolution(solution);  
    }
    return 0;
}
