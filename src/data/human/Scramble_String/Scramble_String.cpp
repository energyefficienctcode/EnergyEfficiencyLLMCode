#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool isScramble(string s1, string s2) {
        if(s1==s2)
            return true;
            
        int len = s1.length();
        int count[26] = {0};
        for(int i=0; i<len; i++)
        {
            count[s1[i]-'a']++;
            count[s2[i]-'a']--;
        }
        
        for(int i=0; i<26; i++)
        {
            if(count[i]!=0)
                return false;
        }
        
        for(int i=1; i<=len-1; i++)
        {
            if( isScramble(s1.substr(0,i), s2.substr(0,i)) && isScramble(s1.substr(i), s2.substr(i)))
                return true;
            if( isScramble(s1.substr(0,i), s2.substr(len-i)) && isScramble(s1.substr(i), s2.substr(0,len-i)))
                return true;
        }
        return false;
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
