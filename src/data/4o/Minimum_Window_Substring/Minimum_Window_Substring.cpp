#include <string>
#include <unordered_map>
#include <climits>
#include <cassert>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        if (t.empty() || s.empty()) return "";

        unordered_map<char, int> tFreq;
        for (char c : t) {
            tFreq[c]++;
        }

        int required = tFreq.size();
        unordered_map<char, int> windowFreq;
        int left = 0, right = 0;
        int formed = 0;
        int minLength = INT_MAX;
        int start = 0;

        while (right < s.length()) {
            char c = s[right];
            windowFreq[c]++;

            if (tFreq.find(c) != tFreq.end() && windowFreq[c] == tFreq[c]) {
                formed++;
            }

            while (left <= right && formed == required) {
                char temp = s[left];

                if (right - left + 1 < minLength) {
                    minLength = right - left + 1;
                    start = left;
                }

                windowFreq[temp]--;
                if (tFreq.find(temp) != tFreq.end() && windowFreq[temp] < tFreq[temp]) {
                    formed--;
                }

                left++;
            }

            right++;
        }

        return minLength == INT_MAX ? "" : s.substr(start, minLength);
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
