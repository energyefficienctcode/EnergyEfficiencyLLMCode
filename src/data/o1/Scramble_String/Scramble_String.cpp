#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool isScramble(string s1, string s2) {
        if(s1.length() != s2.length()) return false;
        int n = s1.length();
        if(n == 0) return true;
        if(s1 == s2) return true;
        
        // Check if both strings have the same character counts
        string sorted_s1 = s1;
        string sorted_s2 = s2;
        sort(sorted_s1.begin(), sorted_s1.end());
        sort(sorted_s2.begin(), sorted_s2.end());
        if(sorted_s1 != sorted_s2) return false;
        
        string key = s1 + " " + s2;
        if(memo.find(key) != memo.end()) return memo[key];
        
        for(int i = 1; i < n; ++i){
            // Without swapping
            string s1_left = s1.substr(0, i);
            string s1_right = s1.substr(i);
            string s2_left = s2.substr(0, i);
            string s2_right = s2.substr(i);
            
            if(isScramble(s1_left, s2_left) && isScramble(s1_right, s2_right)){
                memo[key] = true;
                return true;
            }
            
            // With swapping
            string s2_left_swapped = s2.substr(n - i, i);
            string s2_right_swapped = s2.substr(0, n - i);
            
            if(isScramble(s1_left, s2_left_swapped) && isScramble(s1_right, s2_right_swapped)){
                memo[key] = true;
                return true;
            }
        }
        
        memo[key] = false;
        return false;
    }
    
private:
    unordered_map<string, bool> memo;
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
