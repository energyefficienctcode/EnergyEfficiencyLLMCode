#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <cassert>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        if(t.empty() || s.empty()) return "";
        
        // Frequency of characters in t
        vector<int> target(128, 0);
        for(char c : t) target[c]++;
        
        int required = 0;
        for(int count : target) if(count > 0) required++;
        
        // Sliding window variables
        int left = 0, right = 0;
        int formed = 0;
        vector<int> window(128, 0);
        
        // Result variables: window length and left index
        int minLen = INT32_MAX;
        int minLeft = 0;
        
        while(right < s.size()){
            char c = s[right];
            window[c]++;
            
            // If current character's frequency matches the target
            if(target[c] > 0 && window[c] == target[c]){
                formed++;
            }
            
            // Try to contract the window until it's no longer valid
            while(left <= right && formed == required){
                c = s[left];
                
                // Update minimum window
                if(right - left + 1 < minLen){
                    minLen = right - left + 1;
                    minLeft = left;
                }
                
                // Remove the leftmost character from the window
                window[c]--;
                if(target[c] > 0 && window[c] < target[c]){
                    formed--;
                }
                
                left++;
            }
            
            right++;
        }
        
        return minLen == INT32_MAX ? "" : s.substr(minLeft, minLen);
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
    //assert(solution.minWindow(s, t) == expected_result && "Test case 7 failed.");
}


int main() {
    Solution solution;
    for (int i = 0; i < 3342170; ++i) {
        testSolution(solution);  
    }
    return 0;
}
